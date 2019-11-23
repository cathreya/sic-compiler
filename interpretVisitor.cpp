#include <iostream>
#include "ast.hh"
#include "parser.tab.hh"
#include "visitor.hh"
#include "interpretVisitor.hh"

StartNode *root;
extern FILE* yyin;

int main(int argc, char *argv[]){
	if(argc > 1){
		FILE* fp = fopen(argv[1],"r");
		if(fp != NULL){
			yyin = fp;
		}
	}
	yyparse();
	InterpretVisitor *visitor = new InterpretVisitor();
	visitor->visit(root);

	return 0;
}