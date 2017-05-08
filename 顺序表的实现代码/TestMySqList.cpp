#include"MySqList.h"

namespace tt
{
	SqList::SqList(ElemType maxSize)
	{
		assert(maxSize > 0);
		m_data = new ElemType[maxSize];
		if (!m_data)
		{
			cout << "错误！内存分配失败！" << endl;
			system("pause");
			exit(0);
		}
		m_length = 0;
		m_maxLength = maxSize;
		cout << "********************顺序表初始化成功********************" << "\n" << endl;
	}
	SqList::~SqList()
	{
		this->destroy();
	}
	SqList::ElemType SqList::priorElemAt(ElemType cur_e, ElemType &pri_e)
	{
		int i;
		int *p = m_data;

		for (i = 0; i < m_length; i++, p++) //顺序表长度已知，故用for循环
		{
			if ((i == 0) && (*p == cur_e))
			{
				return TT_ERROR;
			}
			if (*p == cur_e)       //找到了当前元素且不是第一个元素，
			{
				pri_e = *--p;      //将其前驱赋给引用参数
				return TT_OK;
			}
		}
		return TT_ERROR;
	}
	SqList::ElemType SqList::nextElemAt(ElemType cur_e, ElemType &Nex_e)
	{
		int i = 1;
		int *p = m_data;
		while ((i < m_length) && (*p != cur_e))
		{
			++i;
			++p;
		}
		if (i == m_length)
		{
			return TT_ERROR;
		}
		else
		{
			Nex_e = *++p;
			return TT_OK;
		}
	}
	SqList::ElemType SqList::insertAt(ElemType i, ElemType elem) //插入元素，  在线性表中第i个位置之前插入新元素elem
	{                                               //if(i<0 || i>length)
		if ((i < 1) || (i>m_length + 1))  //插入的位置不合理时，返回错误
		{
			return TT_ERROR;
		}
		if ((m_length == m_maxLength))   //表已满
		{
			int *allocateMemory = new int[m_data, m_maxLength + LIST_NCREMENT]; // 用allocateMemory指针是为了保护m_data
			if (!allocateMemory)
			{
				cout << "错误！继续分配内存失败！" << endl;
				system("pause");
				exit(0);
			}
			m_maxLength += LIST_NCREMENT;   //增加存储容量
		}
		if (i <= m_length)  //若插入的位置不在表尾，否则直接插入新元素，只有插入第11个位置才算是表尾
		{
			for (int k = m_length; k >= i; --k)  /*元素i及其后面的元素都往后移一下以腾出i处的空间存放要插入的元素,*/
				m_data[k] = m_data[k - 1];  //假如m_length=10,m_maxSize=20;那么第一次就是把下标为9的元素变成下标为10的元素
											//相当于元素向后移，每次循环都是如此，k为为线性表当前长度，每次循环减一
		}
		m_data[i - 1] = elem; //将新元素插入第i个位置之前
		++m_length;
		return TT_OK;
	}
	SqList::ElemType SqList::removeAt(ElemType i, ElemType &elemOut)  //删除元素线性表中第i个数据元素，并用elem返回其值,表长减一
	{

		if ((i < 1) || (i > m_length))/*假如m_length=10,m_maxSize=20;线性表是是第一个位置数，没有第0个位置，
									  删除的线性表的位置不能大于当前线性表的长度,或者当前没有元素，说白了就是删除位置
									  不合理*/
		{
			return TT_ERROR;
		}
		elemOut = m_data[i - 1];  //把当前下标的元素用elemOut取出
		if (i<m_length)     //如果要删除的不是最后位置
		{
			for (int k = i; k < m_length; ++k)     //将删除位置后的元素向前移动，  要删除的位置不能大于表长
				m_data[k - 1] = m_data[k];  //那么第一次循环就是把下标为10的元素变成下标为9的元素，每次循环向前移动
		}
		--m_length;
		return TT_OK;
	}
	SqList::ElemType SqList::getAt(ElemType i, ElemType &elemOut) //获得元素的操作,将线性表中第i个位置的元素的值返回给e
	{
		if ((i<1 )|| (i>m_length))  //当你获取的元素不在线性表中的范围，就错误呗
		{
			return TT_ERROR;
		}
		elemOut = m_data[i - 1];
		return TT_OK;
	}

	SqList::ElemType SqList::getIndexElem(const ElemType elem)//在线性表中查找与elem的相等的元素，返回第一个与elem相等元素在线性表中的第几个位置
	{
		for (int i = 0; i < m_length; ++i)  //假如m_length=10,m_maxSize=20;那么下标最大到9
		{
			if (m_data[i] == elem)  /*把elem相等的元素返回，因为线性表是从1开始的，数组的下标是0开始的，于是线性表第i个元素存储在
									数组下标i-1的位置，返回的时候要加1*/
				return i + 1;
		}
		return TT_ERROR;
	}


