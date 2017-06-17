/* A Bison parser, made by GNU Bison 3.0.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "pascal_yacc.y" /* yacc.c:339  */

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#include "ast.h"
#include "ir.h"
#include "table.h"
#include "pascal_lex.h"

int yyerror(char*);

#define INT 0
#define REAL 1
#define ARRAY 2



#line 87 "pascal_yacc.c" /* yacc.c:339  */

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "pascal_yacc.h".  */
#ifndef YY_YY_PASCAL_YACC_H_INCLUDED
# define YY_YY_PASCAL_YACC_H_INCLUDED
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
    Iden = 300,
    IntNo = 301,
    RealNo = 302,
    Program = 400,
    Begin = 401,
    End = 402,
    Var = 403,
    Integer = 404,
    Real = 405,
    While = 406,
    Do = 407,
    If = 408,
    Then = 409,
    Else = 410,
    Or = 411,
    And = 412,
    Not = 413,
    For = 414,
    To = 415,
    Repeat = 416,
    Until = 417,
    Of = 418,
    Array = 419,
    LE = 500,
    GE = 501,
    NE = 502,
    ERRORCHAR = 600,
    UMINUS = 602
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 23 "pascal_yacc.y" /* yacc.c:355  */

	int Iv;                //类型                         
	int CH;                //CH表示链             
	int NO;                //NO表示变量在表中的下标
	struct { int TC,FC;} _BExpr;
	struct { int QUAD,CH;} _WBD;   //QUAD  相当于书中的 loopstartplace
	struct { int type,place;} _Expr;
	char _Rop[5];
	int First;
	char str[20];

	//抽象语法树的节点
	struct node *ast_node;
	//CH节点
	struct {
		int CH; 
		struct node *nd;
	} ch_node;
	//类型节点
	struct {
		//1 2 3 
		int type;
		// 1 2 
		int Iv; 
		int array_no;
		struct node *nd;
	} iv_node;
	//变量声明节点
	struct {
		int First; 
		struct node *nd;
	} first_node;
	//循环节点
	struct {
		int CH; 
		int QUAD; 
		struct node *nd;
	} wbd_node;
	//rop节点
	struct {
		char _Rop[5]; 
		struct node *nd;
	} rop_node;
	//表达式节点
	struct {
		int type, place; 
		struct node *nd;
	} exp_node;
	
	struct {
		int NO; 
		struct node *nd;
		} no_node;
	struct {
		int TC, FC, CH; 
		struct node *nd;
	} Bexp_node;

	//for循环节点
	struct {
		int loop, place, CH; 
		struct node *nd;
	} ForLoop_node;
	//变量节点
	struct {
		int NO;
		int OFFSET; //
		struct node* nd;
	}Variable_node;
	//ExprList
	struct {
		int NO; 	  //数组中变量名在符号表中的序号
		int DIM;      //用于记录已经处理的下标的表达式
		int tmp_place; //临时变量名的地址
		struct node* nd;
	}ExprList_node;
	
	//定义类型
	struct {
		int DIM;
		int NO; //数组名在符号表中的序号
		struct node* nd;
	}TypeFirst_node;

	//定义类型
	struct {
		int L;
		int U;
		struct node* nd;
	}OneDim_node;


#line 251 "pascal_yacc.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PASCAL_YACC_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 266 "pascal_yacc.c" /* yacc.c:358  */

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

#ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
# if (! defined __GNUC__ || __GNUC__ < 2 \
      || (__GNUC__ == 2 && __GNUC_MINOR__ < 5))
#  define __attribute__(Spec) /* empty */
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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   159

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  68
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  133

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   602

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
      44,    45,    35,    33,    42,    34,    39,    36,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    40,    38,
      30,    32,    31,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    43,     2,    41,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       3,     4,     5,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      26,    27,    28,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      29,     2,    37
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   197,   197,   233,   247,   266,   283,   296,   329,   346,
     364,   392,   420,   451,   478,   501,   523,   538,   556,   571,
     595,   609,   626,   645,   667,   689,   709,   725,   757,   762,
     789,   821,   846,   872,   901,   924,   948,   964,  1010,  1056,
    1104,  1149,  1173,  1194,  1221,  1240,  1261,  1279,  1297,  1318,
    1340,  1360,  1383,  1408,  1447,  1475,  1492,  1514,  1531,  1550,
    1564,  1579,  1593,  1607,  1621,  1637,  1654,  1683,  1699
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "Iden", "IntNo", "RealNo", "Program",
  "Begin", "End", "Var", "Integer", "Real", "While", "Do", "If", "Then",
  "Else", "Or", "And", "Not", "For", "To", "Repeat", "Until", "Of",
  "Array", "LE", "GE", "NE", "ERRORCHAR", "'<'", "'>'", "'='", "'+'",
  "'-'", "'*'", "'/'", "UMINUS", "';'", "'.'", "':'", "']'", "','", "'['",
  "'('", "')'", "$accept", "ProgDef", "SubProg", "VarDef", "VarDefList",
  "VarDefState", "Type", "TypeFirst", "OneDim", "VarList", "StateList",
  "S_L", "Statement", "ForLoop1", "ForLoop2", "CompState", "AsignState",
  "ISE", "IBT", "WBD", "Wh", "Expr", "BoolExpr", "BoolExpr_or",
  "BoolExpr_and", "ExprList", "Variable", "Const", "RelationOp", "DO",
  "DSW", "RE", "RSU", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   601,   300,   301,   302,   400,   401,   402,   403,
     404,   405,   406,   407,   408,   409,   410,   411,   412,   413,
     414,   415,   416,   417,   418,   419,   500,   501,   502,   600,
      60,    62,    61,    43,    45,    42,    47,   602,    59,    46,
      58,    93,    44,    91,    40,    41
};
# endif

#define YYPACT_NINF -40

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-40)))

#define YYTABLE_NINF -56

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      17,    12,    25,     0,   -40,    31,    45,    20,    58,    41,
      38,   -40,   -24,   -39,   -40,   -40,   112,   -40,     8,    45,
      -1,    45,   -40,     8,   -40,   -40,     3,    68,   -40,    -7,
     112,   -40,    62,    77,   -40,   -40,   112,   112,   112,     3,
      51,   112,     3,   112,     3,   -40,   -40,     8,     8,    53,
     -40,   -40,   -40,   -40,   -40,    49,   -40,   -21,   -40,    53,
     109,     3,     3,   123,    40,     3,     3,    56,   -40,   -40,
     -40,     8,   112,   -40,    81,   -40,    61,    69,    88,     9,
      79,     9,   -40,    28,     8,     8,     8,     8,    99,    92,
      99,   -40,    78,    15,   -40,   -40,   -40,   -40,   -40,   -40,
       8,   -40,   -40,   -40,     9,     9,    85,    53,   -40,   -40,
     -40,     8,   -40,   -40,   -40,    10,    10,   -40,   -40,    82,
     -40,    70,   -40,   -40,    53,     8,    53,    83,   -40,   -40,
      53,   114,   -40
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,     0,     0,     0,     0,    55,
       0,     6,     0,     0,    16,     2,    28,     3,     0,     4,
       0,     0,    56,     0,    36,    65,     0,     0,    67,     0,
      28,    18,     0,     0,    26,    20,    28,    28,    28,     0,
       0,     0,     0,    28,     0,    57,    58,     0,     0,    54,
      43,    44,     5,     8,     9,     0,     7,     0,    15,    53,
      50,     0,     0,     0,     0,     0,     0,     0,    31,    19,
      17,     0,    28,    21,    22,    23,     0,     0,     0,    24,
       0,    25,    42,     0,     0,     0,     0,     0,     0,     0,
       0,    48,     0,     0,    64,    62,    63,    59,    60,    61,
       0,    34,    51,    52,    47,    46,     0,    30,    27,    33,
      35,     0,    66,    68,    41,    37,    38,    39,    40,     0,
      13,     0,    12,    49,    45,     0,    32,     0,    10,    11,
      29,     0,    14
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -40,   -40,   -40,   -40,   -40,   101,   -40,   -40,    37,   -40,
     -40,   -40,    13,   -40,   -40,   120,   -40,   -40,   -40,   -40,
     -40,   -18,    33,   -40,   -40,   -40,    -2,   -40,   -40,   -40,
     -40,   -40,   -40
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     7,     8,    10,    11,    56,    57,   120,    12,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    63,    64,    65,    66,    13,    50,    51,   100,    41,
      42,    43,    44
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      49,    68,    22,    23,    14,    59,    60,    45,    46,    53,
      54,     9,    45,    46,    40,     3,    20,    14,    21,    58,
      89,    90,    61,     1,    55,     4,   102,   103,    40,    82,
      83,    69,   102,   103,    40,    40,    40,    47,     5,    40,
       6,    40,    47,    70,    92,    86,    87,    62,     9,    73,
      74,    75,    48,   107,    78,   101,    80,   102,   103,    15,
     123,    84,    85,    86,    87,    16,   115,   116,   117,   118,
      40,    67,    76,   114,   110,    79,    19,    81,   102,   103,
     128,   129,   124,    71,    18,   108,    84,    85,    86,    87,
      72,    77,    88,   126,    91,    93,   106,   109,   104,   105,
     112,   111,   113,   119,    94,    95,    96,   130,    97,    98,
      99,    84,    85,    86,    87,     9,   121,   125,   132,    16,
      52,   127,   131,   114,    24,    25,    26,   122,    17,     0,
       0,     0,    27,     0,    28,   -55,   -55,   -55,     0,   -55,
     -55,   -55,   -55,   -55,   -55,   -55,     0,     0,     0,    94,
      95,    96,    18,    97,    98,    99,    84,    85,    86,    87
};

