#include "ast.hh"
#include "visitor.hh"
#include <map>
#include <stack>
#include <iostream>

#include <llvm/IR/Verifier.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/LegacyPassManagers.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/AsmParser/Parser.h> 
#include <llvm/IR/Instructions.h>
#include <llvm/IR/CallingConv.h>
// #include <llvm/Bitcode/ReaderWriter.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Pass.h>
#include <llvm/ADT/SmallVector.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/InlineAsm.h>
#include <llvm/Support/FormattedStream.h>
#include <llvm/Support/MathExtras.h>

#ifndef INTERPRET_VISITOR_H
#define INTERPRET_VISITOR_H

llvm::LLVMContext context;


class DataBlock{
public:
	llvm::BasicBlock *block;
	std::map<std::string, llvm::Value *> locals;   
	DataBlock(llvm::BasicBlock *block){
		this->block = block;
	}
};


class CodegenVisitor: public Visitor{
public:
	void codeGen() {
		llvm::BasicBlock *block = llvm::BasicBlock::Create(context, "entry", this->mainFunc, 0);  
		this->printf_f = printf_prototype(context, module);
		pushBlock(block);

		std::string format = "%d";
		builder->SetInsertPoint(topBlock());
		this->form1 = builder->CreateGlobalStringPtr(format);
		format = "%c";
		this->form2 = builder->CreateGlobalStringPtr(format);

		this->visit(start);
		std::cerr<<"Finished visiting"<<std::endl;
		handleBlock(block);
		buildPass(block);
		std::cerr<<"Finished everything"<<std::endl;
	}

