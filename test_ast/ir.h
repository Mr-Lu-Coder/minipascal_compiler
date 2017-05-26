#ifndef __IR_H__
#define __IR_H__

#define MAX_IR_EXP_NUM 100

enum ir_op {
	IR_OP_UNKNOWN,
	IR_OP_ADD,
	IR_OP_SUB,
	IR_OP_MINUS,
	IR_OP_MUL,
	IR_OP_DIV,
};

/**
 * ��Ԫʽ��Ϣ
 */
typedef struct ir_quarter_expression_ {
#if 0
	enum ir_op op;	// ������
#else
	char op[6];
#endif
	int arg1;		// Դ������1
	int arg2;		// Դ������2
	int result;		// Ŀ�Ĳ���������
} ir_quarter_expression;

extern int NXQ;

void OutputQuaterList(void);
int GEN(char * op, int arg1, int arg2, int result);
int Merge(int p1, int p2);
void BackPatch(int p, int t);




#endif