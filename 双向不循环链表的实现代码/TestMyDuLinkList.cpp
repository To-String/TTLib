#include"MyDuLinkList.h"

namespace tt
{
	DuLinkList::DuLinkList()
	{
		m_heap = new DulNode;
		if (!m_heap)
		{
			cout << "建立头结点时，初始化分配内存失败！" << endl;
			system("pause");
			exit(0);
		}
		m_heap->m_next = nullptr;
		m_heap->m_prior = nullptr;
		m_tail = m_heap;
		cout << "***********************   双向不循环链表初始化成功  ***********************" << endl;
	}
	DuLinkList::~DuLinkList()
	{
		this->destroy();
	}
	DuLinkList::Status DuLinkList::createTail(ElemType *datas, ElemType length)//创建长度为length的链表，数据通过数组指定，这里采用尾插法
	{
		DulNode *m = m_heap;
		for (int i = 0; i < length; ++i)
		{
			DulNode *p = new DulNode;
			if (!p)
			{
				cout << "错误，无法分配内存，创建链表失败！" << endl;
				system("pause");
				exit(0);
			}
			p->m_data = datas[i];

			m->m_next = p;   //首先建立第一个节点的时候，头结点的后继节点是p
			p->m_prior = m;   //p的前驱节点是头结点
			m_tail = m = p;  //最后把第一个节点变成m，m_tail是指向最后一个元素的指针  就这样按以上步骤循环
		}
		m->m_next = nullptr; //最好是加上这句，  表示当前的链表创建结束
	}
	DuLinkList::ElemType DuLinkList::insertAt(ElemType i, ElemType elem)
	{
		DulNode *p = m_heap;

		if ((i < 1) || (i > getLength() + 1))  //插入的位置不合理时，返回false
		{
			return TT_ERROR;
		}
		int j = 1;
		while ((p) && (j < i))
		{
			p = p->m_next;
			++j;
		}
		if ((!p) || (j > i))
		{
			return TT_ERROR;
		}
		DulNode *s = new DulNode;
		if (p != m_tail)  //假如插入的不在表尾
		{
			s->m_data = elem;     //把要存储的数据放入数据域中
			s->m_prior = p;         //首先把p变成s的前驱结点
			s->m_next = p->m_next;   //在p的后继节点变成s的后继节点
			p->m_next->m_prior = s;   //把s变成p的后继节点的前驱
			p->m_next = s;   //p的后继节点是s
		}
		else
		{
			pushBack(elem);
			/*s->m_data = elem;
			m_tail->m_next = s;
			s->m_prior = m_tail;
			m_tail = s;
			s->m_next = nullptr;  //一定要添加这句，否则出错，表示最后一个元素的后继为空*/
		}
		return TT_OK;
	}
	DuLinkList::ElemType DuLinkList::removeAt(ElemType i, ElemType &elemOut)
	{
		DulNode *p = m_heap;

		if ((i < 1) || (i > getLength()))
		{
			return TT_ERROR;
		}
		int j = 1; //q所指结点有后继, 当前位置j还没有大于等于就循环继续
		while ((p) && (j <= i))
		{
			p = p->m_next;
			j++;
		}
		if (!(p) || (j < i))   //当前的位置j超过了要查找的位置i，返回错误
		{
			return TT_ERROR;
		}
		if (p != m_tail)   //假如删除的不是表尾
		{
			elemOut = p->m_data;
			p->m_prior->m_next = p->m_next;  //把p的后继节点变成p的前驱结点的后继节点
			p->m_next->m_prior = p->m_prior;   //把p的前驱结点变成p的后继节点的前驱结点

			delete p;  //释放节点的内存
		}
		else
		{
			popBack(elemOut);
			/*elemOut = p->m_data;
			m_tail = p->m_prior;   // 然后 在把倒数第二个元素变成m_tail指针
			p->m_prior->m_next = nullptr;  //在把倒数第二个元素的后继为null*/
		}
		return TT_OK;
	}
	DuLinkList::ElemType DuLinkList::getAt(ElemType i, ElemType &elemOut)
	{
		DulNode *p = m_heap->m_next;  //指向第一个节点

		if ((i < 1) || (i > getLength()))
		{
			return TT_ERROR;
		}
		int j = 1;
		while ((p) && (j < i))
		{
			p = p->m_next;
			++j;
		}
		if ((!p) || (j > i))
		{
			return TT_ERROR;
		}
		elemOut = p->m_data;

		return TT_OK;
	}

