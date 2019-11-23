#include "ast.hh"
#include "visitor.hh"
#include <map>
#include <stack>
#include <iostream>

#ifndef INTERPRET_VISITOR_H
#define INTERPRET_VISITOR_H

struct data{

	int *ival;
	std::string *sval;
	float *fval;
	char *cval;
	bool *bval;
	std::vector<int> *iar;
	std::vector<float> *far;
	std::vector<bool> *bar;
	std::vector<int> *dims;

	void clear(){
		ival = NULL;
		sval = NULL;
		fval = NULL;
		cval = NULL;
		bval = NULL;
		iar = NULL;
		far = NULL;
		bar = NULL;
		dims = NULL;
	}

	data(){
		clear();
	}
	data(const data &d2){
		clear();
		ival = d2.ival ;
		sval = d2.sval ;
		fval = d2.fval ;
		cval = d2.cval ;
		bval = d2.bval ;
		iar = d2.iar ;
		far = d2.far ;
		bar = d2.bar ;
		dims = d2.dims ;
	}
	void operator = (const data &d2) { 
		clear();
		ival = d2.ival ;
		sval = d2.sval ;
		fval = d2.fval ;
		cval = d2.cval ;
		bval = d2.bval ;
		iar = d2.iar ;
		far = d2.far ;
		bar = d2.bar ;
		dims = d2.dims ;
	}
	data(int a){
		clear();
		ival = new int;
		*ival = a;
	}
	data(float a){
		clear();
		fval = new float;
		*fval = a;
	}
	data(char a){
		clear();
		cval = new char;
		*cval = a;
	}
	data(bool a){
		clear();
		bval = new bool;
		*bval = a;
	}
	
	data(std::string a, int dim, std::vector<int> &dimss){
		clear();
		sval = new std::string();
		sval->resize(dim);
		for(int i=1;i<(int)a.size()-1;i++){
			((*sval)[i]) = a[i];
		}
		dims = new std::vector<int>(dimss);
		// std::cout<<sval<<std::endl;
		// std::string tmp = *sval;
		// std::cout<<"still ok\n";
		// std::cout<<(*sval)<<std::endl;

	}
	data(int a, int dim, std::vector<int> &dimss){
		clear();
		iar = new std::vector<int>(dim);
		dims = new std::vector<int>(dimss);
	}
	data(bool a, int dim, std::vector<int> &dimss){
		clear();
		bar = new std::vector<bool>(dim);
		dims = new std::vector<int>(dimss);
	}
	
	data(float a, int dim, std::vector<int> &dimss){
		clear();
		far = new std::vector<float>(dim);
		dims = new std::vector<int>(dimss);
	}
	void destroy(){
		if(ival != NULL){
			delete ival;
		}
		if(bval != NULL){
			delete bval;
		}
		if(fval != NULL){
			delete fval;
		}
		if(sval != NULL){
			delete sval;
		}
		if(cval != NULL){
			delete cval;
		}
		if(iar != NULL){
			delete iar;
		}
		if(far != NULL){
			delete far;
		}
		if(bar != NULL){
			delete bar;
		}
		if(dims != NULL){
			delete dims;
		}
		clear();
	}
};

