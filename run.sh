bison -d parser.y
flex scanner.l
g++ lex.yy.c parser.tab.c -lfl -o parse
