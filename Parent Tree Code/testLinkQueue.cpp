#include"LinkQueue.h"

void InitQueue(LinkQueue *Q)
{
	(*Q).m_front = (*Q).m_rear = (QueuePtr)malloc(sizeof(QNode));
	if (!(*Q).m_front)
	{
		cout << "´íÎó£¬ÄÚ´æ·ÖÅäÊ§°Ü£¡" << endl;
	}
	(*Q).m_front->m_next = nullptr;
}

int QueueEmpty(LinkQueue Q)
{ 
  return (Q.m_front == Q.m_rear);	
}

int insert(LinkQueue *Q, QElemType elem)
{ 
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	if (!p) /* ´æ´¢·ÖÅäÊ§°Ü */
	{
		return TT_ERROR;
	}
	p->m_data = elem;
	p->m_next = nullptr;
	(*Q).m_rear->m_next = p;
	(*Q).m_rear = p;
	return TT_OK;
}

int remove(LinkQueue *Q, QElemType &elemOut)
{ 
	QueuePtr p;
	if ((*Q).m_front == (*Q).m_rear)
	{
		return TT_ERROR;
	}
	p = (*Q).m_front->m_next;
	elemOut = p->m_data;
	(*Q).m_front->m_next = p->m_next;
	if ((*Q).m_rear == p)
	{
		(*Q).m_rear = (*Q).m_front;
	}
	free(p);
	return TT_OK;
}

