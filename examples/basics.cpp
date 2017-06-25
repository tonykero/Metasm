#include <Metasm.hpp>
#include <iostream>

int main()
{
    meta::Engine engine(5);

    std::string script_test6 =
                        "PUSH 5\n"
                        "PUSH 3\n"
                        "MUL\n"     // 15
                        "PUSH 4\n"  // 15 4
                        "MUL\n"     // 60
                        "PUSH 10\n" // 60 10
                        "SWAP\n"    // 10 60
                        "DIV\n";    // 6
                        // 6*/

    
    engine.load_script( script_test6 );
    
    engine.compile();
    std::cout << engine.execute() << std::endl;
}

/*
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/usr/lib/gcc/x86_64-linux-gnu/6
export LIBRARY_PATH=${LIBRARY_PATH}:/usr/lib/gcc/x86_64-linux-gnu/6
export PATH=${PATH}:/usr/lib/gcc/x86_64-linux-gnu/6
*/