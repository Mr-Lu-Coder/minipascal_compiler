%{
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


%}
%start    ProgDef
%union 
{
	int Iv;                //����                         
	int CH;                //CH��ʾ��             
	int NO;                //NO��ʾ�����ڱ��е��±�
	struct { int TC,FC;} _BExpr;
	struct { int QUAD,CH;} _WBD;   //QUAD  �൱�����е� loopstartplace
	struct { int type,place;} _Expr;
	char _Rop[5];
	int First;
	char str[20];

	//**
	struct node *ast_node;
	struct {int CH; struct node *nd;} ch_node;
	struct {int Iv; struct node *nd;} iv_node;
	struct {int First; struct node *nd;} first_node;
	struct {int CH; int QUAD; struct node *nd;} wbd_node;
	struct {char _Rop[5]; struct node *nd;} rop_node;
	struct {int type, place; struct node *nd;} exp_node;
	struct {int NO; struct node *nd;} no_node;
	struct {int TC, FC, CH; struct node *nd;} Bexp_node;
	struct {int loop, place, CH; struct node *nd;} ForLoop_node;

}
/*Define const:  */
%token <str>   	Iden		300
%token <str>   	IntNo		301
%token <str>  	RealNo		302
/*Define keywords here:*/
%token	<str>  	Program		400
%token	<str>  	Begin		401
%token	<str> 	End			402
%token	<str>  	Var			403
%token	<str>  	Integer		404
%token	<str>  	Real		405
%token	<str>  	While		406
%token	<str>  	Do			407
%token	<str>	If			408
%token	<str>	Then		409
%token	<str>	Else		410
%token	<str>	Or			411
%token	<str>	And			412
%token	<str>	Not			413
%token	<str>	For			414
%token	<str>	To			415
/*Define double_character terminates:   */
%token			LE			500
%token			GE			501
%token			NE			502
%token			ERRORCHAR	600

%left 		Or
%left		And
%nonassoc  	Not
%nonassoc '<' '>' '=' LE GE NE
%left '+' '-'
%left '*' '/'
%nonassoc UMINUS

%type <ast_node> ProgDef
%type <ast_node> SubProg
%type <ch_node> VarDef
%type <ch_node> VarDefList
%type <iv_node> Type
%type <ch_node> VarDefState
%type <first_node> VarList
%type <ch_node> Statement
%type <ch_node> StateList
%type <ch_node> S_L

%type <ch_node> CompState
%type <ch_node> AsignState
%type <ch_node> ISE
%type <ch_node> IBT
%type <wbd_node> WBD

%type <rop_node> RelationOp
%type <exp_node> Expr
%type <ch_node> Wh
%type <no_node> Variable 
%type <exp_node> Const 
%type <Bexp_node>BoolExpr
%type <Bexp_node>BoolExpr_and 
%type <Bexp_node>BoolExpr_or 
%type <ForLoop_node>ForLoop1
%type <ForLoop_node>ForLoop2 

%%
ProgDef:	Program Iden ';' SubProg '.'
{
				//printf("\n�����ɹ�\n");
				set_node_val_str(&ast_root,$2);

				struct node *tmpnode=NULL;
				//printf("\n\n**** test ast node ****\n\n");
				$$=&ast_root;
				struct node *node1,*node2, *node3,*node4;   //����ĸ��ڵ�

				complete_init_node(&node1, "Program");
				int re = add_son_node(&ast_root, node1);
				

				complete_init_node(&node2, $2);
				//printf("In ProgDef: %s\n", node2->val.str);
				re = add_brother_node(node1, node2);
				
				complete_init_node(&node3, ";");
				//printf("In ProgDef: %s\n", node3->val.str);
				re = add_brother_node(node2,node3);     
				/*     
				if (re != ADD_BROTHER_NODE_SUCCESS || re != ADD_SON_NODE_SUCCESS){
					printf("Add brother error: %d\n", re);
				} */
				set_node_val_str($4, "SubProg");          //�ӳ����Ѿ���ʼ������
				//printf("In ProgDef: %s\n", $4->val.str);
				add_brother_node(node3, $4);

				complete_init_node(&node4, ".");
				//printf("In ProgDef: %s\n", node4->val.str);
				add_brother_node($4, node4);
}
	;
