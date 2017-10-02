#include<iostream>
using namespace std;

#define TT_OK 1
#define TT_ERROR 0
#define MAX_TREE_SIZE 100
typedef int IElemType;
typedef void Status;
typedef char CElementType;

struct QElemType
{
	IElemType num;
	CElementType name;
}; // 定义队列元素类型 

typedef struct QNode //链队列结构
{
	QElemType m_data;
    QNode *m_next;
}*QueuePtr;

 struct LinkQueue
{
	 QueuePtr m_front, m_rear; //队头、队尾指针 
};




//队列的函数实现
 Status initQueue(LinkQueue *Q)
{
	(*Q).m_front = (*Q).m_rear = (QueuePtr)malloc(sizeof(QNode));
	if (!(*Q).m_front)
	{
		cout << "链队列初始化失败!" << endl;
		system("pause");
		exit(0);
	}
	(*Q).m_front->m_next = nullptr;
	
}

 IElemType queueEmpty(LinkQueue Q)
{
	return (Q.m_front == Q.m_rear);
}


 IElemType insert(LinkQueue *Q, QElemType elem)
{
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	if (!p) /* 存储分配失败 */
	{
		cout << "插入结点内存分配失败！" << endl;
		system("pause");
		exit(0);
	}
	p->m_data = elem;
	p->m_next = nullptr;
	(*Q).m_rear->m_next = p;
	(*Q).m_rear = p;
	return TT_OK;
}

 IElemType remove(LinkQueue *Q, QElemType &elemOut)
{
	if ((*Q).m_front == (*Q).m_rear)
	{
		return TT_ERROR;
	}
	QueuePtr p = (*Q).m_front->m_next;
	elemOut = p->m_data;
	(*Q).m_front->m_next = p->m_next;
	if ((*Q).m_rear == p)
	{
		(*Q).m_rear = (*Q).m_front;
	}
	free(p);
	return TT_OK;
}

struct PTNode  //树的节点结构
{
	CElementType m_Pdata;   //数据域
	IElemType m_parent;   //双亲的位置
};

class PTree
{
public:
	PTree();
	~PTree() {};

	Status create();
	Status traverse(Status(*Visit)(CElementType));
	IElemType clean();
	IElemType empty();
	IElemType depth();
	CElementType root();
	CElementType value(IElemType ele);
	IElemType parent(CElementType &cur_e);
	IElemType leftChild(CElementType &cur_e);
	IElemType rightSibling(CElementType &cur_e);
	IElemType assign(CElementType cur_e, CElementType value);
	IElemType print();
	IElemType insertChild(CElementType p, IElemType i, PTree c);
	IElemType removeChild(CElementType p, IElemType i);
private:
	PTNode m_nodes[MAX_TREE_SIZE];  //结点数组的基址
	IElemType m_n; //当前结点的个数
	IElemType m_rootIndex;  //根结点的位置

};

//树的函数实现
PTree::PTree()
{
	m_n = m_rootIndex = 0;
}



Status PTree::create()
{
	LinkQueue q;
	initQueue(&q);  //初始化队列

	cout << "请输入根结点(字符型,空格为空):";
	cin >> m_nodes[0].m_Pdata; // 根结点序号为0
	getchar();//吃掉回车符

	char Nil = ' ';  //以空格符为空
	if (m_nodes[0].m_Pdata != Nil) // 非空树 
	{
		m_nodes[0].m_parent = -1; // 根结点无双亲 
		QElemType p, qq;
		qq.name = m_nodes[0].m_Pdata;
		qq.num = 0;
		insert(&q, qq); // 入队此结点 
		IElemType temp = 1;
		char c[MAX_TREE_SIZE];  //临时存放孩子结点数组
		while (temp < MAX_TREE_SIZE && !queueEmpty(q))// 数组未满且队不空 
		{
			
			remove(&q, qq);
			cout << "--------请按长幼顺序输入结点c的所有孩子（输入q 表示创建完毕）------ :\n" << endl;
			gets_s(c);
			if (strcmp(c, "q") == 0)
			{
				break;
			}
			int t = strlen(c);
			for (int j = 0; j < t; ++j)
			{
				m_nodes[temp].m_Pdata = c[j];
				m_nodes[temp].m_parent = qq.num;
				p.name = c[j];
				p.num = temp;
				insert(&q, p); /* 入队此结点 */
				++temp;
			}
		}
		if (temp > MAX_TREE_SIZE)
		{
			cout << "结点数超过数组容量\n";
			system("pause");
			exit(0);
		}
		m_n = temp;
	}
	else
	{
		m_n = 0;
	}
}

