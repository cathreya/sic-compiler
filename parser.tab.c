/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 2 "parser.y" /* yacc.c:339  */

	#include <stdio.h>
	#include <iostream>
	using namespace std;

	// stuff from flex that bison needs to know about:
	extern int yylex();
	extern int yyparse();
	extern FILE *yyin;
	void yyerror(char const *s);
	int production = 1;

	void status(int rule){
		cout<<"Reducing using rule "<<rule<<endl;
	}


#line 84 "parser.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.tab.h".  */
#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
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
    DIGIT = 258,
    IMPORT = 259,
    STRINGLIT = 260,
    STMT_SEP = 261,
    LIST_SEP = 262,
    TYPE = 263,
    NAME = 264,
    ASSIGN = 265,
    FLOATV = 266,
    INTV = 267,
    BOOLLIT = 268,
    CHARV = 269,
    VOIDV = 270,
    OPENPAREN = 271,
    CLOSEPAREN = 272,
    OPENBRACE = 273,
    CLOSEBRACE = 274,
    OPENSQUARE = 275,
    CLOSESQUARE = 276,
    BREAK = 277,
    CONTINUE = 278,
    RETURN = 279,
    IF = 280,
    ELSE = 281,
    FOR = 282,
    WHILE = 283,
    OR = 284,
    AND = 285,
    EQ = 286,
    REL = 287,
    ADD = 288,
    MUL = 289,
    UNARY_OP = 290
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 20 "parser.y" /* yacc.c:355  */

	int   ival;
	float fval;
	char  sval[100];

#line 166 "parser.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 183 "parser.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   232

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  36
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  78
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  160

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   290

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    63,    63,    66,    70,    71,    73,    74,    76,    77,
      79,    80,    81,    83,    84,    85,    86,    88,    89,    91,
      93,    94,    95,    96,    98,    99,   100,   101,   102,   103,
     104,   106,   107,   108,   110,   111,   113,   114,   116,   117,
     119,   120,   121,   122,   124,   125,   127,   129,   130,   131,
     132,   133,   134,   135,   136,   138,   140,   141,   143,   144,
     146,   147,   149,   150,   152,   153,   155,   156,   158,   159,
     160,   162,   163,   164,   165,   166,   167,   168,   169
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "DIGIT", "IMPORT", "STRINGLIT",
  "STMT_SEP", "LIST_SEP", "TYPE", "NAME", "ASSIGN", "FLOATV", "INTV",
  "BOOLLIT", "CHARV", "VOIDV", "OPENPAREN", "CLOSEPAREN", "OPENBRACE",
  "CLOSEBRACE", "OPENSQUARE", "CLOSESQUARE", "BREAK", "CONTINUE", "RETURN",
  "IF", "ELSE", "FOR", "WHILE", "OR", "AND", "EQ", "REL", "ADD", "MUL",
  "UNARY_OP", "$accept", "start", "imports", "prog_element", "program",
  "declaration", "function_definition", "parameters", "statement_block",
  "statement_list", "statementsc", "statementcurly",
  "assignment_statement", "multidim", "function_call", "arguments",
  "if_block", "while_block", "for_block", "texp", "or_exp", "and_exp",
  "eq_exp", "rel_exp", "add_exp", "mul_exp", "exp", "term", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290
};
# endif

