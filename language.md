# **Language Specifications**

# Memory
Instructions    | Usage     | Description
:---            | :---      | :---
**PUSH**        | PUSH Imm  | `Puts a value on top of the stack` 
**POP**         | POP       | `Removes a value from the top of the stack`
**LOAD**        | LOAD REG  | `push REG`
**STORE**       | STORE REG | `pop and stores in REG`
**SWAP**        | SWAP      | `pop a, pop b, push a, push b` 
**DUP**         | DUP       | `pop a, push a, push a`

# Arithmetic
Instructions    | Usage     | Description
:---            | :---      | :---
**ADD**         | ADD       | `pop a, pop b, push a + b `
**SUB**         | SUB       | `pop a, pop b, push a - b`
**MUL**         | MUL       | `pop a, pop b, push a * b`
**DIV**         | DIV       | `pop a, pop b, push a / b`
**MOD**         | MOD       | `pop a, pop b, push a % b`

# Logical
Instructions    | Usage     | Description
:---            | :---      | :---
**XOR**         | XOR       | `pop a, pop b, push a ^ b`
**OR**          | OR        | `pop a, pop b, push a | b`
**AND**         | AND       | `pop a, pop b, push a & b`
**NOT**         | NOT       | `pop a, push ~a `
**SHR**         | SHR       | `pop a, pop b, push a >> b`
**SHL**         | SHL       | `pop a, pop b, push a << b`

# Jumps
Instructions    | Usage     | Description
:---            | :---      | :---
**LBL**         | LBL Lbl   | `Declares a label`
**JMP**         | JMP Lbl   | `Jump unconditionally to label "Lbl"`
**JE**          | JE Lbl    | `Jump to label "Lbl" if the 2 topmost values are equal`
**JNE**         | JNE Lbl   | `Jump to label "Lbl" if the 2 topmost values are not equal`
**JGE**         | JGE Lbl   | `Jump to label "Lbl" if the topmost value is greater than the second topmost value`
**JLE**         | JLE Lbl   | `Jump to label "Lbl" if the topmost value is lower than the second topmost value`
**RET**         | RET       | `Return topmost value`

# IO
Instructions    | Usage     | Description
:---            | :---      | :---
**PRINT**       | PRINT     | `pop a, printf("topmost value:%i", a)`