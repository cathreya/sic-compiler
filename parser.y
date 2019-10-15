%{
	#include <stdio.h>
	#include <iostream>
	using namespace std;

	// stuff from flex that bison needs to know about:
	extern int yylex();
	extern int yyparse();
	extern FILE *yyin;
	void yyerror(char *s);
	int production = 1;
%}

%union {
	int   ival;
	float fval;
	char  sval[100];
}

%token  <ival> DIGIT 
%token  <sval> IMPORT
%token  <sval> STRINGLIT
%token  <sval> STMT_SEP
%token  <sval> LIST_SEP
%token  <sval> TYPE
%token  <sval> NAME
%token  <sval> ASSIGN
%token  <sval> FLOATV
%token  <sval> INTV
%token  <sval> BOOLLIT
%token  <sval> CHARV
%token  <sval> VOIDV
%token  <sval> OPENPAREN
%token  <sval> CLOSEPAREN
%token  <sval> OPENBRACE
%token  <sval> CLOSEBRACE


%%
start : imports program { 
	cout << "Parse successful!" << endl; 
}
| program { 
		cout << "Parse successful!" << endl;
}

imports : IMPORT STRINGLIT STMT_SEP ;
| imports IMPORT STRINGLIT STMT_SEP ;

prog_element : declaration STMT_SEP ;
| function_definition ;

program : prog_element program ;
| /*empty*/ ;

declaration : TYPE NAME ASSIGN STRINGLIT ;
| TYPE NAME ASSIGN FLOATV  ;
| TYPE NAME ASSIGN INTV  ;
| TYPE NAME ASSIGN BOOLLIT  ;
| TYPE NAME ASSIGN CHARV  ;
| TYPE NAME ASSIGN NAME  ;

function_definition : TYPE NAME OPENPAREN parameters CLOSEPAREN statement_block ;
| TYPE NAME OPENPAREN CLOSEPAREN statement_block ;
| VOIDV NAME OPENPAREN CLOSEPAREN statement_block ;
| VOIDV NAME OPENPAREN parameters CLOSEPAREN statement_block ;

parameters : TYPE NAME ;
| parameters LIST_SEP TYPE NAME ;

statement_block : OPENBRACE statement_list CLOSEBRACE ;

statement_list : statement STMT_SEP ;
| statement_list statement STMT_SEP ;

%%

void yyerror(char *s)
{
				fprintf(stderr, "error: %s\n", s);
}


main(int argc, char **argv)
{
				yyparse();
				printf("Parsing Over\n");
}



