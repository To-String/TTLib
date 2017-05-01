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
		LinkStack();  //初始化一个栈
		~LinkStack();
		ElemType push(ElemType elem);  //若栈存在，插入新元素e 成为栈顶元素
		ElemType pop(ElemType &elemOut); //若栈存在，删除栈顶元素
		Status  isEmpty()const; //判断栈是否为空

		ElemType getTop(ElemType &elemOut);  //若栈存在且非空，用e返回栈的栈顶元素
		void getLength()const;  //返回栈中的元素个数
		void show();  //显示栈的所有元素

		Status clear();  //将栈清空
		Status destroy();  //若栈存在，则销毁它
	private:
		Node *m_heap;  //声明一个头结点,此链栈中没有栈顶指针
		ElemType m_stackLength;  //栈的当前的元素个数
	};
	inline LinkStack::Status LinkStack::isEmpty()const  //判断栈是否为空
	{
		return (m_stackLength == 0);
	}
	inline void LinkStack::getLength()const  //得到栈中现在的元素个数
	{
		cout << "栈中的元素个数为：" << m_stackLength <<endl;
	}
}
#endif  //TT_LINK_STACK_H