static const yytype_int8 yycheck[] =
{
      18,     8,    41,    42,     6,    23,     3,     4,     5,    10,
      11,     3,     4,     5,    16,     3,    40,    19,    42,    21,
      41,    42,    19,     6,    25,     0,    17,    18,    30,    47,
      48,    38,    17,    18,    36,    37,    38,    34,    38,    41,
       9,    43,    34,    30,    62,    35,    36,    44,     3,    36,
      37,    38,    44,    71,    41,    15,    43,    17,    18,    39,
      45,    33,    34,    35,    36,     7,    84,    85,    86,    87,
      72,     3,    39,    45,    13,    42,    38,    44,    17,    18,
      10,    11,   100,    21,    43,    72,    33,    34,    35,    36,
      13,    40,    43,   111,    61,    62,    40,    16,    65,    66,
      12,    32,    23,     4,    26,    27,    28,   125,    30,    31,
      32,    33,    34,    35,    36,     3,    24,    32,     4,     7,
      19,    39,    39,    45,    12,    13,    14,    90,     8,    -1,
      -1,    -1,    20,    -1,    22,    26,    27,    28,    -1,    30,
      31,    32,    33,    34,    35,    36,    -1,    -1,    -1,    26,
      27,    28,    43,    30,    31,    32,    33,    34,    35,    36
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,    47,     3,     0,    38,     9,    48,    49,     3,
      50,    51,    55,    71,    72,    39,     7,    61,    43,    38,
      40,    42,    41,    42,    12,    13,    14,    20,    22,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      72,    75,    76,    77,    78,     4,     5,    34,    44,    67,
      72,    73,    51,    10,    11,    25,    52,    53,    72,    67,
       3,    19,    44,    67,    68,    69,    70,     3,     8,    38,
      58,    21,    13,    58,    58,    58,    68,    40,    58,    68,
      58,    68,    67,    67,    33,    34,    35,    36,    43,    41,
      42,    68,    67,    68,    26,    27,    28,    30,    31,    32,
      74,    15,    17,    18,    68,    68,    40,    67,    58,    16,
      13,    32,    12,    23,    45,    67,    67,    67,    67,     4,
      54,    24,    54,    45,    67,    32,    67,    39,    10,    11,
      67,    39,     4
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    46,    47,    48,    49,    50,    50,    51,    52,    52,
      52,    52,    53,    53,    54,    55,    55,    56,    56,    57,
      58,    58,    58,    58,    58,    58,    58,    58,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    67,    67,
      67,    67,    67,    67,    67,    68,    68,    68,    68,    68,
      68,    69,    70,    71,    71,    72,    72,    73,    73,    74,
      74,    74,    74,    74,    74,    75,    76,    77,    78
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     5,     2,     3,     3,     1,     3,     1,     1,
       4,     4,     3,     3,     4,     3,     1,     2,     1,     2,
       1,     2,     2,     2,     2,     2,     1,     3,     0,     5,
       3,     3,     4,     3,     3,     3,     1,     3,     3,     3,
       3,     3,     2,     1,     1,     3,     2,     2,     2,     3,
       1,     2,     2,     3,     3,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     3
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
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
#line 198 "pascal_yacc.y" /* yacc.c:1646  */
    {
				//printf("\n分析成功\n");
				set_node_val_str(&ast_root,(yyvsp[-3].str));

				struct node *tmpnode=NULL;
				//printf("\n\n**** test ast node ****\n\n");
				(yyval.ast_node)=&ast_root;
				struct node *node1,*node2, *node3,*node4;   //添加四个节点

				complete_init_node(&node1, "Program");
				int re = add_son_node(&ast_root, node1);
				

				complete_init_node(&node2, (yyvsp[-3].str));
				//printf("In ProgDef: %s\n", node2->val.str);
				re = add_brother_node(node1, node2);
				
				complete_init_node(&node3, ";");
				//printf("In ProgDef: %s\n", node3->val.str);
				re = add_brother_node(node2,node3);     
				/*     
				if (re != ADD_BROTHER_NODE_SUCCESS || re != ADD_SON_NODE_SUCCESS){
					printf("Add brother error: %d\n", re);
				} */

				//子程序已经初始化好了，只需设置名字
				set_node_val_str((yyvsp[-1].ast_node), "SubProg");          
				//printf("In ProgDef: %s\n", $4->val.str);
				add_brother_node(node3, (yyvsp[-1].ast_node));

				complete_init_node(&node4, ".");
				//printf("In ProgDef: %s\n", node4->val.str);
				add_brother_node((yyvsp[-1].ast_node), node4);
}
#line 1486 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 3:
#line 234 "pascal_yacc.y" /* yacc.c:1646  */
    {
		//初始化左值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.ast_node) = cur;
		//设置右值
		set_node_val_str((yyvsp[-1].ch_node).nd,"VarDef");
		set_node_val_str((yyvsp[0].ch_node).nd,"CompState");
		//建立关系
		add_son_node((yyval.ast_node),(yyvsp[-1].ch_node).nd);
		add_brother_node((yyvsp[-1].ch_node).nd,(yyvsp[0].ch_node).nd);    	
		}
#line 1503 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 4:
#line 248 "pascal_yacc.y" /* yacc.c:1646  */
    {
		//初始化左值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.ch_node).nd = cur;
		//初始化右值
		struct node *node1, *node2;
		complete_init_node(&node1, "Var");
		complete_init_node(&node2, ";");
		set_node_val_str((yyvsp[-1].ch_node).nd,"VarDefList");
		//建立关系
		add_son_node((yyval.ch_node).nd ,node1);
		add_brother_node(node1,(yyvsp[-1].ch_node).nd); 
		add_brother_node((yyvsp[-1].ch_node).nd,node2);  


		}
#line 1525 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 5:
#line 267 "pascal_yacc.y" /* yacc.c:1646  */
    {
		//puts("reduce real");
		//初始化左值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.ch_node).nd = cur;
		//初始化右值
		struct node *node1;
		complete_init_node(&node1, ";");
		set_node_val_str((yyvsp[-2].ch_node).nd,"VarDefList");
		set_node_val_str((yyvsp[0].ch_node).nd,"VarDefState");
		//建立关系
		add_son_node((yyval.ch_node).nd ,(yyvsp[-2].ch_node).nd);
		add_brother_node((yyvsp[-2].ch_node).nd,node1); 
		add_brother_node(node1,(yyvsp[0].ch_node).nd);  
		}
#line 1546 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 6:
#line 284 "pascal_yacc.y" /* yacc.c:1646  */
    {
		//puts("reduce real");
		//初始化左值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.ch_node).nd = cur;
		//初始化右值
		set_node_val_str((yyvsp[0].ch_node).nd,"VarDefState");
		//建立关系
		add_son_node((yyval.ch_node).nd ,(yyvsp[0].ch_node).nd);
        }
#line 1562 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 7:
#line 297 "pascal_yacc.y" /* yacc.c:1646  */
    {
		
		//初始化左值
		//puts("AAA");
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.ch_node).nd = cur;
		//将Type类型赋值给VarList所有变量，也是一个回填的操作
		//puts("AAAen");
		//printf("%d\n",$3.Iv);
		if ((yyvsp[0].iv_node).type == INT || (yyvsp[0].iv_node).type == REAL) {
			VarBackPatch((yyvsp[-2].first_node).First, (yyvsp[0].iv_node).type);
		}
		else {
			VarBackArrayPatch((yyvsp[-2].first_node).First, (yyvsp[0].iv_node).type, (yyvsp[0].iv_node).Iv, (yyvsp[0].iv_node).array_no);
		}
		
		//puts("AAAend");
		//printf("Patch: First:%d \n", $1.First);
		//初始化右值
		struct node *node1;
		complete_init_node(&node1, ":");
		set_node_val_str((yyvsp[-2].first_node).nd,"VarList");
		set_node_val_str((yyvsp[0].iv_node).nd,"Type");
		//建立关系
		add_son_node((yyval.ch_node).nd ,(yyvsp[-2].first_node).nd);
		add_brother_node((yyvsp[-2].first_node).nd,node1); 
		add_brother_node(node1,(yyvsp[0].iv_node).nd);  
		//puts("AAAend");

		}