	DuLinkList::ElemType DuLinkList::getIndexElemAt(ElemType &i, ElemType elemOut)//查找与elem相等的元素，返回第一个与elem相等元素在链表中的序号
	{
		DulNode *s = m_heap->m_next;
		int searchLocate = 1;
		while (s && (s->m_data != elemOut))
		{
			++searchLocate;
			s = s->m_next;
		}
		if (!s)
		{
			return TT_ERROR;
		}
		i = searchLocate;

		return TT_OK;
	}
	DuLinkList::ElemType DuLinkList::clear()
	{
		DulNode *s = m_heap->m_next;
		while (s)
		{
			DulNode *m = s->m_next;
			delete s;
			s = m;
		}
		m_heap->m_next = m_heap->m_prior = nullptr;
		m_tail = m_heap;
		return TT_OK;
	}
	DuLinkList::ElemType DuLinkList::destroy()
	{
		while (m_heap)
		{
			DulNode *s = m_heap->m_next;
			delete m_heap;
			m_heap = s;
		}
		m_tail = m_heap = nullptr;
		return TT_OK;
	}
	DuLinkList::Status DuLinkList::show()
	{
		if (isEmpty())
		{
			cout << "当前链表中没有元素，无法显示！" << endl;
		}
		else
		{
			DulNode *p = m_heap->m_next;   //p指向第一个结点
			int temp(0);  //用来显示链表中的个数
			cout << "输出双向不循环链表中的所有元素：";
			while (p)
			{
				++temp;
				cout << (p->m_data) << " ";
				p = p->m_next;
			}
			cout << "\n当前双向不循环链表中的元数个数为：" << temp << endl;
		}
	}
	DuLinkList::Status DuLinkList::traverseBack()
	{
		if (isEmpty())
		{
			cout << "当前链表中没有元素，无法显示！" << endl;
		}
		else
		{
			DulNode *p = m_tail;
			cout << "逆序输出链表中的所有元素：";
			while (p != m_heap)
			{
				cout << (p->m_data) << " ";
				p = p->m_prior;
			}
			cout << endl;
		}
	}
	DuLinkList::ElemType DuLinkList::priorElemAt(ElemType cur_e, ElemType &pri_e)//若cur_e是链表的数据元素，且不是第一个，则用pre_e返回它的前驱
	{
		DulNode *q = m_heap->m_next->m_next;  //指向第二个元素-
		while (q)
		{
			if (q->m_data == cur_e)
			{
				pri_e = q->m_prior->m_data;
				return TT_OK;
			}
			q = q->m_next;
		}
		return TT_ERROR;
	}
	DuLinkList::ElemType DuLinkList::nextElemAt(ElemType cur_e, ElemType &Nex_e) //若cur_e是链表的数据元素,且不是最后一个,则用next_e返回它的后继，
	{
		DulNode *p = m_heap->m_next->m_next;   //指向第二个元素， 如果指向第一个元素的话，获得最后一个元素的后继，就会输出垃圾值
		while (p)
		{
			if (p->m_prior->m_data == cur_e)
			{
				Nex_e = p->m_data;         //将p所指结点的值赋给Nex_e，Nex_e保存返回
				return TT_OK;
			}
			p = p->m_next;
		}
		return TT_ERROR;
	}
	DuLinkList::ElemType DuLinkList::pushBack(const ElemType &elem)  //尾插
	{
		DulNode *s = new DulNode;
		if (m_heap != m_tail)     //假如插入的不是第一个节点，插入的是第n个元素的表尾
		{
			s->m_data = elem;
			m_tail->m_next = s;
			s->m_prior = m_tail;
			m_tail = s;
			s->m_next = nullptr;  //一定要添加这句，否则出错，表示最后一个元素的后继为空
		}
		else
		{
			s->m_data = elem;
			m_heap->m_next = s;
			s->m_prior = m_heap;
			m_tail = s;
			s->m_next = nullptr;
		}
		return TT_OK;
	}
	DuLinkList::ElemType DuLinkList::popBack(ElemType &elemOut) //尾删
	{
		if (isEmpty())
		{
			return TT_ERROR;
		}
		DulNode *p = m_tail;
		elemOut = p->m_data;
		m_tail = p->m_prior;   // 然后 在把倒数第二个元素变成m_tail指针
		p->m_prior->m_next = nullptr;  //在把倒数第二个元素的后继为null
		delete p;
		return TT_OK;
	}
	DuLinkList::ElemType DuLinkList::pushFront(const ElemType &elem)  //头插
	{
		DulNode *m = new DulNode;
		if (m_tail != m_heap)  //插入的不是第一个结点
		{
			m->m_data = elem;
			m->m_prior = m_heap;
			m->m_next = m_heap->m_next;
			m_heap->m_next->m_prior = m;
			m_heap->m_next = m;
		}
		else
		{
			pushBack(elem);
		}
		return TT_OK;
	}
	DuLinkList::ElemType DuLinkList::popFront(ElemType &elemOut)  //头删
	{
		if (isEmpty())
		{
			return TT_ERROR;
		}
		DulNode *s = m_heap->m_next;
		if (m_heap != m_tail)     //假如删除的不是第一个元素
		{
			elemOut = s->m_data;
			m_heap->m_next = s->m_next;
			s->m_next->m_prior = m_heap;
			delete s;
		}
		else
		{
			popBack(elemOut);
		}
		return TT_OK;
	}
	DuLinkList::ElemType DuLinkList::getLength()
	{
		DulNode *p = m_heap->m_next;   //p指向第一个结点
		int i = 0;
		while (p)
		{
			p = p->m_next;
			++i;

		}
		return i;
	}
}

