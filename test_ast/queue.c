#include<stdio.h>
#include<stdlib.h>
#include"queue.h"


void InitQueue(LinkQueue *Q)
{ /* 构造一个空队列Q */
	Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q->front)
	Q->front->next = NULL;
}
void myDestroyQueue(LinkQueue *Q)
{ /* 销毁队列Q(无论空否均可) */
	while (Q->front)
	{
		Q->rear = Q->front->next;
		free(Q->front);
		Q->front = Q->rear;
	}
}
void ClearQueue(LinkQueue *Q)
{ /* 将Q清为空队列 */
	QueuePtr p, q;
	Q->rear = Q->front;
	p = Q->front->next;
	Q->front->next = NULL;
	while (p)
	{
		q = p;
		p = p->next;
		free(q);
	}
}
int QueueEmpty(LinkQueue Q)
{ /* 若Q为空队列，则返回TRUE，否则返回FALSE */
	if (Q.front->next == NULL)
		return TRUE;
	else
		return FALSE;
}
int QueueLength(LinkQueue Q)
{ /* 求队列的长度 */
	int i = 0;
	QueuePtr p;
	p = Q.front;
	while (Q.rear != p)
	{
		i++;
		p = p->next;
	}
	return i;
}

int EnQueue(LinkQueue *Q, QElemType e)
{ /* 插入元素e为Q的新的队尾元素 */
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	if (!p) /* 存储分配失败 */
		return FALSE;
	p->data = e;
	p->next = NULL;
	Q->rear->next = p;
	Q->rear = p;
	return TRUE;
}
int DeQueue(LinkQueue *Q, QElemType *e)
{ /* 若队列不空，删除Q的队头元素，用e返回其值，并返回OK，否则返回ERROR */
	QueuePtr p;
	if (Q->front == Q->rear)
		return FALSE;
	p = Q->front; /* 指向头结点 */
	*e = p->data;
	Q->front = p->next; /* 摘下头节点 */
	if (Q->rear == p)
		Q->rear = Q->front;
	free(p);
	return TRUE;
}
