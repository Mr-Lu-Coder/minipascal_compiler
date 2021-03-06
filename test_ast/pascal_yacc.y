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
#include "queue.h"
#include "stack.h"  
#include "util.h"
extern int line_number;
extern int error_number;
int yyerror(char*);



#define INT 0
#define REAL 1
#define ARRAY 2
#define BOOL 3

#define WHILE 1
#define FOR 2
#define DO 3
#define REPEAT 4





LinkQueue case_queue;
QElemType item;
LoopStack_ *stack_item, stacknode;
%}
%start    ProgDef
%union 
{
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
	struct {
		char str[20];
		struct node *nd;
	} str_node;
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
		int Break_CH, Continue_CH;
		int type;
		struct node *nd;
	} ForLoop_node;
	//变量节点
	struct {
	    int Array_type; //传递数组是real类型还是Int类型
		int NO;
		int OFFSET; //
		char str[20];
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
	//case 节点的类型
	struct {
		int L_cnt;
		int T;
		int check_id;
		int next_id;
		struct node* nd;
	}case_node;

}
/*Define const:  */
%token <str>   	Iden		300
%token <str>   	IntNo		301
%token <str>  	RealNo		302
%token <str>  	CHAR		303
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
%token	<str>	Repeat		416
%token	<str>	Until		417
%token	<str>	Of			418
%token	<str>	Array		419
%token	<str>	OneDimString	420
%token	<str>	Goto	    421
%token	<str>	Case	    422
%token	<str>	Break	    423
%token	<str>	Continue	424
%token	<str>	Boolean 	425
/*Define double_character terminates:   */
%token			LE			500
%token			GE			501
%token			NE			502
%token			Asign		503
%token			ERRORCHAR	600


%left		And
%left 		Or
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


%type <rop_node> RelationOp
%type <exp_node> Expr

%type <Variable_node> Variable 
%type <ExprList_node> ExprList 
%type <exp_node> Const 
%type <Bexp_node>BoolExpr
%type <Bexp_node>BoolExpr_and 
%type <Bexp_node>BoolExpr_or 
%type <ForLoop_node> Wh
%type <ForLoop_node> WBD

%type <ForLoop_node>ForLoop1
%type <ForLoop_node>ForLoop2 


%type <ForLoop_node>DO
%type <ForLoop_node>DSW
%type <ForLoop_node>RE
%type <ForLoop_node>RSU


%type <TypeFirst_node>TypeFirst
%type <OneDim_node>OneDim
%type <str_node>Label
%type <str_node>LabelDef
%type <str_node>case_const

%type <case_node>InCase 
%type <case_node>CaseStart  
%type <case_node>CaseWithConst  
%type <case_node>CaseWithElse 


%%
ProgDef:	Program Iden ';' SubProg '.'
{
				printf("\n分析成功\n");
				set_node_val_str(&ast_root,$2);

				struct node *tmpnode=NULL;
				//printf("\n\n**** test ast node ****\n\n");
				$$=&ast_root;
				struct node *node1,*node2, *node3,*node4;   //添加四个节点

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

				//子程序已经初始化好了，只需设置名字
				set_node_val_str($4, "SubProg");          
				//printf("In ProgDef: %s\n", $4->val.str);
				add_brother_node(node3, $4);

				complete_init_node(&node4, ".");
				//printf("In ProgDef: %s\n", node4->val.str);
				add_brother_node($4, node4);
}
	;
SubProg:	VarDef CompState
		{
		//初始化左值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$ = cur;
		//设置右值
		set_node_val_str($1.nd,"VarDef");
		set_node_val_str($2.nd,"CompState");
		//建立关系
		add_son_node($$,$1.nd);
		add_brother_node($1.nd,$2.nd);    	
		}
	;
CompState:	Begin StateList End
		{
		//printf("test for begin and end\n");
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		
		$$.CH = $2.CH;
	
		//初始化右值
		struct node*node1,*node2;
		complete_init_node(&node1, "Begin");
		complete_init_node(&node2, "End");

		
		set_node_val_str($2.nd, "StateList");
		
		//关系
		add_son_node($$.nd, node1);
		add_brother_node(node1, $2.nd);
		add_brother_node($2.nd, node2);

		}
	;
VarDef:		Var VarDefList ';'
        {
		//初始化左值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//初始化右值
		struct node *node1, *node2;
		complete_init_node(&node1, "Var");
		complete_init_node(&node2, ";");
		set_node_val_str($2.nd,"VarDefList");
		//建立关系
		add_son_node($$.nd ,node1);
		add_brother_node(node1,$2.nd); 
		add_brother_node($2.nd,node2);  


		}
	;
VarDefList:	VarDefList ';' VarDefState
        {
		//puts("reduce real");
		//初始化左值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//初始化右值
		struct node *node1;
		complete_init_node(&node1, ";");
		set_node_val_str($1.nd,"VarDefList");
		set_node_val_str($3.nd,"VarDefState");
		//建立关系
		add_son_node($$.nd ,$1.nd);
		add_brother_node($1.nd,node1); 
		add_brother_node(node1,$3.nd);  
		}
	|	VarDefState
	    {
		//puts("reduce real");
		//初始化左值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//初始化右值
		set_node_val_str($1.nd,"VarDefState");
		//建立关系
		add_son_node($$.nd ,$1.nd);
        }
	;
VarDefState:	VarList':'Type
		{
		
		//初始化左值
		//puts("AAA");
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//将Type类型赋值给VarList所有变量，也是一个回填的操作
		//puts("AAAen");
		//printf("%d\n",$3.Iv);
		if ($3.type == INT || $3.type == REAL) {
			VarBackPatch($1.First, $3.type);
		}
		else {
			VarBackArrayPatch($1.First, $3.type, $3.Iv, $3.array_no);
		}
		
		//puts("AAAend");
		//printf("Patch: First:%d \n", $1.First);
		//初始化右值
		struct node *node1;
		complete_init_node(&node1, ":");
		set_node_val_str($1.nd,"VarList");
		set_node_val_str($3.nd,"Type");
		//建立关系
		add_son_node($$.nd ,$1.nd);
		add_brother_node($1.nd,node1); 
		add_brother_node(node1,$3.nd);  
		//puts("AAAend");

		}
	;
