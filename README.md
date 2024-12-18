> This complete implementation provides a **basic structure** for a **simple assembly language compiler**. The compiler includes tokenization, parsing, AST construction, and a placeholder for code generation. The tree-view file's components outlines the relationships between the various components of the compiler, making it easier to understand the structure and flow of the code. This basic learning example can be further expanded with additional features, optimizations, and error handling to create a more robust compiler. Have fun and dont stop learning.


**Features**

- **Tokenization**: Converts input assembly code into tokens.
- **Parsing**: Constructs an abstract syntax tree (AST) from the tokens.
- **Code Generation**: Placeholder for generating machine code or intermediate representation.
- **Logging**: Logs errors and messages to a log file.
- **Interactive Command Line Interface**: Allows users to input assembly code and see the results in real-time.

**Supported Instructions**

- `MOV dest, src`: Move the value from `src` to `dest`.
- `ADD dest, src`: Add the value of `src` to `dest`.
- `SUB dest, src`: Subtract the value of `src` from `dest`.
- `JMP label`: Jump to the specified label.
- Labels: Defined by a name followed by a colon (e.g., `label:`).
- Registers: Identified by names starting with 'R' (e.g., `R1`, `R2`).
- Numbers: Integer values (including negative numbers).
