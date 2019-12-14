%define parse.error verbose
%{
	#include <stdio.h>
	#include <iostream>
	#include "visitor.hh"
	#include "ast.hh"

	// stuff from flex that bison needs to know about:
	extern int yylex();
	extern int yyparse();
	extern FILE *yyin;

	extern StartNode *root;

	void yyerror(char const *s);
	
	int production = 1;

	void status(int rule){
		std::cout<<"Reducing using rule "<<rule<<std::endl;
	}
%}
%union {
	int   ival;
	float fval;
	char  sval[100];
	Term *TermVal;
	Name *NameVal;
	Float *FloatVal;
	Int *IntVal;
	Bool *BoolVal;
	Char *CharVal;
	MultiDimArr *MultiDimArrVal;
	UnaryTerm *UnaryTermVal;
	Exp *ExpVal;
	BinaryOperator *BinaryOperatorVal;
	TernaryOperator *TernaryOperatorVal;
	std::vector<Square*> *SquareVal;
	FuncCall *FuncCallVal;
	String *StringVal;
	std::vector<Arg*> *ArgVal;
	IfStmt *IfStmtVal;
	For *ForVal;
	While *WhileVal;
	AssignPar *AssignParVal;
	ArrayAssign *ArrayAssignVal;
	Assign *AssignVal;
	Break *BreakVal;
	Continue *ContinueVal;
	Return *ReturnVal;
	Statement *StatementVal;
	std::vector<Statement*> *StatementListVal;
	std::vector<Param*> *ParamVal;
	FuncDef *FuncDefVal;
	std::vector<ProgramNode*> *ProgramNodeVal;
	ProgramNode *SProgramNodeVal;
	StartNode *StartNodeVal;
	VarDec *VarDecVal;
	ParenExp *ParenExpVal;
	Read *ReadVal;
	Print *PrintVal;
    std::vector<Imports*> *ImportsVal;

}

%token  <sval> PRINT 
%token  <sval> IMPORT 
%token  <sval> READ 
%token  <ival> DIGIT 
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
%token  <sval> TQ
%token  <sval> TE

%type <StartNodeVal> start
%type <SProgramNodeVal> prog_element
%type <ProgramNodeVal> program
%type <VarDecVal> declaration
%type <FuncDefVal> function_definition
%type <ParamVal> parameters
%type <StatementListVal> statement_block
%type <StatementListVal> statement_list
%type <StatementVal> statementsc
%type <StatementVal> statementcurly
%type <AssignParVal> assignment_statement
%type <SquareVal> multidim
%type <FuncCallVal> function_call
%type <ArgVal> arguments
%type <IfStmtVal> if_block
%type <WhileVal> while_block
%type <ForVal> for_block
%type <ExpVal> texp
%type <ExpVal> or_exp
%type <ExpVal> and_exp
%type <ExpVal> eq_exp
%type <ExpVal> rel_exp
%type <ExpVal> add_exp
%type <ExpVal> mul_exp
%type <ExpVal> exp
%type <TermVal> term
%type <StringVal> string
%type <ReadVal> read
%type <PrintVal> print
%type <ImportsVal> imports

%%
start : imports program { 
	$$ = new StartNode($1,$2);
	root = $$;
	std::cerr << "Parse successful!" << std::endl; 
}
| program { 
	$$ = new StartNode(NULL,$1);
	root = $$;
	std::cerr << "Parse successful!" << std::endl;
}

imports : IMPORT string STMT_SEP {$$ = new std::vector<Imports*> ({new Imports($2)});}
| imports IMPORT string STMT_SEP {$1->push_back(new Imports($3)); $$ = $1;}


prog_element : declaration STMT_SEP {$1->set_sc(1); $$ = $1;}
| function_definition {$$ = $1;}

program : program prog_element {$1->push_back($2); $$ = $1;}
| prog_element {$$ = new std::vector<ProgramNode*> ({$1});}

