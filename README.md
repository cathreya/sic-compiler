#sic-compiler

*sic*, short for simplified C, is a language designed for the course project of Compilers taken during Monsoon 2019. Its context free grammar can be found in the manual. 

This repo contains a lexical analyzer and parser, written using Flex and Bison. These were used to construct an abstract syntax tree using the visitor design pattern. Contains a visitor that formats obfuscated source code, one that interprets the source code, and one that generates LLVM IR(ongoing).


### To Run
#### Requirements
- llvm 9
- flex
- bison

#### Prettify Visitor
```
./run.sh prettify
./prettify <source code>
```

#### Interpretor Visitor
```
./run.sh interpret
./interpret <source code>
```

#### LLVM IR code generator Visitor
```
./run.sh codegen
./runllvm.sh <source code>
```

### Known Issues
- Codegen is not fully tested, arrays are not supported

