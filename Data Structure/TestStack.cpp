#include"Stack.h"
namespace tt
{

	Stack::Stack(ElemType initSize)  //��ʼ��ջ
	{
		assert(initSize > 0);
		/// ע��: ����Ӧ����newһ������
		m_base = new ElemType[initSize];  //Ϊջ����ռ�
		if (!m_base)  //��û�з��䵽�ռ䣬����false
		{
			cout << "��ʼ��ʧ��!" << "\n" << endl;
		}
		m_top = m_base;  //�ʼ��ջ������ջ��
		m_stackSize = initSize; //����ջ���������Ϊ100	
		cout << "��ʼ���ɹ���ջ�Ĵ�С��: " << m_stackSize << "\n" << endl;
	}
	Stack::~Stack()  //�ͷŷ�����ڴ�
	{
		/// ע��: ����Ӧ����deleteһ������
		delete[] m_base;
	}
	Stack::Status Stack::push(ElemType e)  //Ϊջ���Ԫ��
	{
		if (m_top - m_base >= m_stackSize)
		{
			return TT_ERROR;
		}
		*m_top = e;
		++m_top;
		return TT_OK;
	}
	Stack::Status Stack::pop(ElemType &elemOut)  //ɾ��ջ��Ԫ��
	{
		if (m_top == m_base) //��ջ��ָ���ջ��ָ���غϣ�˵��ջ��û��Ԫ��
		{
			return TT_ERROR;
		}
		//--Top;  //ջ��ָ���������ƶ�һ��
		elemOut = *--(m_top);  //Ȼ��ȡ��ջ��ָ��ָ�ŵ�Ԫ��
		return TT_OK;
	}
	Stack::Status Stack::destroy()  //�ݻ�ջ
	{
		/// ע��: ����Ӧ����deleteһ������
		delete[] m_base;    //�ѷ�����ڴ��ͷŵ�
		m_base = m_top = NULL;  //ջ��ָ���ջ��ָ�붼ָ���
		m_stackSize = 0;  //Ȼ���ջ�������������Ϊ0
		return TT_OK;
	}
	Stack::Status Stack::isFull()const  //�ж��Ƿ�ջ��
	{
		int temp = (m_top - m_base);
		if (temp == m_stackSize)
		{
			cout << "Ŀǰջ������ջ��δ����!" << "\n" << endl;
		}
		else
			cout << "Ŀǰջ�����������Լ����������ݽ�ջ!" << "\n" << endl;
		return TT_OK;
	}
	Stack::ElemType Stack::getTop(ElemType &elemOut)  //�õ�ջ��Ԫ��
	{
		if (m_base == m_top)
		{
			cout << "���󣬷��ʵ�λ�ò���ȷ" << "\n" << endl;
			return TT_ERROR;
		}
		elemOut = *--(m_top);
		++m_top;
		return TT_OK;
	}
	void Stack::show()  //��ʾջ�е�����Ԫ��
	{
		if (m_base == m_top)
		{
			cout << "��ջ��û�����ݣ�����ջδ������" << "\n" << endl;
		}
		else
		{
			int Temp = (m_top - m_base);  //�����ջ�е�Ԫ�صĸ���
			m_top = m_base;  //��ջ��ָ����ջ��ָ�룬��ջ�׿�ʼ�������
			cout << "��ʾ��ջ�е�����Ԫ�أ�";
			for (int i = 1; i <= Temp; ++i)
			{
				cout << *(m_top)++ << ",";
			}
			cout << endl;
		}
	}
}

void testStack()
	{
		tt::Stack myStack(10);  //����һ������ ������ʼ��100
		while (1)
		{
			{
				cout << "\n===================" << endl;
				cout << "˳��ջ�Ļ�����������." << endl;
				cout << "===================" << "\n" << endl;
				cout << "ѡ��1�������ݽ�ջ." << endl;
				cout << "ѡ��2����ջ�����ݳ�ջ." << endl;
				cout << "ѡ��3�����ж�ջ�Ƿ�Ϊ��." << endl;
				cout << "ѡ��4��������ջ�е�Ԫ�ظ���." << endl;
				cout << "===================" << endl;
				cout << "ѡ��5�����ж�ջ�Ƿ�����." << endl;
				cout << "ѡ��6�������ջ��ջ��Ԫ��." << endl;
				cout << "ѡ��7�������ջ������Ԫ��." << endl;
				cout << "ѡ��8������ջ���." << endl;
				cout << "ѡ��9��������һ��ջ." << endl;
				cout << "===================" << endl;
				cout << "ѡ��10��������." << endl;
				cout << "ѡ��0�����˳�����." << endl << endl;
				cout << "===================" << endl;
			}
			cout << "���������ѡ��: " << endl;
			int userChoice = 0;
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
				int pushData = 0;
				cin >> pushData;
				if (myStack.push(pushData))
				{
					cout << "���� " << pushData << "�Ѿ���ջ�ɹ�!" << "\n" << endl;

				}
				else
					cout << "���� " << pushData << "û����ջ�ɹ�!" << "\n" << endl;
				break;
			}
			case 2:
			{
				int removeData = 0;
				if (myStack.pop(removeData))
				{
					cout << "��ջ�гɹ���ջ������Ϊ: " << removeData << "\n" << endl;
				}
				else
					cout << "��ջʧ��!" << "\n" << endl;
				break;
			}
			case 3:
			{
				if (myStack.isEmpty())
				{
					cout << "Ŀǰ�ǿ�ջ������ջ��δ����!" << "\n" << endl;
				}
				else
					cout << "Ŀǰջ�ǿ�!" << "\n" << endl;
				break;
			}
			case 4:
				myStack.getLength();  //�õ�ջ�д�ʱ��Ԫ�ظ���
				break;
			case 5:
				myStack.isFull();  //�ж��Ƿ�ջ��
				break;
			case 6:
			{
				int getElement = 0;
				if (myStack.getTop(getElement))
				{
					cout << "ջ��Ԫ��Ϊ��" << getElement << "\n" << endl;
				}
				break;
			}
			case 7:
				myStack.show();  //��ʾջ�е�Ԫ�أ���ջ�׿�ʼ�����
				break;

			case 8:
			{
				if (myStack.clear())
				{
					cout << "ջ�Ѿ����." << "\n" << endl;
				}
				else
					cout << "ջû�б����." << "\n" << endl;
				break;
			}
			case 9:
			{
				char yesOrNo;
				cout << "��ȷ��Ҫ����һ��ջ��?(����������������(Y/y))";
				cin >> yesOrNo;
				if ((yesOrNo == 'Y') || (yesOrNo == 'y'))
				{
					if (myStack.destroy())
					{
						cout << "ջ�ѱ�����." << "\n" << endl;
					}
					else
						cout << "ջû�б�����." << "\n" << endl;
				}
				break;
			}
			case 10:
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
		testStack();
		system("pause");
		return 0;
	}