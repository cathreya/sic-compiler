%{
	// rendered as is
	#include <iostream>
	using namespace std;

	// extern is used to declare variables that have been defined in some other file
	// 
	extern int yylex();
	extern int yyparse();
	extern FILE *yyin;
	void yyerror(char *s);

%}

// tokens are the return types of flex. the input comes from flex.
%token NAME
%token EMAIL
%token ROLL
%token BRACE

//specify the grammar inside this
// be careful as the grammar might end up in an infinite loop

// bison -d parser.y 
// -d generates a header file to use stuff from the bison file in the flex file
// flex scanner.l
// g++ -std=c++11 parser.tab.c lex.yy.c -lfl -o parse
// cat input.txt | ./parse

%%
	Goal: BRACE NAME EMAIL ROLL BRACE '\n'
		| Goal BRACE NAME EMAIL ROLL BRACE '\n'
		;
%%

//yyerror is a function that is predefined in bison/flex
// you can override it to make it print out the error and exit

void yyerror(char *s){
	cerr<<s<<endl;
}

//main is defined inside the bison file.
main(int argc, char **argv){
	// this calls yylex
	yyparse();
	printf("done");
}