	SqList::Status SqList::clear()
	{
		m_data = nullptr;
		m_length = 0;
		if (!m_data && m_length == 0)
		{
			cout << "顺序表已清空！" << endl;
		}
		else
			cout << "顺序表清空失败！" << endl;
	}
	SqList::Status SqList::show()
	{
		int *p = m_data;
		if (m_length == 0)
		{
			cout << "错误！当前线性表没有元素，无法显示！" << endl;
		}
		else
		{
			cout << "输出线性表的所有元素为：";
			for (int k = 0; k < m_length; ++k, ++p)
			{
				cout << *p << " ";   //data[k] 也是可以的 
			}
			cout << endl;
		}
	}
	SqList::ElemType SqList::destroy()
	{
		delete[] m_data;
		m_data = nullptr;
		m_length = m_maxLength = 0;
		return TT_OK;
	}
}
//测试代码
void testMySqList()
{
	int sizeCapacity(0);
	cout << "输入顺序表的最大容量：";
	cin >> sizeCapacity;
	tt::SqList mySqList(sizeCapacity);
	while (true)
	{
		{
			cout << "*************************************************************" << endl
				<< "*******************   顺序表的基本功能展示   *******************" << endl
				<< "*****************************************************************" << endl
				<< "********************   选择1——数据插入.   **********************" << endl
				<< "********************   选择2——数据删除.   **********************" << endl
				<< "********************   选择3——获取元素.   **********************" << endl
				<< "********************   选择4——查找元素.   **********************" << endl
				<< "********************   选择5——是否为空.   **********************" << endl
				<< "********************   选择6——获取表的长度.   **********************" << endl
				<< "********************   选择7——清空元素.   **********************" << endl
				<< "********************   选择8——显示所有元素.   **********************" << endl
				<< "*********************  选择9——销毁线性表.  ************************" << endl
				<< "*********************  选择10——获得元素的前驱.  *****************" << endl
				<< "*********************  选择11——获得元素的后继.  *****************" << endl
				<< "*******************    选择12——清屏！      ************************" << endl
				<< "******************     选择0——退出程序！   ************************" << endl
				<< "***********************************************************************" << endl
				<< "***********************************************************************" << endl;
		}
		cout << "\n********************   请输入你想要使用的顺序表功能的序号   ***************" << endl;
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
			if (mySqList.insertAt(indexLocition, pushDatas))
			{
				cout << "数据" << pushDatas << "插入成功！" << "\n" << endl;
				mySqList.getLength();
				mySqList.show();
			}
			else
				cout << "当前顺序表已满或者插入位置不合理，数据" << pushDatas << "插入失败！" << endl;
			break;
		}
		case 2:
		{
			int popDatas(0);  //要删除的元素
			int indexLocition(0);  //要删除的位置
			cout << "请输入你想要删除的元素的位置：";
			cin >> indexLocition;
			if (mySqList.removeAt(indexLocition, popDatas))
			{
				cout << "数据" << popDatas << "删除成功！" << "\n" << endl;
				mySqList.getLength();
				mySqList.show();
			}
			else
				cout << "当前顺序表为空或者删除位置不合理，数据" << popDatas << "删除失败！" << endl;
			break;
		}
		case 3:
		{
			int getElem(0);  //要获取的元素
			int indexLocition(0);
			cout << "请输入你想要获取元素的位置：";
			cin >> indexLocition;
			if (mySqList.getAt(indexLocition, getElem))
			{
				cout << "获取的元素为：" << getElem << "\n" << endl;
				mySqList.getLength();
				mySqList.show();
			}
			else
				cout << "当前顺序表为空或者获取的位置不合理，数据" << getElem << "获取失败！" << endl;
			break;
		}
		case 4:
		{
			int findElem(0);   //查找元素
			cout << "请输入你想要查找的元素的值：";
			cin >> findElem;
			if (int indexLocition = mySqList.getIndexElem(findElem))
			{
				cout << "所要查找的元素位于表中第" << indexLocition << "个位置" << endl;
				mySqList.getLength();
				mySqList.show();

			}
			else
			{
				cout << "当前表中无此元素" << endl;
				mySqList.getLength();
			}
			break;
		}
		case 5:
			if (mySqList.isEmpty())  //判断是否为空
			{
				cout << "目前该顺序表为空！" << endl;
				mySqList.getLength();
			}
			else
			{
				cout << "目前顺序表非空！" << endl;
				mySqList.getLength();
				mySqList.show();

			}
			break;
		case 6:
			mySqList.getLength();  //获取线性表的长度
			break;
		case 7:
			mySqList.clear();//清空所有元素   
			mySqList.getLength();
			break;
		case 8:
			mySqList.show();//显示所有元素
			mySqList.getLength();
			break;
		case 9:
		{
			cout << "你确定要销毁该顺序表吗？(若销毁请输入输入(Y/y))";
			char yesOrNo;
			cin >> yesOrNo;
			if ((yesOrNo == 'Y') || (yesOrNo == 'y'))
			{
				if (mySqList.destroy())
				{
					cout << "顺序表已被销毁." << "\n" << endl;
				}
				else
					cout << "顺序表没有被销毁." << "\n" << endl;
			}
			break;
		}
		case 10:
		{
			int priorElem(0);
			int getElem(0);
			cout << "输入你想要获得哪一个元素的前驱？（注意：不能获取第一个元素的）：";
			cin >> priorElem;
			if (mySqList.priorElemAt(priorElem, getElem))
			{
				cout << "数据元素" << priorElem << "的，前驱元素是：" << getElem << endl;
				mySqList.show();
			}
			else
			{
				cout << "获取前驱元素失败，不能获取第一个元素的前驱或者链表中没有你输入的元素！" << endl;
				mySqList.show();
			}
			break;
		}
		case 11:
		{
			int backElem(0);
			int getElem(0);
			cout << "输入你想要获得哪一个元素的后继？（注意：不能获取最后一个元素的）：";
			cin >> backElem;
			if (mySqList.nextElemAt(backElem, getElem))
			{
				cout << "数据元素" << backElem << "的，后继元素是：" << getElem << endl;
				mySqList.show();
			}
			else
			{
				cout << "获取后继元素失败！不能获取最后一个元素的后继或者链表中没有你输入的元素！" << endl;
				mySqList.show();
			}
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
}
int main()
{
	testMySqList();
	system("pause");
	return 0;
}