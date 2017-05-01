#include<iostream>
using namespace std;
#define TT_ERROR 0
#define TT_OK 1
typedef int ElemType;
typedef  bool Status;


class LinkStack
{
public:
	typedef int ElemType;
	typedef  bool Status;
public:
	struct Node
	{
		ElemType m_data;
		Node *m_next;
	};
	LinkStack();  //初始化一个栈
	~LinkStack();
	ElemType push(ElemType elem);  //若栈存在，插入新元素e 成为栈顶元素
	ElemType pop(ElemType &elemOut); //若栈存在，删除栈顶元素
	Status  isEmpty()const; //判断栈是否为空

	ElemType getTop(ElemType &elemOut);  //若栈存在且非空，用e返回栈的栈顶元素
	void getLength()const;  //返回栈中的元素个数
	void show();  //显示栈的所有元素

	Status clear();  //将栈清空
	Status destroy();  //若栈存在，则销毁它
private:
	Node *m_heap;  //声明一个头结点,此链栈中没有栈顶指针
	ElemType m_stackLength;  //栈的当前的元素个数
};
LinkStack::LinkStack()
{
	 m_heap = new Node;
	if (!m_heap)
	{
		cout << "错误，内存分配失败！" << endl;
	}
	m_heap->m_next = nullptr;
	m_stackLength = 0;
	cout << "*******************链栈初始化成功*****************" << endl;
}
LinkStack::~LinkStack()
{
	this->destroy();
}
ElemType LinkStack::push(ElemType elem)      //若栈存在，插入新元素e 成为栈顶元素
{
	Node *p = new Node;  //给一个新结点分配内存
	if (!p)
	{
		return TT_ERROR;
	}
	p->m_data = elem;    //把新元素添进数据域中
	p->m_next = m_heap->m_next;    //把栈顶元素变成p的后继结点
	m_heap->m_next = p; //在把p变成头结点的后继结点，那么p就是栈顶元素
	++m_stackLength;   //链栈的当前个数+1
	return TT_OK;
}
ElemType LinkStack::pop(ElemType &elemOut)  //栈顶数据出栈
{
	if (m_stackLength==0)
	{
		return TT_ERROR;
	}
	Node *p = m_heap->m_next;  //首先把栈顶元素给p
	elemOut = p->m_data;  //输出栈顶元素的数据
	m_heap->m_next = p->m_next;   //在把p的后继节点变成头结点的后继节点，
	delete p;   //释放栈顶元素
	--m_stackLength;
	return TT_OK;
}
ElemType LinkStack::getTop(ElemType &elemOut)  //输出栈顶元素
{
	if (m_stackLength == 0)
	{
		return TT_ERROR;
	}
	//Node *p = m_heap->m_next;  
	elemOut = m_heap->m_next->m_data;  //把栈顶元素的数据返回
	return TT_OK;
}

