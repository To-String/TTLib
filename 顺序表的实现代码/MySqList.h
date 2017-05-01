#include<iostream>
#include<cassert>
#ifndef TT_LIST_H
#define TT_LIST_H
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

		ElemType getIndexElem(const ElemType elem);//查找与e相等的元素，返回第一个与e相等元素在线性表中的下标，否则，返回0
		ElemType isEmpty()const;
		Status getLength()const;
		Status clear();
		Status show();
		ElemType isFull()const;
		ElemType destroy();
	private:
		ElemType *m_data;
		ElemType  m_length;  //线性表当前的元素个数
		ElemType  m_maxLength; //线性表的最大容量

	};
	inline SqList::ElemType SqList::isFull()const  //判断是否满了
	{
		return (m_length == m_maxLength);
	}
	inline SqList::ElemType SqList::isEmpty()const
	{
		return (m_length == 0);
	}
	inline SqList::Status SqList::getLength()const
	{
		cout << "当前的顺序表的长度为：" << m_length << endl;
	}

}
#endif   //TT_LIST_H