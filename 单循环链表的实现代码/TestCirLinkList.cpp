#include"CirLinkList.h"

namespace tt
{
	CirLinkList::CirLinkList()
	{
		m_heap = new Node;
		if (!m_heap)
		{
			cout << "错误！内存分配失败！" << endl;
			system("pause");
			exit(0);
		}
		m_heap->m_next = m_heap;  //这里做个解释，m_heap并不是头结点，m_heap是最后一个结点的指针，m_heap->m_next才是头结点，
		cout << "\n********************单向的循环列表初始化成功！************************" << endl;
	}
	CirLinkList::~CirLinkList()
	{
		this->destroy();
	}
	CirLinkList::Status CirLinkList::createTail(ElemType *datas, ElemType length)
	{
		for (int i = 0; i < length; ++i)
		{                    //m_heap即所设置的尾指针，p即程序中遍历整个链表的指针。
			Node *p = new Node;
			p->m_data = datas[i];
			                       //直接将p结点插入在尾结点后成为新的尾结点即可。
			p->m_next = m_heap->m_next;
			m_heap = m_heap->m_next = p;
		}
	}
	CirLinkList::ElemType CirLinkList::priorElemAt(int cur_e, int &pri_e)
	{                                 //若cur_e是链表的数据元素，且不是第一个，则用pre_e返回它的前驱

			/*Node *p = m_heap->m_next->m_next;  //p指向链表第一个元素
			 while (p != m_heap->m_next)
			{
				Node *q= p->m_next;   //q指向p的后继
			    if (q != m_heap->m_next && q->m_data == cur_e)
			   {
					pri_e = p->m_data;
				    return TT_OK;
			   }
				 p = q;
			}
			  return TT_ERROR;*/

		Node *p = m_heap->m_next->m_next; //p指向第一个结点
		Node *q = p->m_next;
		while (q != m_heap->m_next)
		{
			if (q->m_data == cur_e)
			{
				pri_e = p->m_data;
				return TT_OK;
			}
			p = q;
			q = q->m_next;
		}
		return TT_ERROR;
	}
	CirLinkList::ElemType CirLinkList::nextElemAt(int cur_e, int &Nex_e)
	{                                   //若cur_e是链表的数据元素,且不是最后一个,则用next_e返回它的后继
			/*Node *p =m_heap->m_next->m_next;  //p指向第一个结点
			 while (p != m_heap->m_next)
			{
				if (p->m_data == cur_e)
			    {
					Nex_e = p->m_next->m_data;
					return TT_OK;
		        }
			        p= p->m_next;
			}
				return TT_ERROR;*/

		Node *p = m_heap->m_next->m_next;  //p指向第一个结点
		while (p != m_heap->m_next)  //p还没到头结点
		{
			Node *q = p->m_next; //第一次循环，q是第二个元素
			if (q != m_heap->m_next && p->m_data == cur_e)  
			{
				Nex_e = q->m_data;
				return TT_OK;
			}
			p = q;
		}
		return TT_ERROR;
	}
	CirLinkList::ElemType CirLinkList::insertAt(ElemType i, ElemType elem)
	{
		Node *p = m_heap->m_next;    //p指向表头
		if ((i < 1) || (i > getLength() + 1))   //i位置不合理时，返回false
		{
			return TT_ERROR;
		}
		int j = 1;
		while (j < i)   //当j小于i时  就继续
		{
			p = p->m_next;
			++j;
		}
		Node *s = new Node;
		s->m_data = elem;
		s->m_next = p->m_next;
		p->m_next = s;
		if (p == m_heap)  //在表尾插入改变尾指针
		{
			m_heap = s;
		}
		return TT_OK;
	}
	CirLinkList::ElemType CirLinkList::removeAt(ElemType i, ElemType &elemOut)
	{
		Node *p = m_heap->m_next;   //p指向表头
		if ((i < 1) || (i > getLength()))   //判断删除位置是否合理
		{
			return TT_ERROR;
		}
		int j = 1;
		while (j < i)
		{
			p = p->m_next;
			++j;
		}
		Node *q = p->m_next;    //q指向待删除结点 
		p->m_next = q->m_next;
		elemOut = q->m_data;    //这句放在前面也是可以的，但是需要修改一下判断条件， 放在前面不需要声明一个临时节点q
		if (m_heap == q) //删除的是表尾元素，表尾指针发生改变
		{
			m_heap = p;
		}
		delete q;
		return TT_OK;
	}
	CirLinkList::ElemType CirLinkList::getIndexElemAt(ElemType &i, ElemType elemOut)
	{
		Node *p = m_heap->m_next->m_next;    //从第一个结点开始遍历
		int searchLocate = 1;
		while ((p != m_heap->m_next) && (p->m_data != elemOut)) //p未到表头时
		{
			++searchLocate;
			p = p->m_next;
		}
		if (!(p != m_heap->m_next))
		{
			return TT_ERROR;
		}
		i = searchLocate;
		return TT_OK;
	}
	CirLinkList::ElemType CirLinkList::getAt(ElemType i, ElemType &elemOut)
	{
		Node *q = m_heap->m_next->m_next;    //让q指向链表的第一个节点

		if ((i < 1) || (i > getLength()))
		{
			return TT_ERROR;
		}
		int j = 1;
		while ((j < i))
		{

			q = q->m_next;
			++j;
		}
		elemOut = q->m_data;   //取第i个元素的数据
		return TT_OK;
	}
	CirLinkList::Status CirLinkList::show()
	{
		if (m_heap->m_next == m_heap)
		{
			cout << "当前的链表没有元素，无法显示！" << endl;
		}
		else
		{
			Node *p = m_heap->m_next->m_next;   //p指向第一个结点
			int temp(0);  //用来显示链表中的个数
			cout << "输出单向循环链表中的所有元素：";
			while (p != m_heap->m_next)  //p未到表头
			{
				++temp;
				cout << (p->m_data) << " ";
				p = p->m_next;
			}
			cout << "\n当前循环链表中的元数个数为：" << temp << endl;
		}
	}

