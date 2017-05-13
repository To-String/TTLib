#include<iostream>
#include<cassert>
using namespace std;
#ifndef TT_STACK_H
#define TT_STACK_H
#define STACK_INCREMENT 5   //存储空间分配增量

#define TT_OK 1
#define TT_ERROR 0


namespace tt 
{

	class Stack
	{
	public:
		typedef  int  ElemType;
		typedef  bool Status;
	public:
		/// 注意: 通常我们只把const常数和宏的名字全大写;局部变量名，形参名都第一个字母小写后每个单词的第一个字母大写其他小写如(fooBarCoo)
		Stack(ElemType initSize); //  初始化操作，建立一个空栈
		~Stack();
		Status isFull()const; //确定栈是否已满
		Status destroy();  //若栈存在，则销毁它
		Status clear();  //将栈清空
		Status isEmpty()const;  //若栈为空，返回true 否则false
								/// 注意: at一般用在参数为索引的函数中,你这三个函数没有索引就不用at做为后缀了
								/// 因为: at在英语中后面接地址,而索引通常为一个元素的地址，所以有索引为参数的函数
								/// 就会添加at作为后缀，否则你在这里添加at,有点莫名其妙;
		ElemType getTop(ElemType &elemOut);  //若栈存在且非空，用e返回栈的栈顶元素
		Status push(ElemType e); //若栈存在，插入新元素e 成为栈顶元素
		Status pop(ElemType &elemOut);  //删除栈的栈顶元素，并用e返回其值

		Status getLength()const;  //返回栈中的元素个数
								  // 注意: 同理 showStack前面可以不需要stack直接为show就可以了
		void show();  //显示栈的所以元素
	private:
		ElemType *m_top;  //指向栈顶元素的指针
		ElemType *m_base;   //指向栈底元素的指针
		ElemType m_stackSize;  //栈当前的元数个数
	};
	inline Stack::Status Stack::clear()  //清空所有元素
	{
		m_top = m_base;
		return TT_OK;  //当栈顶指针和栈底指针重合，说明栈中没有元素
	}

	inline Stack::Status Stack::getLength()const //计算栈的当前的元数个数
	{
		cout << "栈中的元素个数为：" << (m_top - m_base) << "\n" << endl;
		return TT_OK;
	}
	inline Stack::Status Stack::isEmpty()const //判断栈是否为空
	{
		return  (m_base == m_top);
	}
}//ns tt

#endif //TT_STACK_H