#line 1598 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 8:
#line 330 "pascal_yacc.y" /* yacc.c:1646  */
    {
		//printf("INTAAA\n");
		//初始化左值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.iv_node).nd = cur;
		//类型设置为整型
		(yyval.iv_node).type = INT;
		(yyval.iv_node).Iv = 0;
		struct node *node1;
		complete_init_node(&node1, "Integer");

		add_son_node((yyval.iv_node).nd, node1);
		
		
		}
#line 1619 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 9:
#line 347 "pascal_yacc.y" /* yacc.c:1646  */
    {
		//printf("REALAAA\n");
		//初始化左值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.iv_node).nd = cur;
		//初始化右值
		//类型设置为实型
		(yyval.iv_node).type = REAL;
		(yyval.iv_node).Iv = 0;
		struct node *node1;
		complete_init_node(&node1, "Real");

		add_son_node((yyval.iv_node).nd, node1);


		}
#line 1641 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 10:
#line 365 "pascal_yacc.y" /* yacc.c:1646  */
    {
		//printf("REALAAA\n");
		//初始化左值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.iv_node).nd = cur;

		//初始化右值
		//类型设置为整型
		(yyval.iv_node).type = ARRAY;
		(yyval.iv_node).Iv = INT;

		//注意上传数组在类型表中的位置
		(yyval.iv_node).array_no = (yyvsp[-3].TypeFirst_node).NO;
		struct node *node1, *node2, *node3;
		complete_init_node(&node1, "]");
		complete_init_node(&node2, "Of");
		complete_init_node(&node3, "Integer");
		set_node_val_str((yyvsp[-3].TypeFirst_node).nd,"TypeFirst");

		//建立关系
		add_son_node((yyval.iv_node).nd ,(yyvsp[-3].TypeFirst_node).nd);
		add_brother_node((yyvsp[-3].TypeFirst_node).nd,node1); 
		add_brother_node(node1,node2);  
		add_brother_node(node2,node3);  

		}
#line 1673 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 11:
#line 393 "pascal_yacc.y" /* yacc.c:1646  */
    {
		//printf("REALAAA\n");
		//初始化左值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.iv_node).nd = cur;

		//初始化右值
		//类型设置为实型
		(yyval.iv_node).type = ARRAY;
		(yyval.iv_node).Iv = REAL;
		//注意上传数组在类型表中的位置
		(yyval.iv_node).array_no = (yyvsp[-3].TypeFirst_node).NO;

		struct node *node1, *node2, *node3;
		complete_init_node(&node1, "]");
		complete_init_node(&node2, "Of");
		complete_init_node(&node3, "Real");
		set_node_val_str((yyvsp[-3].TypeFirst_node).nd,"TypeFirst");

		//建立关系
		add_son_node((yyval.iv_node).nd ,(yyvsp[-3].TypeFirst_node).nd);
		add_brother_node((yyvsp[-3].TypeFirst_node).nd,node1); 
		add_brother_node(node1,node2);  
		add_brother_node(node2,node3);  
		}
#line 1704 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 12:
#line 421 "pascal_yacc.y" /* yacc.c:1646  */
    {
		//printf("REALAAA\n");
		//初始化左值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.TypeFirst_node).nd = cur;
		
		//更新D和C
		int k = (yyvsp[-2].TypeFirst_node).DIM + 1;
		Update_C((yyvsp[-2].TypeFirst_node).NO, k, (yyvsp[0].OneDim_node).L, (yyvsp[0].OneDim_node).U);
		Update_D((yyvsp[-2].TypeFirst_node).NO, k, (yyvsp[0].OneDim_node).L, (yyvsp[0].OneDim_node).U);


		//更新typefirst
		(yyval.TypeFirst_node).NO = (yyvsp[-2].TypeFirst_node).NO;
		(yyval.TypeFirst_node).DIM = k;


		struct node *node1;
		complete_init_node(&node1, ",");
		set_node_val_str((yyvsp[0].OneDim_node).nd,"OneDim");
		set_node_val_str((yyvsp[-2].TypeFirst_node).nd,"TypeFirst");

		//建立关系
		add_son_node((yyval.TypeFirst_node).nd, (yyvsp[-2].TypeFirst_node).nd);
		add_brother_node((yyvsp[-2].TypeFirst_node).nd,node1); 
		add_brother_node(node1,(yyvsp[0].OneDim_node).nd);  

			
		}
#line 1739 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 13:
#line 452 "pascal_yacc.y" /* yacc.c:1646  */
    {
		//printf("REALAAA\n");
		//初始化左值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.TypeFirst_node).nd = cur;

		(yyval.TypeFirst_node).DIM = 1;
		(yyval.TypeFirst_node).NO = New_Array_Type();
		Update_D((yyval.TypeFirst_node).NO, (yyval.TypeFirst_node).DIM, (yyvsp[0].OneDim_node).L, (yyvsp[0].OneDim_node).U);


		struct node *node1, *node2;
		complete_init_node(&node1, "Array");
		complete_init_node(&node2, "[");
		set_node_val_str((yyvsp[0].OneDim_node).nd,"OneDim");

		//建立关系
		add_son_node((yyval.TypeFirst_node).nd, node1);
		add_brother_node(node1,node2); 
		add_brother_node(node2,(yyvsp[0].OneDim_node).nd);  

		}
#line 1767 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 14:
#line 479 "pascal_yacc.y" /* yacc.c:1646  */
    {
		//printf("REALAAA\n");
		//初始化左值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.OneDim_node).nd = cur;

		(yyval.OneDim_node).L = atoi((yyvsp[-3].str));
		(yyval.OneDim_node).U = atoi((yyvsp[0].str));

		struct node *node1, *node2, *node3;
		complete_init_node(&node1, (yyvsp[-3].str));
		complete_init_node(&node2, "..");
		complete_init_node(&node3, (yyvsp[0].str));

		//建立关系
		add_son_node((yyval.OneDim_node).nd, node1);
		add_brother_node(node1,node2); 
		add_brother_node(node2,node3);  


	}
#line 1794 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 15:
#line 502 "pascal_yacc.y" /* yacc.c:1646  */
    {
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.first_node).nd = cur;
		
	
		//初始化右值
		struct node*node1;
		complete_init_node(&node1, ",");

		set_node_val_str((yyvsp[-2].first_node).nd, "VarList");
		set_node_val_str((yyvsp[0].Variable_node).nd, "Variable");
		//关系
		add_son_node((yyval.first_node).nd, (yyvsp[-2].first_node).nd);
		add_brother_node((yyvsp[-2].first_node).nd, node1);
		add_brother_node(node1, (yyvsp[0].Variable_node).nd);
		//将变量连接起来，因为变量定义的时候会出现 Var a,b,c:integer的情况
		//所以需要保存First保存链头,这里是$1.First.addr = $3.NO
		(yyval.first_node).First = Merge_var((yyvsp[0].Variable_node).NO, (yyvsp[-2].first_node).First);
		//printf("First:%d \n", $$.First);
		}
#line 1820 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 16:
#line 524 "pascal_yacc.y" /* yacc.c:1646  */
    {
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.first_node).nd = cur;
		//传递变量的符号，最终Varlist.First 保存的是第一个变量的place
		(yyval.first_node).First = (yyvsp[0].Variable_node).NO;
		//初始化右值

		set_node_val_str((yyvsp[0].Variable_node).nd, "Variable");
		//关系
		add_son_node((yyval.first_node).nd, (yyvsp[0].Variable_node).nd);
		}
