#include"LinkQueue.h"

namespace tt
{
	LinkQueue::LinkQueue()
	{
		m_front = m_rear = new QNode;  //为两个指针分配内存
		if (!m_front)
		{
			cout << "错误，内存分配失败！" << endl;
		}
		m_front->m_next = NULL;  //队头指针指向空
		m_queLength = 0;
		cout << "*******************链队列初始化成功************************" << endl;
	}
	LinkQueue::~LinkQueue()
	{
		this->destroy();
	}
	LinkQueue::ElemType LinkQueue::insert(ElemType elem)
	{
		QNode *p = new QNode;  //给一个新节点分配内存
		if (!p)  //若分配错误，返回错误
		{
			return TT_ERROR;
		}
		p->m_data = elem;  //首先把要把新元素添进数据域
		p->m_next = NULL;  //新结点的后继指向空
		m_rear->m_next = p;  //然后在把p变成原队尾指针指向的后继结点
		m_rear = p; //最后再把p设置为队尾结点，此时m_rear指针指向最后一个元素
		++m_queLength;  //队列的长度加1
		return TT_OK;
	}
	LinkQueue::ElemType LinkQueue::remove(ElemType &elemOut)
	{
		if (m_front == m_rear)  //先判断链队列是否为空，空就错误，
		{
			return TT_ERROR;
		}
		QNode *p = m_front->m_next; //声明一个新结点，该结点等于要删除的第一个元素
		elemOut = p->m_data;  //在把要删除的元素用eleOut返回
		m_front->m_next = p->m_next;  //在把要队头结点的后继结点，即第二个元素，m_front指针指向它，就变成头结点的后继
		if (m_rear == p)  //如果要删除的元素刚好就是最好一个元素，  此时就一个元素
		{
			m_rear = m_front;  //删除后，m_rear指针指向头结点
		}
		delete p;  //释放要删除的结点的内存
		--m_queLength;  //链队列的的长度减一
		return TT_OK;
	}
	LinkQueue::ElemType LinkQueue::getHead(ElemType &eleOut)
	{
		if (m_front == m_rear)  //先判断链队列是否为空，空就错误，
		{
			return TT_ERROR;
		}
		//QNode *q=m_front->m_next; eleOut=q->m_data;
		eleOut = m_front->m_next->m_data;  //把m_front指针指向的后继结点的指针域中的数据用eleOut返回
		return TT_OK;
	}
	LinkQueue::ElemType LinkQueue::clear()  //清空链队列，不包括头结点
	{
		QNode *m = m_front->m_next;  //首先声明一个临时结点m，变成队头元素
		m_front->m_next = NULL; //然后m_front指针指向NULL
		m_rear = m_front;  //m_rear指针指向头结点
		while (m)  //当m不为空时，循环继续
		{
			QNode *s = m->m_next;   //先把m结点的后继结点变成s，即第二个元素
			delete m;  //释放m结点
			m = s;  //然后在把s 结点变成m结点，m结点永远都是第一个元素
		}
		m_queLength = 0;
		return TT_OK;
	}
	LinkQueue::ElemType LinkQueue::destroy()  //销毁队列，包括头结点
	{
		while (m_front)  //m_front指针不NULL，继续
		{
			m_rear = m_front->m_next;  //首先把第一个元素变成m_rear指针
			delete m_front; //释放头结点
			m_front = m_rear;  //在把第一个元素变成m_front指针
		}
		m_queLength = 0;
		m_front = m_rear = nullptr;
		return TT_OK;
	}
	void LinkQueue::traverseElem()   //遍历显示链队列中的所有元素
	{
		if (m_front == m_rear)  //先判断链队列是否为空，空就错误，
		{
			cout << "此队列中没有数据或者队列没有建立,无法显示！" << "\n" << endl;
		}
		else
		{
			cout << "队列从队头至队尾内容依次为：";
			QNode *q = m_front->m_next;  //首先把第一个元素变成临时变量q
			while (q)  //只要q不为NULL，就继续
			{
				cout << q->m_data << " ";  //显示出q指针指向的节点的元素
				q = q->m_next;  //q指针每循环一次往后移动一次
			}
			cout << endl;
		}
	}
}