#define YYPACT_NINF -83

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-83)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      59,    -4,    -6,    15,    26,    76,    75,   -83,    34,   -83,
      45,    77,    40,   -83,    65,   -83,   -83,   -83,   -83,   113,
      49,    64,    89,   -83,   -14,   -83,   -83,   -83,   -83,   129,
     103,   103,   -83,   -83,    71,    73,    79,    72,    87,    96,
     -83,   -83,   124,   135,     3,   135,     8,   -83,     0,   129,
     137,   142,   -83,   -83,   129,   129,   129,   129,   129,   129,
     -83,    20,   -83,   159,   135,   -83,   135,   -83,   -83,    48,
     -83,   147,   129,   -83,    73,    79,    72,    87,    96,   -83,
     154,    82,   -83,   -83,   129,   153,   156,   171,   -83,   157,
     164,   -83,   -83,   -83,   -83,   -83,   -83,   187,   -83,   -83,
     123,   -83,   -83,   178,   190,   129,    -2,   -83,   129,    53,
     129,   -83,   195,   -83,   -83,   -83,   -83,   -83,   -83,   -83,
     129,   185,    25,   198,   188,   -83,   -83,   135,   166,   201,
     138,   135,   191,   135,   197,   169,   186,   209,   -83,   135,
     -83,   135,   135,   199,   135,   202,   189,   -83,   -83,   -83,
     135,   -83,   135,   135,   203,   -83,   -83,   -83,   135,   -83
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     9,     3,     0,     7,
       0,    11,     0,     1,     0,     2,     8,     6,     4,     0,
       0,     0,     0,    10,    71,    72,    73,    74,    75,     0,
       0,     0,    78,    12,    55,    56,    58,    60,    62,    64,
      66,    68,     0,     0,     0,     0,     0,     5,     0,     0,
      77,     0,    70,    69,     0,     0,     0,     0,     0,     0,
      17,     0,    14,     0,     0,    15,     0,    41,    39,     0,
      40,     0,     0,    76,    57,    59,    61,    63,    65,    67,
       0,     0,    27,    28,    29,     0,     0,     0,    24,     0,
       0,    21,    25,    26,    31,    32,    33,     0,    13,    16,
       0,    38,    36,     0,    11,     0,     0,    30,     0,     0,
       0,    19,     0,    23,    20,    18,    43,    42,    37,    34,
       0,     0,     0,     0,     0,    22,    35,     0,     0,     0,
       0,     0,    44,     0,     0,     0,     0,     0,    46,     0,
      47,     0,     0,     0,     0,     0,     0,    45,    48,    49,
       0,    51,     0,     0,     0,    50,    52,    53,     0,    54
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -83,   -83,   -83,   -83,    17,   155,   -83,   200,   -45,   -83,
     -82,   133,   -83,   143,   -57,   -83,   -83,   -83,   -83,     1,
     -83,   172,   163,   167,   168,   170,   173,    38
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,     7,    88,     9,    44,    62,    89,
      90,    91,    92,    50,    32,    69,    94,    95,    96,    33,
      34,    35,    36,    37,    38,    39,    40,    41
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      65,    10,    48,    11,    93,    67,    49,   112,   120,    24,
      63,    25,    26,    27,    28,    63,    29,    68,    72,    98,
      64,    99,    15,    16,    12,    66,    13,   123,    80,    81,
      51,   128,    93,    30,    24,    31,    25,    26,    27,    28,
      17,    29,    82,    83,    84,    85,   134,    86,    87,    70,
      71,    18,    93,   143,   145,   100,    21,    42,    30,   122,
      31,    80,    81,     1,   154,   101,    43,     2,    52,    53,
      22,    93,    42,   103,     3,    82,    83,    84,    93,    93,
      14,    45,   132,     2,     2,   107,   138,    19,   140,    93,
       3,     3,   105,    20,   147,    47,   148,   149,    48,   151,
      54,   117,    49,    55,    57,   155,   119,   156,   157,   121,
      56,   124,    24,   159,    25,    26,    27,    28,    23,    29,
      58,   126,    24,   129,    25,    26,    27,    28,   116,    29,
      59,   137,    24,    60,    25,    26,    27,    28,    24,    29,
      25,    26,    27,    28,   136,    29,    30,    24,    31,    25,
      26,    27,    28,    61,    29,     8,    30,    72,    31,    73,
       8,     8,    30,   104,    31,    80,    81,    97,   102,   108,
     114,    30,   109,    31,    80,    81,   111,    80,    81,    82,
      83,    84,    85,   133,    86,    87,   142,   110,    82,    83,
      84,    82,    83,    84,    80,    81,   115,    80,    81,   118,
      19,   125,   127,   144,   130,   131,   153,   135,    82,    83,
      84,    82,    83,    84,   141,   146,   150,   139,    75,   152,
     158,    46,   113,    76,   106,    77,    74,     0,    78,     0,
       0,     0,    79
};