#line 1837 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 17:
#line 539 "pascal_yacc.y" /* yacc.c:1646  */
    {
		//printf("test for StateList\n");
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.ch_node).nd = cur;
		//此处传递的是$2链的出口
		(yyval.ch_node).CH = (yyvsp[0].ch_node).CH;
	
		//初始化右值
		set_node_val_str((yyvsp[-1].ch_node).nd, "S_L");
		set_node_val_str((yyvsp[0].ch_node).nd, "Statement");
		
		//关系
		add_son_node((yyval.ch_node).nd, (yyvsp[-1].ch_node).nd);
		add_brother_node((yyvsp[-1].ch_node).nd, (yyvsp[0].ch_node).nd);
		}
#line 1859 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 18:
#line 557 "pascal_yacc.y" /* yacc.c:1646  */
    {
		//给左边非终结符赋值

		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.ch_node).nd = cur;
		//传递
		(yyval.ch_node).CH = (yyvsp[0].ch_node).CH;

		set_node_val_str((yyvsp[0].ch_node).nd, "Statement");
		//关系
		add_son_node((yyval.ch_node).nd, (yyvsp[0].ch_node).nd);
		}
#line 1877 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 19:
#line 572 "pascal_yacc.y" /* yacc.c:1646  */
    {
		//printf("test for State_L\n");
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.ch_node).nd = cur;
		//!!!!!!!!!!!!!!!!!!!!
		///此时分析器刚分析完分号，控制流程将继续顺序执行
		//所以下一个四元式的序号回填StateList的出口链
		//$$.CH = $1.CH;
		BackPatch((yyvsp[-1].ch_node).CH, NXQ);
		//初始化右值
		struct node *node1;
		complete_init_node(&node1, ";");

		set_node_val_str((yyvsp[-1].ch_node).nd, "StateList");
		
		
		//关系
		add_son_node((yyval.ch_node).nd, (yyvsp[-1].ch_node).nd);
		add_brother_node((yyvsp[-1].ch_node).nd, node1);
		}
#line 1904 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 20:
#line 596 "pascal_yacc.y" /* yacc.c:1646  */
    {
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.ch_node).nd = cur;

		//链为0 表示为链的终止处
		(yyval.ch_node).CH = 0;

		set_node_val_str((yyvsp[0].ch_node).nd, "AsignState");
		//关系
		add_son_node((yyval.ch_node).nd, (yyvsp[0].ch_node).nd);
		}
#line 1922 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 21:
#line 610 "pascal_yacc.y" /* yacc.c:1646  */
    {
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.ch_node).nd = cur;
		//此时布尔表达式的假出口应该和statement的出口一致
		//合并s1和s2的出口
		(yyval.ch_node).CH = Merge((yyvsp[-1].ch_node).CH, (yyvsp[0].ch_node).CH);

		set_node_val_str((yyvsp[-1].ch_node).nd, "ISE");
		set_node_val_str((yyvsp[0].ch_node).nd, "Statement");
		
		//关系
		add_son_node((yyval.ch_node).nd, (yyvsp[-1].ch_node).nd);
		add_brother_node((yyvsp[-1].ch_node).nd, (yyvsp[0].ch_node).nd);

		}
#line 1943 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 22:
#line 627 "pascal_yacc.y" /* yacc.c:1646  */
    {
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.ch_node).nd = cur;
		//此时布尔表达式的假出口应该和statement的出口一致
		(yyval.ch_node).CH = Merge((yyvsp[-1].ch_node).CH, (yyvsp[0].ch_node).CH);

		set_node_val_str((yyvsp[-1].ch_node).nd, "IBT");
		set_node_val_str((yyvsp[0].ch_node).nd, "Statement");
		
		//关系
		add_son_node((yyval.ch_node).nd, (yyvsp[-1].ch_node).nd);
		add_brother_node((yyvsp[-1].ch_node).nd, (yyvsp[0].ch_node).nd);


		}
#line 1965 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 23:
#line 646 "pascal_yacc.y" /* yacc.c:1646  */
    {
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.ch_node).nd = cur;
		
		BackPatch((yyvsp[0].ch_node).CH, (yyvsp[-1].wbd_node).QUAD);
		//此时应无条件返回到循环初始的位置
		GEN("j", 0, 0, (yyvsp[-1].wbd_node).QUAD);
		//此时布尔表达式的假出口传递
		(yyval.ch_node).CH = (yyvsp[-1].wbd_node).CH;

		set_node_val_str((yyvsp[-1].wbd_node).nd, "IBT");
		set_node_val_str((yyvsp[0].ch_node).nd, "Statement");
		
		//关系
		add_son_node((yyval.ch_node).nd, (yyvsp[-1].wbd_node).nd);
		add_brother_node((yyvsp[-1].wbd_node).nd, (yyvsp[0].ch_node).nd);


		}
#line 1991 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 24:
#line 668 "pascal_yacc.y" /* yacc.c:1646  */
    {
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.ch_node).nd = cur;
		
		//回填bool表达式的真出口
		BackPatch((yyvsp[0].Bexp_node).TC, (yyvsp[-1].ForLoop_node).loop);
		//将bool表达式的假出口上传
		(yyval.ch_node).CH = (yyvsp[0].Bexp_node).FC;


		set_node_val_str((yyvsp[-1].ForLoop_node).nd, "DSW");
		set_node_val_str((yyvsp[0].Bexp_node).nd, "BoolExpr");
		
		//关系
		add_son_node((yyval.ch_node).nd, (yyvsp[-1].ForLoop_node).nd);
		add_brother_node((yyvsp[-1].ForLoop_node).nd, (yyvsp[0].Bexp_node).nd);

		
		}
#line 2017 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 25:
#line 690 "pascal_yacc.y" /* yacc.c:1646  */
    {

		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.ch_node).nd = cur;
		//回填bool表达式的假出口
		BackPatch((yyvsp[0].Bexp_node).FC, (yyvsp[-1].ForLoop_node).loop);
		//将bool表达式的假真出口上传
		(yyval.ch_node).CH = (yyvsp[0].Bexp_node).TC;

		set_node_val_str((yyvsp[-1].ForLoop_node).nd, "DSW");
		set_node_val_str((yyvsp[0].Bexp_node).nd, "BoolExpr");
		
		//关系
		add_son_node((yyval.ch_node).nd, (yyvsp[-1].ForLoop_node).nd);
		add_brother_node((yyvsp[-1].ForLoop_node).nd, (yyvsp[0].Bexp_node).nd);
		
		}
#line 2041 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 26:
#line 710 "pascal_yacc.y" /* yacc.c:1646  */
    {
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.ch_node).nd = cur;
		//此时出口向上传递
		(yyval.ch_node).CH = (yyvsp[0].ch_node).CH;

		set_node_val_str((yyvsp[0].ch_node).nd, "CompState");

		//关系
		add_son_node((yyval.ch_node).nd, (yyvsp[0].ch_node).nd);


		}
#line 2061 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 27:
#line 725 "pascal_yacc.y" /* yacc.c:1646  */
    {
			
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.ch_node).nd = cur;
		//此时控制变量自增的四元式是下一条，
		//对statement进行回填
		BackPatch((yyvsp[0].ch_node).CH, NXQ);
		//控制变量自增的四元式
		GEN("+", (yyvsp[-2].ForLoop_node).place, Entry("1"), (yyvsp[-2].ForLoop_node).place);

		//返回循环起始节点
		GEN("j", 0, 0, (yyvsp[-2].ForLoop_node).loop);

		//传递出口
		(yyval.ch_node).CH = (yyvsp[-2].ForLoop_node).CH;
		
		struct node* node1;
		complete_init_node(&node1, "Do");

		set_node_val_str((yyvsp[-2].ForLoop_node).nd, "ForLoop2");
		set_node_val_str((yyvsp[0].ch_node).nd, "Statement");
		
		
		//关系
		add_son_node((yyval.ch_node).nd, (yyvsp[-2].ForLoop_node).nd);
		add_brother_node((yyvsp[-2].ForLoop_node).nd, node1);
		add_brother_node(node1, (yyvsp[0].ch_node).nd);

	    }
#line 2097 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 28:
#line 757 "pascal_yacc.y" /* yacc.c:1646  */
    {    //需要这个为空也是 有意义的！！！！！！！
	//   StateList:	S_L Statement
	//因为存在上述文法，所以Statement可以为空
	}
