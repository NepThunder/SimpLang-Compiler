# SimpLang-Compiler

clone the repo:

```
git clone https://github.com/NepThunder/SimpLang-Compiler.git
```

Get into the Directory:

```
cd SimpLang-Compiler
```

Run the command:

```
g++ lexer.cpp parser.cpp codegen.cpp main.cpp -o Compiler
```

Run the compiler:

For Linux user:

```
./Compiler.out ./input.txt
```

For Windows user:

```
./Compiler.exe ./input.txt
```

The output.asm text file is the generated assembly language code.

## Design & architecture of Compiler

Working flowchart of the Compiler-

![image](https://github.com/NepThunder/assets/blob/main/1.png)

AST diagram-

![Parser and AST](https://github.com/NepThunder/assets/blob/main/tree.png)

Input code-

![Input Code](https://github.com/NepThunder/assets/blob/main/code.png)

Generated Assembly Code-

![Assembly Code](https://github.com/NepThunder/assets/blob/main/assembly.png)
