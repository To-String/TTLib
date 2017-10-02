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
}; // �������Ԫ������ 

typedef struct QNode //�����нṹ
{
	QElemType m_data;
    QNode *m_next;
}*QueuePtr;

 struct LinkQueue
{
	 QueuePtr m_front, m_rear; //��ͷ����βָ�� 
};




//���еĺ���ʵ��
 Status initQueue(LinkQueue *Q)
{
	(*Q).m_front = (*Q).m_rear = (QueuePtr)malloc(sizeof(QNode));
	if (!(*Q).m_front)
	{
		cout << "�����г�ʼ��ʧ��!" << endl;
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
	if (!p) /* �洢����ʧ�� */
	{
		cout << "�������ڴ����ʧ�ܣ�" << endl;
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

struct PTNode  //���Ľڵ�ṹ
{
	CElementType m_Pdata;   //������
	IElemType m_parent;   //˫�׵�λ��
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
	PTNode m_nodes[MAX_TREE_SIZE];  //�������Ļ�ַ
	IElemType m_n; //��ǰ���ĸ���
	IElemType m_rootIndex;  //������λ��

};

//���ĺ���ʵ��
PTree::PTree()
{
	m_n = m_rootIndex = 0;
}



Status PTree::create()
{
	LinkQueue q;
	initQueue(&q);  //��ʼ������

	cout << "����������(�ַ���,�ո�Ϊ��):";
	cin >> m_nodes[0].m_Pdata; // ��������Ϊ0
	getchar();//�Ե��س���

	char Nil = ' ';  //�Կո��Ϊ��
	if (m_nodes[0].m_Pdata != Nil) // �ǿ��� 
	{
		m_nodes[0].m_parent = -1; // �������˫�� 
		QElemType p, qq;
		qq.name = m_nodes[0].m_Pdata;
		qq.num = 0;
		insert(&q, qq); // ��Ӵ˽�� 
		IElemType temp = 1;
		char c[MAX_TREE_SIZE];  //��ʱ��ź��ӽ������
		while (temp < MAX_TREE_SIZE && !queueEmpty(q))// ����δ���ҶӲ��� 
		{
			
			remove(&q, qq);
			cout << "--------�밴����˳��������c�����к��ӣ�����q ��ʾ������ϣ�------ :\n" << endl;
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
				insert(&q, p); /* ��Ӵ˽�� */
				++temp;
			}
		}
		if (temp > MAX_TREE_SIZE)
		{
			cout << "�����������������\n";
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

IElemType PTree::depth()  //����T�����
{
	
	int max = 0;
	for (int k = 0; k < m_n; ++k)
	{
		int def = 1; /* ��ʼ�����ڵ����� */
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
	return max; /* ������ */
}

CElementType PTree::root()  //����T�ĸ�
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

CElementType PTree::value(IElemType ele) //ele�����е�һ���ڵ㣬 ���ش˽ڵ��ֵ
{
	char vu = '\0';
	if (ele < m_n)
	{
		return m_nodes[ele].m_Pdata;
	}
	return vu;
}

IElemType PTree::assign(CElementType cur_e, CElementType value) //cur_e����T�н���ֵ���������: ��cur_eΪvalue
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
IElemType PTree::parent(CElementType &cur_e)//cur_e������ĳ����㣬��cur_e��T�ķǸ����,�򷵻�����˫��,������ֵΪ���գ�
{
	for (int j = 1; j < m_n; ++j) /* ��������Ϊ0 */
	{
		if (m_nodes[j].m_Pdata == cur_e)
		{
			cur_e = m_nodes[m_nodes[j].m_parent].m_Pdata;
		}
	}
	return TT_OK;
}
IElemType PTree::leftChild(CElementType &cur_e)//cur_e������ĳ����㣬��cur_e�����еķ�Ҷ�ӽ��,�򷵻�����������,���򷵻أ��գ�
{
	
	int i;
	for (i = 0; i < m_n; ++i)
	{
		if (m_nodes[i].m_Pdata == cur_e) /* �ҵ�cur_e,�����Ϊi */
		{
			break;
		}
	}
	for (int j = i+1; j < m_n; ++j) /* �������Ĺ��캯��,���ӵ���ţ���˫�׵���� */
	{
		if (m_nodes[j].m_parent == i) /* �������Ĺ��캯��,������(����)����ţ��������ӵ���� */
		{
			cur_e = m_nodes[j].m_Pdata;
		}
	}
	return TT_OK;
}
IElemType PTree::rightSibling(CElementType &cur_e)//cur_e������ĳ����㣬��cur_e����(��һ��)�ֵ�,�򷵻��������ֵ�,���򷵻أ��գ�
{
	//char rs = '\0';
	int i;
	for (i = 0; i < m_n; ++i)
	{
		if (m_nodes[i].m_Pdata == cur_e) /* �ҵ�cur_e,�����Ϊi */
		{
			break;
		}
	}
	if (m_nodes[i + 1].m_parent == m_nodes[i].m_parent)
	{
		/* �������Ĺ��캯��,��cur_e�����ֵܵĻ������ֵܽ������ */
		cur_e = m_nodes[ i+1 ].m_Pdata;
	}
	return TT_OK;
}
IElemType PTree::print()//��ӡ����Ԫ��
{
	
	cout << "��������" << m_n << endl;
	cout << "��� ˫��\n";
	for (int i = 0; i < m_n; ++i)
	{
		cout<< value(i);/* ��� */
		if (m_nodes[i].m_parent >= 0) /* ��˫�� */
		{
			cout <<"   "<< value(m_nodes[i].m_parent); /* ˫�� */
		}
		cout << endl;
	}
	return TT_OK;
}

IElemType PTree::insertChild(CElementType p, IElemType i, PTree c)
{
	/* ��ʼ����: ��T����,p��T��ĳ�����,1��i��p��ָ���Ķ�+1,�ǿ���c��T���ཻ */
	/* �������: ����cΪT��p���ĵ�i������ */

	if (m_n + 1 > MAX_TREE_SIZE)
	{
		return TT_ERROR;
	}
	int j, k, f = 1, n = 0; /* �轻����־f�ĳ�ֵΪ1,p�ĺ�����n�ĳ�ֵΪ0 */
	
	if (!empty()) /* T���� */
	{
		for (j = 0; j < m_n; j++) /* ��T����p����� */
		{
			if (m_nodes[j].m_Pdata == p) /* p�����Ϊj */
			{
				break;
			}
		}
		int l = j + 1; /* ���c��p�ĵ�1������,�����j+1�� */

		if ( i > 1) /* c����p�ĵ�1������ */
		{
			for (k = j + 1; k < m_n; ++k) /* ��j+1��ʼ��p��ǰi-1������ */
			{
				if (m_nodes[k].m_parent == j) /* ��ǰ�����p�ĺ��� */
				{
					++n; /* ��������1 */
					if (n == i - 1) /* �ҵ�p�ĵ�i-1������,�����Ϊk1 */
						break;
				}
			}
			l = k + 1; /* c����k+1�� */
		} /* p�����Ϊj,c����l�� */

		if (l < m_n) /* �����l������� */
			for (k = m_n - 1; k >= l; k--) /* ���ν����l�Ժ�Ľ�������c.n��λ�� */
			{
				m_nodes[k + c.m_n] = m_nodes[k];
				if (m_nodes[k].m_parent >= l)
				{
					m_nodes[k + c.m_n].m_parent += c.m_n;
				}
			}

		for (k = 0; k<c.m_n; ++k)
		{
			m_nodes[l + k].m_Pdata = c.m_nodes[k].m_Pdata; /* ���ν���c�����н����ڴ˴� */
			m_nodes[l + k].m_parent = c.m_nodes[k].m_parent + l;
		}
		m_nodes[l].m_parent = j; /* ��c�ĸ�����˫��Ϊp */
		m_n += c.m_n; /* ��T�Ľ������c.n�� */
		PTNode t;
		while (f)
		{ /* �Ӳ����֮��,������԰��������� */
			f = 0; /* ������־��0 */
			for (j = l; j < m_n - 1; j++)
			{
				if (m_nodes[j].m_parent > m_nodes[j + 1].m_parent)
				{/* ������j��˫�����ڽ��j+1��˫��֮��(��û�а���������),���������*/
					t = m_nodes[j];
					m_nodes[j] = m_nodes[j + 1];
					m_nodes[j + 1] = t;
					f = 1; /* ������־��1 */

					for (k = j; k < m_n; ++k) /* �ı�˫����� */
					{
						if (m_nodes[k].m_parent == j)
						{
							m_nodes[k].m_parent++; /* ˫����Ÿ�Ϊj+1 */
						}
						else if (m_nodes[k].m_parent == j + 1)
						{
							m_nodes[k].m_parent--; /* ˫����Ÿ�Ϊj */
						}
					}
				}
			}
		}
		return TT_OK;
	}
	else /* ��T������ */
	{
		return TT_ERROR;
	}
}


IElemType deleted[MAX_TREE_SIZE + 1]; /* ɾ����־����(ȫ����) */

IElemType PTree::removeChild(CElementType p, IElemType i)
{
	/* ��ʼ����: ��T����,p��T��ĳ�����,1��i��p��ָ���Ķ� */
	/* �������: ɾ��T�н��p�ĵ�i������ */
	if (m_n == 0)
	{
		return TT_ERROR;
	}
	int j, k;
	
	for (j = 0; j <= m_n; ++j)
	{
		deleted[j] = 0; /* �ó�ֵΪ0(��ɾ�����) */
	}

	QElemType pq, qq;
	LinkQueue q;
	pq.name = 'a'; /* �˳�Ա���� */
	initQueue(&q); /* ��ʼ������ */

	for (j = 0; j < m_n; ++j)
	{
		if (m_nodes[j].m_Pdata == p)
		{
			break; /* jΪ���p����� */
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
			break; /* kΪp�ĵ�i������������� */
		}
	}
	if ( k < m_n) /* p�ĵ�i������������ */
	{
		n = 0;
		pq.num = k;
		deleted[k] = 1; /* ��ɾ����� */
		n++;
		insert(&q, pq);
		while (!queueEmpty(q))
		{
			remove(&q, qq);
			for (j = qq.num + 1; j<m_n; ++j)
				if (m_nodes[j].m_parent == qq.num)
				{
					pq.num = j;
					deleted[j] = 1; /* ��ɾ����� */
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
		m_n -= n; /* nΪ��ɾ������� */
	}
	return TT_OK;
}

Status PTree::traverse(Status(*Visit)(CElementType))
{
	/*��ʼ����:������T����, Visit�ǶԽ�������Ӧ�ú��� * /
		/* �������:���������T,��ÿ�������ú���Visitһ���ҽ�һ�� */
		
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

	cout << "\n���������:\n";
	myPTree.traverse(vi);
	while (true)
	{
		{
			cout << "\n*******************************************************************" << endl
				<< "*******************  ����˫�ױ�ʾ����������չʾ   *******************" << endl
				<< "*******************************************************************" << endl
				<< "********************   ѡ��1��������������.   **********************" << endl
				<< "********************   ѡ��2����ɾ���������.   **********************" << endl
				<< "********************   ѡ��3�������ؽ������ֵ�.   **********************" << endl
				<< "********************   ѡ��4�������ؽ�������.   **********************" << endl
				<< "********************   ѡ��5�������ؽ���˫��.   **********************" << endl
				<< "*******************************************************************" << endl
				<< "********************   ѡ��6����Ϊ���Ԫ�ظ�ֵ.   **********************" << endl
				<< "********************   ѡ��7�������ؽ���ֵ.   **********************" << endl
				<< "********************   ѡ��8�����������ĸ����.   **********************" << endl
				<< "********************   ѡ��9���������������.   **********************" << endl
				<< "********************   ѡ��10�����ж����Ƿ�Ϊ��.   **********************" << endl
				<< "********************   ѡ��11����������н��.   **********************" << endl
			    << "********************   ѡ��12���������������Ԫ��.   **********************\n" << endl;

		}
		
		cout << "\n*******************   ����������Ҫʹ������˫�ױ�ʾ�����ܵ����  ***************" << endl;
		cout << "���������ѡ��";
		int userChoice(0);
		cin >> userChoice;
		if (userChoice == 0)
		{
			cout << "�������˳�����л����ʹ��!" << "\n" << endl;
			break;
		}

		switch (userChoice)
		{
		case 1:                   //��������
		{
			char addEle = '\0';
			int addDegree = 0;
			PTree pushChild;
			pushChild.create();
			cout << "������д�ʱ��Ԫ�أ�\n";
			pushChild.traverse(vi);
			cout << "�������������ĸ�����������������Ҫ����������е�Ԫ�أ���\n";
			cin >> addEle;
			cout << "�����������ڸý������ӵڼ���������";
			cin >> addDegree;
			if (myPTree.insertChild(addEle, addDegree, pushChild))
			{
				cout << "���ɹ��������У�" << endl;
				myPTree.print();
			}
			else
			{
				cout << "������ʧ��,����������������" << endl;
			}
			break;
		}
		case 2:                        //ɾ������
		{
			char popEle = '\0';
			int popDegree = 0;
		
			cout << "����������ɾ���ĸ�����е�������\n";
			cin >> popEle;
			cout << "����������ɾ���ýڵ��еĵڼ���������";
			cin >> popDegree;
			if (myPTree.removeChild(popEle, popDegree))
			{
				cout << "���ɾ���ɹ���" << endl;
			}
			else
			{
				cout << "���ɾ��ʧ�ܣ������Ǹ�������" << endl;
			}
			myPTree.print();
			break;
		}

		case 3:
		{                                      //��������ĳ�ڵ�����ֵ�
			char rightBroth = '\0';
			cout << "�����������ȡ�ĸ��������ֵܣ�";
			cin >> rightBroth;
			if (myPTree.rightSibling(rightBroth))
			{
				cout << "�ýڵ�����ֵ�Ϊ��" << rightBroth << endl;
			}
			else
			{
				cout << "�ýڵ�û�����ֵܣ�" << endl;
			}
			break;
		}
		case 4:
		{                                            //��������ĳ�ڵ��������
			char leftKid = '\0';
			cout << "�����������ȡ�ĸ����������ӣ�";
			cin >> leftKid;
			if (myPTree.leftChild(leftKid))
			{
				cout << "�ýڵ���������ǣ�" << leftKid << endl;
			}
			else
			{
				cout << "�ýڵ�û�������ӣ� �޷���ʾ��" << endl;
			}
			break;
		}
		case 5:
		{
			char genitor = '\0';
			cout << "�����������ȡ�ĸ�����˫�ף����������˫�ף�����";
			cin >> genitor;
			if (myPTree.parent(genitor))
			{
				cout << "��ȡ�ɹ����ýڵ��˫��Ϊ��" << genitor << endl;
			}
			else
			{
				cout << "��ȡʧ�ܣ� �����ǿ���������߷��ʵ��˸���㣡" << endl;
			}
			break;
		}
		case 6:
		{
			char nodeEelm = '\0';
			char assignment = '\0';
			cout << "����������Ϊ�ĸ���㸳ֵ��";
			cin >> nodeEelm;
			cout << "����������Ϊ�ýڵ㸳ֵΪ��";
			cin >> assignment;
			if (myPTree.assign(nodeEelm, assignment))
			{
				cout << "���" << nodeEelm << "�ɹ���ֵ��" << endl;
				myPTree.print();
			}
			else
			{
				cout << "���" << nodeEelm << "��ֵʧ�ܣ���������û�иýڵ㣡" << endl;
			}
			break;
		}
		case 7:
		{
			int nodeValue = 0;
			cout << "���뷵�صڼ�������ֵ��";;
			cin >> nodeValue;
			cout << "�ýڵ��ֵΪ��" << myPTree.value(nodeValue) << endl;
			break;
		}
		case 8:
			cout << "���ĸ�Ϊ��" << myPTree.root() << endl;
			break;
		case 9:
			cout << "���������Ϊ��" << myPTree.depth() << endl;
			break;
		case 10:
			if (myPTree.empty())
			{
				cout << "��Ϊ�գ�" << endl;
			}
			else
			{
				cout << "���ǿգ�" << endl;
			}
			break;
		case 11:
			if (myPTree.clean())
			{
				cout << "������գ�" << endl;
			}
			else
			{
				cout << "�����ʧ�ܣ�" << endl;
			}
			break;
		case 12:
			myPTree.print();
			break;
		default:
			cout << "�������Ų���ȷ�� ���������룡" << endl;

		}
	}
	system("pause");
	return 0;
}
