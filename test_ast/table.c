#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "table.h"
#include "pascal_yacc.h"
#define INT 0
#define REAL 1
#define ARRAY 2

table_variable VarList[TABLE_MAX_VAR_NUM];//
array_variable TypeList[TABLE_MAX_VAR_NUM];



//符号表
int VarCount = 0;
int TypeCount = 0;


int tmp_cnt = 0;
static char KeyWord[][TABLE_MAX_IDENT_NAME_LEN] =
{
	"PROGRAM",
	"BEGIN",
	"END",
	"VAR",
	"INTEGER",
	"REAL",
	"WHILE",
	"DO",
	"IF",
	"THEN",
	"ELSE",
	"OR",
	"AND",
	"NOT"
};

int id_or_keyword(char *str)
{
	unsigned int i, j;
	char *p, buf[TABLE_MAX_IDENT_NAME_LEN];

	for (i = 0; i<sizeof(KeyWord) / sizeof(KeyWord[0]); i++) {
		p = str;
		for (j = 0; j<strlen(str); j++)
			buf[j] = (char)toupper(p[j]);
		buf[j] = '\0';

		if (!strcmp(KeyWord[i], buf)) {
			break;
		}
	}

	if (i<sizeof(KeyWord) / sizeof(KeyWord[0])) return i + 400;

	return Iden;
}

void OutputVarList(void)
{
	int i = 0;

	printf(" No.\t name \t\t   type\n");

	if (i >= VarCount) {
		printf("Symbol Table is NULL!\n");
		return;
	}

	for (i = 1; i<= VarCount; i++) {
		printf("%4d\t%6s\t\t", i, VarList[i].name);
		//pritf("%d")
		if (VarList[i].type == REAL) {
			printf(" REAL  \n");
		}
		else if (VarList[i].type == INT){
			printf(" INTEGER\n");
		}
		else {
			if (VarList[i].Iv == INT)
				printf("INTEGER ARRAY\n");

			else printf("REAL ARRAY\n");
		}
	}

	return;
}

void OutputTypeList(void)
{
	int i = 0;
	for (i = 1; i <= TypeCount; i++)
	{
		printf("N: %d.\t C: %d\t a: %d\n", TypeList[i].n, TypeList[i].C, TypeList[i].a);
		int j;
		for (j = 1; j <= TypeList[i].n; j++) {
			printf("L: %d.\t U : %d\t D: %d\n", TypeList[i].L[j], TypeList[i].U[j], TypeList[i].D[j]);
		}
	}
}

int LookUp(char *Name)
{
	for (int i = 1; i <= VarCount; i++) {
		if (strcmp(VarList[i].name, Name) == 0) {
			return i;
		}
	}
	//printf("No Variable %s!\n", Name);
	return 0;
}

int Enter(char *Name)
{
	//这里先++是让符号表第0个位置不存放符号
	VarCount++;
	if (VarCount > TABLE_MAX_VAR_NUM) {
		printf("There is no enough space!\n");
	}
	strncpy(VarList[VarCount].name, Name, sizeof(Name));
	VarList[VarCount].addr = 0;
	
	return VarCount;
}

int Entry(char *Name)
{
	int i = LookUp(Name);
	if (i> 0) return i;
	else return Enter(Name);
}





int NewTemp()
{
	char tmp_name[5]; //整个字符串
	//保存格式为T0， T1...
	sprintf(tmp_name, "T%d", tmp_cnt);
	tmp_cnt++;
	return Entry(tmp_name);
}

int Merge_var(int p1, int p2)
{
	VarList[p2].addr = p1;
	return p2;
}


void VarBackPatch(int p, int type)
{
	int q = p;
	//printf("%d %d %d", q, VarList[q].addr, t);
	while (q) {
		//注意此处不能颠倒
		int tmp = q;
		q = VarList[q].addr;
		VarList[tmp].type= type;
	}

}


void VarBackArrayPatch(int p, int type, int Iv, int array_no)
{
	int q = p;
	//printf("%d %d %d", q, VarList[q].addr, t);
	while (q) {
		//注意此处不能颠倒
		int tmp = q;
		q = VarList[q].addr;
		VarList[tmp].type= type;
		VarList[tmp].Iv = Iv;
		VarList[tmp].array_no = array_no;
	}

}

int New_Array_Type()
{
	TypeCount ++ ;
	TypeList[TypeCount].n = 0;
	TypeList[TypeCount].C = 0;
	//!!!!!!!!!!!!!!!!!!!!!!!!!!1 如何给一个数组分配空间
	TypeList[TypeCount].a = 0;
	return TypeCount;
}

void Update_D(int no, int dim, int L, int R)
{


	TypeList[no].n = dim;
	TypeList[no].L[dim] = L;
	TypeList[no].U[dim] = R;
	TypeList[no].D[dim] = R-L+1;
}

void Update_C(int no, int dim, int L, int R)
{
	
	if (dim == 2) TypeList[no].C = 1;

	TypeList[no].C = TypeList[no].C * ((R-L+1) + L);
}


//从符号表第NO项的addr域取得C
int Access_C(int no)
{
	no = VarList[no].array_no;
	if (no == 0) 
		printf("no eixst array!\n");
	return TypeList[no].C;

}
//取得a
int Access_a(int no)
{
	no = VarList[no].array_no;
	if (no == 0) 
		printf("no eixst array!\n");
	return TypeList[no].a;
}
//取得d
int Access_d(int no, int k)
{
	no = VarList[no].array_no;
	if (no == 0) 
		printf("no eixst array!\n");
	return TypeList[no].D[k];
}