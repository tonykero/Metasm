# Metasm

[![license](https://img.shields.io/github/license/tonykero/Metasm.svg?style=flat-square)](https://github.com/tonykero/Metasm/blob/master/LICENSE)

Metasm is a very basic interpreted language, indeed, it fits in 16 instructions.

Though it is also an interpreter and a library, written in C++.

# Overview

This project is firstly made to be used with [Moe](https://github.com/tonykero/Moe),
but as i write it in an almost generic way i found legitimate to create a repository for it


There is only 1 class for the moment, and 2 main functions to remember

```cpp
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
```

The only class is Engine, and the 2 functions are loadScript() & run()

the internal container used to store immediates values and results, is indeed a `std::stack<int>`, for now it only supports ints

## Building

Metasm uses CMake

Options         | Description                   | Default Value |
--------------- | ----------------------------- | ------------- |
BUILD_SHARED    | builds Moe as SHARED if ON    | OFF           |
BUILD_EXAMPLES  | build examples                | ON            |
DEBUG           | Enable debugging symbols      | OFF           |

may supports:
* Clang 3.4+
* GCC 4.9+
* untested with MVC (19.0), should get minor errors

```
git clone https://github.com/tonykero/Metasm.git
cd Metasm
mkdir build && cd build && cmake .. && cmake --build .
```

## Examples

[/examples](https://github.com/tonykero/Metasm/tree/master/examples)

## Language Details

Described [here](https://github.com/tonykero/Metasm/tree/master/language.md)

## License

[The MIT License](https://opensource.org/licenses/MIT)