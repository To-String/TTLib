#include"SqDoubleStack.h"

namespace tt
{
	SqDoubleStack::SqDoubleStack(ElemType maxSize)
	{
		assert(maxSize > 0);
		m_data = new ElemType[maxSize];
		if (!m_data)
		{
			cout << "错误，初始化双向栈的内存失败！" << endl;
			system("pause");
			exit(0);
		}
		m_top1 = -1;
		m_top2 = maxSize;
		m_maxLength = maxSize;
		cout << "*****************************   双向栈初始化成功！  **********************" << endl;

	}
	SqDoubleStack::~SqDoubleStack()
	{
		this->destroy();
	}
	SqDoubleStack::ElemType SqDoubleStack::push(ElemType elem)
	{
		if (m_top1 + 1 == m_top2)  //栈满, 添加内存
		{
			return TT_ERROR;
		}

		int stackNumber(0);
		cout << "请输入你想要为哪个栈添加元素的序号（1或者2）：";
		cin >> stackNumber;
		switch (stackNumber)
		{
		case 1:                    //栈1有元素进栈
			m_data[++m_top1] = elem;   //若是栈1则先top1+1后给数组元素赋值
			break;
		case 2:                  //栈2有元素进栈
			m_data[--m_top2] = elem;         //若是栈2则先top2-1后给数组元素赋值
			break;
		default:
			cout << "输入错误，请输入正确的进栈的序号(选择1或2）！" << "\n" << endl;
		}
		return TT_OK;
	}
	SqDoubleStack::ElemType SqDoubleStack::pop(ElemType &elemOut)
	{
		int stackNumber(0);
		cout << "请输入你想要为哪个栈删除元素的序号（1或者2）：";
		cin >> stackNumber;
		switch (stackNumber)
		{
		case 1:
			if (m_top1 == -1)   //栈1空
			{
				cout << "栈1为空，删除元素失败！" << endl;
				return TT_ERROR;
			}
			elemOut = m_data[m_top1--];  //将栈1的栈顶元素出栈
			break;
		case 2:
			if (m_top2 == m_maxLength)  //栈2空
			{
				cout << "栈2为空，删除元素失败！" << endl;
				return TT_ERROR;
			}
			elemOut = m_data[m_top2++]; // 将栈2的栈顶元素出栈
			break;
		default:
			cout << "输入错误，请输入正确的删除的序号(选择1或2）！" << "\n" << endl;
		}
		this->show();
		return TT_OK;
	}
	SqDoubleStack::ElemType SqDoubleStack::getTop(ElemType &elemOut)
	{
		int stackNumber(0);
		cout << "请输入你想要获取哪个栈的元素的序号（1或者2）：";
		cin >> stackNumber;
		switch (stackNumber)
		{
		case 1:
			if (m_top1 == -1)   //栈1空
			{
				cout << "栈1为空，获取元素失败！" << endl;
				return TT_ERROR;
			}
			elemOut = m_data[m_top1];
			break;
		case 2:
			if (m_top2 == m_maxLength)  //栈2空
			{
				cout << "栈2为空，获取元素失败！" << endl;
				return TT_ERROR;
			}
			elemOut = m_data[m_top2];
			break;
		default:
			cout << "输入错误，请输入正确的获取元素的序号(选择1或2）！" << "\n" << endl;
		}
		this->show();
		return TT_OK;
	}
	SqDoubleStack::Status SqDoubleStack::show()
	{

		if (m_top1 == -1)   //栈1空
		{
			cout << "栈1为空，无法显示元素！" << endl;
		}
		else
		{
			cout << "输出栈1中所有元素：";
			for (int i = 0; i <= m_top1; ++i)
			{
				cout << m_data[i] << ' ';
			}
			cout << endl;
		}
		if (m_top2 == m_maxLength)  //栈2空
		{
			cout << "栈2为空，无法显示元素！" << endl;
		}
		else
		{
			cout << "输出栈2中所有元素：";
			for (int i = m_maxLength - 1; i >= m_top2; --i)
			{
				cout << m_data[i] << ' ';
			}
			cout << endl;
		}
		this->getLength();
	}
	SqDoubleStack::ElemType SqDoubleStack::clear()
	{
		m_top1 = -1;
		m_top2 = m_maxLength;
		return TT_OK;
	}
	SqDoubleStack::ElemType SqDoubleStack::destroy()
	{
		delete[]m_data;
		m_data = nullptr;
		m_top1 = -1;
		m_top2 = m_maxLength;
		m_maxLength = 0;
		return TT_OK;
	}
}