	CodegenVisitor(StartNode* node){
		this->builder = new llvm::IRBuilder<>(context);
		this->module = new llvm::Module("main", context);
		this->start = node;
		this->module->setTargetTriple("x86_64-pc-linux-gnu"); 

		llvm::FunctionType *ftype = llvm::FunctionType::get(llvm::Type::getInt64Ty(context), false);
		this->mainFunc = llvm::Function::Create(ftype, llvm::GlobalValue::ExternalLinkage, "main", module);

		// llvm::FunctionType *ftype = llvm::FunctionType::get(llvm::Type::getVoidTy(context), false);
		// this->mainFunc = llvm::Function::Create(ftype, llvm::GlobalValue::ExternalLinkage, "main", module);

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
		llvm::Function *func;
		std::string fn = node->get_name();
		if(fn == "main"){
			func = this->mainFunc;
		}
		else{
			llvm::Type * aT ;
			std::vector<llvm::Type *> argT;
			if(node->get_params() != NULL){
				for(auto x:*node->get_params()){
					if(x->get_type() != "float"){
						if(x->get_multidim() == NULL){
							aT = llvm::Type::getInt64Ty(context);
						}
						else{
							builder->SetInsertPoint(topBlock());
							aT = llvm::ArrayType::get(llvm::Type::getInt64Ty(context), 1000);
						}

					}
					else{
						error("Floats args not supported yet");
					}
					argT.push_back(aT);
				}
			}
			if(node->get_type() == "void"){
				aT = llvm::Type::getVoidTy(context);
			}
			else if(node->get_type() != "float"){
				aT = llvm::Type::getInt64Ty(context);		
			}
			llvm::FunctionType *ft = llvm::FunctionType::get(aT, llvm::makeArrayRef(argT), false);
			func = llvm::Function::Create(ft, llvm::GlobalValue::InternalLinkage, fn, module);
			llvm::BasicBlock *block = llvm::BasicBlock::Create(context, "body", func, 0);
			pushBlock(block);
		}


		if(node->get_params() != NULL){
			llvm::Function::arg_iterator it2 = func->arg_begin();
			for(auto it = node->get_params()->begin(); it != node->get_params()->end(); it++){
				llvm::Value *arg = &(*it2);
				std::string name = (*it)->get_name();
				arg->setName(name);
				if(!arg->getType()->isArrayTy()){
					llvm::AllocaInst *allocaInst = new llvm::AllocaInst(llvm::Type::getInt64Ty(context),0, name, topBlock());
					auto tmp = new llvm::StoreInst(arg, allocaInst, false, topBlock());
					declareLocals(name, allocaInst);
				}
				else{
					std::cerr<<"Array parameter"<<" "<<name<<std::endl;
					declareLocals(name, arg);
				}
				it2++;
			}
		}
		
		if(node->get_exec() != NULL){
			traverse(node->get_exec());
		}

		if(topBlock()->getTerminator() == NULL){ 
			if(node->get_type() != "void"){
				llvm::ReturnInst::Create(context, llvm::ConstantInt::get(llvm::Type::getInt64Ty(context), 0, true), topBlock());
			}
			else {
				llvm::ReturnInst::Create(context, topBlock());
			}
		}
		if(fn != "main"){
			popBlock();
		}
		this->returned = func;
	}
	void visit(VarDec* node){
		// std::cout<<"Got Here"<<std::endl;
		std::string type = node->get_type();
		int dim = 1;
		// std::vector<int> dims;
		llvm::Value * no;
		if(node->get_mdim() != NULL){
			for(auto nx:*(node->get_mdim())){
				nx->accept(this);
				no = static_cast<llvm::Value*>(this->returned);
				// dim *= *(this->exp->ival);
				// dims.push_back(*(this->exp->ival));
				dim++;
			}
		}
		if(type == "float"){
			error("Float Not supported yet");
		}
		else{
			if(dim == 1){
				llvm::AllocaInst *allocaInst = new llvm::AllocaInst(llvm::Type::getInt64Ty(context),0, node->get_name(), topBlock());
				if(node->get_exp() != NULL){
					node->get_exp()->accept(this);
					llvm::Value * val = static_cast<llvm::Value *> (this->returned);
					auto tmp = new llvm::StoreInst(val, allocaInst, false, topBlock());
				}
				else{
					auto tmp = new llvm::StoreInst(llvm::ConstantInt::get(llvm::Type::getInt64Ty(context), 0, true), allocaInst, false, topBlock());
				}
				declareLocals(node->get_name(), allocaInst);
				std::cerr<<"Declared "<<node->get_name()<<" "<<allocaInst->getName().data()<<std::endl;
				this->returned = allocaInst;
			}
			else if(dim == 2){
				llvm::GlobalVariable* variable = new llvm::GlobalVariable(*module, llvm::ArrayType::get(llvm::Type::getInt64Ty(context), 1000), false, llvm::GlobalValue::CommonLinkage, NULL, node->get_name());
				
				variable->setInitializer(llvm::ConstantAggregateZero::get(llvm::ArrayType::get(llvm::Type::getInt64Ty(context), 1000)));
				declareLocals(node->get_name(), variable);
				this->returned = variable;	
			}
			else{
				// TODO ARRAY DECL
				error("MultiDim Array declared not supported yet");
			}
		}
	}

