#ifndef __TABLE_H__
#define __TABLE_H__

#define TABLE_MAX_IDENT_NAME_LEN 20
#define TABLE_MAX_VAR_NUM 200
#define TABLE_MAX_ARRAY_NUM 200

typedef struct table_variable__ {
	char name[TABLE_MAX_IDENT_NAME_LEN]; // ������
	int type; // ����
	int Iv;   //��������飬��int real
	int addr; // ��ַ
	int array_no; //�����array���͵ģ���ôarray_noΪarray_variable���±�
} table_variable;
//�������ͱ�
typedef struct array_variable__ {
	int n;
	int C;
	int a;
	int L[TABLE_MAX_ARRAY_NUM];
	int U[TABLE_MAX_ARRAY_NUM];
	int D[TABLE_MAX_ARRAY_NUM];
}array_variable;
//label��
typedef struct label_variable__ {
	int DEF;
	int ADDR;
	char name[TABLE_MAX_IDENT_NAME_LEN];
}label_variable;

extern table_variable VarList[TABLE_MAX_VAR_NUM];

extern array_variable TypeList[TABLE_MAX_VAR_NUM];

extern label_variable LabelList[TABLE_MAX_VAR_NUM];

extern int VarFlag;

//������ű�
void OutputVarList(void);
//�������ͱ�
void OutputTypeList();
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
//�ϲ���������
int Merge_var(int p1, int p2);
//�������
void VarBackPatch(int p, int t);
//�����������͵ı���
void VarBackArrayPatch(int p, int type, int Iv, int array_no);
//�½�һ����������
int New_Array_Type();
//����D
void Update_D(int no, int dim, int L, int R);
//����C
void Update_C(int no, int dim, int L, int R);

//�ӷ��ű��NO���addr��ȡ��C
int Access_C(int no);
//ȡ��a
int Access_a(int no);
//ȡ��d
int Access_d(int no, int k);

//��ȡһ���ַ�����L ��U
void Get_L_and_U(char *str, int *L, int *U);

//�ŵ�����
int EnterLabel(char *Name);
//���ұ�����û��
int LookUpLabel(char *Name);

//����Label����
void BackLabelPatch(int p, int t);

//��ȡL��ͷ�ı�ǩ
int GetLLabel();
//��ȡNext��ͷ��label
int GetNextLabel();
//��ȡcheck��ͷ��label
int GetCheckLabel();

#endif

