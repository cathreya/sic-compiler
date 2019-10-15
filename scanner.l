%{
#include <string.h>
#include <stdlib.h>
#include <cstdio>
#include <iostream>
using namespace std;
// #include "parser.tab.h"
int lineno = 0;
extern int yylex();

%}

%% 
[ \t] { /* eat white spaces */  }
"//"[a-zA-Z]+ {
	//consume the comment
}
[,] {
	cout<<"found a LIST_SEP;"<<endl;
	// return LIST_SEP;
}
[;] {
	cout<<"found a STMT_SEP;"<<endl;
	// return STMT_SEP;
}
[!] {
	cout<<"found a UNARY_OP;"<<endl;
	// return UNARY_OP;
}
[+-] {
	cout<<"found a ADD;"<<endl;
	// return ADD;
}
[*/%] {
	cout<<"found a MUL;"<<endl;
	// return MUL;
}
[<>]=? {
	cout<<"found a REL;"<<endl;
	// return REL;
}
[=!]= {
	cout<<"found a EQ;"<<endl;
	// return EQ;
}
[&] {
	cout<<"found a AND;"<<endl;
	// return AND;
}
[|] {
	cout<<"found a OR;"<<endl;
	// return OR;
}
"void" {
	cout<<"found a VOIDV;"<<endl;
	// return VOIDV;
}
("uint"|"int"|"float"|"char"|"file")("["[0-9]*"]")* {
	//strcpy(//yylval.sval,yytext);
	cout<<"found a TYPE;"<<endl;
	// return TYPE;
}
return {
	cout<<"found a RETURN;"<<endl;
	// return RETURN;
}
break {
	cout<<"found a BREAK;"<<endl;
	// return BREAK;
}
continue {
	cout<<"found a CONTINUE;"<<endl;
	// return CONTINUE;
}
if {
	cout<<"found a IF;"<<endl;
	// return IF;
}
else {
	cout<<"found a ELSE;"<<endl;
	// return ELSE;
}
for {
	cout<<"found a FOR;"<<endl;
	// return FOR;
}
while {
	cout<<"found a WHILE;"<<endl;
	// return WHILE;
}
import {
	cout<<"found a IMPORT;"<<endl;
	// return IMPORT;
}
true|false {
	//strcpy(//yylval.sval,yytext);
	cout<<"found a BOOLLIT;"<<endl;
	// return BOOLLIT;
}
[0-9]+ { 
	//yylval.ival = atoi(yytext); 
	cout<<"found a INTV;"<<endl;
	// return INTV;
}
[0-9]*[.][0-9]+ {
	//yylval.ival = atof(yytext); 
	cout<<"found a FLOATV;"<<endl;
	// return FLOATV;
}
("\'"[^"\'"]"\'")|("\'\\"[^"\'"]"\'") {
	//yylval.sval[0] = yytext[0];
	//yylval.sval[1] = 0;
	cout<<"found a CHARV;"<<endl;
	// return CHARV;
}
[a-zA-Z][a-zA-Z0-9]* {
	//strcpy(//yylval.sval,yytext);
	cout<<"found a NAME;" <<endl;
	// return NAME; 
}
['+''-''*''%']?= {
	cout<<"found a ASSIGN;"<<endl;
	// return ASSIGN;
}
"(" {
	cout<<"found a OPENPAREN;"<<endl;
	// return OPENPAREN;
}
")" {
	cout<<"found a CLOSEPAREN;"<<endl;
	// return CLOSEPAREN;
}
"{" {
	cout<<"found a OPENBRACE;"<<endl;
	// return OPENBRACE;
}
"}" {
	cout<<"found a CLOSEBRACE;"<<endl;
	// return CLOSEBRACE;
}
"[" {
	cout<<"found a OPENSQUARE;"<<endl;
	// return OPENSQUARE;
}
"]" {
	cout<<"found a CLOSESQUARE;"<<endl;
	// return CLOSESQUARE;
}
"\""[^"\""]+"\"" {
	//strcpy(//yylval.sval,yytext);
	cout<<"found a STRINGLIT;"<<endl;
	// return STRINGLIT;
}
\n		{ ++lineno; return '\n'; }
.		{ printf("Line No %d: Unrecognized character '%c'\n", lineno, yytext[0]);}

%%

int main(){
	while(yylex());
}