inline IElemType PTree::clean()
{
	m_n = 0;
	return TT_OK;
}

inline IElemType PTree::empty()
{
	return (m_n == 0);
}

IElemType PTree::depth()  //返回T的深度
{
	
	int max = 0;
	for (int k = 0; k < m_n; ++k)
	{
		int def = 1; /* 初始化本节点的深度 */
		int m = m_nodes[k].m_parent;
		while (m != -1)
		{
			m = m_nodes[m].m_parent;
			++def;
		}
		if (max < def)
		{
			max = def;
		}
	}
	return max; /* 最大深度 */
}

CElementType PTree::root()  //返回T的根
{
	
	char rElem = '\0';
	for (int i = 0; i < m_n; ++i)
	{
		if (m_nodes[i].m_parent < 0)
		{
			return m_nodes[i].m_Pdata;
		}
	}
	return rElem;
}

CElementType PTree::value(IElemType ele) //ele是树中的一个节点， 返回此节点的值
{
	char vu = '\0';
	if (ele < m_n)
	{
		return m_nodes[ele].m_Pdata;
	}
	return vu;
}

IElemType PTree::assign(CElementType cur_e, CElementType value) //cur_e是树T中结点的值。操作结果: 改cur_e为value
{
	
	for (int j = 0; j < m_n; ++j)
	{
		if (m_nodes[j].m_Pdata == cur_e)
		{
			m_nodes[j].m_Pdata = value;
			return TT_OK;
		}
	}
	return TT_ERROR;
}
IElemType PTree::parent(CElementType &cur_e)//cur_e是树中某个结点，若cur_e是T的非根结点,则返回它的双亲,否则函数值为＂空＂
{
	for (int j = 1; j < m_n; ++j) /* 根结点序号为0 */
	{
		if (m_nodes[j].m_Pdata == cur_e)
		{
			cur_e = m_nodes[m_nodes[j].m_parent].m_Pdata;
		}
	}
	return TT_OK;
}
IElemType PTree::leftChild(CElementType &cur_e)//cur_e是树中某个结点，若cur_e是树中的非叶子结点,则返回它的最左孩子,否则返回＂空＂
{
	
	int i;
	for (i = 0; i < m_n; ++i)
	{
		if (m_nodes[i].m_Pdata == cur_e) /* 找到cur_e,其序号为i */
		{
			break;
		}
	}
	for (int j = i+1; j < m_n; ++j) /* 根据树的构造函数,孩子的序号＞其双亲的序号 */
	{
		if (m_nodes[j].m_parent == i) /* 根据树的构造函数,最左孩子(长子)的序号＜其它孩子的序号 */
		{
			cur_e = m_nodes[j].m_Pdata;
		}
	}
	return TT_OK;
}
IElemType PTree::rightSibling(CElementType &cur_e)//cur_e是树中某个结点，若cur_e有右(下一个)兄弟,则返回它的右兄弟,否则返回＂空＂
{
	//char rs = '\0';
	int i;
	for (i = 0; i < m_n; ++i)
	{
		if (m_nodes[i].m_Pdata == cur_e) /* 找到cur_e,其序号为i */
		{
			break;
		}
	}
	if (m_nodes[i + 1].m_parent == m_nodes[i].m_parent)
	{
		/* 根据树的构造函数,若cur_e有右兄弟的话则右兄弟紧接其后 */
		cur_e = m_nodes[ i+1 ].m_Pdata;
	}
	return TT_OK;
}
IElemType PTree::print()//打印树中元素
{
	
	cout << "结点个数：" << m_n << endl;
	cout << "结点 双亲\n";
	for (int i = 0; i < m_n; ++i)
	{
		cout<< value(i);/* 结点 */
		if (m_nodes[i].m_parent >= 0) /* 有双亲 */
		{
			cout <<"   "<< value(m_nodes[i].m_parent); /* 双亲 */
		}
		cout << endl;
	}
	return TT_OK;
}

