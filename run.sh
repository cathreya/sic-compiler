if [ "$1" = 'prettify' ]; then
	bison -d parser.yy &&
	flex scanner.ll &&
	g++ lex.yy.c parser.tab.cc printVisitorMain.cpp -o prettify
elif [ "$1" = 'interpret' ]; then
	bison -d parser.yy &&
	flex scanner.ll &&
	g++ lex.yy.c parser.tab.cc interpretVisitor.cpp -o interpret	
fi