class InterpretVisitor: public Visitor{
public:
	InterpretVisitor(){
		std::map<std::string,data> ntable;
		this->symbol_table.push(ntable);
	}
	void visit(StartNode* node){
		if(node->get_imports() != NULL){
			traverse(node->get_imports());
		}
		if(node->get_defns() != NULL){
			traverse(node->get_defns());
		}
	}
	void visit(Imports* node){}
	void visit(FuncDef* node){
		if(node->get_name() == "main"){
			this->retType.push("int");
			for(auto nx:*(node->get_exec())){
				nx->accept(this);
				if(this->ret){
					this->ret = 0;
					break;
				}
			}
		}
		else{
			this->function_table[node->get_name()] = node;
		}
	}
	void visit(VarDec* node){
		std::string type = node->get_type();
		int dim = 1;
		std::vector<int> dims;
		if(node->get_mdim() != NULL){
			for(auto nx:*(node->get_mdim())){
				nx->accept(this);
				if(this->exp->ival == NULL){
					error("Array Size must be integer");
				}
				dim *= *(this->exp->ival);
				dims.push_back(*(this->exp->ival));
			}
		}
		if(type == "int"){
			if(dim == 1){
				if(node->get_exp() != NULL){
					node->get_exp()->accept(this);
					this->symbol_table.top()[node->get_name()] = data(*(this->exp->ival));
				}
				else{
					this->symbol_table.top()[node->get_name()] = data(0);
					// std::cout<<"Got Here\n";
				}
			}
			else{
				if(node->get_exp() != NULL){
					error("Attempying to assign an Integer Array");
				}
				else{
					this->symbol_table.top()[node->get_name()] = data(0, dim, dims);
				}
				
			}
		}
		if(type == "bool"){
			if(dim == 1){
				if(node->get_exp() != NULL){
					node->get_exp()->accept(this);
					this->symbol_table.top()[node->get_name()] = data(*(this->exp->bval));
				}
				else{
					this->symbol_table.top()[node->get_name()] = data(false);
					// std::cout<<"Got Here\n";
				}
			}
			else{
				if(node->get_exp() != NULL){
					error("Attempying to assign a boolean Array");
				}
				else{
					this->symbol_table.top()[node->get_name()] = data(false, dim, dims);
				}
				
			}
		}
		
		if(type == "float"){
			if(dim == 1){
				if(node->get_exp() != NULL){
					node->get_exp()->accept(this);
					this->symbol_table.top()[node->get_name()] = data(*(this->exp->fval));
				}
				else{
					this->symbol_table.top()[node->get_name()] = data((float)0.0);
				}
			}
			else{		
				if(node->get_exp() != NULL){
					error("Attempting to assign a Float Array");
				}
				else{
					this->symbol_table.top()[node->get_name()] = data((float)0.0, dim, dims);
				}
			}
		}
		if(type == "char"){
			if(dim == 1){
				if(node->get_exp() != NULL){
					node->get_exp()->accept(this);
					this->symbol_table.top()[node->get_name()] = data(*(this->exp->cval));
				}
				else{
					this->symbol_table.top()[node->get_name()] = data((char)0);
				}
			}
			else{
				if(node->get_exp() != NULL){
					node->get_exp()->accept(this);
					if(this->exp->sval == NULL){
						error("Incorrectly assigning char array");
					}
					this->symbol_table.top()[node->get_name()] = data(*(this->exp->sval),dim, dims);
				}
				else{
					this->symbol_table.top()[node->get_name()] = data(std::string(0), dim, dims);
				}
			}
		}
	}

