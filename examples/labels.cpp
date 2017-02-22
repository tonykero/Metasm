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

    auto equals = [&engine](int _arg1, int _arg2) -> void
    {
        std::string pushARG1 = "PUSH " + to_string(_arg1) + "\n",
                    pushARG2 = "PUSH " + to_string(_arg2) + "\n";

        std::string script =
                        pushARG1 +
                        pushARG2 +
                        "CMP\n" +
                        "JE EQUAL\n"
                        "PUSH 0\n"
                        "JMP EXIT\n"
                        "LBL EQUAL\n"
                        "PUSH 1\n"
                        "LBL EXIT\n";

        engine.loadScript(script);
        engine.run();
    };

    equals(4, 3);   // should be 0
    equals(23, 23); // should be 1
    
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