Type:		Integer
		{
		//printf("INTAAA\n");
		//初始化左值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//类型设置为整型
		$$.type = INT;
		$$.Iv = 0;
		struct node *node1;
		complete_init_node(&node1, "Integer");

		add_son_node($$.nd, node1);
		
		
		}
	|	Real
		{
		//printf("REALAAA\n");
		//初始化左值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//初始化右值
		//类型设置为实型
		$$.type = REAL;
		$$.Iv = 0;
		struct node *node1;
		complete_init_node(&node1, "Real");

		add_son_node($$.nd, node1);


		}
	|	Boolean
		{
		//printf("REALAAA\n");
		//初始化左值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//初始化右值
		//类型设置为实型
		$$.type = BOOL;
		$$.Iv = 0;
		struct node *node1;
		complete_init_node(&node1, "Boolean");

		add_son_node($$.nd, node1);


		}
	|  TypeFirst ']' Of Integer
		{
		//printf("REALAAA\n");
		//初始化左值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;

		//初始化右值
		//类型设置为整型
		$$.type = ARRAY;
		$$.Iv = INT;

		//注意上传数组在类型表中的位置
		$$.array_no = $1.NO;
		struct node *node1, *node2, *node3;
		complete_init_node(&node1, "]");
		complete_init_node(&node2, "Of");
		complete_init_node(&node3, "Integer");
		set_node_val_str($1.nd,"TypeFirst");

		//建立关系
		add_son_node($$.nd ,$1.nd);
		add_brother_node($1.nd,node1); 
		add_brother_node(node1,node2);  
		add_brother_node(node2,node3);  

		}
	| TypeFirst ']' Of Real
		{
		//printf("REALAAA\n");
		//初始化左值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;

		//初始化右值
		//类型设置为实型
		$$.type = ARRAY;
		$$.Iv = REAL;
		//注意上传数组在类型表中的位置
		$$.array_no = $1.NO;

		struct node *node1, *node2, *node3;
		complete_init_node(&node1, "]");
		complete_init_node(&node2, "Of");
		complete_init_node(&node3, "Real");
		set_node_val_str($1.nd,"TypeFirst");

		//建立关系
		add_son_node($$.nd ,$1.nd);
		add_brother_node($1.nd,node1); 
		add_brother_node(node1,node2);  
		add_brother_node(node2,node3);  
		}
	| TypeFirst ']' Of Boolean
		{
		//printf("REALAAA\n");
		//初始化左值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;

		//初始化右值
		//类型设置为实型
		$$.type = ARRAY;
		$$.Iv = BOOL;
		//注意上传数组在类型表中的位置
		$$.array_no = $1.NO;

		struct node *node1, *node2, *node3;
		complete_init_node(&node1, "]");
		complete_init_node(&node2, "Of");
		complete_init_node(&node3, "Boolean");
		set_node_val_str($1.nd,"TypeFirst");

		//建立关系
		add_son_node($$.nd ,$1.nd);
		add_brother_node($1.nd,node1); 
		add_brother_node(node1,node2);  
		add_brother_node(node2,node3);  
		}
	;
TypeFirst : TypeFirst ',' OneDim
		{
		//printf("REALAAA\n");
		//初始化左值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		
		//更新D和C
		int k = $1.DIM + 1;
		Update_C($1.NO, k, $3.L, $3.U);
		Update_D($1.NO, k, $3.L, $3.U);


		//更新typefirst
		$$.NO = $1.NO;
		$$.DIM = k;


		struct node *node1;
		complete_init_node(&node1, ",");
		set_node_val_str($3.nd,"OneDim");
		set_node_val_str($1.nd,"TypeFirst");

		//建立关系
		add_son_node($$.nd, $1.nd);
		add_brother_node($1.nd,node1); 
		add_brother_node(node1,$3.nd);  

			
		} 
		|   Array '[' OneDim
		{
		//printf("REALAAA\n");
		//初始化左值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;

		$$.DIM = 1;
		$$.NO = New_Array_Type();
		Update_D($$.NO, $$.DIM, $3.L, $3.U);


		struct node *node1, *node2;
		complete_init_node(&node1, "Array");
		complete_init_node(&node2, "[");
		set_node_val_str($3.nd,"OneDim");

		//建立关系
		add_son_node($$.nd, node1);
		add_brother_node(node1,node2); 
		add_brother_node(node2,$3.nd);  

		}
		;


OneDim : IntNo '.''.' IntNo	 
	{
		//printf("REALAAA\n");
		//初始化左值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;

		$$.L = atoi($1);
		$$.U = atoi($4);

		struct node *node1, *node2, *node3;
		complete_init_node(&node1, $1);
		complete_init_node(&node2, "..");
		complete_init_node(&node3, $4);

		//建立关系
		add_son_node($$.nd, node1);
		add_brother_node(node1,node2); 
		add_brother_node(node2,node3);  


	}| OneDimString{
		//printf("***************\n");
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		int L, U;
		Get_L_and_U($1, &L, &U);

		$$.L = L;
		$$.U = U;
		//printf("\n*** %d %d\n", $$.L, $$.U);
		struct node *node1;
		complete_init_node(&node1, $1);

		//建立关系
		add_son_node($$.nd, node1);
	  }
	
	
	;
VarList:	VarList','Variable
		{
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		
	
		//初始化右值
		struct node*node1;
		complete_init_node(&node1, ",");

		set_node_val_str($1.nd, "VarList");
		set_node_val_str($3.nd, "Variable");
		//关系
		add_son_node($$.nd, $1.nd);
		add_brother_node($1.nd, node1);
		add_brother_node(node1, $3.nd);
		//将变量连接起来，因为变量定义的时候会出现 Var a,b,c:integer的情况
		//所以需要保存First保存链头,这里是$1.First.addr = $3.NO
		$$.First = Merge_var($3.NO, $1.First);
		//printf("First:%d \n", $$.First);
		}
	|	Variable
		{
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//传递变量的符号，最终Varlist.First 保存的是第一个变量的place
		$$.First = $1.NO;
		//初始化右值

		set_node_val_str($1.nd, "Variable");
		//关系
		add_son_node($$.nd, $1.nd);
		}
	;
//程序主体语句从这开始
StateList:	S_L Statement
		{
		//printf("test for StateList\n");
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//此处传递的是$2链的出口
		$$.CH = $2.CH;
		
		//初始化右值
		//printf("end for State_List\n");
		set_node_val_str($1.nd, "S_L");
		set_node_val_str($2.nd, "Statement");
		//struct node *node1;
		//complete_init_node(&node1, ";");
		//关系
		add_son_node($$.nd, $1.nd);
		add_brother_node($1.nd, $2.nd);
		//add_brother_node($2.nd, node1);
		
		}
	|	Statement
		{

		//printf("test for Statement\n");
		//给左边非终结符赋值

		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//传递
		$$.CH = $1.CH;

		//初始化右值
		//struct node *node1;
		//complete_init_node(&node1, ";");

		set_node_val_str($1.nd, "Statement");
		//关系
		add_son_node($$.nd, $1.nd);
		//add_brother_node($1.nd, node1);
		}
	;
