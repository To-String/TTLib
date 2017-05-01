#include"ChainList.h"

namespace tt
{
	ChainList::ChainList()
	{
		m_heap = new Node;
		if (!m_heap)
		{
			cout << "错误，内存分配失败！" << endl;
			system("pause");
			exit(0);
		}
		m_heap->m_next = nullptr;
		m_heap->m_data = 0;
		cout << "********************单链表初始化成功********************" << "\n" << endl;
	}
	ChainList::~ChainList()
	{
		this->destroy();
	}
	ChainList::Status ChainList::createTail(ElemType *datas, ElemType length)  //单链表的整表创建,尾插法
	{
		m_heap->m_data = length;
		Node *m = m_heap;    //声明一个节点指针指向头结点
		for (int i = 0; i < length; ++i)
		{
			Node *n = new Node;  //每次循环都给新元素分配空间
			n->m_data = datas[i];   //每次循环都把要存储的新元素依次存储到数据域中
			m->m_next = n;  //第一次循环的时候，把新节点n变成头结点的后继节点，就是第一个元素，
			m = n;   //然后把第一个结点变成m，m会随着循环而移动
		}
		m->m_next = nullptr;
	}
	/*ChainList::Status ChainList::createHead(ElemType *datum, ElemType extent)  //写的头插法
	{
	    m_heap->m_data = m_heap->m_data + extent;
	     Node *s = m_heap;
	     for (int i = 0; i < extent; ++i)
	   {
	     Node *p = new Node;
	     p->m_data = datum[i];
	     p->m_next = s->m_next;
	     s->m_next = p;
	   }
	s->m_next = nullptr;
	}*/
	ChainList::ElemType ChainList::insertAt(ElemType i, ElemType elem) //插入元素，  在线性表中第i个位置之前插入新元素elem
	{
		Node *q = m_heap;  //首先把q指针指向头结点
		int j = 1;
		while (q && j < i)  //当q还没有为空时， 当前的位置已经超过了要查找的位置，直接退出循环
		{
			q = q->m_next;
			++j;

		}
		if (!q || j > i)  //q还没有指向空，当当前的位置已经超过了要找的位置，但还是没有找到，就返回错误
		{
			return TT_ERROR;
		}

		Node *s = new Node;
		s->m_data = elem;
		s->m_next = q->m_next;     //将q的后继节点变成s的后继节点
		q->m_next = s;            //将s变成q的后继节点
		++m_heap->m_data;
		return TT_OK;
	}
	ChainList::ElemType ChainList::removeAt(ElemType i, ElemType &elemOut)
	{

		Node *s = m_heap;
		int j = 1;
		while ((s->m_next) && (j < i))
		{                    //当p的后继节点还没有指向空时， 当前的位置已经超过了要查找的位置，直接退出循环
			s = s->m_next;  //s的指针向后移动不断指向下一个节点
			++j;
		}
		if (!(s->m_next) || (j > i))
		{
			return TT_ERROR;
		}
		Node *q = s->m_next;   //将s的后继节点变成q
		s->m_next = q->m_next;    //再把q的后继节点变成s的后继节点
		elemOut = q->m_data;  //将q节点的数据给element
		delete q;   //让系统回收此节点，释放内存
		--m_heap->m_data;
		return TT_OK;
	}
	ChainList::ElemType ChainList::getAt(ElemType i, ElemType &elemOut)
	{
		Node *q = m_heap->m_next;    //让q指向链表的第一个节点
		if (i == 0)  //当查找的位置不合法时，就返回false
		{
			return TT_ERROR;
		}
		int j = 1;  //从一个节点开始循环遍历，就是当前位置
		while (q && j < i)
		{                       /*当q还没有为空时， 当前的位置已经超过了要查找的位置，直接退出循环*/

			q = q->m_next;
			++j;
		}
		if (!q || j < i)   //q还没有指向空，当当前的位置已经超过了要找的位置，但还是没有找到，就返回错误
		{
			return TT_ERROR;
		}
		elemOut = q->m_data;   //取第i个元素的数据
		return TT_OK;
	}
	ChainList::ElemType ChainList::getIndexElemAt(ElemType &i, ElemType elemOut)//在线性表中查找与elem的相等的元素，返回第一个与elem相等元素在线性表中的第几个位置
	{
		Node *p = m_heap->m_next;    //从第一个结点开始遍历
		int searchLocation = 1;
		while (p && (p->m_data != elemOut))  //只要p不为空， 还没有找到元素，循环继续
		{
			++searchLocation;
			p = p->m_next;
		}
		if (!p)
		{
			return TT_ERROR;
		}
		i = searchLocation;
		return TT_OK;
	}
	ChainList::ElemType ChainList::clear()
	{
		Node *m = m_heap->m_next;  //把头节点的后继节点变成m
		while (m != nullptr)   //当还有节点存在时，就循环继续
		{
			Node *n = m->m_next;  //然后把m的后继节点变成n
			delete m;   //删除第一个节点，每循环一次都删除第一个节点
			m = n;  //然后把n变成m， n就变成了第一个节点
		}
		m_heap->m_next = nullptr;   //头结点指向的第一个结点清空
		m_heap->m_data = 0;
		return TT_OK;
	}
	ChainList::Status ChainList::show()
	{
		if (m_heap->m_data == 0)
		{
			cout << "此单链表中没有数据，无法显示！" << "\n" << endl;
		}
		else
		{
			Node *p = m_heap->m_next;
			cout << "输出单链表的所有元素：";
			while (p)
			{
				cout << p->m_data << ",";
				p = p->m_next;

			}
			cout << endl;
		}
	}
	ChainList::ElemType ChainList::destroy()  //单链表销毁
	{
		while (m_heap)
		{
			Node *s = m_heap->m_next;
			delete m_heap;
			m_heap = s;
		}
		m_heap = nullptr;
		return TT_OK;
	}
}