SubProg:	VarDef CompState
		{
		//��ʼ����ֵ
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$ = cur;
		//������ֵ
		set_node_val_str($1.nd,"VarDef");
		set_node_val_str($2.nd,"CompState");
		//������ϵ
		add_son_node($$,$1.nd);
		add_brother_node($1.nd,$2.nd);    	
		}
	;
VarDef:		Var VarDefList ';'
        {
		//��ʼ����ֵ
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//��ʼ����ֵ
		struct node *node1, *node2;
		complete_init_node(&node1, "Var");
		complete_init_node(&node2, ";");
		set_node_val_str($2.nd,"VarDefList");
		//������ϵ
		add_son_node($$.nd ,node1);
		add_brother_node(node1,$2.nd); 
		add_brother_node($2.nd,node2);  


		}
	;
VarDefList:	VarDefList';'VarDefState
        {
		//��ʼ����ֵ
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//��ʼ����ֵ
		struct node *node1;
		complete_init_node(&node1, ";");
		set_node_val_str($1.nd,"VarDefList");
		set_node_val_str($3.nd,"VarDefState");
		//������ϵ
		add_son_node($$.nd ,$1.nd);
		add_brother_node($1.nd,node1); 
		add_brother_node(node1,$3.nd);  
		}
	|	VarDefState
	    {
		//��ʼ����ֵ
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//��ʼ����ֵ
		set_node_val_str($1.nd,"VarDefState");
		//������ϵ
		add_son_node($$.nd ,$1.nd);
        }
	;
VarDefState:	VarList':'Type
		{

		//��ʼ����ֵ
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//��Type���͸�ֵ��VarList���б�����Ҳ��һ������Ĳ���
		VarBackPatch($1.First, $3.Iv);
		//printf("Patch: First:%d \n", $1.First);
		//��ʼ����ֵ
		struct node *node1;
		complete_init_node(&node1, ";");
		set_node_val_str($1.nd,"VarList");
		set_node_val_str($3.nd,"Type");
		//������ϵ
		add_son_node($$.nd ,$1.nd);
		add_brother_node($1.nd,node1); 
		add_brother_node(node1,$3.nd);  

		}
	;
Type:		Integer
		{
		//��ʼ����ֵ
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//��������Ϊ����
		$$.Iv = INT;
		struct node *node1;
		complete_init_node(&node1, "Integer");

		add_son_node($$.nd, node1);
		
		
		}
	|	Real
		{
		//��ʼ����ֵ
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//��ʼ����ֵ
		//��������Ϊʵ��
		$$.Iv = REAL;
		struct node *node1;
		complete_init_node(&node1, "Real");

		add_son_node($$.nd, node1);


		}
	;
VarList:	VarList','Variable
		{
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		
	
		//��ʼ����ֵ
		struct node*node1;
		complete_init_node(&node1, ",");

		set_node_val_str($1.nd, "VarList");
		set_node_val_str($3.nd, "Variable");
		//��ϵ
		add_son_node($$.nd, $1.nd);
		add_brother_node($1.nd, node1);
		add_brother_node(node1, $3.nd);
		//������������������Ϊ���������ʱ������ Var a,b,c:integer�����
		//������Ҫ����First������ͷ
		$$.First = Merge_var($3.NO, $1.First);
		//printf("First:%d \n", $$.First);
		}
	|	Variable
		{
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//���ݱ����ķ��ţ�����Varlist.First ������ǵ�һ��������place
		$$.First = $1.NO;
		//��ʼ����ֵ

		set_node_val_str($1.nd, "Variable");
		//��ϵ
		add_son_node($$.nd, $1.nd);
		}
	;
