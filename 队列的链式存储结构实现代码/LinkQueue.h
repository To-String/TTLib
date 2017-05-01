#include<iostream>
using namespace std;
#ifndef TT_LINK_QUEUE_H
#define TT_LINK_QUEUE_H
#define TT_OK 1
#define TT_ERROR 0

namespace tt
{
	class LinkQueue  //���е�����ṹ
	{
	public:
		typedef int ElemType;
	public:
		struct QNode  //���еĽ��ṹ
		{
			ElemType m_data; //�����е�������
			QNode *m_next; //�����е�ָ����
		};
	public:
		LinkQueue();
		~LinkQueue();
		ElemType isEmpty()const;   //�ж϶����Ƿ�Ϊ��
		ElemType clear();      //��ն���
		ElemType insert(ElemType elem);  //����Ԫ����������β��
		ElemType remove(ElemType &elemOut);  //ɾ�������еĶ�ͷԪ��
		ElemType destroy();      //���ٶ���
		ElemType getHead(ElemType &eleOut);  //��ȡ��ͷԪ��

		void getlength()const;  //�����еĵ�ǰ����
		void traverseElem();   //������ʾ�������е�����Ԫ��
	private:
		QNode *m_front;  //�����еĶ�ͷָ�룬��ͷ������Ԫ�أ�ֻ��ͷ�������,��front==rearʱ������Ϊ��
		QNode *m_rear;  //�����еĶ�βָ��
		ElemType m_queLength;  //�����еĵ�ǰ����
	};
	inline LinkQueue::ElemType LinkQueue::isEmpty()const
	{
		return (m_front == m_rear);
	}
	inline void LinkQueue::getlength()const
	{
		cout<< "�����еĵ�ǰ��Ԫ�ظ���Ϊ��" << m_queLength << "\n" << endl;
	}
}
#endif //TT_LINK_QUEUE_H