//测试myChainList
void testChainList()
{
	tt::ChainList myChainList;    //创建一个单链表对象


	int myLength(0);    //单链表的整表创建,尾插法
	cout << "想创建多少数据的链表？";
	cin >> myLength;
	int *myDatas = new int[myLength];
	cout << "请依次输入这" << myLength << "个数据，中间以回车符隔开：" << endl;

	for (int i = 0; i < myLength; ++i)
	{

		cin >> myDatas[i];  //输入要存储的数据的值
	}
	myChainList.createTail(myDatas, myLength);   //调用create函数 建立单链表
	myChainList.getLength();
	myChainList.show();
	cout << "\n\n";

	while (true)
	{
		{
			cout << "*************************************************************" << endl
				<< "*******************   单链表的基本功能展示   *******************" << endl
				<< "*****************************************************************" << endl
				<< "********************   选择1——数据插入.   **********************" << endl
				<< "********************   选择2——数据删除.   **********************" << endl
				<< "********************   选择3——获取元素.   **********************" << endl
				<< "********************   选择4——查找元素.   **********************" << endl
				<< "********************   选择5——是否为空.   **********************" << endl
				<< "********************   选择6——获取线性表的长度.   **********************" << endl
				<< "********************   选择7——清空元素.   **********************" << endl
				<< "********************   选择8——输出所有元素. ************************" << endl
				<< "********************   选择9——销毁单链表. ************************" << endl
				<< "********************   选择10——清屏！      ************************" << endl
				<< "********************   选择0——退出程序！   ************************" << endl
				<< "***********************************************************************" << endl
				<< "***********************************************************************" << endl;
		}
		cout << "\n********************   请输入你想要使用的单链表功能的序号   ***************" << endl;
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
			int pushDatas(0);  //要插入的元素
			int indexLocition(0);  //要插入的位置
			cout << "请输入你想要插入的元素位置：";
			cin >> indexLocition;
			cout << "请输入你想要插入的元素：";
			cin >> pushDatas;
			if (myChainList.insertAt(indexLocition, pushDatas))
			{
				cout << "数据" << pushDatas << "插入成功！" << "\n" << endl;
				myChainList.getLength();
				myChainList.show();
			}
			else
				cout << "数据" << pushDatas << "插入失败！可能是单链表尚未建立" << endl;
			break;
		}
		case 2:
		{
			int popLocation(0);
			int popElement(0);
			cout << "请输入要删除数据第几个位置：";
			cin >> popLocation;
			if (myChainList.removeAt(popLocation, popElement))
			{
				cout << "数据" << popElement << "删除成功！" << endl;
				myChainList.getLength();
				myChainList.show();
			}
			else
				cout << "数据" << popElement << "删除失败！" << endl;
			break;
		}
		case 3:
		{
			int getElem(0);        //要获取的元素
			int indexLocition(0);
			cout << "请输入你想要获取元素的位置：";
			cin >> indexLocition;
			if (myChainList.getAt(indexLocition, getElem))
			{
				cout << "获取的元素为：" << getElem << "\n" << endl;
				myChainList.getLength();
				myChainList.show();
			}
			else
			{
				cout << "当前单链表为空或者尚未建立，数据" << getElem << "获取失败！" << endl;
				myChainList.getLength();
			}
			break;
		}
		case 4:
		{
			int findElement(0);   //查找元素
			int findLocation(0);
			cout << "请输入要查找的元素：";
			cin >> findElement;
			if (myChainList.getIndexElemAt(findLocation, findElement))
			{
				cout << "找到了元素" << findElement << "，其在表中的索引值为：" << findLocation << "\n" << endl;
				myChainList.getLength();
				myChainList.show();
			}
			else
			{
				cout << "链表中不存在所需找的值！" << "\n" << endl;
				myChainList.getLength();
				myChainList.show();
			}
			break;
		}
		case 5:
			if (myChainList.isEmpty())   //判断是否为空
			{
				cout << "目前该线性表为空！" << endl;
				myChainList.getLength();
			}
			else
			{
				cout << "目前顺序表非空！" << endl;
				myChainList.getLength();
				myChainList.show();
			}
			break;
		case 6:
		{
			myChainList.getLength();
			myChainList.show();
			break;
		}
		case 7:
			if (myChainList.clear())  //清空单链表
			{
				cout << "目前单链表已经被清空！" << endl;
				myChainList.getLength();
			}
			else
			{
				cout << "目前单链表非空！" << endl;
				myChainList.getLength();
				myChainList.show();
			}
			break;
		case 8:
			myChainList.show();  //显示所有元素
			myChainList.getLength();
			break;
		case 9:
		{                                                //销毁单链表
			cout << "你确定要销毁该单链表吗？(若销毁请输入输入(Y/y))";
			char yesOrNo;
			cin >> yesOrNo;
			if ((yesOrNo == 'Y') || (yesOrNo == 'y'))
			{
				if (myChainList.destroy())
				{
					cout << "单链表已被销毁." << "\n" << endl;
				}
				else
					cout << "单链表销毁失败." << "\n" << endl;
			}
			break;
		}
		case 10:
			system("cls");
			cout << "屏幕已经清屏，可以重新输入!" << "\n" << endl;
			break;
		default:
			cout << "输入的序号不正确，请重新输入!" << "\n" << endl;
		}

	}
	delete[] myDatas;
	myDatas = nullptr;
}
int main()
{
	testChainList();
	system("pause");
	return 0;
}