declaration : TYPE NAME ASSIGN string {$$ = new VarDec(std::string($1), NULL, std::string($2), $4);}
| TYPE NAME  {$$ = new VarDec(std::string($1), NULL, std::string($2), NULL);}
| TYPE NAME ASSIGN texp  {$$ = new VarDec(std::string($1), NULL, std::string($2), $4);}
| TYPE multidim NAME  {$$ = new VarDec(std::string($1), $2, std::string($3), NULL);}
| TYPE multidim NAME ASSIGN string {$$ = new VarDec(std::string($1), $2, std::string($3), $5);}

function_definition : TYPE NAME OPENPAREN parameters CLOSEPAREN statement_block {$$ = new FuncDef(std::string($1),std::string($2),$4,$6);}
| TYPE NAME OPENPAREN CLOSEPAREN statement_block {$$ = new FuncDef(std::string($1),std::string($2),NULL,$5);}
| VOIDV NAME OPENPAREN CLOSEPAREN statement_block {$$ = new FuncDef(std::string($1),std::string($2),NULL,$5);}
| VOIDV NAME OPENPAREN parameters CLOSEPAREN statement_block {$$ = new FuncDef(std::string($1),std::string($2),$4,$6);};

parameters : TYPE NAME {$$ = new std::vector<Param*> ({new Param(std::string($1), NULL, std::string($2))});}
| TYPE multidim NAME {$$ = new std::vector<Param*> ({new Param(std::string($1), $2, std::string($3))});}
| parameters LIST_SEP TYPE NAME {$1->push_back(new Param(std::string($3), NULL, std::string($4))); $$ = $1;}
| parameters LIST_SEP TYPE multidim NAME {$1->push_back(new Param(std::string($3), $4, std::string($5))); $$ = $1;}

statement_block : OPENBRACE statement_list CLOSEBRACE {$$ = $2;}

statement_list : statementsc STMT_SEP {$$ = new std::vector<Statement*> ({$1});}
| statementcurly {$$ = new std::vector<Statement*> ({$1});}
| statement_list statementsc STMT_SEP {$1->push_back($2); $$ = $1;}
| statement_list statementcurly {$1->push_back($2); $$ = $1;;}

statementsc : declaration {$1->set_sc(1); $$ = $1;}
| assignment_statement {$1->set_sc(1); $$ = $1;}
| function_call {$1->set_sc(1); $$ = $1;}
| read {$1->set_sc(1); $$ = $1;}
| print {$1->set_sc(1); $$ = $1;}
| BREAK {$$ = new Break(); $$->set_sc(1);}
| CONTINUE {$$ = new Continue(); $$->set_sc(1);}
| RETURN {$$ = new Return(NULL); $$->set_sc(1);}
| RETURN texp {$$ = new Return($2); $$->set_sc(1);}
| RETURN string {$$ = new Return($2); $$->set_sc(1);}

statementcurly : if_block {$1->set_sc(0); $$ = $1;}
| while_block {$1->set_sc(0); $$ = $1;}
| for_block {$1->set_sc(0); $$ = $1;}

assignment_statement : NAME ASSIGN texp {$$ = new Assign(std::string($1),$2,$3);}
| NAME multidim ASSIGN texp {$$ = new ArrayAssign(std::string($1),$2,$3,$4);}

multidim : OPENSQUARE texp CLOSESQUARE {$$ = new std::vector<Square*> ({new Square($2)});}
| multidim OPENSQUARE texp CLOSESQUARE {$1->push_back(new Square($3)); $$ = $1;}

function_call : NAME OPENPAREN arguments CLOSEPAREN {$$ = new FuncCall(std::string($1),$3);}
| NAME OPENPAREN CLOSEPAREN {$$ = new FuncCall(std::string($1), NULL);}

read : READ OPENPAREN NAME CLOSEPAREN {$$ = new Read(std::string($3));}

print : PRINT OPENPAREN string CLOSEPAREN {$$ = new Print($3);}
| PRINT OPENPAREN texp CLOSEPAREN {$$ = new Print($3);}


arguments : texp {$$ = new std::vector<Arg*> ({new Arg($1)});}
| string {$$ = new std::vector<Arg*> ({new Arg($1)});}
| arguments LIST_SEP texp {$1->push_back(new Arg($3)); $$ = $1;}
| arguments LIST_SEP string {$1->push_back(new Arg($3)); $$ = $1;}

