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
			cout << "��ջ��ʼ�������ڴ�ʧ�ܣ�" << endl;
			system("pause");
			exit(0);
		}
		m_top = m_base;  //�ʼ��ջ������ջ��
		m_stackSize = initSize; //����ջ���������Ϊ100	
		cout << "***********************   ˳��ջ��ʼ���ɹ���  ***********************" << endl;
		cout << "ջ�Ĵ�С��: " << m_stackSize << "\n" << endl;
	}
	Stack::~Stack()  //�ͷŷ�����ڴ�
	{
		this->destroy();
	}
	Stack::Status Stack::push(ElemType e)  //Ϊջ���Ԫ��
	{
		if (m_top - m_base >= m_stackSize)  //ջ����׷�Ӵ洢�ռ�
		{
			int *allocateMemory = new int[m_base, m_stackSize + STACK_INCREMENT];
			if (!allocateMemory)
			{
				cout << "���󣡼��������ڴ�ʧ�ܣ�" << endl;
				system("pause");
				exit(0);
			}
			m_stackSize += STACK_INCREMENT;   //���Ӵ洢����
		}
		*(m_top)++ = e;
		//++m_top;
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
		m_base = nullptr; 
		m_top = nullptr;
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
		elemOut = *(m_top-1);
		return TT_OK;
	}
	void Stack::show()  //��ʾջ�е�����Ԫ��
	{
		if (m_base == m_top)
		{
			cout << "��ջ��û������,�޷���ʾԪ�أ�" << endl;
			system("pause");
			exit(0);
		}
		else
		{
			int Temp = (m_top - m_base);  //�����ջ�е�Ԫ�صĸ���
			m_top = m_base;  //��ջ��ָ����ջ��ָ�룬��ջ�׿�ʼ�������
			cout << "��ʾ��ջ�е�����Ԫ�أ�";
			for (int i = 0; i < Temp; ++i)
			{
				cout << *(m_top)++ << ",";
			}
			cout << endl;
		}
	}
}

void testStack()
	{
	int sizeCapacity(0);
	cout << "����˳��ջ�����������";
	cin >> sizeCapacity;
	tt::Stack myStack(sizeCapacity);  
		while (true)
		{
			{
				cout << "\n*******************************************************************" << endl
					<< "*******************   ˳��ջ�Ļ�������չʾ   *******************" << endl
					<< "*******************************************************************" << endl
					<< "********************   ѡ��1�������ݽ�ջ.   **********************" << endl
					<< "********************   ѡ��2�������ݳ�ջ.   **********************" << endl
					<< "********************   ѡ��3�����ж�ջ�Ƿ�Ϊ��.   **********************" << endl
					<< "********************   ѡ��4������ȡջ�ĳ���.   **********************" << endl
					<< "********************   ѡ��5�����ж�ջ�Ƿ�����.   **********************" << endl
					<< "********************   ѡ��6�������ջ��ջ��Ԫ��.   **********************" << endl
					<< "********************   ѡ��7�������ջ������Ԫ��.   **********************" << endl
					<< "********************   ѡ��8������ջ���.   **********************" << endl
					<< "********************   ѡ��9��������ջ.   **********************" << endl
					<< "********************   ѡ��10��������!   **********************" << endl
					<< "********************   ѡ��0�����˳�����!   **********************" << endl
					<< "***********************************************************************" << endl
					<< "***********************************************************************" << endl;
			}
			cout << "\n*******************   ����������Ҫʹ�õ�ջ���ܵ����  ***************" << endl;
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
					cout << "���� " << pushData << "�Ѿ���ջ�ɹ�!" << endl;
					myStack.getLength();
					myStack.show();
				}
				else
				{
					cout << "���� " << pushData << "��ջʧ�ܣ�" << endl;
					myStack.show();
				}
				break;
			}
			case 2:
			{
				int removeData = 0;
				if (myStack.pop(removeData))
				{
					cout << "���� " << removeData << "�ɹ���ջ��" << endl;
					myStack.show();
				}
				else
				{
					cout << "��ջʧ�ܣ�������ջ��û��Ԫ�أ�" << endl;
					myStack.show();
				}
				break;
			}
			case 3:
			{
				if (myStack.isEmpty())
				{
					cout << "Ŀǰ�ǿ�ջ������ջ��δ����!" << endl;
					myStack.getLength();
				}
				else
				{
					cout << "Ŀǰջ�ǿ�!" << endl;
					myStack.show();
					myStack.getLength();
				}
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
					cout << "ջ��Ԫ��Ϊ��" << getElement << endl;
					myStack.show();
				}
				else
				{
					cout << "��ȡջ��Ԫ��ʧ�ܣ�������ջ��û��Ԫ�أ�" << endl;
					myStack.getLength();
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
					cout << "ջ�Ѿ����." << endl;
					myStack.getLength();
				}
				else
				{
					cout << "ջû�б����." << endl;
					myStack.show();
					myStack.getLength();
				}
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
						cout << "ջ�ѱ�����." << endl;
					}
					else
						cout << "ջ����ʧ��." << endl;
				}
				break;
			}
			case 10:
				system("cls");
				cout << "��Ļ�Ѿ�������������������!" << endl;
				break;
			default:
				cout << "�������Ų���ȷ������������!" << endl;
			}
		}
	}
	int main()
	{
		testStack();
		system("pause");
		return 0;
	}