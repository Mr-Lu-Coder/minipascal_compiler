#include<stdio.h>
#include<stdlib.h>
#include"queue.h"


void InitQueue(LinkQueue *Q)
{ /* ����һ���ն���Q */
	Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q->front)
	Q->front->next = NULL;
}
void myDestroyQueue(LinkQueue *Q)
{ /* ���ٶ���Q(���ۿշ����) */
	while (Q->front)
	{
		Q->rear = Q->front->next;
		free(Q->front);
		Q->front = Q->rear;
	}
}
void ClearQueue(LinkQueue *Q)
{ /* ��Q��Ϊ�ն��� */
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
{ /* ��QΪ�ն��У��򷵻�TRUE�����򷵻�FALSE */
	if (Q.front->next == NULL)
		return TRUE;
	else
		return FALSE;
}
int QueueLength(LinkQueue Q)
{ /* ����еĳ��� */
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
{ /* ����Ԫ��eΪQ���µĶ�βԪ�� */
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	if (!p) /* �洢����ʧ�� */
		return FALSE;
	p->data = e;
	p->next = NULL;
	Q->rear->next = p;
	Q->rear = p;
	return TRUE;
}
int DeQueue(LinkQueue *Q, QElemType *e)
{ /* �����в��գ�ɾ��Q�Ķ�ͷԪ�أ���e������ֵ��������OK�����򷵻�ERROR */
	QueuePtr p;
	if (Q->front == Q->rear)
		return FALSE;
	p = Q->front; /* ָ��ͷ��� */
	*e = p->data;
	Q->front = p->next; /* ժ��ͷ�ڵ� */
	if (Q->rear == p)
		Q->rear = Q->front;
	free(p);
	return TRUE;
}
