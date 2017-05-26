#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "table.h"
#include "pascal_yacc.h"

table_variable VarList[TABLE_MAX_VAR_NUM];//
//符号表
int VarCount = 0;



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
		if (VarList[i].type) {
			printf(" REAL  \n");
		}
		else {
			printf(" INTEGER\n");
		}
	}

	return;
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


void VarBackPatch(int p, int t)
{
	int q = p;
	while (q) {
		VarList[q].addr = t;
		q = VarList[q].addr;
	}

}