//�������������⿪ʼ
StateList:	S_L Statement
		{
		//printf("test for StateList\n");
		//����߷��ս����ֵ
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//�˴����ݵ���$2���ĳ���
		$$.CH = $2.CH;
	
		//��ʼ����ֵ
		set_node_val_str($1.nd, "S_L");
		set_node_val_str($2.nd, "Statement");
		
		//��ϵ
		add_son_node($$.nd, $1.nd);
		add_brother_node($1.nd, $2.nd);
		}
	|	Statement
		{
		//����߷��ս����ֵ

		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//����
		$$.CH = $1.CH;

		set_node_val_str($1.nd, "Statement");
		//��ϵ
		add_son_node($$.nd, $1.nd);
		}
	;
S_L:		StateList ';'
		{
		//printf("test for State_L\n");
		//����߷��ս����ֵ
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//!!!!!!!!!!!!!!!!!!!!
		///��ʱ�������շ�����ֺţ��������̽�����˳��ִ��
		//������һ����Ԫʽ����Ż���StateList�ĳ�����
		//$$.CH = $1.CH;
		BackPatch($1.CH, NXQ);
		//��ʼ����ֵ
		struct node *node1;
		complete_init_node(&node1, ";");

		set_node_val_str($1.nd, "StateList");
		
		
		//��ϵ
		add_son_node($$.nd, $1.nd);
		add_brother_node($1.nd, node1);
		}
	;
Statement:	AsignState
		{
		//����߷��ս����ֵ
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;

		//��Ϊ0 ��ʾΪ������ֹ��
		$$.CH = 0;

		set_node_val_str($1.nd, "AsignState");
		//��ϵ
		add_son_node($$.nd, $1.nd);
		}
	|	ISE Statement  //IF Boolexp then statement else statement
		{
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//��ʱ�������ʽ�ļٳ���Ӧ�ú�statement�ĳ���һ��
		//�ϲ�s1��s2�ĳ���
		$$.CH = Merge($1.CH, $2.CH);

		set_node_val_str($1.nd, "ISE");
		set_node_val_str($2.nd, "Statement");
		
		//��ϵ
		add_son_node($$.nd, $1.nd);
		add_brother_node($1.nd, $2.nd);

		}
	|	IBT Statement
		{
		//����߷��ս����ֵ
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//��ʱ�������ʽ�ļٳ���Ӧ�ú�statement�ĳ���һ��
		$$.CH = Merge($1.CH, $2.CH);

		set_node_val_str($1.nd, "IBT");
		set_node_val_str($2.nd, "Statement");
		
		//��ϵ
		add_son_node($$.nd, $1.nd);
		add_brother_node($1.nd, $2.nd);


		}

	|	WBD Statement
		{
		//����߷��ս����ֵ
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		
		BackPatch($2.CH, $1.QUAD);
		//��ʱӦ���������ص�ѭ����ʼ��λ��
		GEN("j", 0, 0, $1.QUAD);
		//��ʱ�������ʽ�ļٳ��ڴ���
		$$.CH = $1.CH;

		set_node_val_str($1.nd, "IBT");
		set_node_val_str($2.nd, "Statement");
		
		//��ϵ
		add_son_node($$.nd, $1.nd);
		add_brother_node($1.nd, $2.nd);


		}
	|	CompState
	    {
		//����߷��ս����ֵ
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//��ʱ�������ϴ���
		$$.CH = $1.CH;

		set_node_val_str($1.nd, "CompState");

		//��ϵ
		add_son_node($$.nd, $1.nd);


		}
	|	ForLoop2 Do Statement{
			
		//����߷��ս����ֵ
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//��ʱ���Ʊ�����������Ԫʽ����һ����
		//��statement���л���
		BackPatch($3.CH, NXQ);
		//���Ʊ�����������Ԫʽ
		GEN("+", $1.place, Entry("1"), $1.place);

		//����ѭ����ʼ�ڵ�
		GEN("j", 0, 0, $1.loop);

		//���ݳ���
		$$.CH = $1.CH;
		
		struct node* node1;
		complete_init_node(&node1, "Do");

		set_node_val_str($1.nd, "ForLoop2");
		set_node_val_str($3.nd, "Statement");
		
		
		//��ϵ
		add_son_node($$.nd, $1.nd);
		add_brother_node($1.nd, node1);
		add_brother_node(node1, $3.nd);

	    }
	|
	{    //��Ҫ���Ϊ��Ҳ�� ������ģ�������������
	}
	;