S_L:		StateList ';'
		{
		//printf("test for State_L\n");
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//!!!!!!!!!!!!!!!!!!!!
		///此时分析器刚分析完分号，控制流程将继续顺序执行
		//所以下一个四元式的序号回填StateList的出口链
		//$$.CH = $1.CH;
		//printf("Back\n");
		BackPatch($1.CH, NXQ);
		
		//初始化右值
		struct node *node1;
		complete_init_node(&node1, ";");
		set_node_val_str($1.nd, "StateList");
		
		
		//关系
		add_son_node($$.nd, $1.nd);
		add_brother_node($1.nd, node1);
		
		}
	;
Statement:	AsignState
		{
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;

		//链为0 表示为链的终止处
		$$.CH = 0;

		set_node_val_str($1.nd, "AsignState");
		//关系
		add_son_node($$.nd, $1.nd);
		}
	|	ISE Statement  //IF Boolexp then statement else statement
		{
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//此时布尔表达式的假出口应该和statement的出口一致
		//合并s1和s2的出口
		$$.CH = Merge($1.CH, $2.CH);

		set_node_val_str($1.nd, "ISE");
		set_node_val_str($2.nd, "Statement");
		
		//关系
		add_son_node($$.nd, $1.nd);
		add_brother_node($1.nd, $2.nd);

		}
	|	IBT Statement
		{
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//此时布尔表达式的假出口应该和statement的出口一致
		$$.CH = Merge($1.CH, $2.CH);

		set_node_val_str($1.nd, "IBT");
		set_node_val_str($2.nd, "Statement");
		
		//关系
		add_son_node($$.nd, $1.nd);
		add_brother_node($1.nd, $2.nd);


		}

	|	WBD Statement
		{
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		
		BackPatch($2.CH, $1.loop);
		//此时应无条件返回到循环初始的位置
		GEN("j", 0, 0, $1.loop);
		//此时布尔表达式的假出口传递
		$$.CH = $1.CH;

		//此时栈顶的break_ch出现
		/*处理break， continue*/
		top(&stack_item);  
		if (stack_item == NULL) {
			error_number = INNER_ERROR;
			yyerror("stack_item is NULL");
		}
		//printf("stack_item->breakch %d\n", stack_item->break_ch);
		BackPatch(stack_item->break_ch, NXQ);
		//同时弹出栈顶元素
		pop();


		set_node_val_str($1.nd, "WBD");
		set_node_val_str($2.nd, "Statement");
		
		//关系
		add_son_node($$.nd, $1.nd);
		add_brother_node($1.nd, $2.nd);


		}
	|   DSW BoolExpr
		{
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		
		//回填bool表达式的真出口
		BackPatch($2.TC, $1.loop);
		//将bool表达式的假出口上传
		$$.CH = $2.FC;

		//此时栈顶的break_ch出现
		/*处理break， continue*/
		top(&stack_item);  
		if (stack_item == NULL) {
			error_number = INNER_ERROR;
			yyerror("stack_item is NULL");
		}
		BackPatch(stack_item->break_ch, NXQ);
		//同时弹出栈顶元素
		pop();


		set_node_val_str($1.nd, "DSW");
		set_node_val_str($2.nd, "BoolExpr");
		
		//关系
		add_son_node($$.nd, $1.nd);
		add_brother_node($1.nd, $2.nd);

		
		}
	|   RSU BoolExpr
		{

		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//回填bool表达式的假出口
		BackPatch($2.FC, $1.loop);
		//将bool表达式的假真出口上传
		$$.CH = $2.TC;

		//此时栈顶的break_ch出现
		/*处理break， continue*/
		top(&stack_item);  
		if (stack_item == NULL) {
			error_number = INNER_ERROR;
			yyerror("stack_item is NULL");
		}
		BackPatch(stack_item->break_ch, NXQ);
		//同时弹出栈顶元素
		pop();


		set_node_val_str($1.nd, "RSU");
		set_node_val_str($2.nd, "BoolExpr");
		
		//关系
		add_son_node($$.nd, $1.nd);
		add_brother_node($1.nd, $2.nd);
		
		}
	|	CompState
	    {
		//printf("compstate in statement\n");
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//此时出口向上传递
		$$.CH = $1.CH;

		set_node_val_str($1.nd, "CompState");

		//关系
		add_son_node($$.nd, $1.nd);


		}
	|	ForLoop2 Do Statement{
			
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//此时控制变量自增的四元式是下一条，
		//对statement进行回填
		BackPatch($3.CH, NXQ);
		//控制变量自增的四元式


		//此时栈顶的continue_ch出现
		/*处理break， continue*/
		top(&stack_item); 
		if (stack_item == NULL) {
			error_number = INNER_ERROR;
			yyerror("stack_item is NULL");
		}
		BackPatch(stack_item->continue_ch, NXQ);

		GEN("+", $1.place, Entry("1"), $1.place);

		//返回循环起始节点
		GEN("j", 0, 0, $1.loop);

		//传递出口
		$$.CH = $1.CH;
		
		//此时栈顶的break_ch出现
		/*处理break， continue*/
		top(&stack_item);  
		if (stack_item == NULL) {
			error_number = INNER_ERROR;
			yyerror("stack_item is NULL");
		}
		BackPatch(stack_item->break_ch, NXQ);
		//同时弹出栈顶元素
		pop();


		struct node* node1;
		complete_init_node(&node1, "Do");

		set_node_val_str($1.nd, "ForLoop2");
		set_node_val_str($3.nd, "Statement");
		
		
		//关系
		add_son_node($$.nd, $1.nd);
		add_brother_node($1.nd, node1);
		add_brother_node(node1, $3.nd);

	    }
	|LabelDef Statement
	{
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//链
		$$.CH = $2.CH;
		
		set_node_val_str($1.nd, "LabelDef");
		set_node_val_str($2.nd, "Statement");
		
		//关系
		add_son_node($$.nd, $1.nd);
		add_brother_node($1.nd, $2.nd);
	
	}
	| Goto Label
	{
		//给左边非终结符赋值
		//printf("goto label****\n");
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		$$.CH = 0;
		//内部逻辑
		//puts($2.str);
		int i = LookUpLabel($2.str);
		//printf("find result i:  %d\n", i);
		//该标号是首次出现
		if (i == 0) {
			i = EnterLabel($2.str);
			LabelList[i].DEF = 0;
			LabelList[i].ADDR = NXQ;

			GEN("j", 0, 0, 0);
		}else{/*该标号已经出现过*/
			if (LabelList[i].DEF) //已定义可以直接使用地址
			{
				GEN("j", 0, 0, LabelList[i].ADDR);
				//printf("get GEN %d ", LabelList[i].ADDR);
			} 
				
			else {
				//未定义，需要拉链
				int n = NXQ;
				GEN("j", 0, 0, LabelList[i].ADDR);
				LabelList[i].ADDR = n;	
			}
		}

		struct node* node1;
		complete_init_node(&node1, "Goto");

		set_node_val_str($2.nd, "Label");
		//关系
		add_son_node($$.nd, node1);
		add_brother_node(node1, $2.nd);
	}
	|CaseWithElse Statement ';' End
{
	

	//给左边非终结符赋值
	struct node* cur;
	complete_init_node(&cur, "NULL");
	$$.nd = cur;
	$$.CH = 0;


	struct node* node1, *node2;
	complete_init_node(&node1, ";");
	complete_init_node(&node2, "End");

	set_node_val_str($1.nd, "CaseWithElse");
	set_node_val_str($2.nd, "Statement");
	//关系
	add_son_node($$.nd, $1.nd);
	add_brother_node($1.nd, $2.nd);
	add_brother_node($2.nd, node1);
	add_brother_node(node1, node2);

	//内部逻辑
	//statement 结束后  goto next
	//未定义，需要拉链
	int n = NXQ;
	GEN("j", 0, 0, LabelList[$1.next_id].ADDR);
	LabelList[$1.next_id].ADDR = n;	

	
	//首先对check_id进行回填
	BackPatch(LabelList[$1.check_id].ADDR, NXQ);
	//此时要开始生成if else 的四元式
	for (int i = 1; i < $1.L_cnt; i++) {
		DeQueue(&case_queue, &item);
		GEN("j=", $1.T, item.arg2, LabelList[item.result].ADDR);
	}
	DeQueue(&case_queue, &item);
	GEN("j", 0, 0, LabelList[item.result].ADDR);
	myDestroyQueue(&case_queue);
	
	//对next进行回填
	BackPatch(LabelList[$1.next_id].ADDR, NXQ);


};
	|Break
	{
		//printf("breakGGG");
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		$$.CH = 0;

		struct node* node1;
		complete_init_node(&node1, "Break");

		add_son_node($$.nd, node1);

		//栈为空表明有错
		if (is_empty()) {
			error_number = INNER_ERROR;
			yyerror("stack is NULL");
			
		}
		top(&stack_item);
		if (stack_item == NULL) {
			error_number = INNER_ERROR;
			yyerror("stack_item is NULL");
		}
		//四种循环都是直接跳出，且跳出的NXQ都是循环的下边
		int n = NXQ;
		if (stack_item == NULL) {
			puts("NULL!!!");
		}
		//printf("breck_ch %d", stack_item->break_ch);
		
		GEN("j", 0, 0, 0);
		stack_item->break_ch = Merge(stack_item->break_ch, n);
		//printf("breck_ch %d", stack_item->break_ch);
		//printf("GG:%d", stack_item->break_ch);
		top(&stack_item);
		if (stack_item == NULL) {
			error_number = INNER_ERROR;
			yyerror("stack_item is NULL");
		}
		//printf("GG:%d", stack_item->break_ch);
		//printf("end4GG");
		
		
	}
	|Continue{
		//printf("continue statement");
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		$$.CH = 0;

		struct node* node1;
		complete_init_node(&node1, "Continue");

		add_son_node($$.nd, node1);
		//栈为空表明有错
		if (is_empty()) {
			error_number = INNER_ERROR;
			yyerror("stack is NULL");
		}
		top(&stack_item);
		if (stack_item == NULL) {
			error_number = INNER_ERROR;
			yyerror("stack_item is NULL");
		}
		switch(stack_item->type) {
			case WHILE:{
				GEN("j", 0, 0, stack_item->loop);
				break;
			}
			case FOR:{
				//此时do的continue中loop还没有确定,需要拉链，因为变量需要自增
				int n = NXQ;
				GEN("j", 0, 0, 0);
				stack_item->continue_ch = Merge(stack_item->continue_ch, n);
				break;
			}
			case DO:{
			    //此时do的continue中loop还没有确定,需要拉链
				int n = NXQ;
				GEN("j", 0, 0, 0);
				stack_item->continue_ch = Merge(stack_item->continue_ch, n);
				break;
			}
			case REPEAT:{
				 //此时do的continue中loop还没有确定,需要拉链
				int n = NXQ;
				GEN("j", 0, 0, 0);
				stack_item->continue_ch = Merge(stack_item->continue_ch, n);
				break;
			}
			default:{
				//lushangqi
				break;
			}
		}
		

	}


	|{   
		//给左边非终结符赋值
		//printf("goto label****\n");
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		$$.CH = 0;	
	 //需要这个为空也是 有意义的！！！！！！！
	//   StateList:	S_L Statement
	//因为存在上述文法，所以Statement可以为空
	}
	;
