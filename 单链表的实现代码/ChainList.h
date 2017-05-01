#include<iostream>
using namespace std;
#ifndef TT_CHAIN_LIST
#define TT_CHAIN_LIST
#define TT_OK 1
#define TT_ERROR 0

namespace tt
{
	class ChainList
	{
	public:
		typedef  int ElemType;
		typedef void Status;
	public:
		struct Node
		{
			ElemType m_data;  //数据域
			Node *m_next;  //指针域
		};
	public:
		ChainList();
		~ChainList();
		ElemType insertAt(ElemType i, ElemType elem);
		ElemType removeAt(ElemType i, ElemType &elemOut);
		ElemType getAt(ElemType i, ElemType &elemOut);
		ElemType destroy();

		ElemType getIndexElemAt(ElemType &i, ElemType elemOut);//查找与e相等的元素，返回第一个与e相等元素在线性表中的下标，否则，返回0
		ElemType isEmpty()const;
		Status getLength()const;
		ElemType clear();
		Status show();
		Status createTail(ElemType *datas, ElemType length);//创建长度为length的链表，数据通过数组指定，这里采用尾插法
															//Status createHead(ElemType *datum, ElemType extent);
	private:
		Node *m_heap;  //头结点

	};

	inline ChainList::ElemType ChainList::isEmpty()const
	{
		return (m_heap->m_data == 0);
	}
	inline ChainList::Status ChainList::getLength()const
	{
		cout << "当前的单链表中的数据为：" << (m_heap->m_data) << "\n" << endl;
	}
}
#endif //TT_CHAIN_LIST