void LinkStack::show()
{
	if (m_stackLength == 0)
	{
		cout << "此栈中没有数据，或者栈未建立！" << "\n" << endl;
	}
	else
	{
		Node *p = m_heap->m_next;
		cout << "输出栈中所有元素有：";
		while (p)
		{
			cout << p->m_data << ",";
			p = p->m_next;

		}
		cout << endl;
	}
}
Status LinkStack::clear()  //清空一个栈，不包括头结点
{
	Node *m = m_heap->m_next;  
	while (m != nullptr)  
	{
		Node *n = m->m_next;  //把第二个元素变成n
		delete m;    //释放栈顶元素
		m = n;    //把n变成栈顶元素
	}
	m_heap->m_next = nullptr;  //头结点的指针域指向空
	m_stackLength = 0;  //当前个数清空
	return TT_OK;
}
Status LinkStack::destroy()   //销毁一个栈，包括头结点
{
	while (m_heap)  //只要头结点不为空，循环继续
	{
		Node *s = m_heap->m_next;  //把栈顶元素变成s
		delete m_heap;  //先释放头结点，
		m_heap = s;  //然后把栈顶元素s变成头结点，头结点会随着循环，向后移动，
	}
	m_heap = nullptr;  //指针清0，防止野指针
	m_stackLength = 0;
	return TT_OK;
}
inline Status LinkStack::isEmpty()const  //判断栈是否为空
{
	return (m_stackLength == 0);
}
inline void LinkStack::getLength()const  //得到栈中现在的元素个数
{
	cout << "栈中的元素个数为：" << m_stackLength << endl;
}
void testLinkStack()
{
	LinkStack myStack;  //初始化一个栈
	while (true)
	{
		{
			cout << "\n************************************************" << endl
				<< "*****           链栈的基本功能演示        *****" << endl
				<< "*************************************************" << endl
				<< "*****            选择1—— 数据进栈.        *****" << endl
				<< "*****            选择2——栈顶元素出栈.     *****" << endl
				<< "*****            选择3——显示栈中的所有数据.****" << endl
				<< "*****            选择4——输出栈顶元素.    *****" << endl
				<< "*****            选择5——判断栈是否为空栈. *****" << endl
				<< "*************************************************" << endl
				<< "*****            选择6——输出栈中的元素个数.*****" << endl
				<< "*****            选择7——清空栈中的所有元素.*****" << endl
				<< "*****            选择8——销毁一个栈.         *****" << endl
				<< "*****            选择9——清屏.               *****" << endl
				<< "*****            选择0——退出程序！          *****" << endl
				<< "*****************************************************" << endl
				<< "*****************************************************" << endl;
		}
		cout << "\n*************请输入你想要使用的链栈功能的序号***************" << endl;
		cout << "请输入选择：";
		int userChoice(0);
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
			int pushDatas(0);
			cin >> pushDatas;
			if (myStack.push(pushDatas))
			{
				cout << "数据" << pushDatas << "进栈成功." << "\n" << endl;
				myStack.getLength();
				myStack.show();
			}
			else
				cout << "内存分配失败，数据" << pushDatas << "进栈失败." << "\n" << endl;
			break;
		}
		case 2:
		{
			int removeData(0);
			if (myStack.pop(removeData))
			{
				cout << "数据" << removeData << "从栈中成功出栈." << "\n" << endl;
				myStack.getLength();
				myStack.show();
			}
			else
			{
				cout << "目前栈为空，数据" << removeData << "出栈失败！" << "\n" << endl;
				myStack.getLength();
			}
			break;
		}
		case 3:
			myStack.getLength();
			myStack.show();   //显示栈中的所有数据元素
			break;
		case 4:
		{
			int getTopElem(0);
			if (myStack.getTop(getTopElem))
			{
				cout << "栈顶元素为：" << getTopElem << "\n" << endl;
				myStack.getLength();
				myStack.show();
			}
			else
			{
				cout << "目前栈为空,栈顶元素出栈失败" << "\n" << endl;
				myStack.getLength();
			}
			break;
		}
		case 5:
			if (myStack.isEmpty())
			{
				cout << "目前是空栈或者是栈初始化失败!" << "\n" << endl;
				myStack.getLength();
			}
			else
			{
				cout << "目前栈非空!" << "\n" << endl;
				myStack.getLength();
				myStack.show();
			}
			break;
		case 6:
			myStack.getLength();  //输出栈中的元素个数
			myStack.show();
			break;
		case 7:
			if (myStack.clear())
			{
				cout << "栈已被清空！" << "\n" << endl;
				myStack.getLength();
			}
			else
			{
				cout << "栈清空失败" << "\n" << endl;
				myStack.getLength();
				myStack.show();
			}
			break;
		case 8:
		{
			cout << "你确定要销毁一个栈吗?(若销毁请输入输入(Y/y))";
			char yesOrNo;
			cin >> yesOrNo;
			if ((yesOrNo == 'Y') || (yesOrNo == 'y'))
			{
				if (myStack.destroy())
				{
					cout << "栈已被销毁." << "\n" << endl;
				}
				else
					cout << "栈销毁失败." << "\n" << endl;
			}
			break;
		}
		case 9:
			system("cls");
			cout << "屏幕已经清屏，可以重新输入!" << "\n" << endl;
			break;
		default:
			cout << "输入的序号不正确，请重新输入!" << "\n" << endl;
		}
	}
}

int main()
{
	testLinkStack();
	cout << endl;
	system("pause");
	return 0;
}