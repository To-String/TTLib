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
		ElemType getIndexElemAt(ElemType &i, ElemType elemOut);//������eleOut��ȵ�Ԫ�أ����ص�һ����eleOut���Ԫ���ڱ��е����
		ElemType getLength()const;
		ElemType isEmpty()const;
		ElemType destroy();
		ElemType clear();
		Status show();
		ElemType priorElemAt(int cur_e, int &pri_e);//��cur_e�����������Ԫ�أ��Ҳ��ǵ�һ��������pre_e��������ǰ��
		ElemType nextElemAt(int cur_e, int &Nex_e); //��cur_e�����������Ԫ��,�Ҳ������һ��,����next_e�������ĺ�̣�
		Status createTail(ElemType *datas, ElemType length);//��������Ϊlength����������ͨ������ָ�����������β�巨
	private:
		Node *m_heap;
	};
	inline CirLinkList::ElemType CirLinkList::isEmpty()const
	{
		return (m_heap->m_next == m_heap);
	}
}
#endif  //TT_CIR_LINK_LIST