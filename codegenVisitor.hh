#include "ast.hh"
#include "visitor.hh"
#include <map>
#include <stack>
#include <iostream>
#include<llvm/IR/Verifier.h>
#include<llvm/IR/DerivedTypes.h>
#include<llvm/IR/IRBuilder.h>
#include<llvm/IR/LLVMContext.h>
#include<llvm/IR/Module.h>

#ifndef INTERPRET_VISITOR_H
#define INTERPRET_VISITOR_H



class DataBlock{
public:
	llvm::BasicBlock *block;
	std::map<std::string, llvm::Value *> locals;   
	DataBlock(llvm::BasicBlock *block){
		this->block = block;
	}
};


class InterpretVisitor: public Visitor{
public:
	InterpretVisitor(StartNode* node){
		llvm::LLVMContext &context = llvm::getGlobalContext();
		this->module = new llvm::Module("main", context);
		this->start = node;
		this->module->setTargetTriple("x86_64-pc-linux-gnu"); 

		llvm::FunctionType *ftype = llvm::FunctionType::get(llvm::Type::getVoidTy(llvm::getGlobalContext()), false);
		this->mainFunc = llvm::Function::Create(ftype, llvm::GlobalValue::ExternalLinkage, "main", module);

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
		auto name = node->get_name();
		if(isGlobal(name)){
			error(name+" not declared");
		}
		
		llvm::Value *val = getBlock(name);
		if(val == NULL){
			error(name+"not initialized");
		}
		llvm::LoadInst *instruction = new llvm::LoadInst(val, "tmp", topBlock());
		this->returned = instruction;
	}
	void visit(Float* node){
		// TODO FLOAT SUPPORT
	}
	void visit(Int* node){
		
		llvm::IntegerType *it = llvm::Type::getInt64Ty(llvm::getGlobalContext());
		this->returned = llvm::ConstantInt::get(it, val, true);
	}
	void visit(Bool* node){
		if(node->get_val() == "true"){
			
			llvm::IntegerType *it = llvm::Type::getInt64Ty(llvm::getGlobalContext());
			this->returned = llvm::ConstantInt::get(it, 1, true);
		}
		else{
			
			llvm::IntegerType *it = llvm::Type::getInt64Ty(llvm::getGlobalContext());
			this->returned = llvm::ConstantInt::get(it, 0, true);
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

		llvm::IntegerType *it = llvm::Type::getInt64Ty(llvm::getGlobalContext());
		this->returned = llvm::ConstantInt::get(it, val, true);
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
		// TODO: ARRAY ACCESS
	}
	void visit(UnaryTerm* node){
		
		if(node->get_term() != NULL){
			node->get_term()->accept(this);
		}
		llvm::Value *val = static_cast<llvm::Value *>(this->returned);
		llvm::ConstantInt *zer = llvm::ConstantInt::get(llvm::Type::getInt64Ty(llvm::getGlobalContext()), 0, true);
		if(node->get_op() == "-"){
			this->returned = llvm::BinaryOperator::Create(llvm::Instruction::Sub, zer, val, "tmp", topBlock());
		}
		if(node->get_op() == "!"){
			this->returned = llvm::CmpInst::Create(llvm::Instruction::ICmp, llvm::ICmpInst::ICMP_EQ, zer, val,"tmp", topBlock());
		}
	}
	void visit(BinaryOperator* node){

		if(node->get_right() != NULL){
			node->get_right()->accept(this);
		}
		llvm::Value* right = static_cast<llvm::Value *>(this->returned);

		if(node->get_left() != NULL){
			node->get_left()->accept(this);
		}
		llvm::Value* left = static_cast<llvm::Value *>(this->returned);
		

		if(node->get_op() == "+"){
			this->returned =  llvm::BinaryOperator::Create(llvm::Instruction::Add, left, right, "tmp", topBlock());
		}
		if(node->get_op() == "-"){
			this->returned =  llvm::BinaryOperator::Create(llvm::Instruction::Sub, left, right, "tmp", topBlock());
			
		}
		if(node->get_op() == "*"){
			this->returned =  llvm::BinaryOperator::Create(llvm::Instruction::Mul, left, right, "tmp", topBlock());
			
		}
		if(node->get_op() == "/"){
			this->returned =  llvm::BinaryOperator::Create(llvm::Instruction::SDiv, left, right, "tmp", topBlock());
			
		}
		if(node->get_op() == "%"){
			this->returned =  llvm::BinaryOperator::Create(llvm::Instruction::SRem, left, right, "tmp", topBlock());
			
		}
		if(node->get_op() == "=="){
			
			this->returned =  new llvm::ZExtInst(llvm::CmpInst::Create(llvm::Instruction::ICmp, llvm::ICmpInst::ICMP_EQ, left, right,"tmp", topBlock()), llvm::Type::getInt64Ty(llvm::getGlobalContext()), "zext", topBlock());
		}
		if(node->get_op() == ">="){
			
			this->returned =  new llvm::ZExtInst(llvm::CmpInst::Create(llvm::Instruction::ICmp, llvm::ICmpInst::ICMP_SGE, left, right,"tmp", topBlock()), llvm::Type::getInt64Ty(llvm::getGlobalContext()), "zext", topBlock());
		}
		if(node->get_op() == ">"){
			
			this->returned =  new llvm::ZExtInst(llvm::CmpInst::Create(llvm::Instruction::ICmp, llvm::ICmpInst::ICMP_SGT, left, right,"tmp", topBlock()), llvm::Type::getInt64Ty(llvm::getGlobalContext()), "zext", topBlock());
		}
		if(node->get_op() == "<="){
			
			this->returned =  new llvm::ZExtInst(llvm::CmpInst::Create(llvm::Instruction::ICmp, llvm::ICmpInst::ICMP_SLE, left, right,"tmp", topBlock()), llvm::Type::getInt64Ty(llvm::getGlobalContext()), "zext", topBlock());
		}
		if(node->get_op() == "<"){
			
			this->returned =  new llvm::ZExtInst(llvm::CmpInst::Create(llvm::Instruction::ICmp, llvm::ICmpInst::ICMP_SLT, left, right,"tmp", topBlock()), llvm::Type::getInt64Ty(llvm::getGlobalContext()), "zext", topBlock());
		}
		if(node->get_op() == "!="){
			
			this->returned =  new llvm::ZExtInst(llvm::CmpInst::Create(llvm::Instruction::ICmp, llvm::ICmpInst::ICMP_NE, left, right,"tmp", topBlock()), llvm::Type::getInt64Ty(llvm::getGlobalContext()), "zext", topBlock());
		}
		if(node->get_op() == "&"){
			
			this->returned =  llvm::BinaryOperator::Create(llvm::Instruction::And, left, right, "tmp", topBlock());
			
		}
		if(node->get_op() == "|"){
			
			this->returned =  llvm::BinaryOperator::Create(llvm::Instruction::Or, left, right, "tmp", topBlock());
				
		}
	}
	void visit(TernaryOperator* node){
		
		if(node->get_left() != NULL){
			node->get_left()->accept(this);
		}
		llvm::Value* left = static_cast<llvm::Value *>(this->returned);
		if(node->get_middle() != NULL){
			node->get_middle()->accept(this);
		}
		llvm::Value* middle = static_cast<llvm::Value *>(this->returned);
		if(node->get_right() != NULL){
			node->get_right()->accept(this);
		}
		llvm::Value* right = static_cast<llvm::Value *>(this->returned);
		// TODO: Ternary support.
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
		
		llvm::BasicBlock *entryBlock = topBlock(); 
		llvm::BasicBlock *bodyBlock = llvm::BasicBlock::Create(llvm::getGlobalContext(), "loop_body", entryBlock->getParent(), 0);
		llvm::BasicBlock *afterLoopBlock = llvm::BasicBlock::Create(llvm::getGlobalContext(), "after_loop", entryBlock->getParent(), 0);
		llvm::BasicBlock *headerBlock = llvm::BasicBlock::Create(llvm::getGlobalContext(), "loop_header", entryBlock->getParent(), 0);


		if(node->get_init() != NULL){
			node->get_init()->accept(this);
		}
		llvm::Value *init = static_cast<llvm::Value *>(this->returned);

		if(node->get_cond() != NULL){
			node->get_cond()->accept(this);
		}
		llvm::Value *cond = static_cast<llvm::Value *>(this->returned);

		if(node->get_exec() != NULL){
			for(auto nx:*node->get_exec()){
				nx->accept(this);
			}
		}
		if(node->get_increment() != NULL){
			node->get_increment()->accept(this);
		}
		llvm::Value *inc = static_cast<llvm::Value *>(this->returned);

		llvm::BranchInst::Create(bodyBlock, afterLoopBlock, cond, headerBlock);
		llvm::BranchInst::Create(headerBlock, entryBlock);                           

		
		
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
		
		llvm::BasicBlock *top = topBlock();
		llvm::Function *function = top->getParent();
		if(function->getReturnType()->isVoidTy() == true){
			if(node->get_ret() != NULL){	
				error("Attempting to return non void in void function");
			}
			else{
				this->returned = llvm::ReturnInst::Create(llvm::getGlobalContext(),topBlock());
			}
		} 
		else{
			if(node->get_ret() != NULL){	
				Value *ret = static_cast<llvm::Value *>(node->get_ret->accept(this));
				this->returned = llvm::ReturnInst::Create(llvm::getGlobalContext(), ret, topBlock());
			}
			else{
				error("No return for function with return type");
			}
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
	llvm::Module* module;
	ASTProgram* start;
	llvm::Function* mainFunc;                   
	std::vector<DataBlock> table; 

	void *returned;

	void error(std::string msg){
		std::cerr<<msg<<"\n";
		exit(0);
	}
	std::unordered_map<std::string, llvm::Value *> getLocals(){
		return table.back().locals;
	}
	void setLocals(std::unordered_map<std::string, llvm::Value *> variables){
		table.back().locals.insert(variables.begin(), variables.end());
	}
	bool isLocal(std::string name){
		return getLocals().count(name);
	}
	void declareLocals(std::string name, llvm::Value *value){
		if(!isLocal(name)){
			std::pair<std::string, llvm::Value *> inp = std::pair<std::string, llvm::Value *>(name, value);
			blockTable.front().localVariables.insert(inp);
		}
		else{
			error("Redeclaration of "+name);
		}
	}
	bool isGlobal(std::string name){
		for(auto it:table){
			if(it.count(name)){
				return true;
			}
		}
		return false;
	}
	llvm::Value *getBlock(std::string name){
		std::list<BlockVariables>::iterator it;
		for(auto *it:table){
			if(it->count(name)){
				return it;
			}
		}
		return NULL;
	}
	llvm:: isGlobal(std::string name){
		for(auto it:table){
			if(it.count(name)){
				return true;
			}
		}
		return false;
	}
	
	void pushBlock(llvm::BasicBlock *block){
		table.push_back(DataBlock(block));
	}
	void popBlock(){
		table.pop_back();
	}
	llvm::BasicBlock *topBlock(){
		for(int i= table.size();i>=0;i--){
			if(table[i].block != NULL){  
				return table[i].block;
			}
		}
		return blockTable.back().block;
	}
	llvm::BasicBlock *botBlock(){
		return blockTable.front().block;
	}          
	void handleBlock(llvm::BasicBlock *block){
		block = topBlock();
		popBlock();
	}
	void buildPass(llvm::BasicBlock *block){
		llvm::legacy::PassManager PM;   
		llvm::ReturnInst::Create(llvm::getGlobalContext(), block);
		llvm::verifyModule(*this->module);
		PM.add(llvm::createPrintModulePass(llvm::outs()));
		PM.run(*this->module);
	}
	void codeGen() {
		llvm::BasicBlock *block = llvm::BasicBlock::Create(llvm::getGlobalContext(), "entry", this->mainFunc, 0);  
		pushBlock(block);
		this->visit(start);
		handleBlock(block);
		buildPass(block);
	}

};

#endif