%option noyywrap
%{
	#include <string.h>
	#include <stdlib.h>
	#include <cstdio>
	#include <iostream>
	#include <vector>
	#include "visitor.hh"
	#include "ast.hh"
	#include "parser.tab.hh"
	int linenumm = 0;
	extern int yylex();
%}

%% 
[ \t] { /* eat white spaces */  }
"/""/"[^"\n"]*"\n" {
	//consume the comment
}
[,] {
	//std::cout<<linenumm<<" found a LIST_SEP;"<<std::endl;
	return LIST_SEP;
}
[;] {
	//std::cout<<linenumm<<" found a STMT_SEP;"<<std::endl;
	return STMT_SEP;
}
[!] {
	strcpy(yylval.sval,yytext);
	//std::cout<<linenumm<<" found a UNARY_OP;"<<std::endl;
	return UNARY_OP;
}
[+-] {
	strcpy(yylval.sval,yytext);
	//std::cout<<linenumm<<" found a ADD;"<<std::endl;
	return ADD;
}
[*/%] {
	strcpy(yylval.sval,yytext);
	//std::cout<<linenumm<<" found a MUL;"<<std::endl;
	return MUL;
}
[<>]=? {
	strcpy(yylval.sval,yytext);
	//std::cout<<linenumm<<" found a REL;"<<std::endl;
	return REL;
}
[=!]= {
	strcpy(yylval.sval,yytext);
	//std::cout<<linenumm<<" found a EQ;"<<std::endl;
	return EQ;
}
[&] {
	strcpy(yylval.sval,yytext);
	//std::cout<<linenumm<<" found a AND;"<<std::endl;
	return AND;
}
[|] {
	strcpy(yylval.sval,yytext);
	//std::cout<<linenumm<<" found a OR;"<<std::endl;
	return OR;
}
"void" {
	strcpy(yylval.sval,yytext);
	//std::cout<<linenumm<<" found a VOIDV;"<<std::endl;
	return VOIDV;
}
("uint"|"int"|"float"|"char"|"file"|"bool") {
	strcpy(yylval.sval,yytext);
	//std::cout<<linenumm<<" found a TYPE;"<<std::endl;
	return TYPE;
}
return {
	//std::cout<<linenumm<<" found a RETURN;"<<std::endl;
	return RETURN;
}
break {
	//std::cout<<linenumm<<" found a BREAK;"<<std::endl;
	return BREAK;
}
continue {
	//std::cout<<linenumm<<" found a CONTINUE;"<<std::endl;
	return CONTINUE;
}
if {
	//std::cout<<linenumm<<" found a IF;"<<std::endl;
	return IF;
}
else {
	//std::cout<<linenumm<<" found a ELSE;"<<std::endl;
	return ELSE;
}
for {
	//std::cout<<linenumm<<" found a FOR;"<<std::endl;
	return FOR;
}
while {
	//std::cout<<linenumm<<" found a WHILE;"<<std::endl;
	return WHILE;
}
import {
	//std::cout<<linenumm<<" found a IMPORT;"<<std::endl;
	return IMPORT;
}
"true"|"false" {
	strcpy(yylval.sval,yytext);
	//std::cout<<linenumm<<" found a BOOLLIT;"<<std::endl;
	return BOOLLIT;
}
[0-9]+ { 
	yylval.ival = atoi(yytext); 
	//std::cout<<linenumm<<" found a INTV; "<<yytext<<std::endl;
	return INTV;
}
[0-9]*[.][0-9]+ {
	yylval.ival = atof(yytext); 
	//std::cout<<linenumm<<" found a FLOATV;"<<std::endl;
	return FLOATV;
}
("\'""\\""n""\'") {
	yylval.sval[0] = yytext[1];
	yylval.sval[1] = yytext[2];
	yylval.sval[2] = 0;
	return CHARV;
}
("\'""\\""0""\'") {
	yylval.sval[0] = yytext[1];
	yylval.sval[1] = yytext[2];
	yylval.sval[2] = 0;
	return CHARV;
}
("\'""\\""t""\'") {
	yylval.sval[0] = yytext[1];
	yylval.sval[1] = yytext[2];
	yylval.sval[2] = 0;
	return CHARV;
}

("\'"[^"\'"]"\'") {
	yylval.sval[0] = yytext[1];
	yylval.sval[1] = 0;
	//std::cout<<linenumm<<" found a CHARV;"<<std::endl;
	return CHARV;
}
[a-zA-Z_][a-zA-Z0-9_]* {
	strcpy(yylval.sval,yytext);
	//std::cout<<linenumm<<" found a NAME; "<< yytext<<std::endl;
	return NAME; 
}
("+"|"-"|"*"|"%")?= {
	strcpy(yylval.sval,yytext);
	//std::cout<<linenumm<<" found a ASSIGN;"<<std::endl;
	return ASSIGN;
}
"?" {
	//std::cout<<linenumm<<" found a TQ;"<<std::endl;
	return TQ;
}
":" {
	//std::cout<<linenumm<<" found a TE;"<<std::endl;
	return TE;
}

"(" {
	//std::cout<<linenumm<<" found a OPENPAREN;"<<std::endl;
	return OPENPAREN;
}
")" {
	//std::cout<<linenumm<<" found a CLOSEPAREN;"<<std::endl;
	return CLOSEPAREN;
}
"{" {
	//std::cout<<linenumm<<" found a OPENBRACE;"<<std::endl;
	return OPENBRACE;
}
"}" {
	//std::cout<<linenumm<<" found a CLOSEBRACE;"<<std::endl;
	return CLOSEBRACE;
}
"[" {
	//std::cout<<linenumm<<" found a OPENSQUARE;"<<std::endl;
	return OPENSQUARE;
}
"]" {
	//std::cout<<linenumm<<" found a CLOSESQUARE;"<<std::endl;
	return CLOSESQUARE;
}
"\""[^"\""]+"\"" {
	strcpy(yylval.sval,yytext);
	//std::cout<<linenumm<<" found a STRINGLIT; "<<yytext<<std::endl;
	return STRINGLIT;
}
\n		{ ++linenumm;}
.		{ printf("Line No %d: Unrecognized character '%c'\n", linenumm, yytext[0]);}

%%

// int main(){
// 	while(yylex());
// }