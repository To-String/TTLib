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
	LinkStack();  //��ʼ��һ��ջ
	~LinkStack();
	ElemType push(ElemType elem);  //��ջ���ڣ�������Ԫ��e ��Ϊջ��Ԫ��
	ElemType pop(ElemType &elemOut); //��ջ���ڣ�ɾ��ջ��Ԫ��
	Status  isEmpty()const; //�ж�ջ�Ƿ�Ϊ��

	ElemType getTop(ElemType &elemOut);  //��ջ�����ҷǿգ���e����ջ��ջ��Ԫ��
	void getLength()const;  //����ջ�е�Ԫ�ظ���
	void show();  //��ʾջ������Ԫ��

	Status clear();  //��ջ���
	Status destroy();  //��ջ���ڣ���������
private:
	Node *m_heap;  //����һ��ͷ���,����ջ��û��ջ��ָ��
	ElemType m_stackLength;  //ջ�ĵ�ǰ��Ԫ�ظ���
};
LinkStack::LinkStack()
{
	 m_heap = new Node;
	if (!m_heap)
	{
		cout << "�����ڴ����ʧ�ܣ�" << endl;
	}
	m_heap->m_next = nullptr;
	m_stackLength = 0;
	cout << "*******************��ջ��ʼ���ɹ�*****************" << endl;
}
LinkStack::~LinkStack()
{
	this->destroy();
}
ElemType LinkStack::push(ElemType elem)      //��ջ���ڣ�������Ԫ��e ��Ϊջ��Ԫ��
{
	Node *p = new Node;  //��һ���½������ڴ�
	if (!p)
	{
		return TT_ERROR;
	}
	p->m_data = elem;    //����Ԫ�������������
	p->m_next = m_heap->m_next;    //��ջ��Ԫ�ر��p�ĺ�̽��
	m_heap->m_next = p; //�ڰ�p���ͷ���ĺ�̽�㣬��ôp����ջ��Ԫ��
	++m_stackLength;   //��ջ�ĵ�ǰ����+1
	return TT_OK;
}
ElemType LinkStack::pop(ElemType &elemOut)  //ջ�����ݳ�ջ
{
	if (m_stackLength==0)
	{
		return TT_ERROR;
	}
	Node *p = m_heap->m_next;  //���Ȱ�ջ��Ԫ�ظ�p
	elemOut = p->m_data;  //���ջ��Ԫ�ص�����
	m_heap->m_next = p->m_next;   //�ڰ�p�ĺ�̽ڵ���ͷ���ĺ�̽ڵ㣬
	delete p;   //�ͷ�ջ��Ԫ��
	--m_stackLength;
	return TT_OK;
}
ElemType LinkStack::getTop(ElemType &elemOut)  //���ջ��Ԫ��
{
	if (m_stackLength == 0)
	{
		return TT_ERROR;
	}
	//Node *p = m_heap->m_next;  
	elemOut = m_heap->m_next->m_data;  //��ջ��Ԫ�ص����ݷ���
	return TT_OK;
}