ForLoop1: For Iden ':''=' Expr
{
		//����߷��ս����ֵ
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		
		int i = Entry($2);
		//��ʱ���ɸ�ֵ��Ԫʽ
		GEN(":=", $5.place, 0, i);
		//�����Ʊ������ڵ�λ�ô���
		$$.place = i;

		//��ʼ����ֵ
		struct node* node1,*node2, *node3;
		complete_init_node(&node1, "For");
		complete_init_node(&node2, $2);
		complete_init_node(&node3, ":=");
		set_node_val_str($5.nd, "Expr");
		
		
		//��ϵ
		add_son_node($$.nd, node1);
		add_brother_node(node1, node2);
		add_brother_node(node2, node3);
		add_brother_node(node3, $5.nd);
};
ForLoop2: ForLoop1 To Expr
{
		//����߷��ս����ֵ
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		
		int p = NXQ;
		//����ѭ�����ص���Ϣ��loopָ��ѭ����ĵ�һ����Ԫʽ
		$$.loop = NXQ;

		//��ʱ���ɸ�ֵ��Ԫʽ
		GEN("j<", $1.place, $3.place, p+2);
		//�����Ʊ������ڵ�λ�ô���
		$$.place = $1.place;
		//ѭ�����ĳ���
		$$.CH = NXQ;
		GEN("j", 0, 0, 0);
		//��ʼ����ֵ
		struct node* node1;
		complete_init_node(&node1, "To");

		set_node_val_str($1.nd, "ForLoop1");
		set_node_val_str($3.nd, "Expr");
		
		
		//��ϵ
		add_son_node($$.nd, $1.nd);
		add_brother_node($1.nd, node1);
		add_brother_node(node1, $3.nd);
};

CompState:	Begin StateList End
		{
		//printf("test for begin and end\n");
		//����߷��ս����ֵ
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		
		$$.CH = $2.CH;
	
		//��ʼ����ֵ
		struct node*node1,*node2;
		complete_init_node(&node1, "Begin");
		complete_init_node(&node2, "End");

		
		set_node_val_str($2.nd, "StateList");
		
		//��ϵ
		add_son_node($$.nd, node1);
		add_brother_node(node1, $2.nd);
		add_brother_node($2.nd, node2);

		}
	;
AsignState:	Variable ':''=' Expr
		{

		//����߷��ս����ֵ
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		
		//���ڸ�ֵ���������Ԫʽ
		GEN(":=", $4.place, 0, $1.NO);
	
		//��ʼ����ֵ
		struct node*node1;
		complete_init_node(&node1, ":=");

		
		set_node_val_str($1.nd, "Variable");
		set_node_val_str($4.nd, "Expr");
		
		//��ϵ
		add_son_node($$.nd, $1.nd);
		add_brother_node($1.nd, node1);
		add_brother_node(node1, $4.nd);

		}
	;
ISE:		IBT Statement Else
		{

		//����߷��ս����ֵ
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		int q = NXQ;
		//��Ҫ���һ����Ԫʽ�����������
		GEN("j",0,0,0);

		//��ʱ��һ����Ԫʽ��Ϊ�ٳ��ڣ�������Ҫ����
		BackPatch($1.CH, NXQ);
		//ͨ���ϲ�����ںͼٳ���Ϊ����S�ĳ���
		$$.CH = Merge($2.CH, q);

		set_node_val_str($1.nd, "IBT");
		set_node_val_str($2.nd, "Statement");
		struct node * node1;
		complete_init_node(&node1, "Else");

		//��ϵ
		add_son_node($$.nd, $1.nd);
		add_brother_node($1.nd, $2.nd);
		add_brother_node($2.nd, node1);


		}
	;