//测试链式队列
void testLinkQueue()
{
	tt::LinkQueue mylinkQueue; //初始化一个队列
	while (true)
	{
		{
			cout << ("\n*********************************************************") << endl
				<< "***************     链队列的基本功能展示    ******************" << endl
				<< "*******************************************************" << endl
				<< "**************      选择1—— 数据进队列尾.       ************" << endl
				<< "**************      选择2—— 删除队列头元素.     ************" << endl
				<< "***************     选择3—— 显示队列头元素.     ************" << endl
				<< "***************     选择4—— 判断队列是否为空.   ************" << endl
				<< "***************************************************************" << endl
				<< "***************     选择5—— 显示队列的元素个数. *************" << endl
				<< "***************     选择6—— 清空队列.           *************" << endl
				<< "****************    选择7—— 销毁队列.           *************" << endl
				<< "****************    选择8—— 显示队列中的所有元素. ***********" << endl
				<< "****************    选择9—— 清屏.              *************" << endl
				<< "****************    选择0—— 退出程序！         *************" << endl
				<< "***************************************************************" << endl
				<< "***************************************************************" << endl;
		}
		cout << "\n*************请输入你想要使用的链队列功能的序号***************" << endl;
		cout << "请输入相应的序号：";
		int userChoice(0);
		cin >> userChoice;
		if (userChoice == 0)
		{
			cout << "程序已退出，感谢您的使用！" << "\n" << endl;
			break;
		}
		switch (userChoice)
		{
		case 1:
		{
			cout << "请输入你想添加的数据：";
			int pushDatas(0);
			cin >> pushDatas;
			if (mylinkQueue.insert(pushDatas))  //添加数据进队尾
			{
				cout << "数据" << pushDatas << "进队列成功！" << endl;
				mylinkQueue.getlength();
				mylinkQueue.traverseElem();
			}
			else
				cout << "内存分配失败，数据" << pushDatas << "进队列失败！" << "\n" << endl;
			break;
		}
		case 2:
		{
			int popHead(0);
			if (mylinkQueue.remove(popHead))  //删除队头元素
			{
				cout << "数据" << popHead << "删除成功！" << "\n" << endl;
				mylinkQueue.getlength();
				mylinkQueue.traverseElem();
			}
			else
			{
				cout << "目前队列为空,数据" << popHead << "删除失败！" << "\n" << endl;
				mylinkQueue.getlength();
			}
			break;
		}
		case 3:
		{
			int showHead(0);
			if (mylinkQueue.getHead(showHead))  //显示队头元素
			{
				cout << "链队列的头元素为：" << showHead << "\n" << endl;
				mylinkQueue.getlength();
				mylinkQueue.traverseElem();
			}
			else
			{
				cout << "目前队列为空，无法显示元素！" << "\n" << endl;
				mylinkQueue.getlength();
			}
			break;
		}
		case 4:
			if (mylinkQueue.isEmpty())  //判断链队列是否为空
			{
				cout << "此队列为空！" << "\n" << endl;
				mylinkQueue.getlength();
			}
			else
			{
				cout << "队列不为空" << "\n" << endl;
				mylinkQueue.getlength();
				mylinkQueue.traverseElem();
			}
			break;
		case 5:                          //显示链队列当前的元素个数
			mylinkQueue.getlength();
			mylinkQueue.traverseElem();
			break;
		case 6:
			if (mylinkQueue.clear())  //清空队列
			{
				cout << "队列已被清空！" << "\n" << endl;
				mylinkQueue.getlength();
			}
			else
			{
				cout << "队列清空失败！" << "\n" << endl;
				mylinkQueue.getlength();
				mylinkQueue.traverseElem();
			}
			break;
		case 7:
		{
			cout << "你确定要销毁此队列吗？如若销毁，就无法恢复，请谨慎操作.（若销毁请输入Y或y,表示确定）";
			char yesOrNo;
			cin >> yesOrNo;
			if ((yesOrNo == 'y') || (yesOrNo == 'y'))
			{
				if (mylinkQueue.destroy())
				{
					cout << "队列已被销毁！" << "\n" << endl;
				}
				else
					cout << "队列销毁失败！" << "\n" << endl;
			}
			break;
		}
		case 8:                          //显示队列中的所有元素
			mylinkQueue.getlength();
			mylinkQueue.traverseElem();
			break;
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
	testLinkQueue();
	system("pause");
	return 0;
}