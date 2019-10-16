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
%token  <fval> FLOATV
%token  <ival> INTV
%token  <sval> BOOLLIT
%token  <sval> CHARV
%token  <sval> VOIDV
%token  <sval> OPENPAREN
%token  <sval> CLOSEPAREN
%token  <sval> OPENBRACE
%token  <sval> CLOSEBRACE
%token  <sval> OPENSQUARE
%token  <sval> CLOSESQUARE
%token  <sval> BREAK
%token  <sval> CONTINUE
%token  <sval> RETURN
%token  <sval> IF
%token  <sval> ELSE
%token  <sval> FOR
%token  <sval> WHILE
%token  <sval> OR
%token  <sval> AND
%token  <sval> EQ
%token  <sval> REL
%token  <sval> ADD
%token  <sval> MUL
%token  <sval> UNARY_OP



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

statement : declaration ;
| assignment_statement ;
| function_call ;
| BREAK ;
| CONTINUE ;
| RETURN ;
| if_block ;
| while_block ;
| for_block ;

assignment_statement : NAME ASSIGN texp ;
| NAME OPENSQUARE term CLOSESQUARE ASSIGN texp ;

function_call : NAME OPENPAREN arguments CLOSEPAREN ;
| NAME OPENPAREN CLOSEPAREN ;

arguments : texp | arguments LIST_SEP texp ;

if_block : IF OPENPAREN texp CLOSEPAREN statement_block ;
| IF OPENPAREN texp CLOSEPAREN statement_block ELSE statement_block ;

while_block : WHILE OPENPAREN texp CLOSEPAREN statement_block ;

for_block : FOR OPENPAREN STMT_SEP STMT_SEP CLOSEPAREN statement_block ;
| FOR OPENPAREN STMT_SEP STMT_SEP statement CLOSEPAREN statement_block ;
| FOR OPENPAREN STMT_SEP texp STMT_SEP CLOSEPAREN statement_block ;
| FOR OPENPAREN STMT_SEP texp STMT_SEP statement CLOSEPAREN statement_block ;
| FOR OPENPAREN statement STMT_SEP STMT_SEP CLOSEPAREN statement_block ;
| FOR OPENPAREN statement STMT_SEP STMT_SEP statement CLOSEPAREN statement_block ;
| FOR OPENPAREN statement STMT_SEP texp STMT_SEP CLOSEPAREN statement_block ;
| FOR OPENPAREN statement STMT_SEP texp STMT_SEP statement CLOSEPAREN statement_block ;

texp : or_exp ;

or_exp : and_exp ;
| or_exp OR and_exp ;

and_exp : eq_exp ;
| and_exp AND eq_exp ;

eq_exp : rel_exp;
| eq_exp EQ rel_exp ;

rel_exp : add_exp ;
| rel_exp REL add_exp ;

add_exp : mul_exp ;
| add_exp ADD mul_exp ; 

mul_exp : exp ;
| mul_exp MUL exp ;

exp : term ;
| UNARY_OP term ;
| ADD term ;

term : NAME ;
| FLOATV  ;
| INTV  ;
| BOOLLIT  ;
| CHARV  ;
| OPENPAREN texp CLOSEPAREN ;
| NAME OPENSQUARE term CLOSESQUARE ;
| function_call ;

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