#line 2106 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 29:
#line 763 "pascal_yacc.y" /* yacc.c:1646  */
    {
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.ForLoop_node).nd = cur;
		
		int i = Entry((yyvsp[-3].str));
		//此时生成赋值四元式
		GEN(":=", (yyvsp[0].exp_node).place, 0, i);
		//将控制变量所在的位置传递
		(yyval.ForLoop_node).place = i;

		//初始化右值
		struct node* node1,*node2, *node3;
		complete_init_node(&node1, "For");
		complete_init_node(&node2, (yyvsp[-3].str));
		complete_init_node(&node3, ":=");
		set_node_val_str((yyvsp[0].exp_node).nd, "Expr");
		
		
		//关系
		add_son_node((yyval.ForLoop_node).nd, node1);
		add_brother_node(node1, node2);
		add_brother_node(node2, node3);
		add_brother_node(node3, (yyvsp[0].exp_node).nd);
}
#line 2137 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 30:
#line 790 "pascal_yacc.y" /* yacc.c:1646  */
    {
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.ForLoop_node).nd = cur;
		
		int p = NXQ;
		//传递循环返回点信息，loop指向循环体的第一条四元式
		(yyval.ForLoop_node).loop = NXQ;

		//此时生成赋值四元式
		GEN("j<", (yyvsp[-2].ForLoop_node).place, (yyvsp[0].exp_node).place, p+2);
		//将控制变量所在的位置传递
		(yyval.ForLoop_node).place = (yyvsp[-2].ForLoop_node).place;
		//循环语句的出口
		(yyval.ForLoop_node).CH = NXQ;
		GEN("j", 0, 0, 0);
		//初始化右值
		struct node* node1;
		complete_init_node(&node1, "To");

		set_node_val_str((yyvsp[-2].ForLoop_node).nd, "ForLoop1");
		set_node_val_str((yyvsp[0].exp_node).nd, "Expr");
		
		
		//关系
		add_son_node((yyval.ForLoop_node).nd, (yyvsp[-2].ForLoop_node).nd);
		add_brother_node((yyvsp[-2].ForLoop_node).nd, node1);
		add_brother_node(node1, (yyvsp[0].exp_node).nd);
}
#line 2172 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 31:
#line 822 "pascal_yacc.y" /* yacc.c:1646  */
    {
		//printf("test for begin and end\n");
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.ch_node).nd = cur;
		
		(yyval.ch_node).CH = (yyvsp[-1].ch_node).CH;
	
		//初始化右值
		struct node*node1,*node2;
		complete_init_node(&node1, "Begin");
		complete_init_node(&node2, "End");

		
		set_node_val_str((yyvsp[-1].ch_node).nd, "StateList");
		
		//关系
		add_son_node((yyval.ch_node).nd, node1);
		add_brother_node(node1, (yyvsp[-1].ch_node).nd);
		add_brother_node((yyvsp[-1].ch_node).nd, node2);

		}
#line 2200 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 32:
#line 847 "pascal_yacc.y" /* yacc.c:1646  */
    {

		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.ch_node).nd = cur;
		
		//对于赋值语句生成四元式
		GEN(":=", (yyvsp[0].exp_node).place, 0, (yyvsp[-3].Variable_node).NO);
	
		//初始化右值
		struct node*node1;
		complete_init_node(&node1, ":=");

		
		set_node_val_str((yyvsp[-3].Variable_node).nd, "Variable");
		set_node_val_str((yyvsp[0].exp_node).nd, "Expr");
		
		//关系
		add_son_node((yyval.ch_node).nd, (yyvsp[-3].Variable_node).nd);
		add_brother_node((yyvsp[-3].Variable_node).nd, node1);
		add_brother_node(node1, (yyvsp[0].exp_node).nd);

		}
#line 2229 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 33:
#line 873 "pascal_yacc.y" /* yacc.c:1646  */
    {

		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.ch_node).nd = cur;
		int q = NXQ;
		//需要添加一个四元式，跳入真出口
		GEN("j",0,0,0);

		//此时下一个四元式，为假出口，所以需要回填
		BackPatch((yyvsp[-2].ch_node).CH, NXQ);
		//通过合并真出口和假出口为整个S的出口
		(yyval.ch_node).CH = Merge((yyvsp[-1].ch_node).CH, q);

		set_node_val_str((yyvsp[-2].ch_node).nd, "IBT");
		set_node_val_str((yyvsp[-1].ch_node).nd, "Statement");
		struct node * node1;
		complete_init_node(&node1, "Else");

		//关系
		add_son_node((yyval.ch_node).nd, (yyvsp[-2].ch_node).nd);
		add_brother_node((yyvsp[-2].ch_node).nd, (yyvsp[-1].ch_node).nd);
		add_brother_node((yyvsp[-1].ch_node).nd, node1);


		}
#line 2261 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 34:
#line 902 "pascal_yacc.y" /* yacc.c:1646  */
    {
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.ch_node).nd = cur;
		//此时下一个四元式，为真出口，所以需要回填
		BackPatch((yyvsp[-1].Bexp_node).TC, NXQ);
		//假出口还不确定
		(yyval.ch_node).CH = (yyvsp[-1].Bexp_node).FC;


		set_node_val_str((yyvsp[-1].Bexp_node).nd, "BoolExpr");
		struct node * node1, *node2;
		complete_init_node(&node1, "IF");
		complete_init_node(&node2, "Then");
		//关系
		add_son_node((yyval.ch_node).nd, node1);
		add_brother_node(node1, (yyvsp[-1].Bexp_node).nd);
		add_brother_node((yyvsp[-1].Bexp_node).nd, node2);
		}
#line 2286 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 35:
#line 925 "pascal_yacc.y" /* yacc.c:1646  */
    {
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.wbd_node).nd = cur;
		//此时下一个四元式，为真出口，所以需要回填
		BackPatch((yyvsp[-1].Bexp_node).TC, NXQ);
		//假出口还不确定
		(yyval.wbd_node).CH = (yyvsp[-1].Bexp_node).FC;
		//传递起始地址
		(yyval.wbd_node).QUAD = (yyvsp[-2].ch_node).CH;

		set_node_val_str((yyvsp[-2].ch_node).nd, "Wh");
		set_node_val_str((yyvsp[-1].Bexp_node).nd, "BoolExpr");
		struct node * node1;
		complete_init_node(&node1, "Do");
		//关系
		add_son_node((yyval.wbd_node).nd, (yyvsp[-2].ch_node).nd);
		add_brother_node((yyvsp[-2].ch_node).nd, (yyvsp[-1].Bexp_node).nd);
		add_brother_node((yyvsp[-1].Bexp_node).nd, node1);

		}
#line 2313 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 36:
#line 949 "pascal_yacc.y" /* yacc.c:1646  */
    {
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.ch_node).nd = cur;
		//设置下一个四元式为链
		(yyval.ch_node).CH = NXQ;
		struct node* node1;
		complete_init_node(&node1, "While");
		//关系
		add_son_node((yyval.ch_node).nd, node1);
        }
#line 2330 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 37:
#line 965 "pascal_yacc.y" /* yacc.c:1646  */
    {
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.exp_node).nd = cur;
		
		int T = NewTemp();
		//对于算数操作生成四元式,如果有一个是real就要把int型进行强制转换
		if ((yyvsp[-2].exp_node).type == INT && (yyvsp[0].exp_node).type == INT)
		{
			GEN("+", (yyvsp[-2].exp_node).place, (yyvsp[0].exp_node).place, T);
			(yyval.exp_node).type = INT;
		}else if ((yyvsp[-2].exp_node).type == REAL && (yyvsp[0].exp_node).type == REAL)
		{
			GEN("+r", (yyvsp[-2].exp_node).place, (yyvsp[0].exp_node).place, T);
			(yyval.exp_node).type = REAL;
		}else if ((yyvsp[-2].exp_node).type == INT)
		{
			int U = NewTemp();
			GEN("itr", (yyvsp[-2].exp_node).place, 0, U);
			GEN("+r", U, (yyvsp[0].exp_node).place, T);
			(yyval.exp_node).type = REAL;
		}else if ((yyvsp[-2].exp_node).type == REAL)
		{
			int U = NewTemp();
			GEN("itr", (yyvsp[0].exp_node).place, 0, U);
			GEN("+r", (yyvsp[-2].exp_node).place, U, T);
			(yyval.exp_node).type = REAL;
		}
		(yyval.exp_node).place = T;
	
		//初始化右值
		struct node*node1;
		complete_init_node(&node1, "+");

		set_node_val_str((yyvsp[-2].exp_node).nd, "Expr");
		set_node_val_str((yyvsp[0].exp_node).nd, "Expr");
		
		//关系
		add_son_node((yyval.exp_node).nd, (yyvsp[-2].exp_node).nd);
		add_brother_node((yyvsp[-2].exp_node).nd, node1);
		add_brother_node(node1, (yyvsp[0].exp_node).nd);


		}
