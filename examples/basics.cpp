#include <Metasm.hpp>
#include <iostream>

void display_stack(const std::stack<int>&);

int main()
{
    meta::Engine engine;

    std::string script_test6 =
                        "PUSH 5\n"
                        "PUSH 3\n"
                        "MUL\n"
                        "PUSH 4\n"
                        "MUL\n"
                        "PUSH 10\n"
                        "SWAP\n"
                        "DIV\n";
                        // 6

    
    engine.loadScript( script_test6 );
    
    engine.run();

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