LabelDef : Label ':'
	{
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//printf(":::::%s", $1.str);
		int i = LookUpLabel($1.str);
		//printf("find result %d", i);
		if (i == 0) {
			i = EnterLabel($1.str);
			LabelList[i].DEF = 1;
			LabelList[i].ADDR = NXQ;
		}else if (LabelList[i].DEF){
			//label 重复定义
			error_number = LABEL_REDEF;
			yyerror("Label redefinition!");
		}else{
			LabelList[i].DEF = 1;
			BackPatch(LabelList[i].ADDR, NXQ);
			LabelList[i].ADDR = NXQ;
		}

		struct node* node1;
		complete_init_node(&node1, "Goto");

		set_node_val_str($1.nd, "Label");
		//关系
		add_son_node($$.nd, $1.nd);
		add_brother_node($1.nd, node1);
	
	}
Label : IntNo
	{
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;

		strncpy($$.str, $1, sizeof($1));
		struct node* node1;
		complete_init_node(&node1, $1);
		//关系
		add_son_node($$.nd, node1);
	}
	|  Iden
	{
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;

		strncpy($$.str, $1, sizeof($1));
		struct node* node1;
		complete_init_node(&node1, $1);
		//关系
		add_son_node($$.nd, node1);
	};
ForLoop1: For Iden Asign Expr
{
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		
		int i = Entry($2);
		//此时生成赋值四元式
		GEN(":=", $4.place, 0, i);
		//将控制变量所在的位置传递
		$$.place = i;

		//初始化右值
		struct node* node1,*node2, *node3;
		complete_init_node(&node1, "For");
		complete_init_node(&node2, $2);
		complete_init_node(&node3, ":=");
		set_node_val_str($4.nd, "Expr");
		
		
		//关系
		add_son_node($$.nd, node1);
		add_brother_node(node1, node2);
		add_brother_node(node2, node3);
		add_brother_node(node3, $4.nd);
};
ForLoop2: ForLoop1 To Expr
{
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		
		int p = NXQ;
		//传递循环返回点信息，loop指向循环体的第一条四元式
		$$.loop = NXQ;

		/*处理break continne */
		stacknode.loop = $$.loop;
		stacknode.type = FOR;
		stacknode.break_ch = 0;
		stacknode.continue_ch = 0;
		push(&stacknode);  //lushangqi   
		
		
		   
		//此时生成赋值四元式
		GEN("j<", $1.place, $3.place, p+2);
		//将控制变量所在的位置传递
		$$.place = $1.place;
		//循环语句的出口
		$$.CH = NXQ;
		GEN("j", 0, 0, 0);
		//初始化右值
		struct node* node1;
		complete_init_node(&node1, "To");

		set_node_val_str($1.nd, "ForLoop1");
		set_node_val_str($3.nd, "Expr");
		
		
		//关系
		add_son_node($$.nd, $1.nd);
		add_brother_node($1.nd, node1);
		add_brother_node(node1, $3.nd);
};