#line 2380 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 38:
#line 1011 "pascal_yacc.y" /* yacc.c:1646  */
    {
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.exp_node).nd = cur;
		
		int T = NewTemp();
		//对于算数操作生成四元式,如果有一个是real就要把int型进行强制转换
		if ((yyvsp[-2].exp_node).type == INT && (yyvsp[0].exp_node).type == INT)
		{
			GEN("-", (yyvsp[-2].exp_node).place, (yyvsp[0].exp_node).place, T);
			(yyval.exp_node).type = INT;
		}else if ((yyvsp[-2].exp_node).type == REAL && (yyvsp[0].exp_node).type == REAL)
		{
			GEN("-r", (yyvsp[-2].exp_node).place, (yyvsp[0].exp_node).place, T);
			(yyval.exp_node).type = REAL;
		}else if ((yyvsp[-2].exp_node).type == INT)
		{
			int U = NewTemp();
			GEN("itr", (yyvsp[-2].exp_node).place, 0, U);
			GEN("-r", U, (yyvsp[0].exp_node).place, T);
			(yyval.exp_node).type = REAL;
		}else if ((yyvsp[-2].exp_node).type == REAL)
		{
			int U = NewTemp();
			GEN("itr", (yyvsp[0].exp_node).place, 0, U);
			GEN("-r", (yyvsp[-2].exp_node).place, U, T);
			(yyval.exp_node).type = REAL;
		}
		(yyval.exp_node).place = T;
	
		//初始化右值
		struct node*node1;
		complete_init_node(&node1, "-");

		set_node_val_str((yyvsp[-2].exp_node).nd, "Expr");
		set_node_val_str((yyvsp[0].exp_node).nd, "Expr");
		
		//关系
		add_son_node((yyval.exp_node).nd, (yyvsp[-2].exp_node).nd);
		add_brother_node((yyvsp[-2].exp_node).nd, node1);
		add_brother_node(node1, (yyvsp[0].exp_node).nd);

		}
#line 2429 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 39:
#line 1057 "pascal_yacc.y" /* yacc.c:1646  */
    {
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.exp_node).nd = cur;
		
		int T = NewTemp();
		//对于算数操作生成四元式,如果有一个是real就要把int型进行强制转换
		if ((yyvsp[-2].exp_node).type == INT && (yyvsp[0].exp_node).type == INT)
		{
			GEN("*", (yyvsp[-2].exp_node).place, (yyvsp[0].exp_node).place, T);
			(yyval.exp_node).type = INT;
		}else if ((yyvsp[-2].exp_node).type == REAL && (yyvsp[0].exp_node).type == REAL)
		{
			GEN("*r", (yyvsp[-2].exp_node).place, (yyvsp[0].exp_node).place, T);
			(yyval.exp_node).type = REAL;
		}else if ((yyvsp[-2].exp_node).type == INT)
		{
			int U = NewTemp();
			GEN("itr", (yyvsp[-2].exp_node).place, 0, U);
			GEN("*r", U, (yyvsp[0].exp_node).place, T);
			(yyval.exp_node).type = REAL;
		}else if ((yyvsp[-2].exp_node).type == REAL)
		{
			int U = NewTemp();
			GEN("itr", (yyvsp[0].exp_node).place, 0, U);
			GEN("*r", (yyvsp[-2].exp_node).place, U, T);
			(yyval.exp_node).type = REAL;
		}
		(yyval.exp_node).place = T;
	
		//初始化右值
		struct node*node1;
		complete_init_node(&node1, "*");

		set_node_val_str((yyvsp[-2].exp_node).nd, "Expr");
		set_node_val_str((yyvsp[0].exp_node).nd, "Expr");
		
		//关系
		add_son_node((yyval.exp_node).nd, (yyvsp[-2].exp_node).nd);
		add_brother_node((yyvsp[-2].exp_node).nd, node1);
		add_brother_node(node1, (yyvsp[0].exp_node).nd);




		}
#line 2481 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 40:
#line 1105 "pascal_yacc.y" /* yacc.c:1646  */
    {
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.exp_node).nd = cur;
		
		int T = NewTemp();
		//对于算数操作生成四元式,如果有一个是real就要把int型进行强制转换
		if ((yyvsp[-2].exp_node).type == INT && (yyvsp[0].exp_node).type == INT)
		{
			GEN("/", (yyvsp[-2].exp_node).place, (yyvsp[0].exp_node).place, T);
			(yyval.exp_node).type = INT;
		}else if ((yyvsp[-2].exp_node).type == REAL && (yyvsp[0].exp_node).type == REAL)
		{
			GEN("/r", (yyvsp[-2].exp_node).place, (yyvsp[0].exp_node).place, T);
			(yyval.exp_node).type = REAL;
		}else if ((yyvsp[-2].exp_node).type == INT)
		{
			int U = NewTemp();
			GEN("itr", (yyvsp[-2].exp_node).place, 0, U);
			GEN("/r", U, (yyvsp[0].exp_node).place, T);
			(yyval.exp_node).type = REAL;
		}else if ((yyvsp[-2].exp_node).type == REAL)
		{
			int U = NewTemp();
			GEN("itr", (yyvsp[0].exp_node).place, 0, U);
			GEN("/r", (yyvsp[-2].exp_node).place, U, T);
			(yyval.exp_node).type = REAL;
		}
		(yyval.exp_node).place = T;
	
		//初始化右值
		struct node*node1;
		complete_init_node(&node1, "/");

		set_node_val_str((yyvsp[-2].exp_node).nd, "Expr");
		set_node_val_str((yyvsp[0].exp_node).nd, "Expr");
		
		//关系
		add_son_node((yyval.exp_node).nd, (yyvsp[-2].exp_node).nd);
		add_brother_node((yyvsp[-2].exp_node).nd, node1);
		add_brother_node(node1, (yyvsp[0].exp_node).nd);

		}
#line 2530 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 41:
#line 1150 "pascal_yacc.y" /* yacc.c:1646  */
    {
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.exp_node).nd = cur;
		(yyval.exp_node) = (yyvsp[-1].exp_node);


		//初始化右值
		struct node*node1,*node2;
		complete_init_node(&node1, "(");
		complete_init_node(&node2, ")");

		
		set_node_val_str((yyvsp[-1].exp_node).nd, "Expr");
		
		//关系
		add_son_node((yyval.exp_node).nd, node1);
		add_brother_node(node1, (yyvsp[-1].exp_node).nd);
		add_brother_node((yyvsp[-1].exp_node).nd, node2);


		}
#line 2558 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 42:
#line 1174 "pascal_yacc.y" /* yacc.c:1646  */
    {
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.exp_node).nd = cur;
		
		//对于赋值语句生成四元式
		GEN(":=", (yyvsp[0].exp_node).place, 0, (yyvsp[0].exp_node).place);
	
		//初始化右值
		struct node*node1;
		complete_init_node(&node1, "-");
		
		set_node_val_str((yyvsp[0].exp_node).nd, "Expr");
		//关系
		add_son_node((yyval.exp_node).nd, node1);
		add_brother_node(node1, (yyvsp[0].exp_node).nd);


		}
#line 2583 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 43:
#line 1195 "pascal_yacc.y" /* yacc.c:1646  */
    {
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.exp_node).nd = cur;
		//将变量在符号表中的类型和位置给表达式
		// !!!!!!!!!!!!!!!!!!!!!!!!!
		//!!!!!!!!!!!!!!!!!!!!!!!!!!有问题

		//$$.type = INT;
		if (!(yyvsp[0].Variable_node).OFFSET) {
			(yyval.exp_node).place = (yyvsp[0].Variable_node).NO;
			set_node_val_str((yyvsp[0].Variable_node).nd, "Variable");
		}
		else {
			int T = NewTemp();
			GEN("=[]", (yyvsp[0].Variable_node).NO, (yyvsp[0].Variable_node).OFFSET, T);
			(yyval.exp_node).place = T;
			set_node_val_str((yyvsp[0].Variable_node).nd, "VariaArray");
		}

		//关系
		add_son_node((yyval.exp_node).nd, (yyvsp[0].Variable_node).nd);

		}
#line 2613 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 44:
#line 1222 "pascal_yacc.y" /* yacc.c:1646  */
    {
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.exp_node).nd = cur;

		

		set_node_val_str((yyvsp[0].exp_node).nd, "Const");
		//关系
		add_son_node((yyval.exp_node).nd, (yyvsp[0].exp_node).nd);
		(yyval.exp_node) = (yyvsp[0].exp_node);

		}