static const yytype_int16 yycheck[] =
{
      45,     5,    16,     9,    61,     5,    20,    89,    10,     9,
       7,    11,    12,    13,    14,     7,    16,    17,    20,    64,
      17,    66,     5,     6,     9,    17,     0,   109,     8,     9,
      29,     6,    89,    33,     9,    35,    11,    12,    13,    14,
       6,    16,    22,    23,    24,    25,   128,    27,    28,    48,
      49,     6,   109,   135,   136,     7,    16,     8,    33,     6,
      35,     8,     9,     4,   146,    17,    17,     8,    30,    31,
       5,   128,     8,    72,    15,    22,    23,    24,   135,   136,
       4,    17,   127,     8,     8,    84,   131,    10,   133,   146,
      15,    15,    10,    16,   139,     6,   141,   142,    16,   144,
      29,   100,    20,    30,    32,   150,   105,   152,   153,   108,
      31,   110,     9,   158,    11,    12,    13,    14,     5,    16,
      33,   120,     9,   122,    11,    12,    13,    14,     5,    16,
      34,   130,     9,     9,    11,    12,    13,    14,     9,    16,
      11,    12,    13,    14,     6,    16,    33,     9,    35,    11,
      12,    13,    14,    18,    16,     0,    33,    20,    35,    17,
       5,     6,    33,     9,    35,     8,     9,     8,    21,    16,
       6,    33,    16,    35,     8,     9,    19,     8,     9,    22,
      23,    24,    25,    17,    27,    28,    17,    16,    22,    23,
      24,    22,    23,    24,     8,     9,     9,     8,     9,    21,
      10,     6,    17,    17,     6,    17,    17,     6,    22,    23,
      24,    22,    23,    24,    17,     6,    17,    26,    55,    17,
      17,    21,    89,    56,    81,    57,    54,    -1,    58,    -1,
      -1,    -1,    59
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,     8,    15,    37,    38,    39,    40,    41,    42,
       5,     9,     9,     0,     4,    40,    40,     6,     6,    10,
      16,    16,     5,     5,     9,    11,    12,    13,    14,    16,
      33,    35,    50,    55,    56,    57,    58,    59,    60,    61,
      62,    63,     8,    17,    43,    17,    43,     6,    16,    20,
      49,    55,    63,    63,    29,    30,    31,    32,    33,    34,
       9,    18,    44,     7,    17,    44,    17,     5,    17,    51,
      55,    55,    20,    17,    57,    58,    59,    60,    61,    62,
       8,     9,    22,    23,    24,    25,    27,    28,    41,    45,
      46,    47,    48,    50,    52,    53,    54,     8,    44,    44,
       7,    17,    21,    55,     9,    10,    49,    55,    16,    16,
      16,    19,    46,    47,     6,     9,     5,    55,    21,    55,
      10,    55,     6,    46,    55,     6,    55,    17,     6,    55,
       6,    17,    44,    17,    46,     6,     6,    55,    44,    26,
      44,    17,    17,    46,    17,    46,     6,    44,    44,    44,
      17,    44,    17,    17,    46,    44,    44,    44,    17,    44
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    36,    37,    37,    38,    38,    39,    39,    40,    40,
      41,    41,    41,    42,    42,    42,    42,    43,    43,    44,
      45,    45,    45,    45,    46,    46,    46,    46,    46,    46,
      46,    47,    47,    47,    48,    48,    49,    49,    50,    50,
      51,    51,    51,    51,    52,    52,    53,    54,    54,    54,
      54,    54,    54,    54,    54,    55,    56,    56,    57,    57,
      58,    58,    59,    59,    60,    60,    61,    61,    62,    62,
      62,    63,    63,    63,    63,    63,    63,    63,    63
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     3,     4,     2,     1,     2,     1,
       4,     2,     4,     6,     5,     5,     6,     2,     4,     3,
       2,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       2,     1,     1,     1,     3,     4,     3,     4,     4,     3,
       1,     1,     3,     3,     5,     7,     5,     6,     7,     7,
       8,     7,     8,     8,     9,     1,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     2,
       2,     1,     1,     1,     1,     1,     3,     2,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 63 "parser.y" /* yacc.c:1646  */
    { 
	cout << "Parse successful!" << endl; 
}
#line 1382 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 66 "parser.y" /* yacc.c:1646  */
    { 
		cout << "Parse successful!" << endl;
}
#line 1390 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 70 "parser.y" /* yacc.c:1646  */
    {status(1);}
#line 1396 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 71 "parser.y" /* yacc.c:1646  */
    {status(2);}
#line 1402 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 73 "parser.y" /* yacc.c:1646  */
    {status(3);}
#line 1408 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 74 "parser.y" /* yacc.c:1646  */
    {status(4);}
#line 1414 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 76 "parser.y" /* yacc.c:1646  */
    {status(5);}
#line 1420 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 77 "parser.y" /* yacc.c:1646  */
    {status(6);}
#line 1426 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 79 "parser.y" /* yacc.c:1646  */
    {status(7);}
#line 1432 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 80 "parser.y" /* yacc.c:1646  */
    {status(77);}
#line 1438 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 81 "parser.y" /* yacc.c:1646  */
    {status(12);}
#line 1444 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 83 "parser.y" /* yacc.c:1646  */
    {status(13);}
#line 1450 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 84 "parser.y" /* yacc.c:1646  */
    {status(14);}
#line 1456 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 85 "parser.y" /* yacc.c:1646  */
    {status(15);}
#line 1462 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 86 "parser.y" /* yacc.c:1646  */
    {status(16);}
#line 1468 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 88 "parser.y" /* yacc.c:1646  */
    {status(17);}
#line 1474 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 89 "parser.y" /* yacc.c:1646  */
    {status(18);}
#line 1480 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 91 "parser.y" /* yacc.c:1646  */
    {status(19);}
#line 1486 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 93 "parser.y" /* yacc.c:1646  */
    {status(20);}
#line 1492 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 94 "parser.y" /* yacc.c:1646  */
    {status(21);}
#line 1498 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 95 "parser.y" /* yacc.c:1646  */
    {status(21);}
#line 1504 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 96 "parser.y" /* yacc.c:1646  */
    {status(21);}
#line 1510 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 98 "parser.y" /* yacc.c:1646  */
    {status(22);}
#line 1516 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 99 "parser.y" /* yacc.c:1646  */
    {status(23);}
#line 1522 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 100 "parser.y" /* yacc.c:1646  */
    {status(24);}
#line 1528 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 101 "parser.y" /* yacc.c:1646  */
    {status(25);}
#line 1534 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 102 "parser.y" /* yacc.c:1646  */
    {status(26);}
#line 1540 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 103 "parser.y" /* yacc.c:1646  */
    {status(27);}
#line 1546 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 104 "parser.y" /* yacc.c:1646  */
    {status(277);}
#line 1552 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 106 "parser.y" /* yacc.c:1646  */
    {status(28);}
#line 1558 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 107 "parser.y" /* yacc.c:1646  */
    {status(29);}
#line 1564 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 108 "parser.y" /* yacc.c:1646  */
    {status(30);}
#line 1570 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 110 "parser.y" /* yacc.c:1646  */
    {status(31);}
#line 1576 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 111 "parser.y" /* yacc.c:1646  */
    {status(32);}
#line 1582 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 113 "parser.y" /* yacc.c:1646  */
    {status(322);}
#line 1588 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 114 "parser.y" /* yacc.c:1646  */
    {status(323);}
#line 1594 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 116 "parser.y" /* yacc.c:1646  */
    {status(33);}
#line 1600 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 117 "parser.y" /* yacc.c:1646  */
    {status(34);}
#line 1606 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 119 "parser.y" /* yacc.c:1646  */
    {status(35);}
#line 1612 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 120 "parser.y" /* yacc.c:1646  */
    {status(355);}
#line 1618 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 121 "parser.y" /* yacc.c:1646  */
    {status(36);}
#line 1624 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 122 "parser.y" /* yacc.c:1646  */
    {status(366);}
#line 1630 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 124 "parser.y" /* yacc.c:1646  */
    {status(37);}
#line 1636 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 125 "parser.y" /* yacc.c:1646  */
    {status(38);}
#line 1642 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 127 "parser.y" /* yacc.c:1646  */
    {status(39);}
#line 1648 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 129 "parser.y" /* yacc.c:1646  */
    {status(40);}
#line 1654 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 130 "parser.y" /* yacc.c:1646  */
    {status(41);}
#line 1660 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 131 "parser.y" /* yacc.c:1646  */
    {status(42);}
#line 1666 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 132 "parser.y" /* yacc.c:1646  */
    {status(43);}
#line 1672 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 133 "parser.y" /* yacc.c:1646  */
    {status(44);}
#line 1678 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 134 "parser.y" /* yacc.c:1646  */
    {status(45);}
#line 1684 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 135 "parser.y" /* yacc.c:1646  */
    {status(46);}
#line 1690 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 136 "parser.y" /* yacc.c:1646  */
    {status(47);}
#line 1696 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 138 "parser.y" /* yacc.c:1646  */
    {status(48);}
#line 1702 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 140 "parser.y" /* yacc.c:1646  */
    {status(49);}
#line 1708 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 141 "parser.y" /* yacc.c:1646  */
    {status(50);}
#line 1714 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 143 "parser.y" /* yacc.c:1646  */
    {status(51);}
#line 1720 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 144 "parser.y" /* yacc.c:1646  */
    {status(52);}
#line 1726 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 147 "parser.y" /* yacc.c:1646  */
    {status(53);}
#line 1732 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 149 "parser.y" /* yacc.c:1646  */
    {status(54);}
#line 1738 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 150 "parser.y" /* yacc.c:1646  */
    {status(55);}
#line 1744 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 152 "parser.y" /* yacc.c:1646  */
    {status(56);}
#line 1750 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 153 "parser.y" /* yacc.c:1646  */
    {status(57);;}
#line 1756 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 155 "parser.y" /* yacc.c:1646  */
    {status(58);}
#line 1762 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 156 "parser.y" /* yacc.c:1646  */
    {status(59);}
#line 1768 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 158 "parser.y" /* yacc.c:1646  */
    {status(60);}
#line 1774 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 159 "parser.y" /* yacc.c:1646  */
    {status(61);}
#line 1780 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 160 "parser.y" /* yacc.c:1646  */
    {status(62);}
#line 1786 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 162 "parser.y" /* yacc.c:1646  */
    {status(63);}
#line 1792 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 163 "parser.y" /* yacc.c:1646  */
    {status(64);}
#line 1798 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 164 "parser.y" /* yacc.c:1646  */
    {status(65);}
#line 1804 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 165 "parser.y" /* yacc.c:1646  */
    {status(66);}
#line 1810 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 166 "parser.y" /* yacc.c:1646  */
    {status(67);}
#line 1816 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 167 "parser.y" /* yacc.c:1646  */
    {status(68);}
#line 1822 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 168 "parser.y" /* yacc.c:1646  */
    {status(69);}
#line 1828 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 169 "parser.y" /* yacc.c:1646  */
    {status(70);}
#line 1834 "parser.tab.c" /* yacc.c:1646  */
    break;


#line 1838 "parser.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 171 "parser.y" /* yacc.c:1906  */


void yyerror(char const *s)
{
				fprintf(stderr, "error: %s\n", s);
}


main(int argc, char **argv)
{
				yyparse();
				printf("Parsing Over\n");
}



