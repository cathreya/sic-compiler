#include "ast.hh"
#include "visitor.hh"
#include <iostream>

#ifndef PRINT_VISITOR_H
#define PRINT_VISITOR_H

class PrintVisitor: public Visitor{
public:
	PrintVisitor(){
		this->layer = 0;
	}
	void visit(StartNode* node){
		
		if(node->get_imports() != NULL){
			traverse(node->get_imports(), "\n");
		}
		if(node->get_defns() != NULL){
			traverse(node->get_defns(), "\n");
		}
	}
	void visit(Imports* node){
		

		std::cout<<"import ";
		if(node->get_import() != NULL){
			node->get_import()->accept(this);
		}
		std::cout<<std::endl;
		// std::cout<<"Imports"<<std::endl;
	}
	void visit(FuncDef* node){
		

		std::cout<<node->get_type()<<" "<<node->get_name()<<"(";
		if(node->get_params() != NULL){
			traverse(node->get_params(),",");
		}
		std::cout<<"){";
		next();
		tabs();
		if(node->get_exec() != NULL){
			traverse(node->get_exec());
		}
		prev();
		tabs();
		std::cout<<"}";
		tabs();
		// std::cout<<node-<<std::endl;
	}
	void visit(VarDec* node){
		
		std::cout<<node->get_type();
		if(node->get_mdim() != NULL){
			traverse(node->get_mdim());
		}
		std::cout<<" "<<node->get_name();

		if(node->get_exp() != NULL){
			std::cout<<" = ";
			node->get_exp()->accept(this);
		}
		if(node->get_sc()){
			std::cout<<";";
			tabs();
		}
		// std::cout<<"VarDec"<<std::endl;
	}

	void visit(Name* node){
		
		std::cout<<node->get_name();
	}
	void visit(Float* node){
		
		std::cout<<node->get_val();
	}
	void visit(Int* node){
		
		std::cout<<node->get_val();
	}
	void visit(Bool* node){
		
		std::cout<<node->get_val();
	}
	void visit(Char* node){
		
		std::cout<<"\'"<<node->get_val()<<"\'";
	}
	void visit(MultiDimArr* node){
		
		std::cout<<node->get_name();
		if(node->get_sq() != NULL){
			traverse(node->get_sq());
		}
	}
	void visit(UnaryTerm* node){
		
		std::cout<<node->get_op()<<" ";
		if(node->get_term() != NULL){
			node->get_term()->accept(this);
		}
	}
	void visit(BinaryOperator* node){
		
		if(node->get_left() != NULL){
			node->get_left()->accept(this);
		}
		std::cout<<" "<<node->get_op()<<" ";
		if(node->get_right() != NULL){
			node->get_right()->accept(this);
		}
	}
	void visit(TernaryOperator* node){
		
		if(node->get_left() != NULL){
			node->get_left()->accept(this);
		}
		std::cout<<" ? ";
		if(node->get_middle() != NULL){
			node->get_middle()->accept(this);
		}
		std::cout<<" : ";
		if(node->get_right() != NULL){
			node->get_right()->accept(this);
		}
		// std::cout<<"Ternary"<<std::endl;
	}
	void visit(Square* node){
		
		std::cout<<"[";
		if(node->get_exp() != NULL){
			node->get_exp()->accept(this);
		}
		std::cout<<"]";
	}
	void visit(FuncCall* node){
		
		std::cout<<node->get_name()<<"(";
		if(node->get_args() != NULL){
			traverse(node->get_args(),",");
		}
		std::cout<<")";
		if(node->get_sc()){
			std::cout<<";";
			tabs();
		}
	}
	void visit(String* node){
		
		// std::cout<<"String"<<std::endl;
		std::cout<<node->get_val();
	}
	void visit(Arg* node){
		
		if(node->get_args() != NULL){
			node->get_args()->accept(this);
		}
	}
	void visit(IfStmt* node){
		
		std::cout<<"if(";
		if(node->get_cond() != NULL){
			node->get_cond()->accept(this);
		}
		std::cout<<"){";
		if(node->get_if_blk() != NULL){
			next();
			tabs();
			traverse(node->get_if_blk());
			prev();
		}
		tabs();
		std::cout<<"}";
		tabs();
		if(node->get_else_blk() != NULL){
			std::cout<<"else{";
			next();
			tabs();
			traverse(node->get_else_blk());
			prev();
			tabs();
			std::cout<<"}";
			tabs();
		}
	}
	void visit(For* node){
		
		std::cout<<"for(";
		if(node->get_init() != NULL){
			node->get_init()->accept(this);
		}
		std::cout<<"; ";
		if(node->get_cond() != NULL){
			node->get_cond()->accept(this);
		}
		std::cout<<"; ";
		if(node->get_increment() != NULL){
			node->get_increment()->accept(this);
		}
		std::cout<<"){";
		next();
		tabs();
		if(node->get_exec() != NULL){
			traverse(node->get_exec());
		}
		prev();
		tabs();
		std::cout<<"}";
		tabs();
	}
	void visit(While* node){
		
		std::cout<<"while(";
		if(node->get_cond() != NULL){
			node->get_cond()->accept(this);
		}
		std::cout<<"){";
		next();
		tabs();
		if(node->get_exec() != NULL){
			traverse(node->get_exec());
		}
		prev();
		tabs();
		std::cout<<"}";
		tabs();
	}
	void visit(ArrayAssign* node){
		
		std::cout<<node->get_name();
		if(node->get_dims() != NULL){
			traverse(node->get_dims());
		}
		std::cout<<" "<<node->get_op()<<" ";
		if(node->get_right() != NULL){
			node->get_right()->accept(this);
		}
		if(node->get_sc()){
			std::cout<<";";
			tabs();
		}
	}
	void visit(Assign* node){
		
		std::cout<<node->get_name();
		std::cout<<" "<<node->get_op()<<" ";
		if(node->get_right() != NULL){
			node->get_right()->accept(this);

		}
		if(node->get_sc()){
			std::cout<<";";
			tabs();
		}
	}
	void visit(Break* node){
		
		std::cout<<"break;";
		tabs();
	}
	void visit(Continue* node){
		
		std::cout<<"continue;";
		tabs();
	}
	void visit(Return* node){
		
		std::cout<<"return ";
		if(node->get_ret() != NULL){
			node->get_ret()->accept(this);
		}
		if(node->get_sc()){
			std::cout<<";";
			tabs();
		}
	}
	void visit(Param* node){
		
		std::cout<<node->get_type();
		if(node->get_multidim() != NULL){
			traverse(node->get_multidim());
		}
		std::cout<<" "<<node->get_name();
	}
			
	void visit(ParenExp* node){
		
		std::cout<<"(";
		if(node->get_exp() != NULL){
			node->get_exp()->accept(this);
		}
		std::cout<<")";
	}
private:
	int layer;
	void tabs(){
		std::cout<<"\n";
		for(int i=0;i<this->layer;i++){
			std::cout<<"    ";
		}
	}
	void next(){
		this->layer += 1;
	}
	void prev(){
		this->layer -= 1;
	}

	template <class T>
	void traverse(std::vector<T> *a, std::string sep=""){
		int n = a->size();
		int i =0 ;
		for(auto nx:*a){
			i++;
			nx->accept(this);
			if(i!=n) std::cout<<sep;
		}
	}

};

#endif