AsignState:	Variable Asign Expr
		{

		//printf("Asignstate\n");
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		
		//对于赋值语句生成四元式
		if ($1.OFFSET == 0) {
			GEN(":=", $3.place, 0, $1.NO);
		}else{
			GEN("[]=", $3.place, $1.NO, $1.OFFSET);
		}
		
	
		//初始化右值
		struct node*node1;
		complete_init_node(&node1, ":=");

		
		set_node_val_str($1.nd, "Variable");
		set_node_val_str($3.nd, "Expr");
		
		//关系
		add_son_node($$.nd, $1.nd);
		add_brother_node($1.nd, node1);
		add_brother_node(node1, $3.nd);
		}
	;
ISE:		IBT Statement Else
		{
		//printf("ISE begin");
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		int q = NXQ;
		//需要添加一个四元式，跳入真出口
		GEN("j",0,0,0);

		//此时下一个四元式，为假出口，所以需要回填
		BackPatch($1.CH, NXQ);
		//通过合并真出口和假出口为整个S的出口
		$$.CH = Merge($2.CH, q);

		set_node_val_str($1.nd, "IBT");
		set_node_val_str($2.nd, "Statement");
		struct node * node1;
		complete_init_node(&node1, "Else");

		//关系
		add_son_node($$.nd, $1.nd);
		add_brother_node($1.nd, $2.nd);
		add_brother_node($2.nd, node1);


		}
	;
IBT:		If BoolExpr Then
		{
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//此时下一个四元式，为真出口，所以需要回填
		BackPatch($2.TC, NXQ);
		//假出口还不确定
		$$.CH = $2.FC;


		set_node_val_str($2.nd, "BoolExpr");
		struct node * node1, *node2;
		complete_init_node(&node1, "IF");
		complete_init_node(&node2, "Then");
		//关系
		add_son_node($$.nd, node1);
		add_brother_node(node1, $2.nd);
		add_brother_node($2.nd, node2);
		}

	;
WBD: Wh BoolExpr Do
		{
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//此时下一个四元式，为真出口，所以需要回填
		BackPatch($2.TC, NXQ);
		//假出口还不确定
		$$.CH = $2.FC;
		//传递起始地址
		$$.loop = $1.CH;

		/*处理break continne */
		stacknode.loop = $$.loop;
		stacknode.type = WHILE;
		stacknode.break_ch = 0;
		stacknode.continue_ch = 0;
		push(&stacknode);  //lushangqi   


		set_node_val_str($1.nd, "Wh");
		set_node_val_str($2.nd, "BoolExpr");
		struct node * node1;
		complete_init_node(&node1, "Do");
		//关系
		add_son_node($$.nd, $1.nd);
		add_brother_node($1.nd, $2.nd);
		add_brother_node($2.nd, node1);

		}
	;
Wh:		While
        {
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//设置下一个四元式为链
		$$.CH = NXQ;
		struct node* node1;
		complete_init_node(&node1, "While");
		//关系
		add_son_node($$.nd, node1);
        }
	;


Expr:		Expr'+'Expr
		{
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//printf("Expr+expr");
		int T = NewTemp();
		//对于算数操作生成四元式,如果有一个是real就要把int型进行强制转换
		if ($1.type == BOOL || $3.type == BOOL) {
		    error_number = BOOL_OP_ERROR;
			yyerror("+");
		}
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
	
		//初始化右值
		struct node*node1;
		complete_init_node(&node1, "+");

		set_node_val_str($1.nd, "Expr");
		set_node_val_str($3.nd, "Expr");
		
		//关系
		add_son_node($$.nd, $1.nd);
		add_brother_node($1.nd, node1);
		add_brother_node(node1, $3.nd);


		}
	|	Expr'-'Expr
		{
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		if ($1.type == BOOL || $3.type == BOOL) {
		    error_number = BOOL_OP_ERROR;
			yyerror("-");
		}
		int T = NewTemp();
		//对于算数操作生成四元式,如果有一个是real就要把int型进行强制转换
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
	
		//初始化右值
		struct node*node1;
		complete_init_node(&node1, "-");

		set_node_val_str($1.nd, "Expr");
		set_node_val_str($3.nd, "Expr");
		
		//关系
		add_son_node($$.nd, $1.nd);
		add_brother_node($1.nd, node1);
		add_brother_node(node1, $3.nd);

		}

	|	Expr'*'Expr
		{
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		if ($1.type == BOOL || $3.type == BOOL) {
		    error_number = BOOL_OP_ERROR;
			yyerror("*");
		}
		int T = NewTemp();
		//对于算数操作生成四元式,如果有一个是real就要把int型进行强制转换
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
	
		//初始化右值
		struct node*node1;
		complete_init_node(&node1, "*");

		set_node_val_str($1.nd, "Expr");
		set_node_val_str($3.nd, "Expr");
		
		//关系
		add_son_node($$.nd, $1.nd);
		add_brother_node($1.nd, node1);
		add_brother_node(node1, $3.nd);




		}
	|	Expr'/'Expr
		{
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		if ($1.type == BOOL || $3.type == BOOL) {
		    error_number = BOOL_OP_ERROR;
			yyerror("/");
		}
		int T = NewTemp();
		//对于算数操作生成四元式,如果有一个是real就要把int型进行强制转换
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
	
		//初始化右值
		struct node*node1;
		complete_init_node(&node1, "/");

		set_node_val_str($1.nd, "Expr");
		set_node_val_str($3.nd, "Expr");
		
		//关系
		add_son_node($$.nd, $1.nd);
		add_brother_node($1.nd, node1);
		add_brother_node(node1, $3.nd);

		}
	|	'('Expr')'
		{
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;

		$$.type = $2.type;
		$$.place = $2.place;
		//$$ = $2;


		//初始化右值
		struct node*node1,*node2;
		complete_init_node(&node1, "(");
		complete_init_node(&node2, ")");

		
		set_node_val_str($2.nd, "Expr");
		
		//关系
		add_son_node($$.nd, node1);
		add_brother_node(node1, $2.nd);
		add_brother_node($2.nd, node2);


		}
	|	'-' Expr %prec UMINUS
		{
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		
		//对于赋值语句生成四元式
		GEN("-", $2.place, 0, $2.place);
		$$.type = $2.type;
		$$.place = $2.place;

		//初始化右值
		struct node*node1;
		complete_init_node(&node1, "-");
		
		set_node_val_str($2.nd, "Expr");
		//关系
		add_son_node($$.nd, node1);
		add_brother_node(node1, $2.nd);


		}
	|	Variable
		{
			//printf("Variable");
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//将变量在符号表中的类型和位置给表达式
		
		if (!$1.OFFSET) {
			$$.place = $1.NO;
			$$.type = VarList[$1.NO].type;
			set_node_val_str($1.nd, "Variable");
		}
		else {
			int T = NewTemp();
			GEN("=[]", $1.NO, $1.OFFSET, T);
			$$.place = T;
			$$.type = $1.Array_type;
			set_node_val_str($1.nd, "VariaArray");
		}

		//关系
		add_son_node($$.nd, $1.nd);

		}

	|	Const
		{
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//   上传type
		$$.type = $1.type;

		set_node_val_str($1.nd, "Const");
		//关系
		add_son_node($$.nd, $1.nd);
		$$ = $1;

		}
	;



