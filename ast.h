#include <vector>
#include "visitor.h"
#include <string>

#ifndef AST_H
#define AST_H


class Node{
public:
	Node(){}
	~Node(){}
	virtual void accept(Visitor *v) = 0;
};


class Term: public Node{
public:
	Term(){}
	~Term(){}
	virtual void accept(Visitor *v) = 0;
};

class Name: public Term{
public:
	Name(std::string name){
		set_name(name);
	}
	std::string get_name(){
		return this->name;
	}
	void accept(Visitor *v){
		v->visit(this);
	}
	~Name(){}
private:
	std::string name;
	void set_name(std::string name){
		this->name = name;
	}	
};

class Float: public Term{
public:
	Float(float val){
		set_val(val);
	}
	float get_val(){
		return this->val;
	}
	void accept(Visitor *v){
		v->visit(this);
	}
	~Float(){}
private:
	float val;
	void set_val(float val){
		this->val = val;
	}	
};

class Int: public Term{
public:
	Int(int val){
		set_val(val);
	}
	int get_val(){
		return this->val;
	}
	void accept(Visitor *v){
		v->visit(this);
	}
	~Int(){}
private:
	int val;
	void set_val(int val){
		this->val = val;
	}	
};

class Bool: public Term{
public:
	Bool(bool val){
		set_val(val);
	}
	bool get_val(){
		return this->val;
	}
	void accept(Visitor *v){
		v->visit(this);
	}
	~Bool(){}
private:
	bool val;
	void set_val(bool val){
		this->val = val;
	}	
};

class Char: public Term{
public:
	Char(char val){
		set_val(val);
	}
	char get_val(){
		return this->val;
	}
	void accept(Visitor *v){
		v->visit(this);
	}
	~Char(){}
private:
	char val;
	void set_val(char val){
		this->val = val;
	}	
};

class MultiDimArr: public Term{
public:
	MultiDimArr(std::string name, Node *sq){
		set_name(name);
		set_sq(sq);
	}
	std::string get_name(){
		return this->name;
	}
	Node *get_sq(){
		return this->sq;
	}
	void accept(Visitor *v){
		v->visit(this);
	}
	~MultiDimArr(){}
private:
	std::string name;
	Node *sq;
	void set_name(std::string name){
		this->name = name;
	}	
	void set_sq(Node *sq){
		this->sq = sq;
	}	
};

class Exp: public Node{
public:
	Exp(){}
	void accept(Visitor *v) = 0;
	~Exp(){}	
};


class UnaryTerm: public Exp{
public:
	UnaryTerm(std::string op, Node *term){
		set_op(op);
		set_term(term);
	}
	std::string get_op(){
		return this->op;
	}
	Node *get_term(){
		return this->term;
	}
	void accept(Visitor *v){
		v->visit(this);
	}
	~UnaryTerm(){}
private:
	std::string op;
	Node *term;
	void set_op(std::string op){
		this->op = op;
	}	
	void set_term(Node *term){
		this->term = term;
	}	
};



class BinaryOperator: public Exp{
public:
	BinaryOperator(std::string op, Node *left, Node *right){
		set_op(op);
		set_left(left);
		set_right(right);
	}
	std::string get_op(){
		return this->op;
	}
	Node *get_left(){
		return this->left;
	}
	Node *get_right(){
		return this->right;
	}
	void accept(Visitor *v){
		v->visit(this);
	}
	~BinaryOperator(){}
private:
	Node *left, *right;
	std::string op;
	void set_op(std::string op){
		this->op = op;
	}
	void set_left(Node *left){
		this->left = left;
	}
	void set_right(Node *right){
		this->right = right;
	}
};

class TernaryOperator: public Exp{
public:
	TernaryOperator(Node *left, Node *middle, Node *right){
		set_left(left);
		set_middle(middle);
		set_right(right);
	}
	Node *get_left(){
		return this->left;
	}
	Node *get_right(){
		return this->right;
	}
	Node *get_middle(){
		return this->middle;
	}
	void accept(Visitor *v){
		v->visit(this);
	}
	~TernaryOperator(){}
private:
	Node *left, *right, *middle;
	void set_left(Node *left){
		this->left = left;
	}
	void set_right(Node *right){
		this->right = right;
	}
	void set_middle(Node *middle){
		this->middle = middle;
	}	
};

class Square: public Node{
public:
	Square(Node *exp){
		set_exp(exp);
	}
	Node *get_exp(){
		return this->exp;
	}
	void accept(Visitor *v){
		v->visit(this);
	}
	~Square(){}

private:
	Node *exp;
	void set_exp(Node *exp){
		this->exp = exp;
	}
};

