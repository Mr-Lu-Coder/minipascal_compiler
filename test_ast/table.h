#ifndef __TABLE_H__
#define __TABLE_H__

#define TABLE_MAX_IDENT_NAME_LEN 20
#define TABLE_MAX_VAR_NUM 200
#define TABLE_MAX_ARRAY_NUM 200

typedef struct table_variable__ {
	char name[TABLE_MAX_IDENT_NAME_LEN]; // 变量名
	int type; // 类型
	int Iv;   //如果是数组，分int real
	int addr; // 地址
	int array_no; //如果是array类型的，那么array_no为array_variable的下标
} table_variable;
//数组类型表
typedef struct array_variable__ {
	int n;
	int C;
	int a;
	int L[TABLE_MAX_ARRAY_NUM];
	int U[TABLE_MAX_ARRAY_NUM];
	int D[TABLE_MAX_ARRAY_NUM];
}array_variable;
//label表
typedef struct label_variable__ {
	int DEF;
	int ADDR;
	char name[TABLE_MAX_IDENT_NAME_LEN];
}label_variable;

extern table_variable VarList[TABLE_MAX_VAR_NUM];

extern array_variable TypeList[TABLE_MAX_VAR_NUM];

extern label_variable LabelList[TABLE_MAX_VAR_NUM];

extern int VarFlag;

//输出符号表
void OutputVarList(void);
//生成类型表
void OutputTypeList();
int id_or_keyword(char *);

//查找变量名在表中的位置
int LookUp(char *Name);
//直接写入符号表
int Enter(char *Name);
//先看有没有，没有的话再写入符号表
int Entry(char *Name);

//新建一个临时变量
int NewTemp();

extern VarCount;
//合并变量声明
int Merge_var(int p1, int p2);
//回填变量
void VarBackPatch(int p, int t);
//回填数组类型的变量
void VarBackArrayPatch(int p, int type, int Iv, int array_no);
//新建一个数组类型
int New_Array_Type();
//更新D
void Update_D(int no, int dim, int L, int R);
//更新C
void Update_C(int no, int dim, int L, int R);

//从符号表第NO项的addr域取得C
int Access_C(int no);
//取得a
int Access_a(int no);
//取得d
int Access_d(int no, int k);

//获取一个字符串的L 和U
void Get_L_and_U(char *str, int *L, int *U);

//放到表中
int EnterLabel(char *Name);
//查找表中有没有
int LookUpLabel(char *Name);

//回填Label拉链
void BackLabelPatch(int p, int t);

//获取L开头的标签
int GetLLabel();
//获取Next开头的label
int GetNextLabel();
//获取check开头的label
int GetCheckLabel();

#endif