void LinkStack::show()
{
	if (m_stackLength == 0)
	{
		cout << "��ջ��û�����ݣ�����ջδ������" << "\n" << endl;
	}
	else
	{
		Node *p = m_heap->m_next;
		cout << "���ջ������Ԫ���У�";
		while (p)
		{
			cout << p->m_data << ",";
			p = p->m_next;

		}
		cout << endl;
	}
}
Status LinkStack::clear()  //���һ��ջ��������ͷ���
{
	Node *m = m_heap->m_next;  
	while (m != nullptr)  
	{
		Node *n = m->m_next;  //�ѵڶ���Ԫ�ر��n
		delete m;    //�ͷ�ջ��Ԫ��
		m = n;    //��n���ջ��Ԫ��
	}
	m_heap->m_next = nullptr;  //ͷ����ָ����ָ���
	m_stackLength = 0;  //��ǰ�������
	return TT_OK;
}
Status LinkStack::destroy()   //����һ��ջ������ͷ���
{
	while (m_heap)  //ֻҪͷ��㲻Ϊ�գ�ѭ������
	{
		Node *s = m_heap->m_next;  //��ջ��Ԫ�ر��s
		delete m_heap;  //���ͷ�ͷ��㣬
		m_heap = s;  //Ȼ���ջ��Ԫ��s���ͷ��㣬ͷ��������ѭ��������ƶ���
	}
	m_heap = nullptr;  //ָ����0����ֹҰָ��
	m_stackLength = 0;
	return TT_OK;
}
inline Status LinkStack::isEmpty()const  //�ж�ջ�Ƿ�Ϊ��
{
	return (m_stackLength == 0);
}
inline void LinkStack::getLength()const  //�õ�ջ�����ڵ�Ԫ�ظ���
{
	cout << "ջ�е�Ԫ�ظ���Ϊ��" << m_stackLength << endl;
}
void testLinkStack()
{
	LinkStack myStack;  //��ʼ��һ��ջ
	while (true)
	{
		{
			cout << "\n************************************************" << endl
				<< "*****           ��ջ�Ļ���������ʾ        *****" << endl
				<< "*************************************************" << endl
				<< "*****            ѡ��1���� ���ݽ�ջ.        *****" << endl
				<< "*****            ѡ��2����ջ��Ԫ�س�ջ.     *****" << endl
				<< "*****            ѡ��3������ʾջ�е���������.****" << endl
				<< "*****            ѡ��4�������ջ��Ԫ��.    *****" << endl
				<< "*****            ѡ��5�����ж�ջ�Ƿ�Ϊ��ջ. *****" << endl
				<< "*************************************************" << endl
				<< "*****            ѡ��6�������ջ�е�Ԫ�ظ���.*****" << endl
				<< "*****            ѡ��7�������ջ�е�����Ԫ��.*****" << endl
				<< "*****            ѡ��8��������һ��ջ.         *****" << endl
				<< "*****            ѡ��9��������.               *****" << endl
				<< "*****            ѡ��0�����˳�����          *****" << endl
				<< "*****************************************************" << endl
				<< "*****************************************************" << endl;
		}
		cout << "\n*************����������Ҫʹ�õ���ջ���ܵ����***************" << endl;
		cout << "������ѡ��";
		int userChoice(0);
		cin >> userChoice;
		if (userChoice == 0)
		{
			cout << "�������˳�����л����ʹ��!" << "\n" << endl;
			break;
		}
		switch (userChoice)
		{
		case 1:
		{
			cout << "������Ҫ��ջ�����ݣ�";
			int pushDatas(0);
			cin >> pushDatas;
			if (myStack.push(pushDatas))
			{
				cout << "����" << pushDatas << "��ջ�ɹ�." << "\n" << endl;
				myStack.getLength();
				myStack.show();
			}
			else
				cout << "�ڴ����ʧ�ܣ�����" << pushDatas << "��ջʧ��." << "\n" << endl;
			break;
		}
		case 2:
		{
			int removeData(0);
			if (myStack.pop(removeData))
			{
				cout << "����" << removeData << "��ջ�гɹ���ջ." << "\n" << endl;
				myStack.getLength();
				myStack.show();
			}
			else
			{
				cout << "ĿǰջΪ�գ�����" << removeData << "��ջʧ�ܣ�" << "\n" << endl;
				myStack.getLength();
			}
			break;
		}
		case 3:
			myStack.getLength();
			myStack.show();   //��ʾջ�е���������Ԫ��
			break;
		case 4:
		{
			int getTopElem(0);
			if (myStack.getTop(getTopElem))
			{
				cout << "ջ��Ԫ��Ϊ��" << getTopElem << "\n" << endl;
				myStack.getLength();
				myStack.show();
			}
			else
			{
				cout << "ĿǰջΪ��,ջ��Ԫ�س�ջʧ��" << "\n" << endl;
				myStack.getLength();
			}
			break;
		}
		case 5:
			if (myStack.isEmpty())
			{
				cout << "Ŀǰ�ǿ�ջ������ջ��ʼ��ʧ��!" << "\n" << endl;
				myStack.getLength();
			}
			else
			{
				cout << "Ŀǰջ�ǿ�!" << "\n" << endl;
				myStack.getLength();
				myStack.show();
			}
			break;
		case 6:
			myStack.getLength();  //���ջ�е�Ԫ�ظ���
			myStack.show();
			break;
		case 7:
			if (myStack.clear())
			{
				cout << "ջ�ѱ���գ�" << "\n" << endl;
				myStack.getLength();
			}
			else
			{
				cout << "ջ���ʧ��" << "\n" << endl;
				myStack.getLength();
				myStack.show();
			}
			break;
		case 8:
		{
			cout << "��ȷ��Ҫ����һ��ջ��?(����������������(Y/y))";
			char yesOrNo;
			cin >> yesOrNo;
			if ((yesOrNo == 'Y') || (yesOrNo == 'y'))
			{
				if (myStack.destroy())
				{
					cout << "ջ�ѱ�����." << "\n" << endl;
				}
				else
					cout << "ջ����ʧ��." << "\n" << endl;
			}
			break;
		}
		case 9:
			system("cls");
			cout << "��Ļ�Ѿ�������������������!" << "\n" << endl;
			break;
		default:
			cout << "�������Ų���ȷ������������!" << "\n" << endl;
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