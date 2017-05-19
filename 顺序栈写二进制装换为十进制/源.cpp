#include<iostream>
using namespace std;

#define TT_OK 1
#define TT_ERROR 0
#define STACK_INCREMENT 5   //存储空间分配增量
typedef int ElemType;
typedef void Status;

class sqStack
{
public:
	sqStack(ElemType iniSize);
	~sqStack();
	ElemType push(ElemType elem);
	ElemType pop(ElemType &elemOut);
	ElemType getLength();
private:
	ElemType *m_base;
	ElemType *m_top;
	ElemType m_stackSize;  //栈的最大容量
};
sqStack::sqStack(ElemType iniSize)
{
	m_base = new ElemType[iniSize];
	if (!m_base)
	{
		cout << "初始化栈的内存失败!" << endl;
		system("pause");
		exit(0);
	}
	m_top = m_base;
	m_stackSize = iniSize;
	cout << "***********************   顺序栈初始化成功！  ***********************" << endl;
}
sqStack::~sqStack()
{
	delete[]m_base;
}
ElemType sqStack::push(ElemType elem)
{
	if (m_top - m_base >= m_stackSize)
	{
		int *assignCapacity = new int[m_base, m_stackSize + STACK_INCREMENT];
		if (!assignCapacity)
		{
			cout << "继续分配栈内存失败！" << endl;
			system("pause");
			exit(0);
		}
		m_stackSize += STACK_INCREMENT;
	}
	*(m_top++) = elem;
	return TT_OK;
}
ElemType sqStack::pop(ElemType &elemOut)
{
	if (m_top == m_base)
	{
		return TT_ERROR;
	}
	elemOut = *--(m_top);
	return TT_OK;
}
ElemType sqStack::getLength()
{
	return (m_top - m_base);
}

int main()
{
	int assignCapacity(0);
	cout << "输入你想为栈分配的内存大小：";
	cin >> assignCapacity;
	if (assignCapacity <= 0)
	{
		cout << "错误，请分配正确的内存！" << endl;
		system("pause");
		exit(0);
	}
	sqStack myStack(assignCapacity);

	char insertElem('\0');
	cout << "请输入二进制数，输入#符号表示结束！" << endl;
	
	while (cin >> insertElem)
	{
		if (insertElem == '#')
		{
			break;
		}
		myStack.push(insertElem);
	}
	getchar();  //把"\n"从缓冲区去掉
	int length = myStack.getLength();
	cout << "栈的当前元素个数为：" << length << endl;
	int cancelElem(0), sum(0);
	for (int i = 0; i < length; ++i)
	{
		myStack.pop(cancelElem);
		sum = sum + (cancelElem - 48)*pow(2, i);  //减48是因为ASCII值对应的是0，如果是0就： 0*2的0次幂，从栈顶开始
	}                                          //其实就是计算二进制转十进制的公式
	cout << "转化为十进制数为：\n" << sum << endl;

	cout << endl;
	system("pause");
	return 0;
}