BoolExpr:	Expr RelationOp Expr
		{
		//printf("Bool op Bool\n");
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//传递 真和假出口
		$$.TC = NXQ;
		$$.FC = NXQ+1;
		
		GEN($2._Rop ,$1.place, $3.place,0);
		GEN("j",0,0,0);

		//struct node*node1;
		//complete_init_node(&node1, $2._Rop);

		//初始化右值
		set_node_val_str($1.nd, "Expr");
		set_node_val_str($2.nd, $2._Rop);
		set_node_val_str($3.nd, "Expr");


		//关系
		add_son_node($$.nd, $1.nd);
		add_brother_node($1.nd, $2.nd);
		add_brother_node($2.nd, $3.nd);

		}
	|	BoolExpr_and BoolExpr
	    {
		//printf("bool_and boolexpr to bool");
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//传递 真和假出口
		$$.FC = Merge($1.FC, $2.FC);
		$$.TC = $2.TC;

		//初始化右值
		set_node_val_str($1.nd, "BoolExpr_and");
		set_node_val_str($2.nd, "BoolExpr");
		
		//关系
		add_son_node($$.nd, $1.nd);
		add_brother_node($1.nd, $2.nd);
		}
	|	BoolExpr_or BoolExpr
	    {
		//printf("bool_or boolexpr to bool");
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//传递 真和假出口
		$$.TC = Merge($1.TC, $2.TC);
		$$.FC = $2.FC;

		//初始化右值
		set_node_val_str($1.nd, "BoolExpr_or");
		set_node_val_str($2.nd, "BoolExpr");
		
		//关系
		add_son_node($$.nd, $1.nd);
		add_brother_node($1.nd, $2.nd);
		}	
	|	Not BoolExpr
	    {
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//传递 真和假出口
		$$.TC = $2.FC;
		$$.FC = $2.TC;

		//初始化右值
		struct node*node1;
		complete_init_node(&node1, "Not");
		
		set_node_val_str($2.nd, "BoolExpr");
		
		//关系
		add_son_node($$.nd, node1);
		add_brother_node(node1, $2.nd);
		
		}
	|	'(' BoolExpr ')'
	    {
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//传递 真和假出口
		$$.TC = $2.TC;
		$$.FC = $2.FC;

		//初始化右值
		struct node*node1,*node2;
		complete_init_node(&node1, "(");
		complete_init_node(&node2, ")");

		set_node_val_str($2.nd, "BoolExpr");
		
		//关系
		add_son_node($$.nd, node1);
		add_brother_node(node1, $2.nd);
		add_brother_node($2.nd, node2);
		}
		| Iden
		{
			//给左边非终结符赋值
			struct node* cur;
			complete_init_node(&cur, "NULL");
			$$.nd = cur;
			//传递 真和假出口
			$$.TC = NXQ;
			$$.FC = NXQ + 1;

			GEN("jnz", Entry($1), 0, 0);
			GEN("j", 0, 0, 0);

			struct node*node1;
			complete_init_node(&node1, $1);
			//关系
			add_son_node($$.nd, node1);

		}
		| IntNo
		{
			//给左边非终结符赋值
			struct node* cur;
			complete_init_node(&cur, "NULL");
			$$.nd = cur;
			//传递 真和假出口
			$$.TC = NXQ;
			$$.FC = NXQ + 1;

			GEN("jnz", Entry($1), 0, 0);
			GEN("j", 0, 0, 0);

			struct node*node1;
			complete_init_node(&node1, $1);
			//关系
			add_son_node($$.nd, node1);

		}

	;
BoolExpr_or: BoolExpr Or
{
		//printf("to bool_or");
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//回填假出口
		BackPatch($1.FC, NXQ);
		$$.TC = $1.TC; 


		//初始化右值
		struct node*node1;
		complete_init_node(&node1, "Or");

		set_node_val_str($1.nd, "BoolExpr");
		
		//关系
		add_son_node($$.nd, $1.nd);
		add_brother_node($1.nd, node1);
		
}

BoolExpr_and: BoolExpr And
{
       //printf("to bool_and");
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//回填真出口
		BackPatch($1.TC, NXQ);

		//此时假出口还没有确定
		$$.FC = $1.FC; 


		//初始化右值
		struct node*node1;
		complete_init_node(&node1, "And");

		set_node_val_str($1.nd, "BoolExpr");
		
		//关系
		add_son_node($$.nd, $1.nd);
		add_brother_node($1.nd, node1);

}



 

CaseWithElse: InCase Else
{
	
	//给左边非终结符赋值
	struct node* cur;
	complete_init_node(&cur, "NULL");
	$$.nd = cur;
	

	struct node* node1;
	complete_init_node(&node1, "Else");
	set_node_val_str($1.nd, "InCase");
	//关系
	add_son_node($$.nd, $1.nd);
	add_brother_node($1.nd, node1);


	int L_id = GetLLabel();
	if (L_id == 0) {
		error_number = INNER_ERROR;
		yyerror("can not find an empty Label id!");
	}

	item.arg2 = 0;
	
	item.result = L_id;
	EnQueue(&case_queue, item);
	
	
	$$.check_id = $1.check_id;
	$$.next_id = $1.next_id;
	$$.T = $1.T;
	$$.L_cnt = $1.L_cnt + 1;
	
	//定义L label.
	LabelList[L_id].DEF = 1;
	LabelList[L_id].ADDR = NXQ;

}

