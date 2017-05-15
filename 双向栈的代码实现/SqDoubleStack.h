#include<iostream>
#include<cassert>
using namespace std;
#ifndef TT_DU_STATCK
#define TT_DU_STATCK
#define TT_OK 1
#define TT_ERROR 0
namespace tt
{
	class SqDoubleStack
	{
	public:
		typedef  int ElemType;
		typedef void Status;
	public:
		SqDoubleStack(ElemType maxSize);
		~SqDoubleStack();

		ElemType isFull()const;
		ElemType destroy();
		ElemType clear();
		ElemType isEmpty()const;
		ElemType getTop(ElemType &elemOut);
		ElemType push(ElemType elem);
		ElemType pop(ElemType &elemOut);
		Status getLength()const;
		Status show();
	private:
		ElemType *m_data;     //���ö�̬�洢����ṹ
		ElemType  m_maxLength; //ջ���������
		ElemType m_top1; //ջ1ջ��ָ��
		ElemType m_top2; //ջ2ջ��ָ��
	};

	inline SqDoubleStack::Status SqDoubleStack::getLength()const
	{
		cout << "\n���˫��ջ��ǰ�ĳ��ȣ�" << (m_top1 + 1) + (m_maxLength - m_top2) << endl;
	}
	inline SqDoubleStack::ElemType SqDoubleStack::isEmpty()const
	{
		return ((m_top1 == -1) && (m_top2 == m_maxLength));
	}
	inline SqDoubleStack::ElemType SqDoubleStack::isFull()const
	{
		return(m_top1 + 1 == m_top2);
	}

}
#endif //TT_DU_STATCK