IElemType PTree::insertChild(CElementType p, IElemType i, PTree c)
{
	/* 初始条件: 树T存在,p是T中某个结点,1≤i≤p所指结点的度+1,非空树c与T不相交 */
	/* 操作结果: 插入c为T中p结点的第i棵子树 */

	if (m_n + 1 > MAX_TREE_SIZE)
	{
		return TT_ERROR;
	}
	int j, k, f = 1, n = 0; /* 设交换标志f的初值为1,p的孩子数n的初值为0 */
	
	if (!empty()) /* T不空 */
	{
		for (j = 0; j < m_n; j++) /* 在T中找p的序号 */
		{
			if (m_nodes[j].m_Pdata == p) /* p的序号为j */
			{
				break;
			}
		}
		int l = j + 1; /* 如果c是p的第1棵子树,则插在j+1处 */

		if ( i > 1) /* c不是p的第1棵子树 */
		{
			for (k = j + 1; k < m_n; ++k) /* 从j+1开始找p的前i-1个孩子 */
			{
				if (m_nodes[k].m_parent == j) /* 当前结点是p的孩子 */
				{
					++n; /* 孩子数加1 */
					if (n == i - 1) /* 找到p的第i-1个孩子,其序号为k1 */
						break;
				}
			}
			l = k + 1; /* c插在k+1处 */
		} /* p的序号为j,c插在l处 */

		if (l < m_n) /* 插入点l不在最后 */
			for (k = m_n - 1; k >= l; k--) /* 依次将序号l以后的结点向后移c.n个位置 */
			{
				m_nodes[k + c.m_n] = m_nodes[k];
				if (m_nodes[k].m_parent >= l)
				{
					m_nodes[k + c.m_n].m_parent += c.m_n;
				}
			}

		for (k = 0; k<c.m_n; ++k)
		{
			m_nodes[l + k].m_Pdata = c.m_nodes[k].m_Pdata; /* 依次将树c的所有结点插于此处 */
			m_nodes[l + k].m_parent = c.m_nodes[k].m_parent + l;
		}
		m_nodes[l].m_parent = j; /* 树c的根结点的双亲为p */
		m_n += c.m_n; /* 树T的结点数加c.n个 */
		PTNode t;
		while (f)
		{ /* 从插入点之后,将结点仍按层序排列 */
			f = 0; /* 交换标志置0 */
			for (j = l; j < m_n - 1; j++)
			{
				if (m_nodes[j].m_parent > m_nodes[j + 1].m_parent)
				{/* 如果结点j的双亲排在结点j+1的双亲之后(树没有按层序排列),交换两结点*/
					t = m_nodes[j];
					m_nodes[j] = m_nodes[j + 1];
					m_nodes[j + 1] = t;
					f = 1; /* 交换标志置1 */

					for (k = j; k < m_n; ++k) /* 改变双亲序号 */
					{
						if (m_nodes[k].m_parent == j)
						{
							m_nodes[k].m_parent++; /* 双亲序号改为j+1 */
						}
						else if (m_nodes[k].m_parent == j + 1)
						{
							m_nodes[k].m_parent--; /* 双亲序号改为j */
						}
					}
				}
			}
		}
		return TT_OK;
	}
	else /* 树T不存在 */
	{
		return TT_ERROR;
	}
}


IElemType deleted[MAX_TREE_SIZE + 1]; /* 删除标志数组(全局量) */

