#include<iostream>
#ifndef TT_LINK_STACK_H
#define TT_LINK_STACK_H
#define TT_ERROR 0
#define TT_OK 1
using namespace std;
namespace tt
{
	class LinkStack
	{
	public:
		typedef int ElemType;
		typedef  bool Status;
	public:
		struct Node
		{
			ElemType m_data;
			Node *m_next;
		};
		LinkStack();  //��ʼ��һ��ջ
		~LinkStack();
		ElemType push(ElemType elem);  //��ջ���ڣ�������Ԫ��e ��Ϊջ��Ԫ��
		ElemType pop(ElemType &elemOut); //��ջ���ڣ�ɾ��ջ��Ԫ��
		Status  isEmpty()const; //�ж�ջ�Ƿ�Ϊ��

		ElemType getTop(ElemType &elemOut);  //��ջ�����ҷǿգ���e����ջ��ջ��Ԫ��
		void getLength()const;  //����ջ�е�Ԫ�ظ���
		void show();  //��ʾջ������Ԫ��

		Status clear();  //��ջ���
		Status destroy();  //��ջ���ڣ���������
	private:
		Node *m_heap;  //����һ��ͷ���,����ջ��û��ջ��ָ��
		ElemType m_stackLength;  //ջ�ĵ�ǰ��Ԫ�ظ���
	};
	inline LinkStack::Status LinkStack::isEmpty()const  //�ж�ջ�Ƿ�Ϊ��
	{
		return (m_stackLength == 0);
	}
	inline void LinkStack::getLength()const  //�õ�ջ�����ڵ�Ԫ�ظ���
	{
		cout << "ջ�е�Ԫ�ظ���Ϊ��" << m_stackLength <<endl;
	}
}
#endif  //TT_LINK_STACK_H