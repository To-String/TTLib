#include"Stack.h"
namespace tt
{

	Stack::Stack(ElemType initSize)  //初始化栈
	{
		assert(initSize > 0);
		/// 注意: 这里应该是new一个数组
		m_base = new ElemType[initSize];  //为栈分配空间
		if (!m_base)  //若没有分配到空间，返回false
		{
			cout << "给栈初始化分配内存失败！" << endl;
			system("pause");
			exit(0);
		}
		m_top = m_base;  //最开始，栈顶就是栈底
		m_stackSize = initSize; //现在栈的最大容量为100	
		cout << "***********************   顺序栈初始化成功！  ***********************" << endl;
		cout << "栈的大小是: " << m_stackSize << "\n" << endl;
	}
	Stack::~Stack()  //释放分配的内存
	{
		this->destroy();
	}
	Stack::Status Stack::push(ElemType e)  //为栈添加元素
	{
		if (m_top - m_base >= m_stackSize)  //栈满，追加存储空间
		{
			int *allocateMemory = new int[m_base, m_stackSize + STACK_INCREMENT];
			if (!allocateMemory)
			{
				cout << "错误！继续分配内存失败！" << endl;
				system("pause");
				exit(0);
			}
			m_stackSize += STACK_INCREMENT;   //增加存储容量
		}
		*(m_top)++ = e;
		//++m_top;
		return TT_OK;
	}
	Stack::Status Stack::pop(ElemType &elemOut)  //删除栈顶元素
	{
		if (m_top == m_base) //当栈底指针和栈顶指针重合，说明栈中没有元素
		{
			return TT_ERROR;
		}
		//--Top;  //栈顶指针先往下移动一格
		elemOut = *--(m_top);  //然后取出栈顶指针指着的元素
		return TT_OK;
	}
	Stack::Status Stack::destroy()  //摧毁栈
	{
		/// 注意: 这里应该是delete一个数组
		delete[] m_base;    //把分配的内存释放掉
		m_base = nullptr; 
		m_top = nullptr;
		m_stackSize = 0;  //然后把栈的最大容量设置为0
		return TT_OK;
	}
	Stack::Status Stack::isFull()const  //判断是否栈满
	{
		int temp = (m_top - m_base);
		if (temp == m_stackSize)
		{
			cout << "目前栈满或者栈尚未建立!" << "\n" << endl;
		}
		else
			cout << "目前栈不满，还可以继续输入数据进栈!" << "\n" << endl;
		return TT_OK;
	}
	Stack::ElemType Stack::getTop(ElemType &elemOut)  //得到栈顶元素
	{
		if (m_base == m_top)
		{
			cout << "错误，访问的位置不正确" << "\n" << endl;
			return TT_ERROR;
		}
		elemOut = *(m_top-1);
		return TT_OK;
	}
	void Stack::show()  //显示栈中的所有元素
	{
		if (m_base == m_top)
		{
			cout << "此栈中没有数据,无法显示元素！" << endl;
			system("pause");
			exit(0);
		}
		else
		{
			int Temp = (m_top - m_base);  //先算出栈中的元素的个数
			m_top = m_base;  //把栈底指针变成栈顶指针，从栈底开始遍历输出
			cout << "显示出栈中的所有元素：";
			for (int i = 0; i < Temp; ++i)
			{
				cout << *(m_top)++ << ",";
			}
			cout << endl;
		}
	}
}

void testStack()
	{
	int sizeCapacity(0);
	cout << "输入顺序栈的最大容量：";
	cin >> sizeCapacity;
	tt::Stack myStack(sizeCapacity);  
		while (true)
		{
			{
				cout << "\n*******************************************************************" << endl
					<< "*******************   顺序栈的基本功能展示   *******************" << endl
					<< "*******************************************************************" << endl
					<< "********************   选择1——数据进栈.   **********************" << endl
					<< "********************   选择2——数据出栈.   **********************" << endl
					<< "********************   选择3——判断栈是否为空.   **********************" << endl
					<< "********************   选择4——获取栈的长度.   **********************" << endl
					<< "********************   选择5——判断栈是否满了.   **********************" << endl
					<< "********************   选择6——输出栈的栈顶元素.   **********************" << endl
					<< "********************   选择7——输出栈的所有元素.   **********************" << endl
					<< "********************   选择8——将栈清空.   **********************" << endl
					<< "********************   选择9——销毁栈.   **********************" << endl
					<< "********************   选择10——清屏!   **********************" << endl
					<< "********************   选择0——退出程序!   **********************" << endl
					<< "***********************************************************************" << endl
					<< "***********************************************************************" << endl;
			}
			cout << "\n*******************   请输入你想要使用的栈功能的序号  ***************" << endl;
			cout << "请输入你的选择: " << endl;
			int userChoice = 0;
			cin >> userChoice;
			if (userChoice == 0)
			{
				cout << "程序已退出，感谢您的使用!" << "\n" << endl;
				break;
			}

			switch (userChoice)
			{
			case 1:
			{
				cout << "请输入要进栈的数据：";
				int pushData = 0;
				cin >> pushData;
				if (myStack.push(pushData))
				{
					cout << "数据 " << pushData << "已经入栈成功!" << endl;
					myStack.getLength();
					myStack.show();
				}
				else
				{
					cout << "数据 " << pushData << "入栈失败！" << endl;
					myStack.show();
				}
				break;
			}
			case 2:
			{
				int removeData = 0;
				if (myStack.pop(removeData))
				{
					cout << "数据 " << removeData << "成功出栈！" << endl;
					myStack.show();
				}
				else
				{
					cout << "出栈失败，可能是栈中没有元素！" << endl;
					myStack.show();
				}
				break;
			}
			case 3:
			{
				if (myStack.isEmpty())
				{
					cout << "目前是空栈或者是栈尚未建立!" << endl;
					myStack.getLength();
				}
				else
				{
					cout << "目前栈非空!" << endl;
					myStack.show();
					myStack.getLength();
				}
				break;
			}
			case 4:
				myStack.getLength();  //得到栈中此时的元素个数
				break;
			case 5:
				myStack.isFull();  //判断是否栈满
				break;
			case 6:
			{
				int getElement = 0;
				if (myStack.getTop(getElement))
				{
					cout << "栈顶元素为：" << getElement << endl;
					myStack.show();
				}
				else
				{
					cout << "获取栈顶元素失败，可能是栈中没有元素！" << endl;
					myStack.getLength();
				}
				break;
			}
			case 7:
				myStack.show();  //显示栈中的元素，从栈底开始输出的
				break;

			case 8:
			{
				if (myStack.clear())
				{
					cout << "栈已经清空." << endl;
					myStack.getLength();
				}
				else
				{
					cout << "栈没有被清空." << endl;
					myStack.show();
					myStack.getLength();
				}
				break;
			}
			case 9:
			{
				char yesOrNo;
				cout << "你确定要销毁一个栈吗?(若销毁请输入输入(Y/y))";
				cin >> yesOrNo;
				if ((yesOrNo == 'Y') || (yesOrNo == 'y'))
				{
					if (myStack.destroy())
					{
						cout << "栈已被销毁." << endl;
					}
					else
						cout << "栈销毁失败." << endl;
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
		testStack();
		system("pause");
		return 0;
	}