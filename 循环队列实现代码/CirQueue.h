#include<iostream>
#include<cassert>
using namespace std;
#ifndef TT_CIR_QUEUE_H
#define TT_CIR_QUEUE_H
#define TT_ERROR 0
#define TT_OK 1

namespace tt
{
	class CirQueue
	{
	public:
		typedef int ElemType;
		typedef bool Status;
	public:
		CirQueue(ElemType INI_SIZE);  //��ʼ������
		~CirQueue();
		Status isEmpty()const;  //�ж϶����Ƿ�Ϊ�ա�
		Status isFull()const;  //ȷ�������Ƿ�����

		ElemType clear(); //���������
		ElemType getHead(ElemType &elemOut); //�����д����ҷǿգ���elem���ض��еĶ�ͷԪ��
		ElemType insert(ElemType elem); //�����д��ڣ�������Ԫ��elem�������в���Ϊ��βԪ�ء�
		ElemType remove(ElemType &elemOut);// ɾ�������еĶ�ͷԪ�أ�����elem���ء�

		ElemType destroy(); //�����д��ڣ���������
		void getLength()const; //���ض����е�ǰԪ�صĸ�����
		void show();  //��ʾ�����е�����Ԫ��
	private:
		ElemType *m_data;  //������
		ElemType m_front;  //ָ���ͷԪ��
		ElemType m_rear;  //ָ���βԪ�ص���һ��λ��
		ElemType m_queueSize;   //���е��������
	};
	inline CirQueue::Status CirQueue::isEmpty()const  //�ж϶����Ƿ�Ϊ��
	{
		return (m_front == m_rear);
	}
	inline void CirQueue::getLength()const //���ض����е�ǰԪ�صĸ���
	{
		cout<< "��ǰ�����е�Ԫ�ظ���Ϊ��" << (m_rear - m_front + m_queueSize) % m_queueSize << endl;
	}
	inline CirQueue::ElemType CirQueue::clear() //���������
	{
		m_front = m_rear = 0;
		return TT_OK;
	}
	inline CirQueue::Status CirQueue::isFull()const  //ȷ�������Ƿ�����
	{
		return (m_rear + 1) % m_queueSize == m_front;
	}
}
#endif  //TT_CIR_QUEUE_H