class String: public Node{
public:
	String(std::string val){
		set_val(val);
	}
	std::string get_val(){
		return this->val;
	}
	void accept(Visitor *v){
		v->visit(this);
	}
	~String(){}
private:
	std::string val;
	void set_val(std::string val){
		this->val = val;
	}	
};


class FuncDef: public Node{
public:
	FuncDef(std::string type, std::string name, Node *params, Node *exec){
		set_type(type);
		set_name(name);
		set_params(params);
		set_exec(exec);
	}
	std::string get_type(){
		return this->type;
	}
	std::string get_name(){
		return this->name;
	}
	Node *get_params(){
		return this->params;
	}
	Node *get_exec(){
		return this->exec;
	}
	void accept(Visitor *v){
		v->visit(this);
	}
	~FuncDef(){}
private:
	std:: string type,name;
	Node *params, *exec;
	void set_type(std::string type){
		this->type = type;
	}
	void set_name(std::string name){
		this->name = name;
	}
	void set_params(Node *params){
		this->params = params;
	}
	void set_exec(Node *exec){
		this->exec = exec;
	}
};

class Param: public Node{
public:
	Param(std::string type, Node *multidim, std::string name){
		set_type(type);
		set_name(name);
		set_multidim(multidim);
	}
	std::string get_type(){
		return this->type;
	}
	std::string get_name(){
		return this->name;
	}
	Node* get_multidim(){
		return this->multidim;
	}
	void accept(Visitor *v){
		v->visit(this);
	}
	~Param(){}
private:
	Node *multidim;
	std::string type,name;
	void set_multidim(Node *multidim){
		this->multidim = multidim;
	}	
	
	void set_type(std::string type){
		this->type = type;
	}
	void set_name(std::string name){
		this->name = name;
	}
};

class Statement: public Node{
public:
	Statement(){}
	void accept(Visitor *v)=0;
	~Statement(){}
};

class AssignPar: public Statement{
public:
	AssignPar(){}
	void accept(Visitor *v){
		v->visit(this);
	}
	~AssignPar(){}
};


class ArrayAssign: public AssignPar{
public:
	ArrayAssign(std::string name, Node *dims, Node *right){
		set_name(name);
		set_dims(dims);
		set_right(right);
	}
	std::string get_name(){
		return this->name;
	}
	Node *get_dims(){
		return this->dims;
	}
	Node *get_right(){
		return this->right;
	}
	void accept(Visitor *v){
		v->visit(this);
	}
	~ArrayAssign(){}
private:
	Node *dims, *right;
	std::string name;
	void set_name(std::string name){
		this->name = name;
	}
	void set_dims(Node *dims){
		this->dims = dims;
	}
	void set_right(Node *right){
		this->right = right;
	}
};

class Assign: public AssignPar{
public:
	Assign(std::string name, Node *right){
		set_name(name);
		set_right(right);
	}
	std::string get_name(){
		return this->name;
	}
	Node *get_right(){
		return this->right;
	}
	void accept(Visitor *v){
		v->visit(this);
	}
	~Assign(){}
private:
	Node *right;
	std::string name;
	void set_name(std::string name){
		this->name = name;
	}
	void set_right(Node *right){
		this->right = right;
	}
};


class For: public Statement{
public:
	For(Node *init, Node *cond, Node *increment, Node *exec){
		set_init(init);
		set_cond(cond);
		set_increment(increment);
		set_exec(exec);

	}
	Node *get_init(){
		return this->init;
	}
	Node *get_increment(){
		return this->increment;
	}
	Node *get_cond(){
		return this->cond;
	}
	Node *get_exec(){
		return this->exec;
	}

	void accept(Visitor *v){
		v->visit(this);
	}
	~For(){}
private:
	Node *init, *increment, *cond, *exec;
	void set_init(Node *init){
		this->init = init;
	}
	void set_increment(Node *increment){
		this->increment = increment;
	}
	void set_cond(Node *cond){
		this->cond = cond;
	}
	void set_exec(Node *exec){
		this->exec = exec;
	}
	
};

class While: public Statement{
public:
	While(Node *cond, Node *exec){
		set_cond(cond);
		set_exec(exec);
	}
	Node *get_cond(){
		return this->cond;
	}
	Node *get_exec(){
		return this->exec;
	}
	void accept(Visitor *v){
		v->visit(this);
	}
	~While(){}
private:
	Node *cond, *exec;
	void set_cond(Node *cond){
		this->cond = cond;
	}
	void set_exec(Node *exec){
		this->exec = exec;
	}
};