// 双向栈的测试函数
void testmySqDoubleStack()
{
	int sizeCapacity(0);
	cout << "输入双向栈的最大容量：";
	cin >> sizeCapacity;
	tt::SqDoubleStack mySqDoubleStack(sizeCapacity);

	while (true)
	{

		{
			cout << "\n*******************************************************************" << endl
				<< "*******************   双向栈的基本功能展示   *******************" << endl
				<< "*******************************************************************" << endl
				<< "********************   选择1——数据进栈.   **********************" << endl
				<< "********************   选择2——数据出栈.   **********************" << endl
				<< "********************   选择3——判断栈是否为空.   **********************" << endl
				<< "********************   选择4——获取栈的长度.   **********************" << endl
				<< "********************   选择5——判断栈是否满了.   **********************" << endl
				<< "*************************************************************************" << endl
				<< "********************   选择6——输出栈的栈顶元素.   **********************" << endl
				<< "********************   选择7——输出栈的所有元素.   **********************" << endl
				<< "********************   选择8——将栈清空.   **********************" << endl
				<< "********************   选择9——销毁栈.   **********************" << endl
				<< "*************************************************************************" << endl
				<< "********************   选择10——清屏!   **********************" << endl
				<< "********************   选择0——退出程序!   **********************" << endl
				<< "***********************************************************************" << endl
				<< "***********************************************************************" << endl;
		}
		cout << "\n*******************   请输入你想要使用的双向栈功能的序号  ***************" << endl;
		int useChoice(0);
		cout << "请输入你的选择：";
		cin >> useChoice;
		if (useChoice == 0)
		{
			cout << "程序已退出，感谢您的使用!" << "\n" << endl;
			break;
		}
		switch (useChoice)
		{
		case 1:
		{
			int insertElem(0);
			cout << "请输入你想要添加的元素：";
			cin >> insertElem;
			if (mySqDoubleStack.push(insertElem))
			{
				cout << "数据" << insertElem << "插入成功！" << "\n" << endl;
				mySqDoubleStack.show();
			}
			else
			{
				cout << "数据" << insertElem << "插入失败，或许栈已经满了！" << endl;
				mySqDoubleStack.getLength();
				mySqDoubleStack.isFull();
			}
			break;
		}
		case 2:
		{
			int cancelElem(0);
			if (mySqDoubleStack.pop(cancelElem))
			{
				cout << "数据" << cancelElem << "删除成功！" << "\n" << endl;
			}
			break;
		}
		case 3:
			if (mySqDoubleStack.isEmpty())
			{
				cout << "目前双向栈为空！" << endl;
				mySqDoubleStack.getLength();
			}
			else
			{
				cout << "目前双向栈非空！" << endl;
				mySqDoubleStack.getLength();
			}
			break;
		case 4:
			mySqDoubleStack.getLength();
			break;
		case 5:
			if (mySqDoubleStack.isFull())
			{
				cout << "目前双向栈已满，不能再添加元素了！" << endl;
				mySqDoubleStack.getLength();
			}
			else
			{
				cout << "目前双向栈非满，还可以添加元素！" << endl;
				mySqDoubleStack.getLength();
			}
			break;
		case 6:
		{
			int getElem(0);
			if (mySqDoubleStack.getTop(getElem))
			{
				cout << "获取的栈顶元素为：" << getElem << endl;
			}
			break;
		}
		case 7:
			mySqDoubleStack.show();
			break;
		case 8:
			if (mySqDoubleStack.clear())
			{
				cout << "双向栈已被清空！" << endl;
				mySqDoubleStack.getLength();
			}
			else
			{
				cout << "双向栈清空失败！" << endl;
				mySqDoubleStack.getLength();
			}
			break;
		case 9:
		{
			char yesOrNo('\0');
			cout << "你确定要销毁一个栈吗?(若销毁请输入输入(Y/y))";
			cin >> yesOrNo;
			if ((yesOrNo == 'Y') || (yesOrNo == 'y'))
			{
				if (mySqDoubleStack.destroy())
				{
					cout << "双向栈已被销毁." << endl;
				}
				else
					cout << "双向栈销毁失败." << endl;
			}
			break;
		}
		case 10:
			system("cls");
			cout << "屏幕已经清屏，可以重新输入!" << endl;
			break;
		default:
			cout << "输入的序号不正确，请重新输入!" << endl;
		}
	}
}
int main()
{
	testmySqDoubleStack();
	system("pause");
	return 0;
}