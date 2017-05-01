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
			ElemType m_data;  //������
			Node *m_next;  //ָ����
		};
	public:
		ChainList();
		~ChainList();
		ElemType insertAt(ElemType i, ElemType elem);
		ElemType removeAt(ElemType i, ElemType &elemOut);
		ElemType getAt(ElemType i, ElemType &elemOut);
		ElemType destroy();

		ElemType getIndexElemAt(ElemType &i, ElemType elemOut);//������e��ȵ�Ԫ�أ����ص�һ����e���Ԫ�������Ա��е��±꣬���򣬷���0
		ElemType isEmpty()const;
		Status getLength()const;
		ElemType clear();
		Status show();
		Status createTail(ElemType *datas, ElemType length);//��������Ϊlength����������ͨ������ָ�����������β�巨
															//Status createHead(ElemType *datum, ElemType extent);
	private:
		Node *m_heap;  //ͷ���

	};

	inline ChainList::ElemType ChainList::isEmpty()const
	{
		return (m_heap->m_data == 0);
	}
	inline ChainList::Status ChainList::getLength()const
	{
		cout << "��ǰ�ĵ������е�����Ϊ��" << (m_heap->m_data) << "\n" << endl;
	}
}
#endif //TT_CHAIN_LIST