	void visit(Name* node){
		auto name = node->get_name();
		if(!isGlobal(name)){
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

		llvm::IntegerType *it = llvm::Type::getInt64Ty(context);
		this->returned = llvm::ConstantInt::get(it, node->get_val(), true);
	}
	void visit(Bool* node){
		if(node->get_val() == "true"){
			
			llvm::IntegerType *it = llvm::Type::getInt64Ty(context);
			this->returned = llvm::ConstantInt::get(it, 1, true);
		}
		else{
			
			llvm::IntegerType *it = llvm::Type::getInt64Ty(context);
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

		std::cerr<<"Here"<<std::endl;
		llvm::IntegerType *it = llvm::Type::getInt8Ty(context);
		this->returned = llvm::ConstantInt::get(it, c, true);
	}
	void visit(MultiDimArr* node){
		
		std::string var_name = node->get_name();
		if(!isGlobal(var_name)){
			error(var_name+"Not Declared");
		}
		(*node->get_sq())[0]->accept(this);
		llvm::Value *idx = static_cast<llvm::Value *>(this->returned);
		builder->SetInsertPoint(topBlock());
		llvm::Value *offset = builder->CreateExtractElement(getBlock(var_name),idx);
		this->returned = new llvm::LoadInst(offset, "load", topBlock());
		// std::cerr<<"Ok till here"<<std::endl;
		
	}
	void visit(UnaryTerm* node){
		
		if(node->get_term() != NULL){
			node->get_term()->accept(this);
		}
		llvm::Value *val = static_cast<llvm::Value *>(this->returned);
		llvm::ConstantInt *zer = llvm::ConstantInt::get(llvm::Type::getInt64Ty(context), 0, true);
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
			
			this->returned =  new llvm::ZExtInst(llvm::CmpInst::Create(llvm::Instruction::ICmp, llvm::ICmpInst::ICMP_EQ, left, right,"tmp", topBlock()), llvm::Type::getInt64Ty(context), "zext", topBlock());
		}
		if(node->get_op() == ">="){
			
			this->returned =  new llvm::ZExtInst(llvm::CmpInst::Create(llvm::Instruction::ICmp, llvm::ICmpInst::ICMP_SGE, left, right,"tmp", topBlock()), llvm::Type::getInt64Ty(context), "zext", topBlock());
		}
		if(node->get_op() == ">"){
			
			this->returned =  new llvm::ZExtInst(llvm::CmpInst::Create(llvm::Instruction::ICmp, llvm::ICmpInst::ICMP_SGT, left, right,"tmp", topBlock()), llvm::Type::getInt64Ty(context), "zext", topBlock());
		}
		if(node->get_op() == "<="){
			
			this->returned =  new llvm::ZExtInst(llvm::CmpInst::Create(llvm::Instruction::ICmp, llvm::ICmpInst::ICMP_SLE, left, right,"tmp", topBlock()), llvm::Type::getInt64Ty(context), "zext", topBlock());
		}
		if(node->get_op() == "<"){
			
			this->returned =  new llvm::ZExtInst(llvm::CmpInst::Create(llvm::Instruction::ICmp, llvm::ICmpInst::ICMP_SLT, left, right,"tmp", topBlock()), llvm::Type::getInt64Ty(context), "zext", topBlock());
		}
		if(node->get_op() == "!="){
			
			this->returned =  new llvm::ZExtInst(llvm::CmpInst::Create(llvm::Instruction::ICmp, llvm::ICmpInst::ICMP_NE, left, right,"tmp", topBlock()), llvm::Type::getInt64Ty(context), "zext", topBlock());
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
		std::string fn = node->get_name();
		llvm::Function *func = module->getFunction(fn);
		std::vector<llvm::Value*> args;
		if(func == NULL){
			error("Undeclared Function "+fn);
		}
		builder->SetInsertPoint(topBlock());
		if(node->get_args() != NULL){
			for(auto x:*node->get_args()){
				x->accept(this);
				llvm::Value *argg = static_cast<llvm::Value*> (this->returned);	
				args.push_back(argg);
			
			}
		}
		this->returned = builder->CreateCall(func, args);
		// this->returned = llvm::CallInst::Create(func, llvm::makeArrayRef(args), fn, topBlock());	
	}
	void visit(Read* node){
		
		node->get_var();
		
	}
	void visit(Print* node){

		node->get_arg()->accept(this);
		llvm::Value * tmp = static_cast<llvm::Value*>(this->returned);
		
		std::vector<llvm::Value *> args;
		if(tmp->getType()->isIntegerTy(8)){
			args.push_back(form2);
		}
		else{
			args.push_back(form1);
		}

		args.push_back(tmp);

		this->returned = llvm::CallInst::Create(printf_f, llvm::makeArrayRef(args), "printf", topBlock());
		
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
		
		
	}
	void visit(Arg* node){
		
		if(node->get_args() != NULL){
			node->get_args()->accept(this);
		}
	}
	void visit(IfStmt* node){
		
		llvm::BasicBlock *entryBlock = topBlock(); 
		llvm::BasicBlock *thenBlock = llvm::BasicBlock::Create(context, "then", entryBlock->getParent(), 0);
		llvm::BasicBlock *elseBlock = llvm::BasicBlock::Create(context, "else", entryBlock->getParent(), 0);
		llvm::BasicBlock *after = llvm::BasicBlock::Create(context, "after", entryBlock->getParent(), 0);
		if(node->get_cond() != NULL){
			node->get_cond()->accept(this);
		}
		llvm::Value *cond = static_cast<llvm::Value *>(this->returned);
		llvm::Constant *zero = llvm::ConstantInt::get(llvm::Type::getInt64Ty(context), 0, true);
		llvm::ICmpInst *comparison = new llvm::ICmpInst(*entryBlock, llvm::ICmpInst::ICMP_NE, cond, zero, "tmp");
		llvm::BranchInst::Create(thenBlock, elseBlock, comparison, entryBlock);
		
		pushBlock(thenBlock);
		if(node->get_if_blk() != NULL){
			traverse(node->get_if_blk());
		}
		llvm::BranchInst::Create(after, thenBlock);                           
		popBlock();
		pushBlock(elseBlock);
		if(node->get_else_blk() != NULL){
			traverse(node->get_else_blk());
		}
		llvm::BranchInst::Create(after, elseBlock);                           
		popBlock();
		auto locals = getLocals();
		popBlock();
		pushBlock(after);
		setLocals(locals);
		
	}
	void visit(For* node){
		
		llvm::BasicBlock *entryBlock = topBlock(); 
		llvm::BasicBlock *bodyBlock = llvm::BasicBlock::Create(context, "loop_body", entryBlock->getParent(), 0);
		llvm::BasicBlock *afterLoopBlock = llvm::BasicBlock::Create(context, "after_loop", entryBlock->getParent(), 0);
		llvm::BasicBlock *headerBlock = llvm::BasicBlock::Create(context, "loop_header", entryBlock->getParent(), 0);

		if(node->get_init() != NULL){
			node->get_init()->accept(this);
		}
		llvm::Value *init = static_cast<llvm::Value *>(this->returned);
		llvm::BranchInst::Create(headerBlock, entryBlock);                           

		pushBlock(headerBlock);
		if(node->get_cond() != NULL){
			node->get_cond()->accept(this);
		}
		llvm::Value *cond = static_cast<llvm::Value *>(this->returned);
		llvm::Constant *zero = llvm::ConstantInt::get(llvm::Type::getInt64Ty(context), 0, true);
		llvm::ICmpInst *comparison = new llvm::ICmpInst(*topBlock(), llvm::ICmpInst::ICMP_NE, cond, zero, "tmp");
		llvm::BranchInst::Create(bodyBlock, afterLoopBlock, comparison, headerBlock);
		popBlock();

		pushBlock(bodyBlock);
		if(node->get_exec() != NULL){
			for(auto nx:*node->get_exec()){
				nx->accept(this);
			}
		}
		if(node->get_increment() != NULL){
			node->get_increment()->accept(this);
		}
		llvm::Value *inc = static_cast<llvm::Value *>(this->returned);
		llvm::BranchInst::Create(headerBlock, topBlock());                           
		popBlock();
		auto locals = getLocals();
		popBlock();
		pushBlock(afterLoopBlock);
		setLocals(locals);
		std::cerr<<"AT end Top Block "<<topBlock()->getName().data()<<std::endl;
	}
	void visit(While* node){
		
		llvm::BasicBlock *entryBlock = topBlock(); 
		llvm::BasicBlock *bodyBlock = llvm::BasicBlock::Create(context, "while_body", entryBlock->getParent(), 0);
		llvm::BasicBlock *afterLoopBlock = llvm::BasicBlock::Create(context, "after_while", entryBlock->getParent(), 0);
		llvm::BasicBlock *headerBlock = llvm::BasicBlock::Create(context, "while_header", entryBlock->getParent(), 0);
		
		pushBlock(headerBlock);
		if(node->get_cond() != NULL){
			node->get_cond()->accept(this);
		}
		llvm::Value *cond = static_cast<llvm::Value *>(this->returned);
		llvm::BranchInst::Create(bodyBlock, afterLoopBlock, cond, headerBlock);
		popBlock();

		pushBlock(bodyBlock);
		if(node->get_exec() != NULL){
			for(auto nx:*node->get_exec()){
				nx->accept(this);
			}
		}
		llvm::BranchInst::Create(headerBlock, topBlock());                           
		popBlock();
		auto locals = getLocals();
		popBlock();
		pushBlock(afterLoopBlock);
		setLocals(locals);

	}
	void visit(ArrayAssign* node){
	
		std::cerr<<"Ok till here"<<std::endl;
		std::string arr_name = node->get_name();
		if(!isGlobal(arr_name)){
			error(arr_name+" not declared");
		}
		(*node->get_dims())[0]->accept(this);
		llvm::Value *idx = static_cast<llvm::Value *>(this->returned);
		builder->SetInsertPoint(topBlock());
		// llvm::Value *location = builder->CreateExtractElement(getBlock(arr_name),idx);
		std::string op = node->get_op();
		if(node->get_right() != NULL){
			node->get_right()->accept(this);
		}
		llvm::Value *expr = static_cast<llvm::Value *>(this->returned);
		// if (op ==  "+="){
		// 	expr = llvm::BinaryOperator::Create(llvm::Instruction::Add, new llvm::LoadInst(location, "load", topBlock()), expr, "tmp", topBlock());
		// }
		// if (op ==  "-="){
		// 	expr = llvm::BinaryOperator::Create(llvm::Instruction::Sub, new llvm::LoadInst(location, "load", topBlock()), expr, "tmp", topBlock());
			
		// }
		// if (op ==  "*="){
		// 	expr = llvm::BinaryOperator::Create(llvm::Instruction::Mul, new llvm::LoadInst(location, "load", topBlock()), expr, "tmp", topBlock());
			
		// }
		// if (op ==  "/="){
		// 	expr = llvm::BinaryOperator::Create(llvm::Instruction::SDiv, new llvm::LoadInst(location, "load", topBlock()), expr, "tmp", topBlock());
		// }
		this->returned = builder->CreateInsertElement(getBlock(arr_name), expr, idx);

	}
	void visit(Assign* node){
		
		std::string name = node->get_name();
		if(!isGlobal(name)){
			error(name+" not declared");
		}
		llvm::Value *location = getBlock(name);
		std::string op = node->get_op();
		if(node->get_right() != NULL){
			node->get_right()->accept(this);
		}
		llvm::Value *expr = static_cast<llvm::Value *>(this->returned);
		if (op ==  "+="){
			expr = llvm::BinaryOperator::Create(llvm::Instruction::Add, new llvm::LoadInst(location, "load", topBlock()), expr, "tmp", topBlock());
		}
		if (op ==  "-="){
			expr = llvm::BinaryOperator::Create(llvm::Instruction::Sub, new llvm::LoadInst(location, "load", topBlock()), expr, "tmp", topBlock());
			
		}
		if (op ==  "*="){
			expr = llvm::BinaryOperator::Create(llvm::Instruction::Mul, new llvm::LoadInst(location, "load", topBlock()), expr, "tmp", topBlock());
			
		}
		if (op ==  "/="){
			expr = llvm::BinaryOperator::Create(llvm::Instruction::SDiv, new llvm::LoadInst(location, "load", topBlock()), expr, "tmp", topBlock());
		}
		this->returned = new llvm::StoreInst(expr, location, false, topBlock());

	}
	void visit(Break* node){
		
		error("Not Implemented yet");
	}
	void visit(Continue* node){
		
		error("Not Implemented yet");
	}
	void visit(Return* node){
		
		llvm::BasicBlock *top = topBlock();
		llvm::Function *function = top->getParent();
		if(function->getReturnType()->isVoidTy() == true){
			if(node->get_ret() != NULL){	
				error("Attempting to this->returned = non void in void function");
			}
			else{
				this->returned = llvm::ReturnInst::Create(context,topBlock());
			}
		} 
		else{
			if(node->get_ret() != NULL){	
				node->get_ret()->accept(this);
				llvm::Value *ret = static_cast<llvm::Value *>(this->returned);
				this->returned = llvm::ReturnInst::Create(context, ret, topBlock());
			}
			else{
				error("No this->returned = for function with this->returned = type");
			}
		}
	}
	void visit(Param* node){
		
		// std::cout<<node->get_type();
		if(node->get_multidim() != NULL){
			traverse(node->get_multidim());
		}
		// std::cout<<" "<<node->get_name();
	}
			
	void visit(ParenExp* node){
		
		if(node->get_exp() != NULL){
			node->get_exp()->accept(this);
		}		
	}
	~CodegenVisitor(){}

private:
	llvm::Module* module;
	llvm::IRBuilder<> *builder;
	StartNode* start;
	llvm::Function* mainFunc;                   
	std::vector<DataBlock> table; 
	llvm::Value *form1, *form2;
	void *returned;

	void error(std::string msg){
		std::cerr<<msg<<"\n";
		exit(0);
	}
	std::map<std::string, llvm::Value *> getLocals(){
		return table.back().locals;
	}
	void setLocals(std::map<std::string, llvm::Value *> variables){
		table.back().locals.insert(variables.begin(), variables.end());
	}
	bool isLocal(std::string name){
		return getLocals().count(name);
	}
	void declareLocals(std::string name, llvm::Value *value){
		if(!isLocal(name)){
			std::pair<std::string, llvm::Value *> inp = make_pair(name, value);
			std::cerr<<"Declaring with "<<name<<" "<<value->getName().data()<<std::endl;
			table.back().locals.insert(inp);
		}
		else{
			error("Redeclaration of "+name);
		}
	}
	bool isGlobal(std::string name){
		for(auto it:table){
			if(it.locals.count(name)){
				return true;
			}
		}
		return false;
	}
	llvm::Value *getBlock(std::string name){
		std::vector<DataBlock>::iterator it;
		for(it = table.begin(); it != table.end(); it++){
			if(it->locals.count(name)){
				llvm::Value *ret = it->locals.find(name)->second;
				// std::cerr<<"Found "<<it->locals.find(name)->first<<std::endl;
				std::cerr<<"Associated with "<<name<<" "<<ret->getName().data()<<" "<<ret->getType()->isArrayTy()<<std::endl;
				return  ret;
			}
		}
		return  NULL;
	}
	
	void pushBlock(llvm::BasicBlock *block){
		std::cerr<<"Pushing Top "<<block->getName().data()<<std::endl;
		table.push_back(DataBlock(block));
	}
	void popBlock(){
		std::cerr<<"Popping Top "<<topBlock()->getName().data()<<std::endl;
		table.pop_back();
	}
	llvm::BasicBlock *topBlock(){
		// for(int i= table.size();i>=0;i--){
		// 	if(table[i].block != NULL){  
		// 		return  table[i].block;
		// 	}
		// }
		if(table.size() == 0){
			std::cerr<<"Empty table"<<std::endl;
		}
		return table.back().block;
	}
	llvm::BasicBlock *botBlock(){
		return table.front().block;
	}          
	void handleBlock(llvm::BasicBlock *block){
		block = topBlock();
		popBlock();
	}
	void buildPass(llvm::BasicBlock *block){
		llvm::legacy::PassManager PM;   
		// llvm::ReturnInst::Create(context, block);
		llvm::verifyModule(*this->module);
		// if(!llvm::verifyModule(*this->module)){
		// 	error("Verify failed");
		// }
		PM.add(llvm::createPrintModulePass(llvm::outs()));
		std::cerr<<"Ok till here"<<std::endl;
		PM.run(*this->module);
	}
	
	template <class T>
	void traverse(std::vector<T> *a){
		for(auto nx:*a){
			nx->accept(this);
		}
	}
	llvm::Function *printf_f;
	static llvm::Function*
	printf_prototype(llvm::LLVMContext& ctx, llvm::Module *mod){
		std::vector<llvm::Type*> printf_arg_types;
		printf_arg_types.push_back(llvm::Type::getInt8PtrTy(ctx));

		llvm::FunctionType* printf_type =
			llvm::FunctionType::get(
				llvm::Type::getInt32Ty(ctx), printf_arg_types, true);

		llvm::Function *func = llvm::Function::Create(
					printf_type, llvm::Function::ExternalLinkage,
					llvm::Twine("printf"),
					mod
			   );
		func->setCallingConv(llvm::CallingConv::C);
		return func;
	}
};

#endif