InCase : CaseWithConst Statement  ';'
{

	//给左边非终结符赋值
	struct node* cur;
	complete_init_node(&cur, "NULL");
	$$.nd = cur;
	

	struct node* node1;
	complete_init_node(&node1, ";");
	set_node_val_str($1.nd, "CaseWithConst");
	set_node_val_str($2.nd, "Statement");
	//关系
	add_son_node($$.nd, $1.nd);
	add_brother_node($1.nd, $2.nd);
	add_brother_node($2.nd, node1);



	$$.check_id = $1.check_id;
	$$.next_id = $1.next_id;
	$$.T = $1.T;
	$$.L_cnt = $1.L_cnt;
	//此时statement的四元式已经生成

	// goto next  
	//未定义，需要拉链
	int n = NXQ;
	GEN("j", 0, 0, LabelList[$$.next_id].ADDR);
	LabelList[$$.next_id].ADDR = n;	

}

CaseWithConst : CaseStart case_const ':'
{
	//printf("test CaseWithconst");

	//给左边非终结符赋值
	struct node* cur;
	complete_init_node(&cur, "NULL");
	$$.nd = cur;
	

	struct node* node1;
	complete_init_node(&node1, ":");
	set_node_val_str($1.nd, "CaseStart");
	set_node_val_str($2.nd, "case_const");
	//关系
	add_son_node($$.nd, $1.nd);
	add_brother_node($1.nd, $2.nd);
	add_brother_node($2.nd, node1);



	//这里找的肯定是没有出现过的，
	int L_id = GetLLabel();
	if (L_id == 0) {
		error_number = INNER_ERROR;
		yyerror("can not find an empty Label id!");
	}
	
	//进队列
	item.arg2 = Entry($2.str);
	item.result = L_id;
	EnQueue(&case_queue, item);

	$$.check_id = $1.check_id;
	$$.next_id = $1.next_id;
	$$.T = $1.T;
	$$.L_cnt = 1;
	//定义L label.
	LabelList[L_id].DEF = 1;
	LabelList[L_id].ADDR = NXQ;
	

}
| InCase case_const ':'
{

	//给左边非终结符赋值
	struct node* cur;
	complete_init_node(&cur, "NULL");
	$$.nd = cur;
	

	struct node* node1;
	complete_init_node(&node1, ":");
	set_node_val_str($1.nd, "InCase");
	set_node_val_str($2.nd, "case_const");
	//关系
	add_son_node($$.nd, $1.nd);
	add_brother_node($1.nd, $2.nd);
	add_brother_node($2.nd, node1);


	int L_id = GetLLabel();
	if (L_id == 0) {
		error_number = INNER_ERROR;
		yyerror("can not find a empty Label id!");
	}

	//进队列
	item.arg2 = Entry($2.str);
	item.result = L_id;
	EnQueue(&case_queue, item);

	$$.check_id = $1.check_id;
	$$.next_id = $1.next_id;
	$$.T = $1.T;
	$$.L_cnt = $1.L_cnt + 1;
	//此时statement的四元式已经生成

	//定义L label.
	LabelList[L_id].DEF = 1;
	LabelList[L_id].ADDR = NXQ;

}
CaseStart : Case Expr Of
{
	//printf("test Case start");
	//给左边非终结符赋值
	struct node* cur;
	complete_init_node(&cur, "NULL");
	$$.nd = cur;
	

	struct node* node1, *node2;
	complete_init_node(&node1, "Case");
	complete_init_node(&node2, "Of");
	set_node_val_str($2.nd, "Expr");
	//关系
	add_son_node($$.nd, node1);
	add_brother_node(node1, $2.nd);
	add_brother_node($2.nd, node2);
	
	//生成check Label 和next label  该label未出现过
	int check_id = GetCheckLabel();
	int next_id = GetNextLabel();
	if (check_id == 0 || next_id == 0) {
		error_number = INNER_ERROR;
		yyerror("can not find an empty Label id!");
	}
	$$.check_id = check_id;
	$$.next_id = next_id;

	int T = NewTemp();
	GEN(":=", $2.place, 0, T); //T = Expr

	$$.T = T;
	LabelList[check_id].ADDR = NXQ;   //还没确定，需要拉链
	GEN("j", 0, 0, 0);		//goto check

	//初始化队列
	//
	InitQueue(&case_queue);
}
case_const: IntNo{
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;

		strncpy($$.str, $1, sizeof($1));
		struct node* node1;
		complete_init_node(&node1, $1);
		//关系
		add_son_node($$.nd, node1);
	  }
	|CHAR{
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;

		strncpy($$.str, $1, sizeof($1));
		struct node* node1;
		complete_init_node(&node1, $1);
		//关系
		add_son_node($$.nd, node1);
	}

ExprList: ExprList ',' Expr
		{
		//给左边非终结符赋值
			struct node* cur;
			complete_init_node(&cur, "NULL");
			$$.nd = cur;

			int k, d;
			int T1 = NewTemp();
			//int T2 = NewTemp();
			k = $1.DIM + 1;

			d = Access_d($1.NO, k);
			//printf("%d....\n", d);
			//生成四元式
			char name[TABLE_MAX_IDENT_NAME_LEN];
			_itoa(d, name,10);
			//GEN(":=",Entry(name), 0, T1);
			int d_place = Entry(name);
			//puts(name);
			GEN("*", $1.tmp_place, d_place, T1);
			GEN("+", $3.place, T1, T1);

			//上传
			$$.NO = $1.NO;
			//传递存放中间结果的VARPART
			$$.tmp_place = T1;
			$$.DIM = k;

			//初始化右值
			struct node*node1;

			complete_init_node(&node1, ",");

			set_node_val_str($1.nd, "ExprList");
			set_node_val_str($1.nd, "Expr");

			//关系
			add_son_node($$.nd, $1.nd);
			add_brother_node($1.nd, node1);
			add_brother_node(node1, $3.nd);


		}
		| Iden '[' Expr 
		{
			//给左边非终结符赋值
			struct node* cur;
			complete_init_node(&cur, "NULL");
			$$.nd = cur;


			$$.NO = Entry($1);
			$$.DIM = 1;
			//相当于VARPART = Ii;
			$$.tmp_place = $3.place;


			//初始化右值
			struct node*node1, *node2;

			complete_init_node(&node1, $1);
			complete_init_node(&node2, "[");

			set_node_val_str($3.nd, "Expr");

			//关系
			add_son_node($$.nd, node1);
			add_brother_node(node1, node2);
			add_brother_node(node2, $3.nd);
		}
	;
Variable:	Iden
		{ 
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//获取标示符的下标
		$$.NO = Entry($1);
		//此时为普通变量
		$$.OFFSET = 0;

		//初始化右值
		struct node *node1;
		complete_init_node(&node1, $1);
		//关系
		add_son_node($$.nd, node1);
			
		}
	|   ExprList ']'
		{
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;

		int a, C;
		int T = NewTemp();
		C = Access_C($1.NO);
		a = Access_a($1.NO);
		//printf("**%d**", C);
		char tmp_C[20], tmp_a[20];
		_itoa(C,tmp_C, 10);
		_itoa(a,tmp_a, 10);
		//产生a - C的代码
		GEN("-", Entry(tmp_a), Entry(tmp_C), T);
		//传递数组名的下标
		$$.Array_type = VarList[$1.NO].Iv;
		$$.NO = T;
		$$.OFFSET = $1.tmp_place;



	
		}
	;
