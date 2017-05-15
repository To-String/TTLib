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
		ElemType *m_data;     //采用动态存储分配结构
		ElemType  m_maxLength; //栈的最大容量
		ElemType m_top1; //栈1栈顶指针
		ElemType m_top2; //栈2栈顶指针
	};

	inline SqDoubleStack::Status SqDoubleStack::getLength()const
	{
		cout << "\n输出双向栈当前的长度：" << (m_top1 + 1) + (m_maxLength - m_top2) << endl;
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