IBT:		If BoolExpr Then
		{
		//����߷��ս����ֵ
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//��ʱ��һ����Ԫʽ��Ϊ����ڣ�������Ҫ����
		BackPatch($2.TC, NXQ);
		//�ٳ��ڻ���ȷ��
		$$.CH = $2.FC;


		set_node_val_str($2.nd, "BoolExpr");
		struct node * node1, *node2;
		complete_init_node(&node1, "IF");
		complete_init_node(&node2, "Then");
		//��ϵ
		add_son_node($$.nd, node1);
		add_brother_node(node1, $2.nd);
		add_brother_node($2.nd, node2);
		}

	;
WBD: Wh BoolExpr Do
		{
		//����߷��ս����ֵ
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//��ʱ��һ����Ԫʽ��Ϊ����ڣ�������Ҫ����
		BackPatch($2.TC, NXQ);
		//�ٳ��ڻ���ȷ��
		$$.CH = $2.FC;
		//������ʼ��ַ
		$$.QUAD = $1.CH;

		set_node_val_str($1.nd, "Wh");
		set_node_val_str($2.nd, "BoolExpr");
		struct node * node1;
		complete_init_node(&node1, "Do");
		//��ϵ
		add_son_node($$.nd, $1.nd);
		add_brother_node($1.nd, $2.nd);
		add_brother_node($2.nd, node1);

		}
	;
Wh:		While
        {
		//����߷��ս����ֵ
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//������һ����ԪʽΪ��
		$$.CH = NXQ;
		struct node* node1;
		complete_init_node(&node1, "While");
		//��ϵ
		add_son_node($$.nd, node1);
        }
	;


