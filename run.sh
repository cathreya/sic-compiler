if [ "$1" = 'prettify' ]; then
	bison -d parser.yy &&
	flex scanner.ll &&
	g++ lex.yy.c parser.tab.cc printVisitorMain.cpp -o prettify
elif [ "$1" = 'interpret' ]; then
	bison -d parser.yy &&
	flex scanner.ll &&
	g++ lex.yy.c parser.tab.cc interpretVisitor.cpp -o interpret	
elif [ "$1" = 'codegen' ]; then
	bison -d parser.yy &&
	flex scanner.ll &&
	clang++-9 -O3 lex.yy.c parser.tab.cc codegenVisitor.cpp `llvm-config --cxxflags --ldflags --system-libs --libs core` -o codegen
fi