Const:		IntNo
		{
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//设置常量为INT型，并检查该常量是否在表中，如果不在表中
		//则需要添加到表中
		$$.type = INT;
		$$.place = Entry($1); 
		//同时在符号表中设置类型
		VarList[VarCount].type = INT;
		//初始化右值
		struct node *node1;
		complete_init_node(&node1, $1);
		//关系
		add_son_node($$.nd, node1);
		}
	|	RealNo
		{
		//printf("")
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		//设置常量为REAL型，并检查该常量是否在表中，如果不在表中
		//则需要添加到表中
		$$.type = REAL;
		$$.place = Entry($1); 
		//printf("%s", $1);
		//同时在符号表中设置类型
		VarList[VarCount].type = REAL;
		//初始化右值
		struct node *node1;
		complete_init_node(&node1, $1);
		//关系
		add_son_node($$.nd, node1);
		}
	;
RelationOp:	'<'
		{
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;

		memcpy($$._Rop, "j<", sizeof("j<"));
		//初始化右值
		struct node *node1;
		complete_init_node(&node1, "<");
		//关系
		add_son_node($$.nd, node1);
		}
	|	'>'
		{
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;

		memcpy($$._Rop, "j>", sizeof("j>"));
		//初始化右值
		struct node *node1;
		complete_init_node(&node1, ">");
		//关系
		add_son_node($$.nd, node1);

		}	
	|	'='
		{
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;

		memcpy($$._Rop, "j=", sizeof("j="));
		//初始化右值
		struct node *node1;
		complete_init_node(&node1, "=");
		//关系
		add_son_node($$.nd, node1);
		}
	|	GE
		{
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;

		memcpy($$._Rop, "j>=", sizeof("j>="));
		//初始化右值
		struct node *node1;
		complete_init_node(&node1, ">=");
		//关系
		add_son_node($$.nd, node1);
		}
	|	NE
		{
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;

		memcpy($$._Rop, "j<>", sizeof("j<>"));
		//初始化右值
		struct node *node1;
		complete_init_node(&node1, "<>");
		//关系
		add_son_node($$.nd, node1);
		}
	|	LE
		{
		//给左边非终结符赋值
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;

		memcpy($$._Rop, "j<=", sizeof("j<="));
		//初始化右值
		struct node *node1;
		complete_init_node(&node1, "<=");
		//关系
		add_son_node($$.nd, node1);
		}
	;

DO: Do
{
	//给左边非终结符赋值
	struct node* cur;
	complete_init_node(&cur, "NULL");
	$$.nd = cur;
	//下一个四元式是循环起始位置
	$$.loop = NXQ;
	
	/*处理break continne */
	stacknode.loop = 0;
	stacknode.type = DO;
	stacknode.break_ch = 0;
	stacknode.continue_ch = 0;
	push(&stacknode);  //lushangqi   

	//初始化右值
	struct node *node1;
	complete_init_node(&node1, "Do");
	//关系
	add_son_node($$.nd, node1);

}
;
DSW: DO Statement While
{
	//给左边非终结符赋值
	struct node* cur;
	complete_init_node(&cur, "NULL");
	$$.nd = cur;
	
	//将循环起始位置上传
	$$.loop = $1.loop;
	//同时由与bool表达式语句出现，因此回填出口
	BackPatch($2.CH, NXQ);

	/*处理break， continue*/
	//此时真正应该判断的语句出现
	top(&stack_item);  
	if (stack_item == NULL) {
			error_number = INNER_ERROR;
			yyerror("stack_item is NULL");
	}
	BackPatch(stack_item->continue_ch, NXQ);


	//初始化右值
	struct node*node1;
	complete_init_node(&node1, "While");

	set_node_val_str($1.nd, "DO");
	set_node_val_str($2.nd, "Statement");
		
	//关系
	add_son_node($$.nd, $1.nd);
	add_brother_node($1.nd, $2.nd);
	add_brother_node($2.nd, node1);

}
;



RE: Repeat
{
	//给左边非终结符赋值
	struct node* cur;
	complete_init_node(&cur, "NULL");
	$$.nd = cur;
	//下一个四元式是循环起始位置
	$$.loop = NXQ;

	/*处理break continne */
	stacknode.loop = 0;
	stacknode.type = REPEAT;
	stacknode.break_ch = 0;
	stacknode.continue_ch = 0;
	push(&stacknode);  //lushangqi    

	//初始化右值
	struct node *node1;
	complete_init_node(&node1, "Repeat");
	//关系
	add_son_node($$.nd, node1);
}
;
RSU: RE Statement Until
{
	//给左边非终结符赋值
	struct node* cur;
	complete_init_node(&cur, "NULL");
	$$.nd = cur;
	
	//将循环起始位置上传
	$$.loop = $1.loop;
	//同时由与bool表达式语句出现，因此回填出口
	BackPatch($2.CH, NXQ);


	/*处理break， continue*/
	//此时真正应该判断的语句出现
	top(&stack_item);  
	if (stack_item == NULL) {
			error_number = INNER_ERROR;
			yyerror("stack_item is NULL");
	}
	BackPatch(stack_item->continue_ch, NXQ);

	//初始化右值
	struct node*node1;
	complete_init_node(&node1, "Until");

	set_node_val_str($1.nd, "Repeat");
	set_node_val_str($2.nd, "Statement");
		
	//关系
	add_son_node($$.nd, $1.nd);
	add_brother_node($1.nd, $2.nd);
	add_brother_node($2.nd, node1);
}
;

%%

int yyerror(char *errstr)
{ 
	printf("\n\n Error: ");
	printf("Line: %d Reason: ", line_number);
	switch(error_number) {
		case REDEFINE_ARRAY :{
			printf("Array %s is redefined!\n", errstr);
			break;
		}
		case REDEFINE_SIM_VAR :{
			printf("Simple Var %s is redefined!\n", errstr);
			break;
		}
		case UNDEFINE_VAR :{
		    printf("Var %s is not defined!\n", errstr);
			break;
		}
		case ILLEGALIDEN :{
		    printf("%s is illegal Identifier!\n", errstr);
			break;
		}
		case UNRE_COG_SYMBOL :{
		    printf("%s can not be recognized!\n", errstr);
			break;
		}
		case BOOL_OP_ERROR :{
		    printf("Bool VAR cannot be %s\n", errstr);
			break;
		}
		case LABEL_REDEF :{
		    printf("%s\n", errstr);
			break;
		}
		case INNER_ERROR :{
		    printf("%s\n", errstr);
			break;
		}
		default :{
			printf("%s\n", errstr);
			break;
		}	
	}
	exit(-1);
	return 0;
}