	CirLinkList::ElemType CirLinkList::getLength()const
	{
		Node *p = m_heap->m_next->m_next;   //p指向第一个结点
		int i = 0;
		while (p != m_heap->m_next) //p未到表头时
		{
			p = p->m_next;
			++i;
		}
		return i;
	}
	CirLinkList::ElemType CirLinkList::clear()
	{
		m_heap = m_heap->m_next;       //先把尾指针指向头结点，不然释放最后一个结点时尾指针，无法指向头结点 
		Node *p = m_heap->m_next;   //p指向第一个结点
		while (p != m_heap)   //p不等于表头时
		{
			Node *q = p->m_next;
			delete p;
			p = q;
		}
		m_heap->m_next = m_heap; //头结点指针域指向其本身
		return TT_OK;
	}
	CirLinkList::ElemType CirLinkList::destroy()
	{
		this->clear();  //去调用clear()函数，  清空所有元素， 在次函数中，因为只剩下一个m_heap，  所以直接下面直接释放m_heap
		delete m_heap;
		m_heap = nullptr;
		return TT_OK;
	}
}

//测试单向循环链表
void testMyCirLinkList()
{
	tt::CirLinkList myCirLinkList;

	int myLength(0);    //单链表的整表创建,尾插法
	cout << "想创建多少数据的链表？";
	cin >> myLength;
	int *myDatas = new int[myLength];
	cout << "请依次输入这" << myLength << "个数据，中间以回车符隔开：" << endl;

	for (int i = 0; i < myLength; ++i)
	{

		cin >> myDatas[i];  //输入要存储的数据的值
	}
	myCirLinkList.createTail(myDatas, myLength);   //调用createTail函数 建立单链表
	myCirLinkList.show();

	while (true)
	{
		{
			cout << "\n*************************************************************" << endl
				<< "*******************   单向循环链表的基本功能展示   *******************" << endl
				<< "*****************************************************************" << endl
				<< "********************   选择1——数据插入.   **********************" << endl
				<< "********************   选择2——数据删除.   **********************" << endl
				<< "********************   选择3——获取元素.   **********************" << endl
				<< "********************   选择4——查找元素.   **********************" << endl
				<< "********************   选择5——是否为空.   **********************" << endl
				<< "********************   选择6——获取链表长度.   **********************" << endl
				<< "********************   选择7——清空元素.   **********************" << endl
				<< "********************   选择8——输出所有元素. ************************" << endl
				<< "********************   选择9——销毁链表. ************************" << endl
				<< "*********************  选择10——获得元素的前驱.  *****************" << endl
				<< "*********************  选择11——获得元素的后继.  *****************" << endl
				<< "********************   选择12——清屏！      ************************" << endl
				<< "********************   选择0——退出程序！   ************************" << endl
				<< "***********************************************************************" << endl
				<< "***********************************************************************" << endl;
		}
		cout << "\n********************   请输入你想要使用的循环链表功能的序号   ***************" << endl;
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
		{                                 //插入元素
			int pushLocate(0);
			int pushElement;
			cout << "请输入想添加元素的位置：";
			cin >> pushLocate;
			cout << "请输入想添加的元素：";
			cin >> pushElement;
			if (myCirLinkList.insertAt(pushLocate, pushElement))
			{
				cout << "数据" << pushElement << "插入成功！" << endl;
				myCirLinkList.show();
			}
			else
				cout << "插入的位置不合理，数据" << pushElement << "插入失败！" << endl;
			break;
		}
		case 2:
		{                                                //删除元素
			int cancelElem(0);  //要删除的元素
			int cancelLocate(0);  //要删除的位置
			cout << "请输入想要删除的位置：";
			cin >> cancelLocate;
			if (myCirLinkList.removeAt(cancelLocate, cancelElem))
			{
				cout << "数据" << cancelElem << "删除成功！" << endl;
				myCirLinkList.show();
			}
			else
				cout << "删除的位置不合理或者链表中没有元素，数据删除失败！" << endl;
			break;
		}
		case 3:                                   //获取元素
		{
			int getLocate(0);
			int getElem(0);
			cout << "请输入想要获取的位置：";
			cin >> getLocate;
			if (myCirLinkList.getAt(getLocate, getElem))
			{
				cout << "获取的元素为：" << getElem << endl;
				myCirLinkList.show();
			}
			else
			{
				cout << "获取的位置不合理或者链表中没有元素，获取数据失败！" << endl;
				myCirLinkList.getLength();
			}
			break;
		}
		case 4:
		{                                             //查找元素
			int getLocate(0);
			int findElem(0);
			cout << "请输入你想要查找的元素的值：";
			cin >> findElem;
			if (myCirLinkList.getIndexElemAt(getLocate, findElem))
			{
				cout << "找到了元素" << findElem << "，其在表中的索引值为：" << getLocate << "\n" << endl;
				myCirLinkList.show();
			}
			else
			{
				cout << "链表中不存在所需找的值！" << "\n" << endl;
				myCirLinkList.show();
			}
			break;
		}
		case 5:
			if (myCirLinkList.isEmpty())
			{
				cout << "当前循环链表为空！" << endl;
				myCirLinkList.getLength();
			}
			else
			{
				cout << "当前的循环链表非空！" << endl;
				myCirLinkList.show();
			}
			break;
		case 6:
		{                                         //获取长度
			int temp = myCirLinkList.getLength();
			cout << "循环链表当前的长度为：" << temp << endl;
			break;
		}
		case 7:
			if (myCirLinkList.clear())
			{
				cout << "循环链表已被清空！" << endl;
				myCirLinkList.show();
			}
			else
			{
				cout << "循环链表清空失败！" << endl;
				myCirLinkList.show();
			}
			break;
		case 8:
			myCirLinkList.show();
			break;
		case 9:
		{
			cout << "你确定要销毁该单链表吗？(若销毁请输入输入(Y/y))";
			char yesOrNo;
			cin >> yesOrNo;
			if ((yesOrNo == 'Y') || (yesOrNo == 'y'))
			{
				if (myCirLinkList.destroy())
				{
					cout << "单链表已被销毁." << "\n" << endl;
				}
				else
					cout << "单链表销毁失败." << "\n" << endl;
			}
			break;
		}
		case 10:
		{
			int frontElem(0);
			int getElem(0); //返回的是要获得哪一个元素的前驱的元素
			cout << "输入你想要获得哪一个元素的前驱？（注意：不能获取第一个元素的）：";
			cin >> frontElem;
			if (myCirLinkList.priorElemAt(frontElem, getElem))
			{
				cout << "数据元素" << frontElem << "的，前驱元素是：" << getElem << endl;
			}
			else
				cout << "获取前驱元素失败，不能获取第一个元素的前驱或者链表中没有你输入的元素！" << endl;
			break;
		}
		case 11:
		{
			int rearElem(0);
			int getElem(0);
			cout << "输入你想要获得哪一个元素的后继？（注意：不能获取最后一个元素的）：";
			cin >> rearElem;
			if (myCirLinkList.nextElemAt(rearElem, getElem))
			{
				cout << "数据元素" << rearElem << "的，后继元素是：" << getElem << endl;
			}
			else
				cout << "获取后继元素失败！不能获取最后一个元素的后继或者链表中没有你输入的元素！" << endl;
			break;
		}
		case 12:
			system("cls");
			cout << "屏幕已经清屏，可以重新输入!" << "\n" << endl;
			break;
		default:
			cout << "输入的序号不正确，请重新输入!" << "\n" << endl;
		}
	}
	delete[]myDatas;
	myDatas = nullptr;
}
int main()
{
	testMyCirLinkList();
	system("pause");
	return 0;
}