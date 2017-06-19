#ifndef __STACK_H__
#define __STACK_H__
/*
** ��ջģ��Ľӿ� stack.h
*/
#include<stdlib.h>  

//#define STACK_TYPE int /* ��ջ���洢��ֵ���������� */  
typedef struct Stack{
	int loop;
	int type;
	int break_ch;
	int continue_ch;
}LoopStack_;
/*
** ����ԭ�ͣ�create_stack
** ������ջ������ָ����ջ���Ա�����ٸ�Ԫ�ء�
** ע�⣺�˺���ֻ�����ڶ�̬����������ʽ�Ķ�ջ��
*/
void create_stack(size_t size);

/*
** ����ԭ�ͣ�destroy_stack
** ����һ����ջ���ͷŶ�ջ�����õ��ڴ档
** ע�⣺�˺���ֻ�����ڶ�̬�����������ʽ�ṹ�Ķ�ջ��
*/
void destroy_stack(void);

/*
** ����ԭ�ͣ�push
** ��һ����ֵѹ���ջ�У������Ǳ�ѹ���ֵ��
*/
void push(LoopStack_ *value);

/*
** ����ԭ�ͣ�pop
** ������ջ��ջ����һ��ֵ����������
*/
int pop();

/*
** ����ԭ�ͣ�top
** ���ض�ջ����Ԫ�ص�ֵ�������ı��ջ�ṹ��
*/
int top(LoopStack_ **item);

/*
** ����ԭ�ͣ�is_empty
** �����ջΪ�գ�����TRUE,���򷵻�FALSE��
*/
int is_empty(void);

/*
** ����ԭ�ͣ�is_full
** �����ջΪ��������TRUE,���򷵻�FALSE��
*/
int is_full(void);


#endif