// 测试函数
void testMyDuLinkList()
{
	tt::DuLinkList  MyDuLinkList;

	int myLength(0);    //链表的整表创建,尾插法
	cout << "想创建多少数据的链表？";
	cin >> myLength;
	int *myDatas = new int[myLength];
	cout << "请依次输入这" << myLength << "个数据，中间以回车符隔开：" << endl;

	for (int i = 0; i < myLength; ++i)
	{

		cin >> myDatas[i];  //输入要存储的数据的值
	}
	MyDuLinkList.createTail(myDatas, myLength);   //调用createTail函数 建立链表
	MyDuLinkList.show();

	while (true)
	{
		{
			cout << "\n*******************************************************************" << endl
				<< "*******************   双向不循环链表基本功能展示   *******************" << endl
				<< "*******************************************************************" << endl
				<< "********************   选择1——数据插入.   **********************" << endl
				<< "********************   选择2——数据删除.   **********************" << endl
				<< "********************   选择3——获取元素.   **********************" << endl
				<< "********************   选择4——查找元素.   **********************" << endl
				<< "********************   选择5——是否为空.   **********************" << endl
				<< "*******************************************************************" << endl
				<< "********************   选择6——获取链表长度.   **********************" << endl
				<< "********************   选择7——清空元素.   **********************" << endl
				<< "********************   选择8——输出所有元素. ************************" << endl
				<< "********************   选择9——销毁链表. ************************" << endl
				<< "*********************  选择10——获得元素的前驱.  *****************" << endl
				<< "*******************************************************************" << endl
				<< "*********************  选择11——获得元素的后继.  *****************" << endl
				<< "*********************  选择12——逆序输出所有元素.  *****************" << endl
				<< "*********************  选择13——链表尾插元素.  *****************" << endl
				<< "*********************  选择14——链表尾删元素.  *****************" << endl
				<< "*******************************************************************" << endl
				<< "*********************  选择15——链表头插元素.  *****************" << endl
				<< "*********************  选择16——链表头删元素.  *****************" << endl
				<< "*******************************************************************" << endl
				<< "********************   选择17——清屏！      ************************" << endl
				<< "********************   选择0——退出程序！   ************************" << endl
				<< "***********************************************************************" << endl
				<< "***********************************************************************" << endl;
		}
		cout << "\n*******************   请输入你想要使用的双向循环链表功能的序号  ***************" << endl;
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
			if (MyDuLinkList.insertAt(pushLocate, pushElement))
			{
				cout << "数据" << pushElement << "插入成功！" << endl;
				MyDuLinkList.show();
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
			if (MyDuLinkList.removeAt(cancelLocate, cancelElem))
			{
				cout << "数据" << cancelElem << "删除成功！" << endl;
				MyDuLinkList.show();
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
			if (MyDuLinkList.getAt(getLocate, getElem))
			{
				cout << "获取的元素为：" << getElem << endl;
				MyDuLinkList.show();
			}
			else
			{
				cout << "获取的位置不合理或者链表中没有元素，获取数据失败！" << endl;
				MyDuLinkList.getLength();
			}
			break;
		}
		case 4:
		{                                             //查找元素
			int getLocate(0);
			int findElem(0);
			cout << "请输入你想要查找的元素的值：";
			cin >> findElem;
			if (MyDuLinkList.getIndexElemAt(getLocate, findElem))
			{
				cout << "找到了元素" << findElem << "，其在表中的索引值为：" << getLocate << "\n" << endl;
				MyDuLinkList.show();
			}
			else
			{
				cout << "链表中不存在所需找的值！" << "\n" << endl;
				MyDuLinkList.show();
			}
			break;
		}
		case 5:
			if (MyDuLinkList.isEmpty())
			{
				cout << "当前循环链表为空！" << endl;
				MyDuLinkList.getLength();
			}
			else
			{
				cout << "当前的链表非空！" << endl;
				MyDuLinkList.show();
			}
			break;
		case 6:
		{                                         //获取长度
			cout << "双向不循环链表当前的长度为：" << MyDuLinkList.getLength() << endl;
			break;
		}
		case 7:
			if (MyDuLinkList.clear())
			{
				cout << "双向不循环链表已被清空！" << endl;
				MyDuLinkList.show();
			}
			else
			{
				cout << "双向不循环链表清空失败！" << endl;
				MyDuLinkList.show();
			}
			break;
		case 8:
			MyDuLinkList.show();
			break;
		case 9:
		{
			cout << "你确定要销毁该双向不循环链表吗？(若销毁请输入输入(Y/y))";
			char yesOrNo;
			cin >> yesOrNo;
			if ((yesOrNo == 'Y') || (yesOrNo == 'y'))
			{
				if (MyDuLinkList.destroy())
				{
					cout << "双向不循环链表已被销毁." << "\n" << endl;
				}
				else
					cout << "双向不循环链表销毁失败." << "\n" << endl;
			}
			break;
		}
		case 10:
		{
			int frontElem(0);
			int getElem(0); //返回的是要获得哪一个元素的前驱的元素
			cout << "输入你想要获得哪一个元素的前驱？（注意：不能获取第一个元素的）：";
			cin >> frontElem;
			if (MyDuLinkList.priorElemAt(frontElem, getElem))
			{
				cout << "数据元素" << frontElem << "的，前驱元素是：" << getElem << endl;
				MyDuLinkList.show();
			}
			else
			{
				cout << "获取前驱元素失败，不能获取第一个元素的前驱或者链表中没有你输入的元素！" << endl;
				MyDuLinkList.show();
			}
			break;
		}
		case 11:
		{
			int rearElem(0);
			int getElem(0);
			cout << "输入你想要获得哪一个元素的后继？（注意：不能获取最后一个元素的）：";
			cin >> rearElem;
			if (MyDuLinkList.nextElemAt(rearElem, getElem))
			{
				cout << "数据元素" << rearElem << "的，后继元素是：" << getElem << endl;
				MyDuLinkList.show();
			}
			else
			{
				cout << "获取后继元素失败！不能获取最后一个元素的后继或者链表中没有你输入的元素！" << endl;
				MyDuLinkList.show();
			}
			break;
		}
		case 12:
			MyDuLinkList.traverseBack();
			break;
		case 13:
		{
			int addBackElem(0);
			cout << "请输入你想要在尾部插入的元素的值：";
			cin >> addBackElem;
			if (MyDuLinkList.pushBack(addBackElem))
			{
				cout << "数据" << addBackElem << "在尾部添加成功！" << endl;
				MyDuLinkList.show();
			}
			else
				cout << "数据" << addBackElem << "在尾部添加失败！" << endl;
			break;
		}
		case 14:
		{
			int cancelBackElem(0);
			if (MyDuLinkList.popBack(cancelBackElem))
			{
				cout << "表尾数据" << cancelBackElem << "删除成功！" << endl;
				MyDuLinkList.show();
			}
			else
				cout << "表尾数据" << cancelBackElem << "删除失败,可能是链表中没有元素！" << endl;
			break;
		}
		case 15:
		{
			int addFirstElem(0);
			cout << "请输入你想要在头部插入的元素的值：";
			cin >> addFirstElem;
			if (MyDuLinkList.pushFront(addFirstElem))
			{
				cout << "数据" << addFirstElem << "在头部添加成功！" << endl;
				MyDuLinkList.show();
			}
			else
				cout << "数据" << addFirstElem << "在头部添加失败！" << endl;
			break;
		}
		case 16:
		{
			int cancelFirstElem(0);
			if (MyDuLinkList.popFront(cancelFirstElem))
			{
				cout << "表头数据" << cancelFirstElem << "删除成功！" << endl;
				MyDuLinkList.show();
			}
			else
				cout << "表头数据" << cancelFirstElem << "删除失败，可能是链表中没有元素！" << endl;
			break;
		}
		case 17:
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
	testMyDuLinkList();
	system("pause");
	return 0;
}