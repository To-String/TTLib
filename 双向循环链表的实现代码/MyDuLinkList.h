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
			ElemType m_data;  //������
			DulNode *m_prior;   //ָ��ǰ������ָ��
			DulNode *m_next;    //ָ���̽���ָ��
		};
	public:
		DuLinkList();
		~DuLinkList();
		ElemType insertAt(ElemType i, ElemType elem);
		ElemType removeAt(ElemType i, ElemType &elemOut);
		ElemType getAt(ElemType i, ElemType &elemOut);
		ElemType getIndexElemAt(ElemType &i, ElemType elemOut);//������elem��ȵ�Ԫ�أ����ص�һ����elem���Ԫ���������е����
		ElemType getLength()const;
		ElemType isEmpty()const;
		ElemType destroy();
		ElemType clear();
		Status show();
		Status traverseBack();
		ElemType priorElemAt(ElemType cur_e, ElemType &pri_e);//��cur_e�����������Ԫ�أ��Ҳ��ǵ�һ��������pre_e��������ǰ��
		ElemType nextElemAt(ElemType cur_e, ElemType &Nex_e); //��cur_e�����������Ԫ��,�Ҳ������һ��,����next_e�������ĺ�̣�
		Status createTail(ElemType *datas, ElemType length);//��������Ϊlength����������ͨ������ָ�����������β�巨
	private:
		DulNode *m_heap;
	};
	inline DuLinkList::ElemType DuLinkList::isEmpty()const
	{
		return ((m_heap->m_next == m_heap) && (m_heap->m_prior == m_heap));
	}
}
#endif  //TT_DU_LINK_LIST