if_block : IF OPENPAREN texp CLOSEPAREN statement_block {$$ = new IfStmt($3,$5,NULL);}
| IF OPENPAREN texp CLOSEPAREN statement_block ELSE statement_block {$$ = new IfStmt($3,$5,$7);}

while_block : WHILE OPENPAREN texp CLOSEPAREN statement_block {$$ = new While($3, $5);}

for_block : FOR OPENPAREN STMT_SEP STMT_SEP CLOSEPAREN statement_block {$$ = new For(NULL, NULL, NULL, $6);}
| FOR OPENPAREN STMT_SEP STMT_SEP statementsc CLOSEPAREN statement_block {$5->set_sc(0); $$ = new For(NULL,NULL,$5,$7);}
| FOR OPENPAREN STMT_SEP texp STMT_SEP CLOSEPAREN statement_block {$$ = new For(NULL,$4,NULL,$7);}
| FOR OPENPAREN STMT_SEP texp STMT_SEP statementsc CLOSEPAREN statement_block {$6->set_sc(0); $$ = new For(NULL,$4,$6,$8);}
| FOR OPENPAREN statementsc STMT_SEP STMT_SEP CLOSEPAREN statement_block {$3->set_sc(0); $$ = new For($3,NULL,NULL,$7);}
| FOR OPENPAREN statementsc STMT_SEP STMT_SEP statementsc CLOSEPAREN statement_block {$6->set_sc(0); $3->set_sc(0); $$ = new For($3, NULL, $6, $8);}
| FOR OPENPAREN statementsc STMT_SEP texp STMT_SEP CLOSEPAREN statement_block {$3->set_sc(0); $$ = new For($3, $5, NULL, $8);}
| FOR OPENPAREN statementsc STMT_SEP texp STMT_SEP statementsc CLOSEPAREN statement_block {$3->set_sc(0); $7->set_sc(0); $$ = new For($3, $5, $7, $9);}

texp : or_exp {$$ = $1;}
| or_exp TQ texp TE or_exp {$$ = new TernaryOperator($1,$3,$5);}

or_exp : and_exp {$$ = $1;}
| or_exp OR and_exp {$$ = new BinaryOperator(std::string($2),$1,$3);}

and_exp : eq_exp {$$ = $1;}
| and_exp AND eq_exp {$$ = new BinaryOperator(std::string($2),$1,$3);}

eq_exp : rel_exp {$$ = $1;};
| eq_exp EQ rel_exp {$$ = new BinaryOperator(std::string($2),$1,$3);}

rel_exp : add_exp {$$ = $1;}
| rel_exp REL add_exp {$$ = new BinaryOperator(std::string($2),$1,$3);}

add_exp : mul_exp {$$ = $1;}
| add_exp ADD mul_exp {$$ = new BinaryOperator(std::string($2),$1,$3);} 

mul_exp : exp {$$ = $1;}
| mul_exp MUL exp {$$ = new BinaryOperator(std::string($2),$1,$3);}

exp : term {$$ = $1;}
| UNARY_OP term {$$ = new UnaryTerm(std::string($1),$2);}
| ADD term {$$ = new UnaryTerm(std::string($1),$2);}

term : NAME {$$ = new Name($1);}
| FLOATV  {$$ = new Float($1);}
| INTV  {$$ = new Int($1);}
| BOOLLIT  {$$ = new Bool($1);}
| CHARV  {$$ = new Char(std::string($1));}
| OPENPAREN texp CLOSEPAREN {$$ = new ParenExp($2);}
| NAME multidim {$$ = new MultiDimArr(std::string($1),$2);}
| function_call {$1->set_sc(0); $$ = $1;}

string : STRINGLIT {$$ = new String(std::string($1));}

%%

void yyerror(char const *s){
	fprintf (stderr, "%s\n", s);
}

// main(int argc, char **argv)
// {
// 				yyparse();
// 				printf("Parsing Over\n");
// }



