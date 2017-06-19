#ifndef __QUEUE_H__
#define __QUEUE_H__


#define TRUE 1
#define FALSE 0
typedef struct QElemType_
{
	int arg2;
	int result;
}QElemType;


typedef struct QNode
{
	QElemType data;
	struct QNode *next;
}QNode, *QueuePtr;
typedef struct
{
	QueuePtr front, rear; /* ��ͷ����βָ�� */
}LinkQueue;
/* ����һ���ն���Q */
void InitQueue(LinkQueue *Q);
/* ��Q��Ϊ�ն��� */
void myDestroyQueue(LinkQueue *Q);
/* ��Q��Ϊ�ն��� */
void ClearQueue(LinkQueue *Q);
/* ��QΪ�ն��У��򷵻�TRUE�����򷵻�FALSE */
int QueueEmpty(LinkQueue Q);
/* ����еĳ��� */
int QueueLength(LinkQueue Q);
/* ����Ԫ��eΪQ���µĶ�βԪ�� */
int EnQueue(LinkQueue *Q, QElemType e);
/* �����в��գ�ɾ��Q�Ķ�ͷԪ�أ���e������ֵ��������OK�����򷵻�ERROR */
int DeQueue(LinkQueue *Q, QElemType *e);

#endif