%{
	// This stuff is copied verbatim into the cpp program
	#include <iostream>
	using namespace std;
	extern int yylex();	
%}

%%
// Regex and action written in {}
[\ \t] //eat up whitespace
[;] {
	cout<<"SEMICOLON"<<endl;
}
%%

// Always generates a c program called lex.yy.c
// Compile it with g++ lex.yy.c -lfl -o scan

//yyin : a global variable in the lex code
// by default yyin is set to stdin
// to set it to a file declate a file pointer and the set yyin = file