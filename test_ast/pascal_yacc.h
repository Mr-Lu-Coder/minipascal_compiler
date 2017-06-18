/* A Bison parser, made by GNU Bison 3.0.  */

/* Bison interface for Yacc-like parsers in C

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
    OneDimString = 420,
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
#line 23 "pascal_yacc.y" /* yacc.c:1909  */

	int Iv;                //����                         
	int CH;                //CH��ʾ��             
	int NO;                //NO��ʾ�����ڱ��е��±�
	struct { int TC,FC;} _BExpr;
	struct { int QUAD,CH;} _WBD;   //QUAD  �൱�����е� loopstartplace
	struct { int type,place;} _Expr;
	char _Rop[5];
	int First;
	char str[20];

	//�����﷨���Ľڵ�
	struct node *ast_node;
	//CH�ڵ�
	struct {
		int CH; 
		struct node *nd;
	} ch_node;
	//���ͽڵ�
	struct {
		//1 2 3 
		int type;
		// 1 2 
		int Iv; 
		int array_no;
		struct node *nd;
	} iv_node;
	//���������ڵ�
	struct {
		int First; 
		struct node *nd;
	} first_node;
	//ѭ���ڵ�
	struct {
		int CH; 
		int QUAD; 
		struct node *nd;
	} wbd_node;
	//rop�ڵ�
	struct {
		char _Rop[5]; 
		struct node *nd;
	} rop_node;
	//���ʽ�ڵ�
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

	//forѭ���ڵ�
	struct {
		int loop, place, CH; 
		struct node *nd;
	} ForLoop_node;
	//�����ڵ�
	struct {
		int NO;
		int OFFSET; //
		struct node* nd;
	}Variable_node;
	//ExprList
	struct {
		int NO; 	  //�����б������ڷ��ű��е����
		int DIM;      //���ڼ�¼�Ѿ�������±�ı��ʽ
		int tmp_place; //��ʱ�������ĵ�ַ
		struct node* nd;
	}ExprList_node;
	
	//��������
	struct {
		int DIM;
		int NO; //�������ڷ��ű��е����
		struct node* nd;
	}TypeFirst_node;

	//��������
	struct {
		int L;
		int U;
		struct node* nd;
	}OneDim_node;


#line 179 "pascal_yacc.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PASCAL_YACC_H_INCLUDED  */