IElemType PTree::removeChild(CElementType p, IElemType i)
{
	/* 初始条件: 树T存在,p是T中某个结点,1≤i≤p所指结点的度 */
	/* 操作结果: 删除T中结点p的第i棵子树 */
	if (m_n == 0)
	{
		return TT_ERROR;
	}
	int j, k;
	
	for (j = 0; j <= m_n; ++j)
	{
		deleted[j] = 0; /* 置初值为0(不删除标记) */
	}

	QElemType pq, qq;
	LinkQueue q;
	pq.name = 'a'; /* 此成员不用 */
	initQueue(&q); /* 初始化队列 */

	for (j = 0; j < m_n; ++j)
	{
		if (m_nodes[j].m_Pdata == p)
		{
			break; /* j为结点p的序号 */
		}
	}
	int n = 0;
	for (k = j + 1; k < m_n; ++k)
	{
		if (m_nodes[k].m_parent == j)
		{
			++n;
		}
		if (n == i)
		{
			break; /* k为p的第i棵子树结点的序号 */
		}
	}
	if ( k < m_n) /* p的第i棵子树结点存在 */
	{
		n = 0;
		pq.num = k;
		deleted[k] = 1; /* 置删除标记 */
		n++;
		insert(&q, pq);
		while (!queueEmpty(q))
		{
			remove(&q, qq);
			for (j = qq.num + 1; j<m_n; ++j)
				if (m_nodes[j].m_parent == qq.num)
				{
					pq.num = j;
					deleted[j] = 1; /* 置删除标记 */
					++n;
					insert(&q, pq);
				}
		}
		for (j = 0; j < m_n; ++j)
		{
			if (deleted[j] == 1)
			{
				for (k = j + 1; k <= m_n; ++k)
				{
					deleted[k - 1] = deleted[k];
					m_nodes[k - 1] = m_nodes[k];
					if (m_nodes[k].m_parent > j)
					{
						m_nodes[k - 1].m_parent--;
					}
				}
				--j;
			}
		}
		m_n -= n; /* n为待删除结点数 */
	}
	return TT_OK;
}

