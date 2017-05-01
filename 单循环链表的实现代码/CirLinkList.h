#include<iostream>
using namespace std;
#ifndef TT_CIR_LINK_LIST
#define TT_CIR_LINK_LIST
#define TT_OK 1
#define TT_ERROR 0	

namespace tt
{
	class CirLinkList
	{
	public:
		typedef  int ElemType;
		typedef void Status;
	public:
		struct Node
		{
			ElemType m_data;
			Node *m_next;
		};
	public:
		CirLinkList();
		~CirLinkList();
		ElemType insertAt(ElemType i, ElemType elem);
		ElemType removeAt(ElemType i, ElemType &elemOut);
		ElemType getAt(ElemType i, ElemType &elemOut);
		ElemType getIndexElemAt(ElemType &i, ElemType elemOut);//查找与eleOut相等的元素，返回第一个与eleOut相等元素在表中的序号
		ElemType getLength()const;
		ElemType isEmpty()const;
		ElemType destroy();
		ElemType clear();
		Status show();
		ElemType priorElemAt(int cur_e, int &pri_e);//若cur_e是链表的数据元素，且不是第一个，则用pre_e返回它的前驱
		ElemType nextElemAt(int cur_e, int &Nex_e); //若cur_e是链表的数据元素,且不是最后一个,则用next_e返回它的后继，
		Status createTail(ElemType *datas, ElemType length);//创建长度为length的链表，数据通过数组指定，这里采用尾插法
	private:
		Node *m_heap;
	};
	inline CirLinkList::ElemType CirLinkList::isEmpty()const
	{
		return (m_heap->m_next == m_heap);
	}
}
#endif  //TT_CIR_LINK_LIST