#include <iostream>
#include "ast.hh"
#include "parser.tab.hh"
#include "visitor.hh"
#include "printVisitor.cpp"

StartNode *root;


int main(){
	yyparse();
	PrintVisitor *visitor = new PrintVisitor();
	visitor->visit(root);

	return 0;
}