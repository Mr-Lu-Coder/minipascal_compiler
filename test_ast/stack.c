/*
**
** ��̬����ʵ�ֶ�ջ���� a_stack.c �����鳤����#defineȷ��
*/


#include<stdio.h>  
#include<assert.h>
#include"stack.h"  
#define STACK_SIZE 100 /* ��ջ�������Ԫ������ */  

/*
** �洢��ջ�е������һ��ָ���ջ����Ԫ�ص�ָ��
*/
static LoopStack_ stack[STACK_SIZE];
static int top_element = -1;

/* push */
void push(LoopStack_ *value)
{
	assert(!is_full()); /* ѹ���ջ֮ǰ���ж��Ƿ��ջ����*/
	top_element += 1;
	stack[top_element].type = value->type;
	stack[top_element].loop = value->loop;
	stack[top_element].break_ch = value->break_ch;
	stack[top_element].continue_ch = value->continue_ch;
}

/* pop */
int pop()
{
	if (!is_empty()) /* ������ջ֮ǰ���ж��Ƿ��ջ�ѿ� */
	{
		top_element -= 1;
		return 1;
	}
	return 0;
	
}

/* top */
int top(LoopStack_ **item)
{
	if (!is_empty())
	{
		//printf("%d", top_element);
		*item = &stack[top_element];
		return 1;
	}
	return 0;
	
}

/* is_empty */
int is_empty(void)
{
	return top_element == -1;
}

/* is_full */
int is_full(void)
{
	return top_element == STACK_SIZE - 1;
}

