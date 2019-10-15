%{
  #include <stdio.h>
  #include <iostream>
  using namespace std;

  // stuff from flex that bison needs to know about:
  extern int yylex();
  extern int yyparse();
  extern FILE *yyin;
  void yyerror(char *s);
  int production = 1;
%}

%union {
  int   ival;
  float fval;
  char  sval[100];
}

%token  <ival> DIGIT 
%token  <sval> IDENTIFIER
%token  <sval> OP
%%

Goal:	Expr '\n' {printf("\n production = %d Expr ", production) ; production++; }
	| Goal Expr '\n'{printf("\n production = %d Goal Expr ",production) ; production++; }
	;

Expr: 	Expr OP Term  {printf("\n production = %d Expr OP Term",production) ; production++; }
	| Term {printf("\n production = %d Term",production) ; production++; }
	;

Term:	DIGIT { printf("\n production = %d DIGIT=%d",production, $1); production++;} 
	| IDENTIFIER { printf("\n production = %d IDENTIFIER=%s\n",production, $1); production++; }
	;

%%

void yyerror(char *s)
{
        fprintf(stderr, "error: %s\n", s);
}


main(int argc, char **argv)
{
        yyparse();
        printf("Parsing Over\n");
}



