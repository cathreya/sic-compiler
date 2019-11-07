#include "visitor.hh"
// #include "ast.h"
#include <iostream>


void Visitor::visit(Name* visitee){
	std::cout<<"Ok"<<std::endl;
}
void Visitor::visit(Float* visitee){
	std::cout<<"Ok"<<std::endl;
}
void Visitor::visit(Int* visitee){
	std::cout<<"Ok"<<std::endl;
}
void Visitor::visit(Bool* visitee){
	std::cout<<"Ok"<<std::endl;
}
void Visitor::visit(Char* visitee){
	std::cout<<"Ok"<<std::endl;
}
void Visitor::visit(MultiDimArr* visitee){
	std::cout<<"Ok"<<std::endl;
}
void Visitor::visit(UnaryTerm* visitee){
	std::cout<<"Ok"<<std::endl;
}
void Visitor::visit(BinaryOperator* visitee){
	std::cout<<"Ok"<<std::endl;
}
void Visitor::visit(TernaryOperator* visitee){
	std::cout<<"Ok"<<std::endl;
}
void Visitor::visit(Square* visitee){
	std::cout<<"Ok"<<std::endl;
}
void Visitor::visit(FuncCall* visitee){
	std::cout<<"Ok"<<std::endl;
}
void Visitor::visit(String* visitee){
	std::cout<<"Ok"<<std::endl;
}
void Visitor::visit(Arg* visitee){
	std::cout<<"Ok"<<std::endl;
}
void Visitor::visit(IfStmt* visitee){
	std::cout<<"Ok"<<std::endl;
}
void Visitor::visit(For* visitee){
	std::cout<<"Ok"<<std::endl;
}
void Visitor::visit(While* visitee){
	std::cout<<"Ok"<<std::endl;
}
void Visitor::visit(AssignPar* visitee){
	std::cout<<"Ok"<<std::endl;
}
void Visitor::visit(ArrayAssign* visitee){
	std::cout<<"Ok"<<std::endl;
}
void Visitor::visit(Assign* visitee){
	std::cout<<"Ok"<<std::endl;
}
void Visitor::visit(Break* visitee){
	std::cout<<"Ok"<<std::endl;
}
void Visitor::visit(Continue* visitee){
	std::cout<<"Ok"<<std::endl;
}
void Visitor::visit(Return* visitee){
	std::cout<<"Ok"<<std::endl;
}
void Visitor::visit(Statement* visitee){
	std::cout<<"Ok"<<std::endl;
}
void Visitor::visit(Param* visitee){
	std::cout<<"Ok"<<std::endl;
}
void Visitor::visit(FuncDef* visitee){
	std::cout<<"Ok"<<std::endl;
}
void Visitor::visit(VarDec* visitee){
	std::cout<<"Ok"<<std::endl;
}
void Visitor::visit(ProgramNode* visitee){
	std::cout<<"Ok"<<std::endl;
}
void Visitor::visit(Imports* visitee){
	std::cout<<"Ok"<<std::endl;
}
void Visitor::visit(StartNode* visitee){
	std::cout<<"Ok"<<std::endl;
}
void Visitor::visit(ParenExp* visitee){
	std::cout<<"Ok"<<std::endl;
}