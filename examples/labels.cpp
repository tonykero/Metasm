#include <Metasm.hpp>
#include <iostream>

using namespace std;

int main()
{
    meta::Engine engine(4);
    
    std::string script =
                    "PUSH 23\n"
                    "PUSH 23\n"
                    "JE EQUAL\n"
                    "PUSH 0\n"
                    "JMP EXIT\n"
                    "LBL EQUAL\n"
                    "PUSH 1\n"
                    "LBL EXIT\n"
                    "PRINT\n";

    engine.load_script(script);

    std::function<int(void)> function = engine.compile();
    std::cout << function() << std::endl;
    engine.compile("lbl", true);
}