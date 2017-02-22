#include <Metasm.hpp>
#include <iostream>

#ifdef __MINGW32__
    #include <sstream>

    std::string to_string(int i)
    {
        std::stringstream ss;
        ss << i;
        return ss.str();
    }
#endif

void display_stack(const std::stack<int>&);

using namespace std;

int main()
{
    meta::Engine engine;

    auto square_root = [&engine](int _arg1) -> void
    {
        int r1 = _arg1/2;
        std::string pushARG1    = "PUSH " + to_string(_arg1)+ "\n",
                    pushR1      = "PUSH " + to_string(r1)   + "\n";

        std::string script = 
                        pushR1 +
                        "DUP\n" +
                        pushARG1 +
                        "DIV\n" +
                        pushR1 +
                        "LBL L1\n"
                        "ADD\n"
                        "PUSH 1\n"
                        "SHF\n"
                        "CMP\n"
                        "JE EXIT\n"
                        "SWAP\n"
                        "POP\n"
                        "DUP\n"
                        "DUP\n" +
                        pushARG1 +
                        "DIV\n"
                        "JNE L1\n"
                        "LBL EXIT\n"
                        "POP\n"; 

        engine.loadScript(script);
        engine.run();
    };

    square_root(16); // should be 4
    square_root(29888089); //should be 5467

    std::cout << "stack contains: " << std::endl;
    display_stack(engine.getStack());
}

void display_stack(const std::stack<int>& _stack)
{
    std::stack<int> stack = _stack;

    while(stack.size() != 0)
    {
        std::cout << stack.top() << std::endl;
        stack.pop();
    }
}