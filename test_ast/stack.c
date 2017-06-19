/*
**
** 静态数组实现堆栈程序 a_stack.c ，数组长度由#define确定
*/


#include<stdio.h>  
#include<assert.h>
#include"stack.h"  
#define STACK_SIZE 100 /* 堆栈最大容纳元素数量 */  

/*
** 存储堆栈中的数组和一个指向堆栈顶部元素的指针
*/
static LoopStack_ stack[STACK_SIZE];
static int top_element = -1;

/* push */
void push(LoopStack_ *value)
{
	assert(!is_full()); /* 压入堆栈之前先判断是否堆栈已满*/
	top_element += 1;
	stack[top_element].type = value->type;
	stack[top_element].loop = value->loop;
	stack[top_element].break_ch = value->break_ch;
	stack[top_element].continue_ch = value->continue_ch;
}

/* pop */
int pop()
{
	if (!is_empty()) /* 弹出堆栈之前先判断是否堆栈已空 */
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

