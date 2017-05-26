#include <stdio.h>
#include <string.h>
#include "pascal_lex.h"
#include "pascal_yacc.h"

#include "ast.h"
#include "table.h"
#include "ir.h"

#ifdef LEX_MAIN
int main(int argc, char** argv)
{
	int c;
	FILE *pout;
	FILE * fp = stdin;

	if (argc>1) {
		if ((fp = fopen(argv[1], "r")) == NULL) {
			printf("Can't open file %s\n", argv[1]);
			return -1;
		}
	}
	yyset_in(fp);

	pout = fopen("lex_output.dat", "w");
	while (c = yylex()) {
		static int i = 0;
		fprintf(pout, "(%4d,  %s)\t", c, yyget_text()); i++;
		if (i == i / 4 * 4) fprintf(pout, "\n");
	}
	fprintf(pout, "\n");
	fclose(pout);
	return 0;
}
#else
int main(int argc, char *argv[])
{
	FILE * fp = stdin;
	
	if (argc > 1) {
		if ((fp = fopen(argv[1], "r")) == NULL) {
			printf("Can't open file %s\n", argv[1]);
			return -1;
		}
	}

	// �ʷ������������ļ����������ⲿ����
	yyset_in(fp);
	// �����﷨��AST��ʼ��
	init_ast();

	// ���дʷ��������﷨�����Լ��﷨������ͬʱ�������������߳����﷨����
	yyparse();


	// �����Ԫʽ
	puts("�����Ԫʽ");
	OutputQuaterList();
	// ������ű�(��������
	puts("������ű�");
	OutputVarList();

	//��������﷨��
	puts("�����﷨��");
	draw_ast(&ast_root, 0);
	return 0;
}
#endif
