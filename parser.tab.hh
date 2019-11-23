/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_PARSER_TAB_HH_INCLUDED
# define YY_YY_PARSER_TAB_HH_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    PRINT = 258,
    IMPORT = 259,
    READ = 260,
    DIGIT = 261,
    STRINGLIT = 262,
    STMT_SEP = 263,
    LIST_SEP = 264,
    TYPE = 265,
    NAME = 266,
    ASSIGN = 267,
    FLOATV = 268,
    INTV = 269,
    BOOLLIT = 270,
    CHARV = 271,
    VOIDV = 272,
    OPENPAREN = 273,
    CLOSEPAREN = 274,
    OPENBRACE = 275,
    CLOSEBRACE = 276,
    OPENSQUARE = 277,
    CLOSESQUARE = 278,
    BREAK = 279,
    CONTINUE = 280,
    RETURN = 281,
    IF = 282,
    ELSE = 283,
    FOR = 284,
    WHILE = 285,
    OR = 286,
    AND = 287,
    EQ = 288,
    REL = 289,
    ADD = 290,
    MUL = 291,
    UNARY_OP = 292,
    TQ = 293,
    TE = 294
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 23 "parser.yy" /* yacc.c:1909  */

	int   ival;
	float fval;
	char  sval[100];
	Term *TermVal;
	Name *NameVal;
	Float *FloatVal;
	Int *IntVal;
	Bool *BoolVal;
	Char *CharVal;
	MultiDimArr *MultiDimArrVal;
	UnaryTerm *UnaryTermVal;
	Exp *ExpVal;
	BinaryOperator *BinaryOperatorVal;
	TernaryOperator *TernaryOperatorVal;
	std::vector<Square*> *SquareVal;
	FuncCall *FuncCallVal;
	String *StringVal;
	std::vector<Arg*> *ArgVal;
	IfStmt *IfStmtVal;
	For *ForVal;
	While *WhileVal;
	AssignPar *AssignParVal;
	ArrayAssign *ArrayAssignVal;
	Assign *AssignVal;
	Break *BreakVal;
	Continue *ContinueVal;
	Return *ReturnVal;
	Statement *StatementVal;
	std::vector<Statement*> *StatementListVal;
	std::vector<Param*> *ParamVal;
	FuncDef *FuncDefVal;
	std::vector<ProgramNode*> *ProgramNodeVal;
	ProgramNode *SProgramNodeVal;
	StartNode *StartNodeVal;
	VarDec *VarDecVal;
	ParenExp *ParenExpVal;
	Read *ReadVal;
	Print *PrintVal;
    std::vector<Imports*> *ImportsVal;


#line 137 "parser.tab.hh" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_HH_INCLUDED  */
