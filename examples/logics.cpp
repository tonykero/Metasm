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

void display_stack(const std::stack<int>& _stack);

using namespace std;

int main()
{
    meta::Engine engine;
    auto xor_fakejit = [&engine]( int _arg1, int _arg2 ) -> void
    {

        std::string pushARG1 = "PUSH " + to_string(_arg1) + "\n",
                    pushARG2 = "PUSH " + to_string(_arg2) + "\n";
        
        std::string script_xor =
                            pushARG2 +
                            pushARG1 +
                            "NAND\n" +
                            pushARG1 +
                            "NAND\n" +
                            pushARG2 +
                            pushARG1 +
                            "NAND\n" +
                            pushARG2 +
                            "NAND\n"
                            "NAND\n";
                            // 16 ^ 45
        engine.loadScript(script_xor);
        engine.run();
    };

    xor_fakejit(16, 45); //should be 61
    xor_fakejit(61, 45); // should be 16
    xor_fakejit(14352, 4635); // should be 10763


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