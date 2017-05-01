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
		CirQueue(ElemType INI_SIZE);  //初始化队列
		~CirQueue();
		Status isEmpty()const;  //判断队列是否为空。
		Status isFull()const;  //确定队列是否满了

		ElemType clear(); //将队列清空
		ElemType getHead(ElemType &elemOut); //若队列存在且非空，用elem返回队列的队头元素
		ElemType insert(ElemType elem); //若队列存在，插入新元素elem到队列中并成为队尾元素。
		ElemType remove(ElemType &elemOut);// 删除队列中的队头元素，并用elem返回。

		ElemType destroy(); //若队列存在，则销毁它
		void getLength()const; //返回队列中当前元素的个数。
		void show();  //显示队列中的所有元素
	private:
		ElemType *m_data;  //数据域
		ElemType m_front;  //指向队头元素
		ElemType m_rear;  //指向队尾元素的下一个位置
		ElemType m_queueSize;   //队列的最大容量
	};
	inline CirQueue::Status CirQueue::isEmpty()const  //判断队列是否为空
	{
		return (m_front == m_rear);
	}
	inline void CirQueue::getLength()const //返回队列中当前元素的个数
	{
		cout<< "当前队列中的元素个数为：" << (m_rear - m_front + m_queueSize) % m_queueSize << endl;
	}
	inline CirQueue::ElemType CirQueue::clear() //将队列清空
	{
		m_front = m_rear = 0;
		return TT_OK;
	}
	inline CirQueue::Status CirQueue::isFull()const  //确定队列是否满了
	{
		return (m_rear + 1) % m_queueSize == m_front;
	}
}
#endif  //TT_CIR_QUEUE_H