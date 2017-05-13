#include<iostream>
#include<cassert>
using namespace std;
#ifndef TT_STACK_H
#define TT_STACK_H
#define STACK_INCREMENT 5   //�洢�ռ��������

#define TT_OK 1
#define TT_ERROR 0


namespace tt 
{

	class Stack
	{
	public:
		typedef  int  ElemType;
		typedef  bool Status;
	public:
		/// ע��: ͨ������ֻ��const�����ͺ������ȫ��д;�ֲ����������β�������һ����ĸСд��ÿ�����ʵĵ�һ����ĸ��д����Сд��(fooBarCoo)
		Stack(ElemType initSize); //  ��ʼ������������һ����ջ
		~Stack();
		Status isFull()const; //ȷ��ջ�Ƿ�����
		Status destroy();  //��ջ���ڣ���������
		Status clear();  //��ջ���
		Status isEmpty()const;  //��ջΪ�գ�����true ����false
								/// ע��: atһ�����ڲ���Ϊ�����ĺ�����,������������û�������Ͳ���at��Ϊ��׺��
								/// ��Ϊ: at��Ӣ���к���ӵ�ַ,������ͨ��Ϊһ��Ԫ�صĵ�ַ������������Ϊ�����ĺ���
								/// �ͻ����at��Ϊ��׺�����������������at,�е�Ī������;
		ElemType getTop(ElemType &elemOut);  //��ջ�����ҷǿգ���e����ջ��ջ��Ԫ��
		Status push(ElemType e); //��ջ���ڣ�������Ԫ��e ��Ϊջ��Ԫ��
		Status pop(ElemType &elemOut);  //ɾ��ջ��ջ��Ԫ�أ�����e������ֵ

		Status getLength()const;  //����ջ�е�Ԫ�ظ���
								  // ע��: ͬ�� showStackǰ����Բ���Ҫstackֱ��Ϊshow�Ϳ�����
		void show();  //��ʾջ������Ԫ��
	private:
		ElemType *m_top;  //ָ��ջ��Ԫ�ص�ָ��
		ElemType *m_base;   //ָ��ջ��Ԫ�ص�ָ��
		ElemType m_stackSize;  //ջ��ǰ��Ԫ������
	};
	inline Stack::Status Stack::clear()  //�������Ԫ��
	{
		m_top = m_base;
		return TT_OK;  //��ջ��ָ���ջ��ָ���غϣ�˵��ջ��û��Ԫ��
	}

	inline Stack::Status Stack::getLength()const //����ջ�ĵ�ǰ��Ԫ������
	{
		cout << "ջ�е�Ԫ�ظ���Ϊ��" << (m_top - m_base) << "\n" << endl;
		return TT_OK;
	}
	inline Stack::Status Stack::isEmpty()const //�ж�ջ�Ƿ�Ϊ��
	{
		return  (m_base == m_top);
	}
}//ns tt

#endif //TT_STACK_H

