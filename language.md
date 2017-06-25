# **Language Specifications**

Instructions    | Usage     | Description
---             | ---       | ---
**PUSH**        | PUSH Imm  | Puts a value on top of the stack 
**POP**         | POP       | Removes a value from the top of the stack 
**SWAP**        | SWAP      | Swap the 2 topmost values 
**DUP**         | DUP       | Puts the topmost value (DUPlicates)
**ADD**         | ADD       | Adds the 2 topmost values, pops them, pushes the result 
**SUB**         | SUB       | Substracts the 2 topmost values, pops them, pushes the result
**MUL**         | MUL       | Multiplies the 2 topmost values, pops them, pushes the result
**DIV**         | DIV       | Divides the 2 topmost values, pops them, pushes the result
**XOR**         | XOR       | Performs a binary XOR on the 2 topmost values, pops them, pushes the result
**OR**          | OR        | Performs a binary OR on the 2 topmost values, pops them, pushes the result
**AND**         | AND       | Performs a binary AND on the 2 topmost values, pops them, pushes the result
**NOT**         | NOT       | Performs a binary NOT on the topmost value
**SHR**         | SHR       | Performs a binary SHIFT to the right on the topmost value
**SHL**         | SHL       | Performs a binary SHIFT to the left on the topmost value 
**LBL**         | LBL Lbl   | Declares a label
**JMP**         | JMP Lbl   | Jump unconditionally to label "Lbl"
**JE**          | JE Lbl    | Jump to label "Lbl" if the 2 topmost values are equal
**JNE**         | JNE Lbl   | Jump to label "Lbl" if the 2 topmost values are not equal
**JGE**         | JGE Lbl   | Jump to label "Lbl" if the topmost value is greater than the second topmost value
**JLE**         | JLE Lbl   | Jump to label "Lbl" if the topmost value is lower than the second topmost value