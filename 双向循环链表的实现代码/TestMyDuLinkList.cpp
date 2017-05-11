#include"MyDuLinkList.h"

namespace tt
{
	DuLinkList::DuLinkList()
	{
		m_heap = new DulNode;
		if (!m_heap)
		{
			cout << "错误，内存分配失败！" << endl;
			system("pause");
			exit(0);
		}
		m_heap->m_next = m_heap;
		m_heap->m_prior = m_heap;
		cout << "\n********************双向的循环链表初始化成功！************************" << endl;
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
			p->m_next = m_heap;  //然后第一个节点的后继变成头结点
			m_heap->m_prior = p;  //那么头结点的前驱变成p，   这样就会形成一个首尾相接的双向循环链表
			m = p;  //最后把第一个节点变成m，  就这样按以上步骤循环
		}
	}
	DuLinkList::ElemType DuLinkList::insertAt(ElemType i, ElemType elem)
	{
		DulNode *p = m_heap;  //p指向头结点
		if ((i < 1) || (i > getLength() + 1))
		{
			return TT_ERROR;
		}
		int j = 1;
		while (j < i)
		{
			p = p->m_next;
			++j;
		}
		DulNode *s = new DulNode;
		s->m_data = elem;     //把要存储的数据放入数据域中
		s->m_prior = p;         //首先把p变成s的前驱结点
		s->m_next = p->m_next;   //在p的后继节点变成s的后继节点
		p->m_next->m_prior = s;   //把s变成p的后继节点的前驱
		p->m_next = s;   //p的后继节点是s

		return TT_OK;
	}
	DuLinkList::ElemType DuLinkList::removeAt(ElemType i, ElemType &elemOut)
	{
		DulNode *p = m_heap;  //p指向头结点
		if ((i < 1) || (i >getLength()))
		{
			return TT_ERROR;
		}
		int j = 1;
		while (j <= i)
		{
			p = p->m_next;
			j++;
		}
		elemOut = p->m_data;
		p->m_prior->m_next = p->m_next;  //把p的后继节点变成p的前驱结点的后继节点
		p->m_next->m_prior = p->m_prior;   //把p的前驱结点变成p的后继节点的前驱结点
		delete p;  //释放节点的内存
		return TT_OK;
	}
	DuLinkList::ElemType DuLinkList::getAt(ElemType i, ElemType &elemOut)
	{
		DulNode *q = m_heap->m_next;    //让q指向链表的第一个节点
		if ((i < 1) || (i >getLength()))  // 判断i的位置是否超过链表的长度
		{
			return TT_ERROR;
		}
		int j = 1;
		while ((q != m_heap) && (j < i))  //如果q的后继不是m_heap，  当前位置j=1小于要查找的位置，循环继续
		{                               //删除第一个元素时，退出循环

			q = q->m_next;
			++j;
		}
		if (!(q != m_heap) || (j > i))   //删除第一个元素时，  j并没有比i大， q的后继不是m_heap取逆，  直接退出循环
		{
			return TT_ERROR;
		}
		elemOut = q->m_data;
		return TT_OK;
	}
	DuLinkList::ElemType DuLinkList::getIndexElemAt(ElemType &i, ElemType elemOut)  //查找与elem相等的元素，返回第一个与elem相等元素在链表中的序号
	{
		DulNode *p = m_heap->m_next;    //从第一个结点开始遍历
		int searchLocate = 1;
		while ((p != m_heap) && (p->m_data != elemOut)) //p未到表头时，  p的指针域不等于要查找的元素
		{
			++searchLocate;
			p = p->m_next;
		}
		if (!(p != m_heap))
		{
			return TT_ERROR;
		}
		i = searchLocate;   //返回要查找的元素的位置的序号
		return TT_OK;
	}

	DuLinkList::ElemType DuLinkList::getLength()const
	{
		DulNode *p = m_heap->m_next;   //p指向第一个结点
		int i = 0;
		while (p != m_heap) //p未到表头时
		{
			++i;
			p = p->m_next;

		}
		return i;
	}

	DuLinkList::ElemType DuLinkList::destroy()
	{
		DulNode *p = m_heap->m_next; //p指向第一个结点
		while (p != m_heap)   //p没到表头
		{
			DulNode *q = p->m_next;  //第一次循环，把第二个元素变成q
			delete p;  //第一次循环，  释放第一个元素
			p = q;   //第一次循环，  把第二个元素变成p，  那么现在p就是第一个元素
		}
		delete m_heap;  //所有元素删除完后，  因为上面是从第一个节点开始删除的，  头结点没有删除，  所有这个要删除头结点
		m_heap = nullptr;
		return TT_OK;
	}
	DuLinkList::ElemType DuLinkList::clear()
	{
		DulNode *p = m_heap->m_next; //p指向第一个结点
		while (p != m_heap) //p没到表头
		{
			DulNode *q = p->m_next;
			delete p;
			p = q;
		}
		m_heap->m_next = m_heap->m_prior = m_heap; //头结点的两个指针域均指向自身
		return TT_OK;
	}

	DuLinkList::Status DuLinkList::show()
	{
		if (isEmpty())
		{
			cout << "当前的链表没有元素，无法显示！" << endl;
		}
		else
		{
			DulNode *p = m_heap->m_next;   //p指向第一个结点
			int temp(0);  //用来显示链表中的个数
			cout << "输出双向循环链表中的所有元素：";
			while (p != m_heap)  //p未到表头
			{
				++temp;
				cout << (p->m_data) << " ";
				p = p->m_next;
			}
			cout << "\n当前双向循环链表中的元数个数为：" << temp << endl;
		}
	}
	DuLinkList::Status DuLinkList::traverseBack()  //逆序输出链表的所有元素
	{
		if (isEmpty())
		{
			cout << "当前的链表没有元素，无法显示！" << endl;
		}
		else
		{
			DulNode *m = m_heap->m_prior;  //把m指向最后一个元素
			cout << "逆序输出双向链表中的所有元素：";
			while (m != m_heap)
			{
				cout << (m->m_data) << " ";
				m = m->m_prior;   //输出元素后，m向前前进
			}
			cout << endl;
		}

	}
	DuLinkList::ElemType DuLinkList::priorElemAt(ElemType cur_e, ElemType &pri_e)//若cur_e是链表的数据元素，且不是第一个，则用pre_e返回它的前驱
	{
		DulNode *p = m_heap->m_next->m_next;  //p指向第二个元素
		while (p != m_heap)
		{
			if (p->m_data == cur_e)  //p指向结点的数据与cur_e值进行比较判断
			{
				pri_e = p->m_prior->m_data;  //将p的前驱结点的值赋给pre_e，pre_e保存返回
				return TT_OK;;
			}
			p = p->m_next;
		}
		return TT_ERROR;
	}
	DuLinkList::ElemType DuLinkList::nextElemAt(ElemType cur_e, ElemType &Nex_e) //若cur_e是链表的数据元素,且不是最后一个,则用next_e返回它的后继，
	{
		DulNode *p = m_heap->m_next->m_next;   //指向第二个元素， 如果指向第一个元素的话，获得最后一个元素的后继，就会输出垃圾值
		while (p != m_heap)
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
}
// MyDuLinkList 的测试函数
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
	MyDuLinkList.createTail(myDatas, myLength);   //调用createTail函数 建立单链表
	MyDuLinkList.show();

	while (true)
	{
		{
			cout << "\n*************************************************************" << endl
				<< "*******************   双向循环链表基本功能展示   *******************" << endl
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
				<< "*********************  选择12——逆序输出所有元素.  *****************" << endl
				<< "********************   选择13——清屏！      ************************" << endl
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
				cout << "当前双向循环链表为空！" << endl;
				MyDuLinkList.getLength();
			}
			else
			{
				cout << "当前的双向循环链表非空！" << endl;
				MyDuLinkList.show();
			}
			break;
		case 6:
		{                                         //获取长度
			cout << "双向循环链表当前的长度为：" << MyDuLinkList.getLength() << endl;
			break;
		}
		case 7:
			if (MyDuLinkList.clear())
			{
				cout << "双向循环链表已被清空！" << endl;
				MyDuLinkList.show();
			}
			else
			{
				cout << "双向循环链表清空失败！" << endl;
				MyDuLinkList.show();
			}
			break;
		case 8:
			MyDuLinkList.show();
			break;
		case 9:
		{
			cout << "你确定要销毁该双向循环链表吗？(若销毁请输入输入(Y/y))";
			char yesOrNo;
			cin >> yesOrNo;
			if ((yesOrNo == 'Y') || (yesOrNo == 'y'))
			{
				if (MyDuLinkList.destroy())
				{
					cout << "双向循环链表已被销毁." << "\n" << endl;
				}
				else
					cout << "双向循环链表销毁失败." << "\n" << endl;
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