Expr:		Expr'+'Expr
		{
		//����߷��ս����ֵ
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		
		int T = NewTemp();
		//������������������Ԫʽ,�����һ����real��Ҫ��int�ͽ���ǿ��ת��
		if ($1.type == INT && $3.type == INT)
		{
			GEN("+", $1.place, $3.place, T);
			$$.type = INT;
		}else if ($1.type == REAL && $3.type == REAL)
		{
			GEN("+r", $1.place, $3.place, T);
			$$.type = REAL;
		}else if ($1.type == INT)
		{
			int U = NewTemp();
			GEN("itr", $1.place, 0, U);
			GEN("+r", U, $3.place, T);
			$$.type = REAL;
		}else if ($1.type == REAL)
		{
			int U = NewTemp();
			GEN("itr", $3.place, 0, U);
			GEN("+r", $1.place, U, T);
			$$.type = REAL;
		}
		$$.place = T;
	
		//��ʼ����ֵ
		struct node*node1;
		complete_init_node(&node1, "+");

		set_node_val_str($1.nd, "Expr");
		set_node_val_str($3.nd, "Expr");
		
		//��ϵ
		add_son_node($$.nd, $1.nd);
		add_brother_node($1.nd, node1);
		add_brother_node(node1, $3.nd);


		}
	|	Expr'-'Expr
		{
		//����߷��ս����ֵ
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		
		int T = NewTemp();
		//������������������Ԫʽ,�����һ����real��Ҫ��int�ͽ���ǿ��ת��
		if ($1.type == INT && $3.type == INT)
		{
			GEN("-", $1.place, $3.place, T);
			$$.type = INT;
		}else if ($1.type == REAL && $3.type == REAL)
		{
			GEN("-r", $1.place, $3.place, T);
			$$.type = REAL;
		}else if ($1.type == INT)
		{
			int U = NewTemp();
			GEN("itr", $1.place, 0, U);
			GEN("-r", U, $3.place, T);
			$$.type = REAL;
		}else if ($1.type == REAL)
		{
			int U = NewTemp();
			GEN("itr", $3.place, 0, U);
			GEN("-r", $1.place, U, T);
			$$.type = REAL;
		}
		$$.place = T;
	
		//��ʼ����ֵ
		struct node*node1;
		complete_init_node(&node1, "-");

		set_node_val_str($1.nd, "Expr");
		set_node_val_str($3.nd, "Expr");
		
		//��ϵ
		add_son_node($$.nd, $1.nd);
		add_brother_node($1.nd, node1);
		add_brother_node(node1, $3.nd);

		}

	|	Expr'*'Expr
		{
		//����߷��ս����ֵ
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		
		int T = NewTemp();
		//������������������Ԫʽ,�����һ����real��Ҫ��int�ͽ���ǿ��ת��
		if ($1.type == INT && $3.type == INT)
		{
			GEN("*", $1.place, $3.place, T);
			$$.type = INT;
		}else if ($1.type == REAL && $3.type == REAL)
		{
			GEN("*r", $1.place, $3.place, T);
			$$.type = REAL;
		}else if ($1.type == INT)
		{
			int U = NewTemp();
			GEN("itr", $1.place, 0, U);
			GEN("*r", U, $3.place, T);
			$$.type = REAL;
		}else if ($1.type == REAL)
		{
			int U = NewTemp();
			GEN("itr", $3.place, 0, U);
			GEN("*r", $1.place, U, T);
			$$.type = REAL;
		}
		$$.place = T;
	
		//��ʼ����ֵ
		struct node*node1;
		complete_init_node(&node1, "*");

		set_node_val_str($1.nd, "Expr");
		set_node_val_str($3.nd, "Expr");
		
		//��ϵ
		add_son_node($$.nd, $1.nd);
		add_brother_node($1.nd, node1);
		add_brother_node(node1, $3.nd);




		}
	|	Expr'/'Expr
		{
		//����߷��ս����ֵ
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		
		int T = NewTemp();
		//������������������Ԫʽ,�����һ����real��Ҫ��int�ͽ���ǿ��ת��
		if ($1.type == INT && $3.type == INT)
		{
			GEN("/", $1.place, $3.place, T);
			$$.type = INT;
		}else if ($1.type == REAL && $3.type == REAL)
		{
			GEN("/r", $1.place, $3.place, T);
			$$.type = REAL;
		}else if ($1.type == INT)
		{
			int U = NewTemp();
			GEN("itr", $1.place, 0, U);
			GEN("/r", U, $3.place, T);
			$$.type = REAL;
		}else if ($1.type == REAL)
		{
			int U = NewTemp();
			GEN("itr", $3.place, 0, U);
			GEN("/r", $1.place, U, T);
			$$.type = REAL;
		}
		$$.place = T;
	
		//��ʼ����ֵ
		struct node*node1;
		complete_init_node(&node1, "/");

		set_node_val_str($1.nd, "Expr");
		set_node_val_str($3.nd, "Expr");
		
		//��ϵ
		add_son_node($$.nd, $1.nd);
		add_brother_node($1.nd, node1);
		add_brother_node(node1, $3.nd);

		}
	|	'('Expr')'
		{
		//����߷��ս����ֵ
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		$$ = $2;


		//��ʼ����ֵ
		struct node*node1,*node2;
		complete_init_node(&node1, "(");
		complete_init_node(&node2, ")");

		
		set_node_val_str($2.nd, "Expr");
		
		//��ϵ
		add_son_node($$.nd, node1);
		add_brother_node(node1, $2.nd);
		add_brother_node($2.nd, node2);


		}
	|	'-' Expr %prec UMINUS
		{
		//����߷��ս����ֵ
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		
		//���ڸ�ֵ���������Ԫʽ
		GEN(":=", $2.place, 0, $2.place);
	
		//��ʼ����ֵ
		struct node*node1;
		complete_init_node(&node1, "-");
		
		set_node_val_str($2.nd, "Expr");
		//��ϵ
		add_son_node($$.nd, node1);
		add_brother_node(node1, $2.nd);


		}
	|	Variable
		{
		//����߷��ս����ֵ
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//�������ڷ��ű��е����ͺ�λ�ø����ʽ
		$$.type = INT;
		$$.place = $1.NO;

		set_node_val_str($1.nd, "Variable");
		//��ϵ
		add_son_node($$.nd, $1.nd);

		}

	|	Const
		{
		//����߷��ս����ֵ
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;

		

		set_node_val_str($1.nd, "Const");
		//��ϵ
		add_son_node($$.nd, $1.nd);
		$$ = $1;

		}
	;

