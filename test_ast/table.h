#ifndef __TABLE_H__
#define __TABLE_H__

#define TABLE_MAX_IDENT_NAME_LEN 20
#define TABLE_MAX_VAR_NUM 200


typedef struct table_variable__ {
	char name[TABLE_MAX_IDENT_NAME_LEN]; // ������
	int type; // ����
	int addr; // ��ַ
} table_variable;

extern table_variable VarList[TABLE_MAX_VAR_NUM];


//������ű�
void OutputVarList(void);

int id_or_keyword(char *);

//���ұ������ڱ��е�λ��
int LookUp(char *Name);
//ֱ��д����ű�
int Enter(char *Name);
//�ȿ���û�У�û�еĻ���д����ű�
int Entry(char *Name);

//�½�һ����ʱ����
int NewTemp();

extern VarCount;
int Merge_var(int p1, int p2);
void VarBackPatch(int p, int t);

#endif

