#include"CirQueue.h"

namespace tt
{
	void foo()
	{
		return;
	}
	CirQueue::CirQueue(ElemType INI_SIZE)
	{
		assert(INI_SIZE > 0);
		m_data = new int[INI_SIZE];
		if (!m_data)
		{
			cout << "内存分配失败！请重新分配！" << endl;
		}
		m_queueSize = INI_SIZE;  //把队列的初始化的最大容量赋值给成员数据
		m_front = m_rear = 0;  //m_front等于m_rear 就是空队列
		cout << "***********     循环队列初始化成功！   **************" << endl;
	}
	CirQueue::~CirQueue()
	{
		this->destroy();
	}
	CirQueue::ElemType CirQueue::insert(ElemType elem)  //插入元素致队列的尾部
	{
		if (((m_rear + 1) % m_queueSize) == m_front)//判断队列满的情况
		{
			return TT_ERROR;
		}
		m_data[m_rear] = elem;    //将元素elem  添加到队列的末尾
		m_rear = (m_rear + 1) % m_queueSize;  //尾指针应以此种方式加1，才会实现循环队列， 若到末尾转到数组的头部
		return TT_OK;
	}
	CirQueue::ElemType CirQueue::remove(ElemType &elemOut)  //删除队列的队头元素
	{
		if (m_front == m_rear)   //判断循环队列是否为空
		{
			return TT_ERROR;
		}
		elemOut = m_data[m_front];  //将对头元素赋给elem返回
		m_front = (m_front + 1) % m_queueSize;  //m_front指针向后移动一位，若到最后则转到数组头部
		return TT_OK;
	}
	CirQueue::ElemType CirQueue::getHead(ElemType &elemOut) //若队列存在且非空，用elem返回队列的队头元素
	{
		if (m_front == m_rear)   //判断循环队列是否为空
		{
			return TT_ERROR;
		}
		elemOut = m_data[m_front];  //把队头元素用elem返回
		return TT_OK;
	}

	CirQueue::ElemType CirQueue::destroy() //若队列存在，则销毁它
	{
		delete[] m_data;
		m_data = nullptr;
		m_front = m_rear = m_queueSize = 0;
		return ((!m_data) && (m_front == m_rear == m_queueSize == 0));  //多一个判断看队列是否被销毁
	}
	void CirQueue::show()  //显示队列的所有元素
	{
		if (m_front == m_rear)
		{
			cout << "错误，此队列中没有数据或者队列没有建立,无法显示！" << endl;
		}
		else
		{
			int count = (m_rear - m_front + m_queueSize) % m_queueSize;  //一个临时变量存储该队列的元素个数
			cout << "队列从队头至队尾内容依次为：";
			for (int i = m_front; i <m_front + count; ++i)
			{
				cout << m_data[i] << ' ';
			}
			cout << endl;
		}
	}
}

//测试循环队列的功能
void testCirQueue()
{
	int allocMemory(0);
	cout << "请输入队列初始化的最大容量：";
	cin >> allocMemory;
	tt::CirQueue myCirQueue(allocMemory);  //初始化一个队列
	while (true)
	{
		{
			cout << ("\n***************************************************") << endl
				<< "***************     循环队列的基本功能展示    **************" << endl
				<< "*******************************************************" << endl
				<< "**************      选择1—— 数据进队列尾.       ************" << endl
				<< "**************      选择2—— 删除队列头元素.     ************" << endl
				<< "***************     选择3—— 显示队列头元素.     ************" << endl
				<< "***************     选择4—— 判断队列是否为空.   ************" << endl
				<< "***************     选择5—— 判断队列是否满了.   ************" << endl
				<< "***************************************************************" << endl
				<< "***************     选择6—— 显示队列的元素个数. *************" << endl
				<< "***************     选择7—— 清空队列.           *************" << endl
				<< "****************     选择8—— 销毁队列.           *************" << endl
				<< "****************     选择9—— 显示队列中的所有元素. ***********" << endl
				<< "****************     选择10—— 清屏.              *************" << endl
				<< "****************     选择0—— 退出程序！         *************" << endl
				<< "***************************************************************" << endl
				<< "***************************************************************" << endl;
		}
		cout << "\n*****************     请输入你想要使用的队列功能的序号   ***************" << endl;
		cout << "请输入你的选择：";
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
			int pushDatas(0);
			cout << "请输入想要添加的数据：";
			cin >> pushDatas;
			if (myCirQueue.insert(pushDatas))   //进队列
			{
				cout << "数据" << pushDatas << "成功进入队列中！" << endl;
				myCirQueue.getLength();
				myCirQueue.show();  //显示所有元素
			}
			else
				cout << "目前队列已满, 数据" << pushDatas << "进入失败！" << endl;
			break;
		}
		case 2:
		{
			int popDatas(0);
			if (myCirQueue.remove(popDatas))   //删除队列头元素
			{
				cout << "数据" << popDatas << "从队列中成功删除！" << endl;
				myCirQueue.getLength();
				myCirQueue.show();
			}
			else
			{
				cout << "目前队列为空， 数据" << popDatas << "删除失败！" << endl;
				myCirQueue.getLength();
			}
			break;
		}
		case 3:
		{
			int disHead(0);
			if (myCirQueue.getHead(disHead))   //获取队头元素
			{
				cout << "队列头元素为：" << disHead << endl;
				myCirQueue.getLength();
				myCirQueue.show();
			}
			else
			{
				cout << "目前队列为空， 数据" << disHead << "获取失败！" << endl;
				myCirQueue.getLength();
			}
			break;
		}
		case 4:
			if (myCirQueue.isEmpty())  //判断队列是否空
			{
				cout << "队列为空,或者队列尚未建立！" << endl;
				myCirQueue.getLength();
			}
			else
			{
				cout << "队列非空！" << endl;
				myCirQueue.getLength();
				myCirQueue.show();
			}
			break;
		case 5:
			if (myCirQueue.isFull())  //判断队列是否满
			{
				cout << "目前队列已满，不能再添加数据了！" << endl;
				myCirQueue.getLength();
				myCirQueue.show();
			}
			else
			{
				cout << "目前队列不满，还可以继续输入数据进栈!" << "\n" << endl;
				myCirQueue.getLength();
				myCirQueue.show();
			}
			break;
		case 6:
			myCirQueue.getLength();  //显示队列的元素个数
			myCirQueue.show();
			break;

		case 7:
			if (myCirQueue.clear())
			{
				cout << "队列已清空！" << endl;
				myCirQueue.getLength();
			}
			else
			{
				cout << "队列清空失败！" << endl;
				myCirQueue.getLength();
				myCirQueue.show();
			}
			break;
		case 8:
		{
			cout << "你确定要销毁一个队列吗?(若销毁请输入输入(Y/y))";
			char yesOrNo;
			cin >> yesOrNo;
			if ((yesOrNo == 'Y') || (yesOrNo == 'y'))
			{
				if (myCirQueue.destroy())
				{
					cout << "队列已被销毁！" << endl;
				}
				else
					cout << "队列销毁失败！" << endl;
			}
			break;
		}
		case 9:
			myCirQueue.getLength();
			myCirQueue.show();
			break;
		case 10:
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
	testCirQueue();
	system("pause");
	return 0;
}