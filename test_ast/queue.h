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
	QueuePtr front, rear; /* 队头、队尾指针 */
}LinkQueue;
/* 构造一个空队列Q */
void InitQueue(LinkQueue *Q);
/* 将Q清为空队列 */
void myDestroyQueue(LinkQueue *Q);
/* 将Q清为空队列 */
void ClearQueue(LinkQueue *Q);
/* 若Q为空队列，则返回TRUE，否则返回FALSE */
int QueueEmpty(LinkQueue Q);
/* 求队列的长度 */
int QueueLength(LinkQueue Q);
/* 插入元素e为Q的新的队尾元素 */
int EnQueue(LinkQueue *Q, QElemType e);
/* 若队列不空，删除Q的队头元素，用e返回其值，并返回OK，否则返回ERROR */
int DeQueue(LinkQueue *Q, QElemType *e);

#endif