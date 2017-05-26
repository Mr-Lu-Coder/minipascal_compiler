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

	// 词法分析的输入文件，必须由外部设置
	yyset_in(fp);
	// 抽象语法树AST初始化
	init_ast();

	// 进行词法分析、语法分析以及语法分析，同时产生分析树或者抽象语法树等
	yyparse();


	// 输出四元式
	puts("输出四元式");
	OutputQuaterList();
	// 输出符号表(变量名）
	puts("输出符号表");
	OutputVarList();

	//输出抽象语法树
	puts("画出语法树");
	draw_ast(&ast_root, 0);
	return 0;
}
#endif
