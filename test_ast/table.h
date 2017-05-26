#ifndef __TABLE_H__
#define __TABLE_H__

#define TABLE_MAX_IDENT_NAME_LEN 20
#define TABLE_MAX_VAR_NUM 200


typedef struct table_variable__ {
	char name[TABLE_MAX_IDENT_NAME_LEN]; // 变量名
	int type; // 类型
	int addr; // 地址
} table_variable;

extern table_variable VarList[TABLE_MAX_VAR_NUM];


//输出符号表
void OutputVarList(void);

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
int Merge_var(int p1, int p2);
void VarBackPatch(int p, int t);

#endif

