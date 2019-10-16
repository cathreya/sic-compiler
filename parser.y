%define parse.error verbose
%{
	#include <stdio.h>
	#include <iostream>
	using namespace std;

	// stuff from flex that bison needs to know about:
	extern int yylex();
	extern int yyparse();
	extern FILE *yyin;
	void yyerror(char const *s);
	int production = 1;

	void status(int rule){
		cout<<"Reducing using rule "<<rule<<endl;
	}

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

imports : IMPORT STRINGLIT STMT_SEP {status(1);};
| imports IMPORT STRINGLIT STMT_SEP {status(2);};

prog_element : declaration STMT_SEP {status(3);};
| function_definition {status(4);};

program : prog_element program {status(5);};
| prog_element {status(6);};

declaration : TYPE NAME ASSIGN STRINGLIT {status(7);};
| TYPE NAME  {status(77);};
| TYPE NAME ASSIGN FLOATV  {status(8);};
| TYPE NAME ASSIGN INTV  {status(9);};
| TYPE NAME ASSIGN BOOLLIT  {status(10);};
| TYPE NAME ASSIGN CHARV  {status(11);};
| TYPE NAME ASSIGN NAME  {status(12);};

function_definition : TYPE NAME OPENPAREN parameters CLOSEPAREN statement_block {status(13);};
| TYPE NAME OPENPAREN CLOSEPAREN statement_block {status(14);};
| VOIDV NAME OPENPAREN CLOSEPAREN statement_block {status(15);};
| VOIDV NAME OPENPAREN parameters CLOSEPAREN statement_block {status(16);};

parameters : TYPE NAME {status(17);};
| parameters LIST_SEP TYPE NAME {status(18);};

statement_block : OPENBRACE statement_list CLOSEBRACE {status(19);};

statement_list : statement STMT_SEP {status(20);};
| statement_list statement STMT_SEP {status(21);};

statement : declaration {status(22);};
| assignment_statement {status(23);};
| function_call {status(24);};
| BREAK {status(25);};
| CONTINUE {status(26);};
| RETURN {status(27);};
| RETURN texp {status(277);};
| if_block {status(28);};
| while_block {status(29);};
| for_block {status(30);};

assignment_statement : NAME ASSIGN texp {status(31);};
| NAME OPENSQUARE term CLOSESQUARE ASSIGN texp {status(32);};

function_call : NAME OPENPAREN arguments CLOSEPAREN {status(33);};
| NAME OPENPAREN CLOSEPAREN {status(34);};

arguments : texp {status(35);};
| STRINGLIT {status(355);};
| arguments LIST_SEP texp {status(36);};
| arguments LIST_SEP STRINGLIT {status(366);};

if_block : IF OPENPAREN texp CLOSEPAREN statement_block {status(37);};
| IF OPENPAREN texp CLOSEPAREN statement_block ELSE statement_block {status(38);};

while_block : WHILE OPENPAREN texp CLOSEPAREN statement_block {status(39);};

for_block : FOR OPENPAREN STMT_SEP STMT_SEP CLOSEPAREN statement_block {status(40);};
| FOR OPENPAREN STMT_SEP STMT_SEP statement CLOSEPAREN statement_block {status(41);};
| FOR OPENPAREN STMT_SEP texp STMT_SEP CLOSEPAREN statement_block {status(42);};
| FOR OPENPAREN STMT_SEP texp STMT_SEP statement CLOSEPAREN statement_block {status(43);};
| FOR OPENPAREN statement STMT_SEP STMT_SEP CLOSEPAREN statement_block {status(44);};
| FOR OPENPAREN statement STMT_SEP STMT_SEP statement CLOSEPAREN statement_block {status(45);};
| FOR OPENPAREN statement STMT_SEP texp STMT_SEP CLOSEPAREN statement_block {status(46);};
| FOR OPENPAREN statement STMT_SEP texp STMT_SEP statement CLOSEPAREN statement_block {status(47);};

texp : or_exp {status(48);};

or_exp : and_exp {status(49);};
| or_exp OR and_exp {status(50);};

and_exp : eq_exp {status(51);};
| and_exp AND eq_exp {status(52);};

eq_exp : rel_exp;
| eq_exp EQ rel_exp {status(53);};

rel_exp : add_exp {status(54);};
| rel_exp REL add_exp {status(55);};

add_exp : mul_exp {status(56);};
| add_exp ADD mul_exp {status(57);;} 

mul_exp : exp {status(58);};
| mul_exp MUL exp {status(59);};

exp : term {status(60);};
| UNARY_OP term {status(61);};
| ADD term {status(62);};

term : NAME {status(63);};
| FLOATV  {status(64);};
| INTV  {status(65);};
| BOOLLIT  {status(66);};
| CHARV  {status(67);};
| OPENPAREN texp CLOSEPAREN {status(68);};
| NAME OPENSQUARE term CLOSESQUARE {status(69);};
| function_call {status(70);};

%%

void yyerror(char const *s)
{
				fprintf(stderr, "error: %s\n", s);
}


main(int argc, char **argv)
{
				yyparse();
				printf("Parsing Over\n");
}