BoolExpr:	Expr RelationOp Expr
		{
		//����߷��ս����ֵ
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//���� ��ͼٳ���
		$$.TC = NXQ;
		$$.FC = NXQ+1;
		
		GEN($2._Rop ,$1.place, $3.place,0);
		GEN("j",0,0,0);

		struct node*node1;
		complete_init_node(&node1, $2._Rop);
		//��ϵ
		add_son_node($$.nd, $1.nd);
		add_brother_node($1.nd, $2.nd);
		add_brother_node($2.nd, $3.nd);

		}
	|	BoolExpr_and BoolExpr
	    {
		//����߷��ս����ֵ
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//���� ��ͼٳ���
		$$.FC = Merge($1.FC, $2.FC);
		$$.TC = $2.TC;

		//��ʼ����ֵ
		set_node_val_str($1.nd, "BoolExpr_and");
		set_node_val_str($2.nd, "BoolExpr");
		
		//��ϵ
		add_son_node($$.nd, $1.nd);
		add_brother_node($1.nd, $2.nd);
		}
	|	BoolExpr_or BoolExpr
	    {
		//����߷��ս����ֵ
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//���� ��ͼٳ���
		$$.TC = Merge($1.TC, $2.TC);
		$$.FC = $2.FC;

		//��ʼ����ֵ
		set_node_val_str($1.nd, "BoolExpr_or");
		set_node_val_str($2.nd, "BoolExpr");
		
		//��ϵ
		add_son_node($$.nd, $1.nd);
		add_brother_node($1.nd, $2.nd);
		}	
	|	Not BoolExpr
	    {
		//����߷��ս����ֵ
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//���� ��ͼٳ���
		$$.TC = $2.FC;
		$$.FC = $2.TC;

		//��ʼ����ֵ
		struct node*node1;
		complete_init_node(&node1, "Not");
		
		set_node_val_str($2.nd, "BoolExpr");
		
		//��ϵ
		add_son_node($$.nd, node1);
		add_brother_node(node1, $2.nd);
		
		}
	|	'(' BoolExpr ')'
	    {
		//����߷��ս����ֵ
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//���� ��ͼٳ���
		$$.TC = $2.TC;
		$$.FC = $2.FC;

		//��ʼ����ֵ
		struct node*node1,*node2;
		complete_init_node(&node1, "(");
		complete_init_node(&node2, ")");

		set_node_val_str($2.nd, "BoolExpr");
		
		//��ϵ
		add_son_node($$.nd, node1);
		add_brother_node(node1, $2.nd);
		add_brother_node($2.nd, node2);
		}
		|   Iden
		{
		//����߷��ս����ֵ
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//���� ��ͼٳ���
		$$.TC = NXQ;
		$$.FC = NXQ+1;
		
		GEN("jnz",Entry($1),0,0);
		GEN("j",0,0,0);

		struct node*node1;
		complete_init_node(&node1, $1);
		//��ϵ
		add_son_node($$.nd, node1);
		
		}
	;
BoolExpr_or: BoolExpr Or
{
		//����߷��ս����ֵ
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//����ٳ���
		BackPatch($1.FC, NXQ);
		$$.TC = $1.TC; 


		//��ʼ����ֵ
		struct node*node1;
		complete_init_node(&node1, "Or");

		set_node_val_str($1.nd, "BoolExpr");
		
		//��ϵ
		add_son_node($$.nd, $1.nd);
		add_brother_node($1.nd, node1);
		
}