#line 2632 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 45:
#line 1241 "pascal_yacc.y" /* yacc.c:1646  */
    {
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.Bexp_node).nd = cur;
		//传递 真和假出口
		(yyval.Bexp_node).TC = NXQ;
		(yyval.Bexp_node).FC = NXQ+1;
		
		GEN((yyvsp[-1].rop_node)._Rop ,(yyvsp[-2].exp_node).place, (yyvsp[0].exp_node).place,0);
		GEN("j",0,0,0);

		struct node*node1;
		complete_init_node(&node1, (yyvsp[-1].rop_node)._Rop);
		//关系
		add_son_node((yyval.Bexp_node).nd, (yyvsp[-2].exp_node).nd);
		add_brother_node((yyvsp[-2].exp_node).nd, (yyvsp[-1].rop_node).nd);
		add_brother_node((yyvsp[-1].rop_node).nd, (yyvsp[0].exp_node).nd);

		}
#line 2657 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 46:
#line 1262 "pascal_yacc.y" /* yacc.c:1646  */
    {
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.Bexp_node).nd = cur;
		//传递 真和假出口
		(yyval.Bexp_node).FC = Merge((yyvsp[-1].Bexp_node).FC, (yyvsp[0].Bexp_node).FC);
		(yyval.Bexp_node).TC = (yyvsp[0].Bexp_node).TC;

		//初始化右值
		set_node_val_str((yyvsp[-1].Bexp_node).nd, "BoolExpr_and");
		set_node_val_str((yyvsp[0].Bexp_node).nd, "BoolExpr");
		
		//关系
		add_son_node((yyval.Bexp_node).nd, (yyvsp[-1].Bexp_node).nd);
		add_brother_node((yyvsp[-1].Bexp_node).nd, (yyvsp[0].Bexp_node).nd);
		}
#line 2679 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 47:
#line 1280 "pascal_yacc.y" /* yacc.c:1646  */
    {
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.Bexp_node).nd = cur;
		//传递 真和假出口
		(yyval.Bexp_node).TC = Merge((yyvsp[-1].Bexp_node).TC, (yyvsp[0].Bexp_node).TC);
		(yyval.Bexp_node).FC = (yyvsp[0].Bexp_node).FC;

		//初始化右值
		set_node_val_str((yyvsp[-1].Bexp_node).nd, "BoolExpr_or");
		set_node_val_str((yyvsp[0].Bexp_node).nd, "BoolExpr");
		
		//关系
		add_son_node((yyval.Bexp_node).nd, (yyvsp[-1].Bexp_node).nd);
		add_brother_node((yyvsp[-1].Bexp_node).nd, (yyvsp[0].Bexp_node).nd);
		}
#line 2701 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 48:
#line 1298 "pascal_yacc.y" /* yacc.c:1646  */
    {
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.Bexp_node).nd = cur;
		//传递 真和假出口
		(yyval.Bexp_node).TC = (yyvsp[0].Bexp_node).FC;
		(yyval.Bexp_node).FC = (yyvsp[0].Bexp_node).TC;

		//初始化右值
		struct node*node1;
		complete_init_node(&node1, "Not");
		
		set_node_val_str((yyvsp[0].Bexp_node).nd, "BoolExpr");
		
		//关系
		add_son_node((yyval.Bexp_node).nd, node1);
		add_brother_node(node1, (yyvsp[0].Bexp_node).nd);
		
		}
#line 2726 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 49:
#line 1319 "pascal_yacc.y" /* yacc.c:1646  */
    {
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.Bexp_node).nd = cur;
		//传递 真和假出口
		(yyval.Bexp_node).TC = (yyvsp[-1].Bexp_node).TC;
		(yyval.Bexp_node).FC = (yyvsp[-1].Bexp_node).FC;

		//初始化右值
		struct node*node1,*node2;
		complete_init_node(&node1, "(");
		complete_init_node(&node2, ")");

		set_node_val_str((yyvsp[-1].Bexp_node).nd, "BoolExpr");
		
		//关系
		add_son_node((yyval.Bexp_node).nd, node1);
		add_brother_node(node1, (yyvsp[-1].Bexp_node).nd);
		add_brother_node((yyvsp[-1].Bexp_node).nd, node2);
		}
#line 2752 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 50:
#line 1341 "pascal_yacc.y" /* yacc.c:1646  */
    {
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.Bexp_node).nd = cur;
		//传递 真和假出口
		(yyval.Bexp_node).TC = NXQ;
		(yyval.Bexp_node).FC = NXQ+1;
		
		GEN("jnz",Entry((yyvsp[0].str)),0,0);
		GEN("j",0,0,0);

		struct node*node1;
		complete_init_node(&node1, (yyvsp[0].str));
		//关系
		add_son_node((yyval.Bexp_node).nd, node1);
		
		}
#line 2775 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 51:
#line 1361 "pascal_yacc.y" /* yacc.c:1646  */
    {
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.Bexp_node).nd = cur;
		//回填假出口
		BackPatch((yyvsp[-1].Bexp_node).FC, NXQ);
		(yyval.Bexp_node).TC = (yyvsp[-1].Bexp_node).TC; 


		//初始化右值
		struct node*node1;
		complete_init_node(&node1, "Or");

		set_node_val_str((yyvsp[-1].Bexp_node).nd, "BoolExpr");
		
		//关系
		add_son_node((yyval.Bexp_node).nd, (yyvsp[-1].Bexp_node).nd);
		add_brother_node((yyvsp[-1].Bexp_node).nd, node1);
		
}
#line 2801 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 52:
#line 1384 "pascal_yacc.y" /* yacc.c:1646  */
    {
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.Bexp_node).nd = cur;
		//回填真出口
		BackPatch((yyvsp[-1].Bexp_node).TC, NXQ);

		//此时假出口还没有确定
		(yyval.Bexp_node).FC = (yyvsp[-1].Bexp_node).FC; 


		//初始化右值
		struct node*node1;
		complete_init_node(&node1, "And");

		set_node_val_str((yyvsp[-1].Bexp_node).nd, "BoolExpr");
		
		//关系
		add_son_node((yyval.Bexp_node).nd, (yyvsp[-1].Bexp_node).nd);
		add_brother_node((yyvsp[-1].Bexp_node).nd, node1);

}
#line 2829 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 53:
#line 1409 "pascal_yacc.y" /* yacc.c:1646  */
    {
		//给左边非终结符赋值
			struct node* cur;
			complete_init_node(&cur, "NULL");
			(yyval.ExprList_node).nd = cur;

			int k, d;
			int T1 = NewTemp();
			int T2 = NewTemp();
			k = (yyvsp[-2].ExprList_node).DIM + 1;

			d = Access_d((yyvsp[-2].ExprList_node).NO, k);
			printf("%d....\n", d);
			//生成四元式
			GEN(":=",d, 0, T1);
			GEN("*", (yyvsp[-2].ExprList_node).tmp_place, T1, T2);
			GEN("+", (yyvsp[0].exp_node).place, T2, T2);

			//上传
			(yyval.ExprList_node).NO = (yyvsp[-2].ExprList_node).NO;
			(yyval.ExprList_node).tmp_place = T2;
			(yyval.ExprList_node).DIM = k;

			//初始化右值
			struct node*node1;

			complete_init_node(&node1, ",");

			set_node_val_str((yyvsp[-2].ExprList_node).nd, "ExprList");
			set_node_val_str((yyvsp[-2].ExprList_node).nd, "Expr");

			//关系
			add_son_node((yyval.ExprList_node).nd, (yyvsp[-2].ExprList_node).nd);
			add_brother_node((yyvsp[-2].ExprList_node).nd, node1);
			add_brother_node(node1, (yyvsp[0].exp_node).nd);


		}
#line 2872 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 54:
#line 1448 "pascal_yacc.y" /* yacc.c:1646  */
    {
			//给左边非终结符赋值
			struct node* cur;
			complete_init_node(&cur, "NULL");
			(yyval.ExprList_node).nd = cur;


			(yyval.ExprList_node).NO = Entry((yyvsp[-2].str));
			(yyval.ExprList_node).DIM = 1;
			//相当于VARPART = Ii;
			(yyval.ExprList_node).tmp_place = (yyvsp[0].exp_node).place;


			//初始化右值
			struct node*node1, *node2;

			complete_init_node(&node1, (yyvsp[-2].str));
			complete_init_node(&node2, "[");

			set_node_val_str((yyvsp[0].exp_node).nd, "Expr");

			//关系
			add_son_node((yyval.ExprList_node).nd, node1);
			add_brother_node(node1, node2);
			add_brother_node(node2, (yyvsp[0].exp_node).nd);
		}