class Break: public Statement{
public:
	Break(){}
	void accept(Visitor *v){
		v->visit(this);
	}
	~Break(){}
};

class Continue: public Statement{
public:
	Continue(){}
	void accept(Visitor *v){
		v->visit(this);
	}
	~Continue(){}
};

class Return: public Statement{
public:
	Return(Node *ret){
		set_ret(ret);
	}
	Node *get_ret(){
		return this->ret;
	}
	void accept(Visitor *v){
		v->visit(this);
	}
	~Return(){}
private:
	Node *ret;
	void set_ret(Node *ret){
		this->ret = ret;
	}
};


class IfStmt: public Statement{
public:
	IfStmt(Node *cond, Node *if_blk, Node *else_blk){
		set_cond(cond);
		set_if_blk(if_blk);
		set_else_blk(else_blk);
	}
	Node *get_cond(){
		return this->cond;
	}
	Node *get_else_blk(){
		return this->else_blk;
	}
	Node *get_if_blk(){
		return this->if_blk;
	}
	void accept(Visitor *v){
		v->visit(this);
	}
	~IfStmt(){}
private:
	Node *cond, *else_blk, *if_blk;
	void set_cond(Node *cond){
		this->cond = cond;
	}
	void set_else_blk(Node *else_blk){
		this->else_blk = else_blk;
	}
	void set_if_blk(Node *if_blk){
		this->if_blk = if_blk;
	}
	
};


class FuncCall: public Statement{
public:
	FuncCall(std::string name, Node *args){
		set_name(name);
		set_args(args);
	}
	Node *get_args(){
		return this->args;
	}
	std::string get_name(){
		return this->name;
	}
	void accept(Visitor *v){
		v->visit(this);
	}
	~FuncCall(){}
private:
	std::string name;
	Node *args;

	void set_name(std::string name){
		this->name = name;
	}
	void set_args(Node *args){
		this->args = args;
	}
};


class Arg: public Statement{
public:
	Arg(Node* args){
		set_args(args);
	}
	Node* get_args(){
		return this->args;
	}
	void accept(Visitor *v){
		v->visit(this);
	}
	~Arg(){}
private:
	Node *args;
	void set_args(Node *args){
		this->args = args;
	}	
};


class VarDec: public Node{
public:
	VarDec(std::string type, Node *mdim, std::string name, Node *exp){
		set_type(type);
		set_mdim(mdim);
		set_name(name);
		set_exp(exp);
	}
	std::string get_type(){
		return this->type;
	}
	std::string get_name(){
		return this->name;
	}
	Node* get_mdim(){
		return this->mdim;
	}
	Node* get_exp(){
		return this->exp;
	}
	void accept(Visitor *v){
		v->visit(this);
	}
private:
	Node *mdim, *exp;
	std::string type,name;
	void set_type(std::string type){
		this->type = type;
	}
	void set_name(std::string name){
		this->name = name;
	}
	void set_mdim(Node *mdim){
		this->mdim = mdim;
	}
	void set_exp(Node *exp){
		this->exp = exp;
	}
	
};

class ProgramNode: public Node{
public:
	ProgramNode(Node *element, Node *list){
		set_element(element);
		set_list(list);
	}
	Node *get_element(){
		return this->element;
	}
	Node *get_list(){
		return this->list;
	}
	void accept(Visitor *v){
		v->visit(this);
	}
	~ProgramNode(){}
private:
	Node *element, *list;
	void set_element(Node *element){
		this->element = element;
	}
	void set_list(Node *list){
		this->list = list;
	}
};

class Imports: public Node{
public:
	Imports(Node* import){
		set_import(import);
	}
	Node* get_import(){
		return this->import;
	}
	void accept(Visitor *v){
		v->visit(this);
	}
	~Imports(){}
private:
	Node* import;
	void set_import(Node* import){
		this->import = import;
	}
};

class StartNode: public Node{
public:
	StartNode(Node *imports, Node *defns){
		set_imports(imports);
		set_defns(defns);
	}
	Node *get_imports(){
		return this->imports;
	}
	Node *get_defns(){
		return this->defns;
	}
	void accept(Visitor *v){
		v->visit(this);
	}
	~StartNode(){}
private:
	Node *imports, *defns;
	void set_imports(Node *imports){
		this->imports = imports;
	}
	void set_defns(Node *defns){
		this->defns = defns;
	}
};


#endif