#ifndef VISITOR_H
#define VISITOR_H

class Node;
class Term;
class Name;
class Float;
class Int;
class Bool;
class Char;
class MultiDimArr;
class Exp;
class UnaryTerm;
class BinaryOperator;
class TernaryOperator;
class Square;
class FuncCall;
class String;
class Arg;
class IfStmt;
class For;
class While;
class AssignPar;
class ArrayAssign;
class Assign;
class Break;
class Continue;
class Return;
class Statement;
class Param;
class FuncDef;
class VarDec;
class ProgramNode;
class Imports;
class StartNode;
class ParenExp;

class Visitor{
public:
	Visitor(){}
	virtual void visit(Node* visitee) = 0;
	virtual void visit(Term* visitee) = 0;
	virtual void visit(Name* visitee) = 0;
	virtual void visit(Float* visitee) = 0;
	virtual void visit(Int* visitee) = 0;
	virtual void visit(Bool* visitee) = 0;
	virtual void visit(Char* visitee) = 0;
	virtual void visit(MultiDimArr* visitee) = 0;
	virtual void visit(Exp* visitee) = 0;
	virtual void visit(UnaryTerm* visitee) = 0;
	virtual void visit(BinaryOperator* visitee) = 0;
	virtual void visit(TernaryOperator* visitee) = 0;
	virtual void visit(Square* visitee) = 0;
	virtual void visit(FuncCall* visitee) = 0;
	virtual void visit(String* visitee) = 0;
	virtual void visit(Arg* visitee) = 0;
	virtual void visit(IfStmt* visitee) = 0;
	virtual void visit(For* visitee) = 0;
	virtual void visit(While* visitee) = 0;
	virtual void visit(AssignPar* visitee) = 0;
	virtual void visit(ArrayAssign* visitee) = 0;
	virtual void visit(Assign* visitee) = 0;
	virtual void visit(Break* visitee) = 0;
	virtual void visit(Continue* visitee) = 0;
	virtual void visit(Return* visitee) = 0;
	virtual void visit(Statement* visitee) = 0;
	virtual void visit(Param* visitee) = 0;
	virtual void visit(FuncDef* visitee) = 0;
	virtual void visit(VarDec* visitee) = 0;
	virtual void visit(ProgramNode* visitee) = 0;
	virtual void visit(Imports* visitee) = 0;
	virtual void visit(StartNode* visitee) = 0;
	virtual void visit(ParenExp* visitee) = 0;
};



#endif