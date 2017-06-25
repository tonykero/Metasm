# Metasm

[![license](https://img.shields.io/github/license/tonykero/Metasm.svg?style=flat-square)](https://github.com/tonykero/Metasm/blob/master/LICENSE)

Metasm is a just-in-time compiler written in C++, it fits in 20 instructions.

# Overview

This project is firstly made to be used with [Moe](https://github.com/tonykero/Moe),
but since i'm writing Moe and Metasm in a generic way, i found legitimate to create a repository for each.


```cpp
#include <Metasm.hpp>
#include <iostream>

int main()
{
    meta::Engine engine(5);

    std::string script_test6 =
                        "PUSH 5\n"  // 5
                        "PUSH 3\n"  // 5 3
                        "MUL\n"     // 15
                        "PUSH 4\n"  // 15 4
                        "MUL\n"     // 60
                        "PUSH 10\n" // 60 10
                        "SWAP\n"    // 10 60
                        "DIV\n";    // 6
                        // 6

    
    engine.load_script( script_test6 );
    
    engine.compile();
    std::cout << engine.execute() << std::endl;
}
```

## Building

Metasm uses CMake, and requires libgccjit installed

Options         | Description                   | Default Value |
--------------- | ----------------------------- | ------------- |
BUILD_SHARED    | builds Metasm as SHARED if ON | OFF           |
BUILD_EXAMPLES  | build examples                | ON            |
DEBUG           | Enable debugging symbols      | OFF           |

may supports(untested consistently):
* GCC 4.9+

```
apt-get install libgccjit-6-dev
git clone https://github.com/tonykero/Metasm.git
cd Metasm
mkdir build && cd build
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:PATH WHERE libgccjit.so IS LOCATED
export LIBRARY_PATH=${LIBRARY_PATH}:PATH WHERE libgccjit.so IS LOCATED
export PATH=${PATH}:PATH WHERE libgccjit.so IS LOCATED
cmake .. && cmake --build .
```

The path i used was /usr/lib/gcc/x86_64-linux-gnu/6



## Examples

[/examples](https://github.com/tonykero/Metasm/tree/master/examples)

## Language Details

Described [here](https://github.com/tonykero/Metasm/tree/master/language.md)

## License

[The MIT License](https://opensource.org/licenses/MIT)
