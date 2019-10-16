%{
#include <string.h>
#include <stdlib.h>
#include <cstdio>
#include <iostream>
using namespace std;
#include "parser.tab.h"
int lineno = 0;
extern int yylex();

%}

%% 
[ \t] { /* eat white spaces */  }
"/""/"[^"\n"]*"\n" {
	//consume the comment
}
[,] {
	cout<<lineno<<" found a LIST_SEP;"<<endl;
	return LIST_SEP;
}
[;] {
	cout<<lineno<<" found a STMT_SEP;"<<endl;
	return STMT_SEP;
}
[!] {
	cout<<lineno<<" found a UNARY_OP;"<<endl;
	return UNARY_OP;
}
[+-] {
	cout<<lineno<<" found a ADD;"<<endl;
	return ADD;
}
[*/%] {
	cout<<lineno<<" found a MUL;"<<endl;
	return MUL;
}
[<>]=? {
	cout<<lineno<<" found a REL;"<<endl;
	return REL;
}
[=!]= {
	cout<<lineno<<" found a EQ;"<<endl;
	return EQ;
}
[&] {
	cout<<lineno<<" found a AND;"<<endl;
	return AND;
}
[|] {
	cout<<lineno<<" found a OR;"<<endl;
	return OR;
}
"void" {
	cout<<lineno<<" found a VOIDV;"<<endl;
	return VOIDV;
}
("uint"|"int"|"float"|"char"|"file"|"bool")("["[0-9]*"]")* {
	strcpy(yylval.sval,yytext);
	cout<<lineno<<" found a TYPE;"<<endl;
	return TYPE;
}
return {
	cout<<lineno<<" found a RETURN;"<<endl;
	return RETURN;
}
break {
	cout<<lineno<<" found a BREAK;"<<endl;
	return BREAK;
}
continue {
	cout<<lineno<<" found a CONTINUE;"<<endl;
	return CONTINUE;
}
if {
	cout<<lineno<<" found a IF;"<<endl;
	return IF;
}
else {
	cout<<lineno<<" found a ELSE;"<<endl;
	return ELSE;
}
for {
	cout<<lineno<<" found a FOR;"<<endl;
	return FOR;
}
while {
	cout<<lineno<<" found a WHILE;"<<endl;
	return WHILE;
}
import {
	cout<<lineno<<" found a IMPORT;"<<endl;
	return IMPORT;
}
true|false {
	strcpy(yylval.sval,yytext);
	cout<<lineno<<" found a BOOLLIT;"<<endl;
	return BOOLLIT;
}
[0-9]+ { 
	yylval.ival = atoi(yytext); 
	cout<<lineno<<" found a INTV; "<<yytext<<endl;
	return INTV;
}
[0-9]*[.][0-9]+ {
	yylval.ival = atof(yytext); 
	cout<<lineno<<" found a FLOATV;"<<endl;
	return FLOATV;
}
("\'"[^"\'"]"\'")|("\'\\"[^"\'"]"\'") {
	yylval.sval[0] = yytext[0];
	yylval.sval[1] = 0;
	cout<<lineno<<" found a CHARV;"<<endl;
	return CHARV;
}
[a-zA-Z_][a-zA-Z0-9_]* {
	strcpy(yylval.sval,yytext);
	cout<<lineno<<" found a NAME; "<< yytext<<endl;
	return NAME; 
}
("+"|"-"|"*"|"%")?= {
	cout<<lineno<<" found a ASSIGN;"<<endl;
	return ASSIGN;
}
"(" {
	cout<<lineno<<" found a OPENPAREN;"<<endl;
	return OPENPAREN;
}
")" {
	cout<<lineno<<" found a CLOSEPAREN;"<<endl;
	return CLOSEPAREN;
}
"{" {
	cout<<lineno<<" found a OPENBRACE;"<<endl;
	return OPENBRACE;
}
"}" {
	cout<<lineno<<" found a CLOSEBRACE;"<<endl;
	return CLOSEBRACE;
}
"[" {
	cout<<lineno<<" found a OPENSQUARE;"<<endl;
	return OPENSQUARE;
}
"]" {
	cout<<lineno<<" found a CLOSESQUARE;"<<endl;
	return CLOSESQUARE;
}
"\""[^"\""]+"\"" {
	strcpy(yylval.sval,yytext);
	cout<<lineno<<" found a STRINGLIT; "<<yytext<<endl;
	return STRINGLIT;
}
\n		{ ++lineno;}
.		{ printf("Line No %d: Unrecognized character '%c'\n", lineno, yytext[0]);}

%%

// int main(){
// 	while(yylex());
// }