Status PTree::traverse(Status(*Visit)(CElementType))
{
	/*初始条件:二叉树T存在, Visit是对结点操作的应用函数 * /
		/* 操作结果:层序遍历树T,对每个结点调用函数Visit一次且仅一次 */
		
	for (int i = 0; i < m_n; ++i)
	{
		Visit(m_nodes[i].m_Pdata);
	}
	cout << endl;
}
Status vi(CElementType c)
{
	cout << c << " " << endl;
}
int main()
{
	PTree myPTree;
	myPTree.create();

	cout << "\n层序遍历树:\n";
	myPTree.traverse(vi);
	while (true)
	{
		{
			cout << "\n*******************************************************************" << endl
				<< "*******************  树的双亲表示法基本功能展示   *******************" << endl
				<< "*******************************************************************" << endl
				<< "********************   选择1——插入结点字树.   **********************" << endl
				<< "********************   选择2——删除结点字树.   **********************" << endl
				<< "********************   选择3——返回结点的右兄弟.   **********************" << endl
				<< "********************   选择4——返回结点的左孩子.   **********************" << endl
				<< "********************   选择5——返回结点的双亲.   **********************" << endl
				<< "*******************************************************************" << endl
				<< "********************   选择6——为结点元素赋值.   **********************" << endl
				<< "********************   选择7——返回结点的值.   **********************" << endl
				<< "********************   选择8——返回树的根结点.   **********************" << endl
				<< "********************   选择9——返回树的深度.   **********************" << endl
				<< "********************   选择10——判断树是否为空.   **********************" << endl
				<< "********************   选择11——清空树中结点.   **********************" << endl
			    << "********************   选择12——输出树中所有元素.   **********************\n" << endl;

		}
		
		cout << "\n*******************   请输入你想要使用树的双亲表示法功能的序号  ***************" << endl;
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
		case 1:                   //插入字树
		{
			char addEle = '\0';
			int addDegree = 0;
			PTree pushChild;
			pushChild.create();
			cout << "输出树中此时的元素：\n";
			pushChild.traverse(vi);
			cout << "请输入你想在哪个结点上添加字树（不要添加树中已有的元素）：\n";
			cin >> addEle;
			cout << "请输入你想在该结点上添加第几个字树：";
			cin >> addDegree;
			if (myPTree.insertChild(addEle, addDegree, pushChild))
			{
				cout << "结点成功插入树中！" << endl;
				myPTree.print();
			}
			else
			{
				cout << "结点插入失败,可能是容量已满！" << endl;
			}
			break;
		}
		case 2:                        //删除字树
		{
			char popEle = '\0';
			int popDegree = 0;
		
			cout << "请输入你想删除哪个结点中的字树：\n";
			cin >> popEle;
			cout << "请输入你想删除该节点中的第几个字树：";
			cin >> popDegree;
			if (myPTree.removeChild(popEle, popDegree))
			{
				cout << "结点删除成功！" << endl;
			}
			else
			{
				cout << "结点删除失败，可能是个空树！" << endl;
			}
			myPTree.print();
			break;
		}

		case 3:
		{                                      //返回树中某节点的右兄弟
			char rightBroth = '\0';
			cout << "请输入你想获取哪个结点的右兄弟：";
			cin >> rightBroth;
			if (myPTree.rightSibling(rightBroth))
			{
				cout << "该节点的右兄弟为：" << rightBroth << endl;
			}
			else
			{
				cout << "该节点没有右兄弟！" << endl;
			}
			break;
		}
		case 4:
		{                                            //返回树中某节点的最左孩子
			char leftKid = '\0';
			cout << "请输入你想获取哪个结点的最左孩子：";
			cin >> leftKid;
			if (myPTree.leftChild(leftKid))
			{
				cout << "该节点的最左孩子是：" << leftKid << endl;
			}
			else
			{
				cout << "该节点没有最左孩子， 无法显示！" << endl;
			}
			break;
		}
		case 5:
		{
			char genitor = '\0';
			cout << "请输入你想获取哪个结点的双亲，（根结点无双亲！：）";
			cin >> genitor;
			if (myPTree.parent(genitor))
			{
				cout << "获取成功，该节点的双亲为：" << genitor << endl;
			}
			else
			{
				cout << "获取失败， 可能是空树，亦或者访问到了根结点！" << endl;
			}
			break;
		}
		case 6:
		{
			char nodeEelm = '\0';
			char assignment = '\0';
			cout << "请输入你想为哪个结点赋值：";
			cin >> nodeEelm;
			cout << "请输入你想为该节点赋值为：";
			cin >> assignment;
			if (myPTree.assign(nodeEelm, assignment))
			{
				cout << "结点" << nodeEelm << "成功赋值！" << endl;
				myPTree.print();
			}
			else
			{
				cout << "结点" << nodeEelm << "赋值失败，可能树中没有该节点！" << endl;
			}
			break;
		}
		case 7:
		{
			int nodeValue = 0;
			cout << "你想返回第几个结点的值：";;
			cin >> nodeValue;
			cout << "该节点的值为：" << myPTree.value(nodeValue) << endl;
			break;
		}
		case 8:
			cout << "树的根为：" << myPTree.root() << endl;
			break;
		case 9:
			cout << "该树的深度为：" << myPTree.depth() << endl;
			break;
		case 10:
			if (myPTree.empty())
			{
				cout << "树为空！" << endl;
			}
			else
			{
				cout << "树非空！" << endl;
			}
			break;
		case 11:
			if (myPTree.clean())
			{
				cout << "树已清空！" << endl;
			}
			else
			{
				cout << "树清空失败！" << endl;
			}
			break;
		case 12:
			myPTree.print();
			break;
		default:
			cout << "输入的序号不正确， 请重新输入！" << endl;

		}
	}
	system("pause");
	return 0;
}
