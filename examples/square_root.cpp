#include <Metasm.hpp>
#include <iostream>

using namespace std;

int main()
{
    meta::Engine engine(4);

     //square_root
    std::string script =
                    "PUSH 2\n"  // 2
                    "PUSH 8\n"  // 2 8
                    "PUSH 16\n" // 2 8 16
                    "PUSH 8\n"  // 2 8 16 8
                    "SWAP\n"    // 2 8 8 16
                    "LBL L1\n"  //          // 2 5 5 16
                    "DIV\n"     // 2 8 2    // 2 5 3
                    "ADD\n"     // 2 10     // 2 8
                    "DIV\n"     // 5        // 4
                    "DUP\n"     // 5 5      // 4 4
                    "DUP\n"     // 5 5 5    // 4 4 4
                    "MUL\n"     // 5 25     // 4 16
                    "PUSH 16\n" // 5 25 16  // 4 16 16
                    "JE EXIT\n" //          //
                    "POP\n"     // 5 25
                    "POP\n"     // 5
                    "PUSH 2\n"  // 5 2
                    "SWAP\n"    // 2 5
                    "DUP\n"     // 2 5 5
                    "PUSH 16\n" // 2 5 5 16
                    "JMP L1\n"  
                    "LBL EXIT\n"            // 4 16 16
                    "POP\n"                 // 4 16
                    "POP\n"                 // 4
                    "PRINT\n";              // but outputs 5 ¯\_(ツ)_/¯

    engine.load_script(script);

    std::function<int(void)> function = engine.compile();
    std::cout << function() << std::endl;
    engine.compile( "sqrt", true );
}