	void visit(Name* node){
		
		if(this->symbol_table.top().count(node->get_name()) == 0){
			error(node->get_name()+" not declared");
		}
		
		this->alloced.push_back(this->symbol_table.top()[node->get_name()]);
		this->exp = &this->alloced.back();
	}
	void visit(Float* node){
		
		
		this->alloced.push_back( data(node->get_val()));
		this->exp = &this->alloced.back();
	}
	void visit(Int* node){
		
		
		this->alloced.push_back( data(node->get_val()));
		this->exp = &this->alloced.back();
	}
	void visit(Bool* node){
		if(node->get_val() == "true"){
			
			this->alloced.push_back( data(true));
			this->exp = &this->alloced.back();
		}
		else{
			
			this->alloced.push_back( data(false));
			this->exp = &this->alloced.back();
		}
	}
	void visit(Char* node){
		
		char c;
		if(node->get_val()[0] == '\\' && node->get_val()[1] == 'n'){
			c = '\n';
		}
		else if(node->get_val()[0] == '\\' && node->get_val()[1] == 't'){
			c = '\t';
		}
		else if(node->get_val()[0] == '\\' && node->get_val()[1] == '0'){
			c = '\0';
		}
		else{
			c = node->get_val()[0];
		}
		
		this->alloced.push_back( data(c));
		this->exp = &this->alloced.back();
	}
	void visit(MultiDimArr* node){
		
		if(this->symbol_table.top().count(node->get_name()) == 0){
			error(node->get_name()+" not declared");
		}
		data cur = this->symbol_table.top()[node->get_name()];
		int prod = 1;
		for(int i:*(cur.dims)) prod*=i;
		int index = 0;
		int i = 0;
		if(node->get_sq() != NULL){
			for(auto nx:*(node->get_sq())){
				if(i > (cur.dims)->size()){
					error("Too many dimensions");
				}
				nx->accept(this);
				if(this->exp->ival == NULL){
					error("Array Index must be integer");
				}
				if(*(this->exp->ival) >= (*(cur.dims))[i]){
					error("Out of bound array access");
				}
				prod /= (*(cur.dims))[i];
				index += *(this->exp->ival)*(prod);
				i++;
			}
		}
		if(cur.iar != NULL){
			
			this->alloced.push_back( data((*(cur.iar))[index]));
			this->exp = &this->alloced.back();
		}
		else if(cur.far != NULL){
			
			this->alloced.push_back( data((*(cur.far))[index]));
			this->exp = &this->alloced.back();
		}
		else if(cur.bar != NULL){
			
			this->alloced.push_back( data((*(cur.bar))[index]));
			this->exp = &this->alloced.back();
		}
		else if(cur.sval != NULL){
			
			this->alloced.push_back( data((*(cur.sval))[index]));
			this->exp = &this->alloced.back();
		}
	}
	void visit(UnaryTerm* node){
		
		if(node->get_term() != NULL){
			node->get_term()->accept(this);
		}
		
		if(node->get_op() == "-"){
			if(this->exp->ival != NULL){
				*(this->exp->ival) = -*(this->exp->ival);
			}
			else if(this->exp->fval != NULL){
				*(this->exp->fval) = -*(this->exp->fval);
			}
			else{
				error("Can't negate non int/float");
			}
		}
		if(node->get_op() == "!"){
			if(this->exp->ival != NULL){
				*(this->exp->ival) = !*(this->exp->ival);
			}
			else if(this->exp->fval != NULL){
				*(this->exp->fval) = !*(this->exp->fval);
			}
			else if(this->exp->bval != NULL){
				*(this->exp->bval) = !*(this->exp->bval);
			}
			else{
				error("Can't not non int/float/bool");
			}
		}
	}
	void visit(BinaryOperator* node){

		if(node->get_right() != NULL){
			node->get_right()->accept(this);
		}
		data right = *this->exp;

		if(node->get_left() != NULL){
			node->get_left()->accept(this);
		}


		if(node->get_op() == "+"){
			if(this->exp->ival != NULL && right.ival != NULL){
				
				this->alloced.push_back( data(*(this->exp->ival) + *(right.ival)));
				this->exp = &this->alloced.back();
			}
			else if(this->exp->fval != NULL && right.fval != NULL){
				
				this->alloced.push_back( data(*(this->exp->fval) + *(right.fval)));
				this->exp = &this->alloced.back();
			}
			else{
				error("Cannot add non int/float");
			}
		}
		if(node->get_op() == "-"){
			if(this->exp->ival != NULL && right.ival != NULL){
				
				this->alloced.push_back( data(*(this->exp->ival) - *(right.ival)));
				this->exp = &this->alloced.back();
			}
			else if(this->exp->fval != NULL && right.fval != NULL){
				
				this->alloced.push_back( data(*(this->exp->fval) - *(right.fval)));
				this->exp = &this->alloced.back();
			}
			else{
				error("Cannot sub non int/float");
			}
		}
		if(node->get_op() == "*"){
			if(this->exp->ival != NULL && right.ival != NULL){
				
				this->alloced.push_back( data(*(this->exp->ival) * *(right.ival)));
				this->exp = &this->alloced.back();
			}
			else if(this->exp->fval != NULL && right.fval != NULL){
				
				this->alloced.push_back( data(*(this->exp->fval) * *(right.fval)));
				this->exp = &this->alloced.back();
			}
			else{
				error("Cannot mul non int/float");
			}
		}
		if(node->get_op() == "/"){
			if(this->exp->ival != NULL && right.ival != NULL){
				
				this->alloced.push_back( data(*(this->exp->ival) / *(right.ival)));
				this->exp = &this->alloced.back();
			}
			else if(this->exp->fval != NULL && right.fval != NULL){
				
				this->alloced.push_back( data(*(this->exp->fval) / *(right.fval)));
				this->exp = &this->alloced.back();
			}
			else{
				error("Cannot div non int/float");
			}
		}
		if(node->get_op() == "%"){
			if(this->exp->ival != NULL && right.ival != NULL){
				
				this->alloced.push_back( data(*(this->exp->ival) %  *(right.ival)));
				this->exp = &this->alloced.back();
			}
			else{
				error("Cannot mod non int");
			}
		}
		if(node->get_op() == "=="){
			if(this->exp->ival != NULL && right.ival != NULL){
				
				this->alloced.push_back( data((int)(*(this->exp->ival) == *(right.ival))));
				this->exp = &this->alloced.back();
			}
			else if(this->exp->ival != NULL && right.bval != NULL){
				
				this->alloced.push_back( data((int)(*(this->exp->ival) == *(right.bval))));
				this->exp = &this->alloced.back();
			}
			else if(this->exp->bval != NULL && right.ival != NULL){
				
				this->alloced.push_back( data((int)(*(this->exp->bval) == *(right.ival))));
				this->exp = &this->alloced.back();
			}
			else if(this->exp->ival != NULL && right.fval != NULL){
				
				this->alloced.push_back( data((int)(*(this->exp->ival) == *(right.fval))));
				this->exp = &this->alloced.back();
			}
			else if(this->exp->fval != NULL && right.ival != NULL){
				
				this->alloced.push_back( data((int)(*(this->exp->fval) == *(right.ival))));
				this->exp = &this->alloced.back();
			}
			else if(this->exp->fval != NULL && right.fval != NULL){
				
				this->alloced.push_back( data((int)(*(this->exp->fval) == *(right.fval))));
				this->exp = &this->alloced.back();
			}
			else if(this->exp->bval != NULL && right.bval != NULL){
				
				this->alloced.push_back( data((int)(*(this->exp->bval) == *(right.bval))));
				this->exp = &this->alloced.back();
			}
			else if(this->exp->cval != NULL && right.cval != NULL){
				
				this->alloced.push_back( data((int)(*(this->exp->cval) == *(right.cval))));
				this->exp = &this->alloced.back();
			}
			else{
				error("Cannot compare different types");
			}
		}
		if(node->get_op() == ">="){
			if(this->exp->ival != NULL && right.ival != NULL){
				
				this->alloced.push_back( data((int)(*(this->exp->ival) >= *(right.ival))));
				this->exp = &this->alloced.back();
			}
			else if(this->exp->ival != NULL && right.bval != NULL){
				
				this->alloced.push_back( data((int)(*(this->exp->ival) >= *(right.bval))));
				this->exp = &this->alloced.back();
			}
			else if(this->exp->bval != NULL && right.ival != NULL){
				
				this->alloced.push_back( data((int)(*(this->exp->bval) >= *(right.ival))));
				this->exp = &this->alloced.back();
			}
			else if(this->exp->ival != NULL && right.fval != NULL){
				
				this->alloced.push_back( data((int)(*(this->exp->ival) >= *(right.fval))));
				this->exp = &this->alloced.back();
			}
			else if(this->exp->fval != NULL && right.ival != NULL){
				
				this->alloced.push_back( data((int)(*(this->exp->fval) >= *(right.ival))));
				this->exp = &this->alloced.back();
			}
			else if(this->exp->fval != NULL && right.fval != NULL){
				
				this->alloced.push_back( data((int)(*(this->exp->fval) >= *(right.fval))));
				this->exp = &this->alloced.back();
			}
			else if(this->exp->bval != NULL && right.bval != NULL){
				
				this->alloced.push_back( data((int)(*(this->exp->bval) >= *(right.bval))));
				this->exp = &this->alloced.back();
			}
			else if(this->exp->cval != NULL && right.cval != NULL){
				
				this->alloced.push_back( data((int)(*(this->exp->cval) >= *(right.cval))));
				this->exp = &this->alloced.back();
			}
			else{
				error("Cannot compare different types");
			}
		}
		if(node->get_op() == ">"){
			if(this->exp->ival != NULL && right.ival != NULL){
				
				this->alloced.push_back( data((int)(*(this->exp->ival) > *(right.ival))));
				this->exp = &this->alloced.back();
			}
			else if(this->exp->ival != NULL && right.bval != NULL){
				
				this->alloced.push_back( data((int)(*(this->exp->ival) > *(right.bval))));
				this->exp = &this->alloced.back();
			}
			else if(this->exp->bval != NULL && right.ival != NULL){
				
				this->alloced.push_back( data((int)(*(this->exp->bval) > *(right.ival))));
				this->exp = &this->alloced.back();
			}
			else if(this->exp->ival != NULL && right.fval != NULL){
				
				this->alloced.push_back( data((int)(*(this->exp->ival) > *(right.fval))));
				this->exp = &this->alloced.back();
			}
			else if(this->exp->fval != NULL && right.ival != NULL){
				
				this->alloced.push_back( data((int)(*(this->exp->fval) > *(right.ival))));
				this->exp = &this->alloced.back();
			}
			else if(this->exp->fval != NULL && right.fval != NULL){
				
				this->alloced.push_back( data((int)(*(this->exp->fval) > *(right.fval))));
				this->exp = &this->alloced.back();
			}
			else if(this->exp->bval != NULL && right.bval != NULL){
				
				this->alloced.push_back( data((int)(*(this->exp->bval) > *(right.bval))));
				this->exp = &this->alloced.back();
			}
			else if(this->exp->cval != NULL && right.cval != NULL){
				
				this->alloced.push_back( data((int)(*(this->exp->cval) > *(right.cval))));
				this->exp = &this->alloced.back();
			}
			else{
				error("Cannot compare different types");
			}
		}
		if(node->get_op() == "<="){
			if(this->exp->ival != NULL && right.ival != NULL){
				
				this->alloced.push_back( data((int)(*(this->exp->ival) <= *(right.ival))));
				this->exp = &this->alloced.back();
			}
			else if(this->exp->ival != NULL && right.bval != NULL){
				
				this->alloced.push_back( data((int)(*(this->exp->ival) <= *(right.bval))));
				this->exp = &this->alloced.back();
			}
			else if(this->exp->bval != NULL && right.ival != NULL){
				
				this->alloced.push_back( data((int)(*(this->exp->bval) <= *(right.ival))));
				this->exp = &this->alloced.back();
			}
			else if(this->exp->ival != NULL && right.fval != NULL){
				
				this->alloced.push_back( data((int)(*(this->exp->ival) <= *(right.fval))));
				this->exp = &this->alloced.back();
			}
			else if(this->exp->fval != NULL && right.ival != NULL){
				
				this->alloced.push_back( data((int)(*(this->exp->fval) <= *(right.ival))));
				this->exp = &this->alloced.back();
			}
			else if(this->exp->fval != NULL && right.fval != NULL){
				
				this->alloced.push_back( data((int)(*(this->exp->fval) <= *(right.fval))));
				this->exp = &this->alloced.back();
			}
			else if(this->exp->bval != NULL && right.bval != NULL){
				
				this->alloced.push_back( data((int)(*(this->exp->bval) <= *(right.bval))));
				this->exp = &this->alloced.back();
			}
			else if(this->exp->cval != NULL && right.cval != NULL){
				
				this->alloced.push_back( data((int)(*(this->exp->cval) <= *(right.cval))));
				this->exp = &this->alloced.back();
			}
			else{
				error("Cannot compare different types");
			}
		}
		if(node->get_op() == "<"){
			if(this->exp->ival != NULL && right.ival != NULL){
				
				this->alloced.push_back( data((int)(*(this->exp->ival) < *(right.ival))));
				this->exp = &this->alloced.back();
			}
			else if(this->exp->ival != NULL && right.bval != NULL){
				
				this->alloced.push_back( data((int)(*(this->exp->ival) < *(right.bval))));
				this->exp = &this->alloced.back();
			}
			else if(this->exp->bval != NULL && right.ival != NULL){
				
				this->alloced.push_back( data((int)(*(this->exp->bval) < *(right.ival))));
				this->exp = &this->alloced.back();
			}
			else if(this->exp->ival != NULL && right.fval != NULL){
				
				this->alloced.push_back( data((int)(*(this->exp->ival) < *(right.fval))));
				this->exp = &this->alloced.back();
			}
			else if(this->exp->fval != NULL && right.ival != NULL){
				
				this->alloced.push_back( data((int)(*(this->exp->fval) < *(right.ival))));
				this->exp = &this->alloced.back();
			}
			else if(this->exp->fval != NULL && right.fval != NULL){
				
				this->alloced.push_back( data((int)(*(this->exp->fval) < *(right.fval))));
				this->exp = &this->alloced.back();
			}
			else if(this->exp->bval != NULL && right.bval != NULL){
				
				this->alloced.push_back( data((int)(*(this->exp->bval) < *(right.bval))));
				this->exp = &this->alloced.back();
			}
			else if(this->exp->cval != NULL && right.cval != NULL){
				
				this->alloced.push_back( data((int)(*(this->exp->cval) < *(right.cval))));
				this->exp = &this->alloced.back();
			}
			else{
				error("Cannot compare different types");
			}
		}
		if(node->get_op() == "!="){
			if(this->exp->ival != NULL && right.ival != NULL){
				
				this->alloced.push_back( data((int)(*(this->exp->ival) != *(right.ival))));
				this->exp = &this->alloced.back();
			}
			else if(this->exp->ival != NULL && right.bval != NULL){
				
				this->alloced.push_back( data((int)(*(this->exp->ival) != *(right.bval))));
				this->exp = &this->alloced.back();
			}
			else if(this->exp->bval != NULL && right.ival != NULL){
				
				this->alloced.push_back( data((int)(*(this->exp->bval) != *(right.ival))));
				this->exp = &this->alloced.back();
			}
			else if(this->exp->ival != NULL && right.fval != NULL){
				
				this->alloced.push_back( data((int)(*(this->exp->ival) != *(right.fval))));
				this->exp = &this->alloced.back();
			}
			else if(this->exp->fval != NULL && right.ival != NULL){
				
				this->alloced.push_back( data((int)(*(this->exp->fval) != *(right.ival))));
				this->exp = &this->alloced.back();
			}
			else if(this->exp->fval != NULL && right.fval != NULL){
				
				this->alloced.push_back( data((int)(*(this->exp->fval) != *(right.fval))));
				this->exp = &this->alloced.back();
			}
			else if(this->exp->bval != NULL && right.bval != NULL){
				
				this->alloced.push_back( data((int)(*(this->exp->bval) != *(right.bval))));
				this->exp = &this->alloced.back();
			}
			else if(this->exp->cval != NULL && right.cval != NULL){
				
				this->alloced.push_back( data((int)(*(this->exp->cval) != *(right.cval))));
				this->exp = &this->alloced.back();
			}
			else{
				error("Cannot compare different types");
			}
		}
		if(node->get_op() == "&"){
			if(this->exp->ival != NULL && right.ival != NULL){
				
				this->alloced.push_back( data((int)(*(this->exp->ival) && *(right.ival))));
				this->exp = &this->alloced.back();
			}
			else if(this->exp->bval != NULL && right.bval != NULL){
				
				this->alloced.push_back( data((int)(*(this->exp->bval) && *(right.bval))));
				this->exp = &this->alloced.back();
			}
			else{
				error("Attempting AND on non integer/bool");
			}
			
		}
		if(node->get_op() == "|"){
			if(this->exp->ival != NULL && right.ival != NULL){
				
				this->alloced.push_back( data((int)(*(this->exp->ival) || *(right.ival))));
				this->exp = &this->alloced.back();
			}
			else if(this->exp->bval != NULL && right.bval != NULL){
				
				this->alloced.push_back( data((int)(*(this->exp->bval) || *(right.bval))));
				this->exp = &this->alloced.back();
			}
			else{
				error("Attempting OR on non integer/bool");
			}
				
		}
	}
	void visit(TernaryOperator* node){
		
		if(node->get_left() != NULL){
			node->get_left()->accept(this);
		}
		
		if(this->exp->ival != NULL){
			if(*(this->exp->ival)){
				if(node->get_middle() != NULL){
					node->get_middle()->accept(this);
				}
			}
			else{
				if(node->get_right() != NULL){
					node->get_right()->accept(this);
				}
			}
		}
		else if(this->exp->bval != NULL){
			if(*(this->exp->bval)){
				if(node->get_middle() != NULL){
					node->get_middle()->accept(this);
				}
			}
			else{
				if(node->get_right() != NULL){
					node->get_right()->accept(this);
				}
			}
		}
		else{
			error("Attempting Ternary on non integer/bool");
		}
	}
	void visit(Square* node){
		
		if(node->get_exp() != NULL){
			node->get_exp()->accept(this);
		}
	}
	void visit(FuncCall* node){
		std::map<std::string, data> ntable;
		if(this->function_table.count(node->get_name()) == 0){
			error("Undeclared Function "+node->get_name());
		}
		FuncDef *func = this->function_table[node->get_name()];
		if(node->get_args() != NULL && func->get_params() != NULL){
			if(node->get_args()->size() != func->get_params()->size()){
				error("func call doesn't match definition");			
			}
			for(int i=0;i<node->get_args()->size();i++){
				Arg *nx = (*(node->get_args()))[i];
				Param *px = (*(func->get_params()))[i];
				nx->accept(this);
				if(this->exp->ival != NULL && px->get_type() == "int"
				|| this->exp->cval != NULL && px->get_type() == "char"
				|| this->exp->fval != NULL && px->get_type() == "float"
				|| this->exp->bval != NULL && px->get_type() == "bool"
				|| this->exp->iar != NULL && px->get_type() == "int" && px->get_multidim() != NULL
				|| this->exp->far != NULL && px->get_type() == "float" && px->get_multidim() != NULL
				|| this->exp->bar != NULL && px->get_type() == "bool" && px->get_multidim() != NULL
				|| this->exp->sval != NULL && px->get_type() == "char" && px->get_multidim() != NULL){
					if(ntable.count(px->get_name()) == 1){
						error("Redeclaration of "+px->get_name());
					}
					ntable[px->get_name()] = *this->exp;
				}
				else{
					error("func call doesn't match definition");
				}	
			}

		}
		else{
			error("func call doesn't match definition");
		}
		this->symbol_table.push(ntable);
		this->retType.push(func->get_type());
		for(auto nx:*func->get_exec()){
			nx->accept(this);
			if(this->ret){
				this->ret = 0;
				break;
			}
		}
		this->symbol_table.pop();

	}
	void visit(Read* node){
		if(this->symbol_table.top().count(node->get_var()) == 0){
			error("Reading undeclared var");
		}
		data *rhs = &(this->symbol_table.top()[node->get_var()]);
		if(rhs->ival != NULL){
			std::cin>>*(rhs->ival);
		}
		if(rhs->fval != NULL){
			std::cin>>*(rhs->fval);
		}
		if(rhs->cval != NULL){
			std::cin>>*(rhs->cval);
		}
		if(rhs->bval != NULL){
			std::cin>>*(rhs->bval);
		}
	}
	void visit(Print* node){

		node->get_arg()->accept(this);
		
		
		if(this->exp->ival != NULL){
			std::cout<<*(this->exp->ival);
		}
		if(this->exp->fval != NULL){
			std::cout<<*(this->exp->fval);
		}
		if(this->exp->cval != NULL){
			std::cout<<*(this->exp->cval);
		}
		if(this->exp->sval != NULL){
			std::cout<<*(this->exp->sval);
		// std::cout<<"Ok"<<std::endl;
		}
		if(this->exp->bval != NULL){
			std::cout<<*(this->exp->bval);
		}
	}
	void visit(String* node){
		
		std::string lit = node->get_val(); 
		std::string lit2;
		for(int i=0;i<lit.size();i++){
			if(lit[i] == '\\'){
				if(i != (int)lit.size() -1 && lit[i+1] == 'n'){
					lit2+='\n';
					i++;
				}
				else if(i != (int)lit.size() -1 && lit[i+1] == 't'){
					lit2+='\t';
					i++;
				}
				else if(i != (int)lit.size() -1 && lit[i+1] == '0'){
					lit2+='\0';
					i++;
				}
				else{
					lit2+='\\';
				}
			}
			else{
				lit2+=lit[i];
			}
		}
		lit = lit2;
		std::vector<int> dims; dims.push_back(lit.size());
		
		this->alloced.push_back( data(lit, lit.size(), dims));
		this->exp = &this->alloced.back();
		
	}
	void visit(Arg* node){
		
		if(node->get_args() != NULL){
			node->get_args()->accept(this);
		}
	}
	void visit(IfStmt* node){
		
		if(node->get_cond() != NULL){
			node->get_cond()->accept(this);
		}
		data cond = *this->exp;
		if(cond.ival == NULL && cond.bval == NULL){
			error("Condition doesn't evaluate to bool");
		}
		if(cond.ival != NULL && *(cond.ival) && node->get_if_blk() != NULL){
			traverse(node->get_if_blk());
		}
		else if(cond.ival != NULL && !*(cond.ival) && node->get_else_blk() != NULL){
			traverse(node->get_else_blk());
		}
		if(cond.bval != NULL && *(cond.bval) && node->get_if_blk() != NULL){
			traverse(node->get_if_blk());
		}
		else if(cond.bval != NULL && !*(cond.bval) && node->get_else_blk() != NULL){
			traverse(node->get_else_blk());
		}
		
	}
	void visit(For* node){
		
		if(node->get_init() != NULL){
			node->get_init()->accept(this);
		}
		this->inLoop = 1;
		while(1){
			if(node->get_cond() != NULL){
				node->get_cond()->accept(this);
			}
			data cond = *this->exp;
			if(cond.ival == NULL){
				error("Condition doesn't evaluate to bool");
			}
			if(!*(cond.ival)) break;

			if(node->get_exec() != NULL){
				for(auto nx:*node->get_exec()){
					nx->accept(this);
					if(this->br || this->cont){
						this->cont = 0;
						break;
					}
				}
			}

			if(this->br){
				this->br = 0;
				break;
			}

			if(node->get_increment() != NULL){
				node->get_increment()->accept(this);
			}
		}
		this->inLoop = 0;
	}
	void visit(While* node){
		
		this->inLoop = 1;
		while(1){
			if(node->get_cond() != NULL){
				node->get_cond()->accept(this);
			}
			data cond = *this->exp;
			if(cond.ival == NULL){
				error("Condition doesn't evaluate to bool");
			}
			if(!*cond.ival) break;

			if(node->get_exec() != NULL){
				for(auto nx:*node->get_exec()){
					nx->accept(this);
					if(this->br || this->cont){
						this->cont = 0;
						break;
					}
				}
			}
			if(this->br){
				this->br = 0;
				break;
			}
		}	
		this->inLoop = 0;
	}
	void visit(ArrayAssign* node){
	
		if(this->symbol_table.top().count(node->get_name()) == 0){
			error(node->get_name()+" not declared");
		}
		data cur = this->symbol_table.top()[node->get_name()];
		int prod = 1;
		for(int i:*(cur.dims)) prod*=i;
		int index = 0;
		int i = 0;
		if(node->get_dims() != NULL){
			for(auto nx:*node->get_dims()){
				if(i > (*(cur.dims)).size()){
					error("Too many dimensions");
				}
				nx->accept(this);
				if(this->exp->ival == NULL){
					error("Array Index must be integer");
				}
				if(*(this->exp->ival) >= (*(cur.dims))[i]){
					error("Out of bound array access");
				}
				prod /= (*(cur.dims))[i];
				index += *(this->exp->ival)*(prod);
				i++;
			}
		}
		if(node->get_right() != NULL){
			node->get_right()->accept(this);
		}
		if(cur.iar != NULL && this->exp->ival != NULL){
			(*(this->symbol_table.top()[node->get_name()].iar))[index] = *(this->exp->ival);
		}
		else if(cur.far != NULL && this->exp->fval != NULL){
			(*(this->symbol_table.top()[node->get_name()].far))[index] = *(this->exp->fval);
		}
		else if(cur.bar != NULL && this->exp->bval != NULL){
			(*(this->symbol_table.top()[node->get_name()].bar))[index] = *(this->exp->bval);
		}
		else if(cur.sval != NULL && this->exp->cval != NULL){
			(*(this->symbol_table.top()[node->get_name()].sval))[index] = *(this->exp->cval);
		}	
		else{
			error("Invalid Array Assignment");
		}
		
	}
	void visit(Assign* node){
		
		if(this->symbol_table.top().count(node->get_name()) == 0){
			error(node->get_name()+" not declared");
		}
		data cur = this->symbol_table.top()[node->get_name()];
		std::string op = node->get_op();
		if(node->get_right() != NULL){
			node->get_right()->accept(this);
		}
		
		if (op ==  "="){
			if(cur.ival != NULL && this->exp->ival != NULL){
				*(this->symbol_table.top()[node->get_name()].ival) = *(this->exp->ival);
			}
			else if(cur.fval != NULL && this->exp->fval != NULL){
				*(this->symbol_table.top()[node->get_name()].fval) = *(this->exp->fval);
			}
			else if(cur.bval != NULL && this->exp->bval != NULL){
				*(this->symbol_table.top()[node->get_name()].bval) = *(this->exp->bval);
			}
			else if(cur.cval != NULL && this->exp->cval != NULL){
				*(this->symbol_table.top()[node->get_name()].cval) = *(this->exp->cval);
			}
			else{
				error("Invalid Assignment");
			}
		}
		if (op ==  "+="){
			if(cur.ival != NULL && this->exp->ival != NULL){
				*(this->symbol_table.top()[node->get_name()].ival) += *(this->exp->ival);
			}
			else if(cur.fval != NULL && this->exp->fval != NULL){
				*(this->symbol_table.top()[node->get_name()].fval) += *(this->exp->fval);
			}
			else{
				error("Invalid Assignment");
			}
		}
		if (op ==  "-="){
			if(cur.ival != NULL && this->exp->ival != NULL){
				*(this->symbol_table.top()[node->get_name()].ival) -= *(this->exp->ival);
			}
			else if(cur.fval != NULL && this->exp->fval != NULL){
				*(this->symbol_table.top()[node->get_name()].fval) -= *(this->exp->fval);
			}
			else{
				error("Invalid Assignment");
			}
		}
		if (op ==  "*="){
			if(cur.ival != NULL && this->exp->ival != NULL){
				*(this->symbol_table.top()[node->get_name()].ival) *= *(this->exp->ival);
			}
			else if(cur.fval != NULL && this->exp->fval != NULL){
				*(this->symbol_table.top()[node->get_name()].fval) *= *(this->exp->fval);
			}
			else{
				error("Invalid Assignment");
			}
		}
		if (op ==  "/="){
			if(cur.ival != NULL && this->exp->ival != NULL){
				*(this->symbol_table.top()[node->get_name()].ival) /= *(this->exp->ival);
			}
			else if(cur.fval != NULL && this->exp->fval != NULL){
				*(this->symbol_table.top()[node->get_name()].fval) /= *(this->exp->fval);
			}
			else{
				error("Invalid Assignment");
			}
		}
		if (op ==  "%="){
			if(cur.ival != NULL && this->exp->ival != NULL){
				*(this->symbol_table.top()[node->get_name()].ival) %= *(this->exp->ival);
			}
			else{
				error("Invalid Assignment");
			}
		}
	}
	void visit(Break* node){
		
		if(!this->inLoop){
			error("break used outside loop");
		}
		this->br = 1;
	}
	void visit(Continue* node){
		
		if(!this->inLoop){
			error("continue used outside loop");
		}
		this->cont = 1;
	}
	void visit(Return* node){
		
		if(node->get_ret() != NULL){
			if(this->retType.top() == "void"){
				error("Attempting to return non void in void function");
			}
			node->get_ret()->accept(this);
		}
		if(this->retType.top() == "void"){

		}
		else if(this->exp->ival != NULL && this->retType.top() == "int"){

		}
		else if(this->exp->cval != NULL && this->retType.top() == "char"){

		}
		else if(this->exp->fval != NULL && this->retType.top() == "float"){

		}
		else if(this->exp->bval != NULL && this->retType.top() == "bool"){

		}
		else{
			error("Return value doesn't match return type");
		}
		this->ret = 1;
	}
	void visit(Param* node){
		
		std::cout<<node->get_type();
		if(node->get_multidim() != NULL){
			traverse(node->get_multidim());
		}
		std::cout<<" "<<node->get_name();
	}
			
	void visit(ParenExp* node){
		
		if(node->get_exp() != NULL){
			node->get_exp()->accept(this);
		}		
	}
	~InterpretVisitor(){
		for(int i=0;i<alloced.size();i++){
			alloced[i].destroy();
		}
	}
private:
	std::stack<std::map<std::string, data> > symbol_table;
	std::map<std::string, FuncDef*> function_table;

	std::vector<data> alloced;
	data *exp;

	bool br, cont, inLoop, ret;
	std::stack<std::string> retType;

	template <class T>
	void traverse(std::vector<T> *a){
		for(auto nx:*a){
			nx->accept(this);
		}
	}
	void error(std::string message){
		std::cerr<<"Fatal: "<<message<<std::endl;
		exit(1);
	}

};

#endif