#line 2903 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 55:
#line 1476 "pascal_yacc.y" /* yacc.c:1646  */
    { 
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.Variable_node).nd = cur;
		//获取标示符的下标
		(yyval.Variable_node).NO = Entry((yyvsp[0].str));
		//此时为普通变量
		(yyval.Variable_node).OFFSET = 0;

		//初始化右值
		struct node *node1;
		complete_init_node(&node1, (yyvsp[0].str));
		//关系
		add_son_node((yyval.Variable_node).nd, node1);
			
		}
#line 2924 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 56:
#line 1493 "pascal_yacc.y" /* yacc.c:1646  */
    {
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.Variable_node).nd = cur;

		int a, C;
		int T = NewTemp();
		C = Access_C((yyvsp[-1].ExprList_node).NO);
		a = Access_a((yyvsp[-1].ExprList_node).NO);

		//产生a - C的代码
		GEN("-", a, C, T);

		(yyval.Variable_node).NO = T;
		(yyval.Variable_node).OFFSET = (yyvsp[-1].ExprList_node).tmp_place;



	
		}
#line 2949 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 57:
#line 1515 "pascal_yacc.y" /* yacc.c:1646  */
    {
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.exp_node).nd = cur;
		//设置常量为INT型，并检查该常量是否在表中，如果不在表中
		//则需要添加到表中
		(yyval.exp_node).type = INT;
		(yyval.exp_node).place = Entry((yyvsp[0].str)); 
		//同时在符号表中设置类型
		VarList[VarCount].type = INT;
		//初始化右值
		struct node *node1;
		complete_init_node(&node1, (yyvsp[0].str));
		//关系
		add_son_node((yyval.exp_node).nd, node1);
		}
#line 2970 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 58:
#line 1532 "pascal_yacc.y" /* yacc.c:1646  */
    {
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.exp_node).nd = cur;
		//设置常量为REAL型，并检查该常量是否在表中，如果不在表中
		//则需要添加到表中
		(yyval.exp_node).type = REAL;
		(yyval.exp_node).place = Entry((yyvsp[0].str)); 
		//printf("%s", $1);
		//同时在符号表中设置类型
		VarList[VarCount].type = REAL;
		//初始化右值
		struct node *node1;
		complete_init_node(&node1, (yyvsp[0].str));
		//关系
		add_son_node((yyval.exp_node).nd, node1);
		}
#line 2992 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 59:
#line 1551 "pascal_yacc.y" /* yacc.c:1646  */
    {
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.rop_node).nd = cur;

		memcpy((yyval.rop_node)._Rop, "j<", sizeof("j<"));
		//初始化右值
		struct node *node1;
		complete_init_node(&node1, "<");
		//关系
		add_son_node((yyval.rop_node).nd, node1);
		}
#line 3010 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 60:
#line 1565 "pascal_yacc.y" /* yacc.c:1646  */
    {
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.rop_node).nd = cur;

		memcpy((yyval.rop_node)._Rop, "j>", sizeof("j>"));
		//初始化右值
		struct node *node1;
		complete_init_node(&node1, ">");
		//关系
		add_son_node((yyval.rop_node).nd, node1);

		}
#line 3029 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 61:
#line 1580 "pascal_yacc.y" /* yacc.c:1646  */
    {
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.rop_node).nd = cur;

		memcpy((yyval.rop_node)._Rop, "j=", sizeof("j="));
		//初始化右值
		struct node *node1;
		complete_init_node(&node1, "=");
		//关系
		add_son_node((yyval.rop_node).nd, node1);
		}
#line 3047 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 62:
#line 1594 "pascal_yacc.y" /* yacc.c:1646  */
    {
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.rop_node).nd = cur;

		memcpy((yyval.rop_node)._Rop, "j>=", sizeof("j>="));
		//初始化右值
		struct node *node1;
		complete_init_node(&node1, ">=");
		//关系
		add_son_node((yyval.rop_node).nd, node1);
		}
#line 3065 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 63:
#line 1608 "pascal_yacc.y" /* yacc.c:1646  */
    {
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.rop_node).nd = cur;

		memcpy((yyval.rop_node)._Rop, "j<>", sizeof("j<>"));
		//初始化右值
		struct node *node1;
		complete_init_node(&node1, "<>");
		//关系
		add_son_node((yyval.rop_node).nd, node1);
		}
#line 3083 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 64:
#line 1622 "pascal_yacc.y" /* yacc.c:1646  */
    {
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		(yyval.rop_node).nd = cur;

		memcpy((yyval.rop_node)._Rop, "j<=", sizeof("j<="));
		//初始化右值
		struct node *node1;
		complete_init_node(&node1, "<=");
		//关系
		add_son_node((yyval.rop_node).nd, node1);
		}
#line 3101 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 65:
#line 1638 "pascal_yacc.y" /* yacc.c:1646  */
    {
	//给左边非终结符赋值
	struct node* cur;
	complete_init_node(&cur, "NULL");
	(yyval.ForLoop_node).nd = cur;
	//下一个四元式是循环起始位置
	(yyval.ForLoop_node).loop = NXQ;

	//初始化右值
	struct node *node1;
	complete_init_node(&node1, "Do");
	//关系
	add_son_node((yyval.ForLoop_node).nd, node1);

}
#line 3121 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 66:
#line 1655 "pascal_yacc.y" /* yacc.c:1646  */
    {
	//给左边非终结符赋值
	struct node* cur;
	complete_init_node(&cur, "NULL");
	(yyval.ForLoop_node).nd = cur;
	
	//将循环起始位置上传
	(yyval.ForLoop_node).loop = (yyvsp[-2].ForLoop_node).loop;
	//同时由与bool表达式语句出现，因此回填出口
	BackPatch((yyvsp[-1].ch_node).CH, NXQ);

	//初始化右值
	struct node*node1;
	complete_init_node(&node1, "While");

	set_node_val_str((yyvsp[-2].ForLoop_node).nd, "DO");
	set_node_val_str((yyvsp[-1].ch_node).nd, "Statement");
		
	//关系
	add_son_node((yyval.ForLoop_node).nd, (yyvsp[-2].ForLoop_node).nd);
	add_brother_node((yyvsp[-2].ForLoop_node).nd, (yyvsp[-1].ch_node).nd);
	add_brother_node((yyvsp[-1].ch_node).nd, node1);

}
#line 3150 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 67:
#line 1684 "pascal_yacc.y" /* yacc.c:1646  */
    {
	//给左边非终结符赋值
	struct node* cur;
	complete_init_node(&cur, "NULL");
	(yyval.ForLoop_node).nd = cur;
	//下一个四元式是循环起始位置
	(yyval.ForLoop_node).loop = NXQ;

	//初始化右值
	struct node *node1;
	complete_init_node(&node1, "Repeat");
	//关系
	add_son_node((yyval.ForLoop_node).nd, node1);
}
#line 3169 "pascal_yacc.c" /* yacc.c:1646  */
    break;

  case 68:
#line 1700 "pascal_yacc.y" /* yacc.c:1646  */
    {
	//给左边非终结符赋值
	struct node* cur;
	complete_init_node(&cur, "NULL");
	(yyval.ForLoop_node).nd = cur;
	
	//将循环起始位置上传
	(yyval.ForLoop_node).loop = (yyvsp[-2].ForLoop_node).loop;
	//同时由与bool表达式语句出现，因此回填出口
	BackPatch((yyvsp[-1].ch_node).CH, NXQ);

	//初始化右值
	struct node*node1;
	complete_init_node(&node1, "Until");

	set_node_val_str((yyvsp[-2].ForLoop_node).nd, "Repeat");
	set_node_val_str((yyvsp[-1].ch_node).nd, "Statement");
		
	//关系
	add_son_node((yyval.ForLoop_node).nd, (yyvsp[-2].ForLoop_node).nd);
	add_brother_node((yyvsp[-2].ForLoop_node).nd, (yyvsp[-1].ch_node).nd);
	add_brother_node((yyvsp[-1].ch_node).nd, node1);
}
#line 3197 "pascal_yacc.c" /* yacc.c:1646  */
    break;


#line 3201 "pascal_yacc.c" /* yacc.c:1646  */
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
#line 1725 "pascal_yacc.y" /* yacc.c:1906  */


int yyerror(char *errstr)
{
	printf(" Reason:%s\n", errstr);
	return 0;
}