BoolExpr_and: BoolExpr And
{
		//����߷��ս����ֵ
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//���������
		BackPatch($1.TC, NXQ);

		//��ʱ�ٳ��ڻ�û��ȷ��
		$$.FC = $1.FC; 


		//��ʼ����ֵ
		struct node*node1;
		complete_init_node(&node1, "And");

		set_node_val_str($1.nd, "BoolExpr");
		
		//��ϵ
		add_son_node($$.nd, $1.nd);
		add_brother_node($1.nd, node1);

}


Variable:	Iden
		{ 
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//��ȡ��ʾ�����±�
		$$.NO = Entry($1);

		//��ʼ����ֵ
		struct node *node1;
		complete_init_node(&node1, $1);
		//��ϵ
		add_son_node($$.nd, node1);
			
		}
	;
Const:		IntNo
		{
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//���ó���ΪINT�ͣ������ó����Ƿ��ڱ��У�������ڱ���
		//����Ҫ��ӵ�����
		$$.type = INT;
		$$.place = Entry($1); 
		//ͬʱ�ڷ��ű�����������
		VarList[VarCount].type = INT;
		//��ʼ����ֵ
		struct node *node1;
		complete_init_node(&node1, $1);
		//��ϵ
		add_son_node($$.nd, node1);
		}
	|	RealNo
		{
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//���ó���ΪREAL�ͣ������ó����Ƿ��ڱ��У�������ڱ���
		//����Ҫ��ӵ�����
		$$.type = REAL;
		$$.place = Entry($1); 
		//ͬʱ�ڷ��ű�����������
		VarList[VarCount].type = REAL;
		//��ʼ����ֵ
		struct node *node1;
		complete_init_node(&node1, $1);
		//��ϵ
		add_son_node($$.nd, node1);
		}
	;
RelationOp:	'<'
		{
		//����߷��ս����ֵ
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;

		memcpy($$._Rop, "j<", sizeof("j<"));
		//��ʼ����ֵ
		struct node *node1;
		complete_init_node(&node1, "<");
		//��ϵ
		add_son_node($$.nd, node1);
		}
	|	'>'
		{
		//����߷��ս����ֵ
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;

		memcpy($$._Rop, "j>", sizeof("j>"));
		//��ʼ����ֵ
		struct node *node1;
		complete_init_node(&node1, ">");
		//��ϵ
		add_son_node($$.nd, node1);

		}	
	|	'='
		{
		//����߷��ս����ֵ
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;

		memcpy($$._Rop, "j=", sizeof("j="));
		//��ʼ����ֵ
		struct node *node1;
		complete_init_node(&node1, "=");
		//��ϵ
		add_son_node($$.nd, node1);
		}
	|	GE
		{
		//����߷��ս����ֵ
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;

		memcpy($$._Rop, "j>=", sizeof("j>="));
		//��ʼ����ֵ
		struct node *node1;
		complete_init_node(&node1, ">=");
		//��ϵ
		add_son_node($$.nd, node1);
		}
	|	NE
		{
		//����߷��ս����ֵ
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;

		memcpy($$._Rop, "j<>", sizeof("j<>"));
		//��ʼ����ֵ
		struct node *node1;
		complete_init_node(&node1, "<>");
		//��ϵ
		add_son_node($$.nd, node1);
		}
	|	LE
		{
		//����߷��ս����ֵ
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;

		memcpy($$._Rop, "j<=", sizeof("j<="));
		//��ʼ����ֵ
		struct node *node1;
		complete_init_node(&node1, "<=");
		//��ϵ
		add_son_node($$.nd, node1);
		}
	;

%%

int yyerror(char *errstr)
{
	printf(" Reason:%s\n", errstr);
	return 0;
}
