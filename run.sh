bison -d parser.yy &&
flex scanner.ll &&
g++ lex.yy.c parser.tab.cc printVisitorMain.cpp printVisitor.cpp -o prettify
