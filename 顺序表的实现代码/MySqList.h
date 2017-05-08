#include<iostream>
#include<cassert>
#ifndef TT_LIST_H
#define TT_LIST_H
#define LIST_NCREMENT 5  // ˳���洢�ռ�ķ�������
using namespace std;
#define TT_OK 1
#define TT_ERROR 0
namespace tt
{
	class SqList
	{
	public:
		typedef  int ElemType;
		typedef void Status;
	public:
		SqList(ElemType maxSize);
		~SqList();
		ElemType insertAt(ElemType i, ElemType elem);
		ElemType removeAt(ElemType i, ElemType &elemOut);
		ElemType getAt(ElemType i, ElemType &elemOut);

		ElemType getIndexElem(const ElemType elem);//������e��ȵ�Ԫ�أ����ص�һ����e���Ԫ�������Ա��е��±꣬���򣬷���0
		ElemType isEmpty()const;
		Status getLength()const;
		Status clear();
		Status show();
		ElemType destroy();
		ElemType priorElemAt(ElemType cur_e, ElemType &pri_e);//��cur_e�����������Ԫ�أ��Ҳ��ǵ�һ��������pre_e��������ǰ��
		ElemType nextElemAt(ElemType cur_e, ElemType &Nex_e); //��cur_e�����������Ԫ��,�Ҳ������һ��,����next_e�������ĺ�̣�
	private:
		ElemType *m_data;
		ElemType  m_length;  //���Ա�ǰ��Ԫ�ظ���
		ElemType  m_maxLength; //���Ա���������

	};
	inline SqList::ElemType SqList::isEmpty()const
	{
		return (m_length == 0);
	}
	inline SqList::Status SqList::getLength()const
	{
		cout << "��ǰ��˳���ĳ���Ϊ��" << m_length << endl;
	}

}
#endif   //TT_LIST_H