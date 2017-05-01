#include<iostream>
using namespace std;
#ifndef TT_LINK_QUEUE_H
#define TT_LINK_QUEUE_H
#define TT_OK 1
#define TT_ERROR 0

namespace tt
{
	class LinkQueue  //队列的链表结构
	{
	public:
		typedef int ElemType;
	public:
		struct QNode  //队列的结点结构
		{
			ElemType m_data; //链队列的数据域
			QNode *m_next; //链队列的指针域
		};
	public:
		LinkQueue();
		~LinkQueue();
		ElemType isEmpty()const;   //判断队列是否为空
		ElemType clear();      //清空队列
		ElemType insert(ElemType elem);  //插入元素致链队列尾部
		ElemType remove(ElemType &elemOut);  //删除链队列的对头元素
		ElemType destroy();      //销毁队列
		ElemType getHead(ElemType &eleOut);  //获取对头元素

		void getlength()const;  //链队列的当前个数
		void traverseElem();   //遍历显示链队列中的所有元素
	private:
		QNode *m_front;  //链队列的对头指针，队头不保存元素，只起头结点作用,当front==rear时，队列为空
		QNode *m_rear;  //链队列的队尾指针
		ElemType m_queLength;  //链队列的当前长度
	};
	inline LinkQueue::ElemType LinkQueue::isEmpty()const
	{
		return (m_front == m_rear);
	}
	inline void LinkQueue::getlength()const
	{
		cout<< "链队列的当前的元素个数为：" << m_queLength << "\n" << endl;
	}
}
#endif //TT_LINK_QUEUE_H