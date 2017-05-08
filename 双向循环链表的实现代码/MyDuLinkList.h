#include<iostream>
using namespace std;
#ifndef TT_DU_LINK_LIST
#define TT_DU_LINK_LIST
#define TT_OK 1
#define TT_ERROR 0
namespace tt

{
	class  DuLinkList
	{
	public:
		typedef  int ElemType;
		typedef void Status;
	public:
		struct DulNode
		{
			ElemType m_data;  //数据域
			DulNode *m_prior;   //指向前驱结点的指针
			DulNode *m_next;    //指向后继结点的指针
		};
	public:
		DuLinkList();
		~DuLinkList();
		ElemType insertAt(ElemType i, ElemType elem);
		ElemType removeAt(ElemType i, ElemType &elemOut);
		ElemType getAt(ElemType i, ElemType &elemOut);
		ElemType getIndexElemAt(ElemType &i, ElemType elemOut);//查找与elem相等的元素，返回第一个与elem相等元素在链表中的序号
		ElemType getLength()const;
		ElemType isEmpty()const;
		ElemType destroy();
		ElemType clear();
		Status show();
		Status traverseBack();
		ElemType priorElemAt(ElemType cur_e, ElemType &pri_e);//若cur_e是链表的数据元素，且不是第一个，则用pre_e返回它的前驱
		ElemType nextElemAt(ElemType cur_e, ElemType &Nex_e); //若cur_e是链表的数据元素,且不是最后一个,则用next_e返回它的后继，
		Status createTail(ElemType *datas, ElemType length);//创建长度为length的链表，数据通过数组指定，这里采用尾插法
	private:
		DulNode *m_heap;
	};
	inline DuLinkList::ElemType DuLinkList::isEmpty()const
	{
		return ((m_heap->m_next == m_heap) && (m_heap->m_prior == m_heap));
	}
}
#endif  //TT_DU_LINK_LIST