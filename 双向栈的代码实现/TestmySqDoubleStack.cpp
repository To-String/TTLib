#include"SqDoubleStack.h"

namespace tt
{
	SqDoubleStack::SqDoubleStack(ElemType maxSize)
	{
		assert(maxSize > 0);
		m_data = new ElemType[maxSize];
		if (!m_data)
		{
			cout << "���󣬳�ʼ��˫��ջ���ڴ�ʧ�ܣ�" << endl;
			system("pause");
			exit(0);
		}
		m_top1 = -1;
		m_top2 = maxSize;
		m_maxLength = maxSize;
		cout << "*****************************   ˫��ջ��ʼ���ɹ���  **********************" << endl;

	}
	SqDoubleStack::~SqDoubleStack()
	{
		this->destroy();
	}
	SqDoubleStack::ElemType SqDoubleStack::push(ElemType elem)
	{
		if (m_top1 + 1 == m_top2)  //ջ��, ����ڴ�
		{
			return TT_ERROR;
		}

		int stackNumber(0);
		cout << "����������ҪΪ�ĸ�ջ���Ԫ�ص���ţ�1����2����";
		cin >> stackNumber;
		switch (stackNumber)
		{
		case 1:                    //ջ1��Ԫ�ؽ�ջ
			m_data[++m_top1] = elem;   //����ջ1����top1+1�������Ԫ�ظ�ֵ
			break;
		case 2:                  //ջ2��Ԫ�ؽ�ջ
			m_data[--m_top2] = elem;         //����ջ2����top2-1�������Ԫ�ظ�ֵ
			break;
		default:
			cout << "���������������ȷ�Ľ�ջ�����(ѡ��1��2����" << "\n" << endl;
		}
		return TT_OK;
	}
	SqDoubleStack::ElemType SqDoubleStack::pop(ElemType &elemOut)
	{
		int stackNumber(0);
		cout << "����������ҪΪ�ĸ�ջɾ��Ԫ�ص���ţ�1����2����";
		cin >> stackNumber;
		switch (stackNumber)
		{
		case 1:
			if (m_top1 == -1)   //ջ1��
			{
				cout << "ջ1Ϊ�գ�ɾ��Ԫ��ʧ�ܣ�" << endl;
				return TT_ERROR;
			}
			elemOut = m_data[m_top1--];  //��ջ1��ջ��Ԫ�س�ջ
			break;
		case 2:
			if (m_top2 == m_maxLength)  //ջ2��
			{
				cout << "ջ2Ϊ�գ�ɾ��Ԫ��ʧ�ܣ�" << endl;
				return TT_ERROR;
			}
			elemOut = m_data[m_top2++]; // ��ջ2��ջ��Ԫ�س�ջ
			break;
		default:
			cout << "���������������ȷ��ɾ�������(ѡ��1��2����" << "\n" << endl;
		}
		this->show();
		return TT_OK;
	}
	SqDoubleStack::ElemType SqDoubleStack::getTop(ElemType &elemOut)
	{
		int stackNumber(0);
		cout << "����������Ҫ��ȡ�ĸ�ջ��Ԫ�ص���ţ�1����2����";
		cin >> stackNumber;
		switch (stackNumber)
		{
		case 1:
			if (m_top1 == -1)   //ջ1��
			{
				cout << "ջ1Ϊ�գ���ȡԪ��ʧ�ܣ�" << endl;
				return TT_ERROR;
			}
			elemOut = m_data[m_top1];
			break;
		case 2:
			if (m_top2 == m_maxLength)  //ջ2��
			{
				cout << "ջ2Ϊ�գ���ȡԪ��ʧ�ܣ�" << endl;
				return TT_ERROR;
			}
			elemOut = m_data[m_top2];
			break;
		default:
			cout << "���������������ȷ�Ļ�ȡԪ�ص����(ѡ��1��2����" << "\n" << endl;
		}
		this->show();
		return TT_OK;
	}
	SqDoubleStack::Status SqDoubleStack::show()
	{

		if (m_top1 == -1)   //ջ1��
		{
			cout << "ջ1Ϊ�գ��޷���ʾԪ�أ�" << endl;
		}
		else
		{
			cout << "���ջ1������Ԫ�أ�";
			for (int i = 0; i <= m_top1; ++i)
			{
				cout << m_data[i] << ' ';
			}
			cout << endl;
		}
		if (m_top2 == m_maxLength)  //ջ2��
		{
			cout << "ջ2Ϊ�գ��޷���ʾԪ�أ�" << endl;
		}
		else
		{
			cout << "���ջ2������Ԫ�أ�";
			for (int i = m_maxLength - 1; i >= m_top2; --i)
			{
				cout << m_data[i] << ' ';
			}
			cout << endl;
		}
		this->getLength();
	}
	SqDoubleStack::ElemType SqDoubleStack::clear()
	{
		m_top1 = -1;
		m_top2 = m_maxLength;
		return TT_OK;
	}
	SqDoubleStack::ElemType SqDoubleStack::destroy()
	{
		delete[]m_data;
		m_data = nullptr;
		m_top1 = -1;
		m_top2 = m_maxLength;
		m_maxLength = 0;
		return TT_OK;
	}
}


// ˫��ջ�Ĳ��Ժ���
void testmySqDoubleStack()
{
	int sizeCapacity(0);
	cout << "����˫��ջ�����������";
	cin >> sizeCapacity;
	tt::SqDoubleStack mySqDoubleStack(sizeCapacity);

	while (true)
	{

		{
			cout << "\n*******************************************************************" << endl
				<< "*******************   ˫��ջ�Ļ�������չʾ   *******************" << endl
				<< "*******************************************************************" << endl
				<< "********************   ѡ��1�������ݽ�ջ.   **********************" << endl
				<< "********************   ѡ��2�������ݳ�ջ.   **********************" << endl
				<< "********************   ѡ��3�����ж�ջ�Ƿ�Ϊ��.   **********************" << endl
				<< "********************   ѡ��4������ȡջ�ĳ���.   **********************" << endl
				<< "********************   ѡ��5�����ж�ջ�Ƿ�����.   **********************" << endl
				<< "*************************************************************************" << endl
				<< "********************   ѡ��6�������ջ��ջ��Ԫ��.   **********************" << endl
				<< "********************   ѡ��7�������ջ������Ԫ��.   **********************" << endl
				<< "********************   ѡ��8������ջ���.   **********************" << endl
				<< "********************   ѡ��9��������ջ.   **********************" << endl
				<< "*************************************************************************" << endl
				<< "********************   ѡ��10��������!   **********************" << endl
				<< "********************   ѡ��0�����˳�����!   **********************" << endl
				<< "***********************************************************************" << endl
				<< "***********************************************************************" << endl;
		}
		cout << "\n*******************   ����������Ҫʹ�õ�˫��ջ���ܵ����  ***************" << endl;
		int useChoice(0);
		cout << "���������ѡ��";
		cin >> useChoice;
		if (useChoice == 0)
		{
			cout << "�������˳�����л����ʹ��!" << "\n" << endl;
			break;
		}
		switch (useChoice)
		{
		case 1:
		{
			int insertElem(0);
			cout << "����������Ҫ��ӵ�Ԫ�أ�";
			cin >> insertElem;
			if (mySqDoubleStack.push(insertElem))
			{
				cout << "����" << insertElem << "����ɹ���" << "\n" << endl;
				mySqDoubleStack.show();
			}
			else
			{
				cout << "����" << insertElem << "����ʧ�ܣ�����ջ�Ѿ����ˣ�" << endl;
				mySqDoubleStack.getLength();
				mySqDoubleStack.isFull();
			}
			break;
		}
		case 2:
		{
			int cancelElem(0);
			if (mySqDoubleStack.pop(cancelElem))
			{
				cout << "����" << cancelElem << "ɾ���ɹ���" << "\n" << endl;
			}
			break;
		}
		case 3:
			if (mySqDoubleStack.isEmpty())
			{
				cout << "Ŀǰ˫��ջΪ�գ�" << endl;
				mySqDoubleStack.getLength();
			}
			else
			{
				cout << "Ŀǰ˫��ջ�ǿգ�" << endl;
				mySqDoubleStack.getLength();
			}
			break;
		case 4:
			mySqDoubleStack.getLength();
			break;
		case 5:
			if (mySqDoubleStack.isFull())
			{
				cout << "Ŀǰ˫��ջ���������������Ԫ���ˣ�" << endl;
				mySqDoubleStack.getLength();
			}
			else
			{
				cout << "Ŀǰ˫��ջ���������������Ԫ�أ�" << endl;
				mySqDoubleStack.getLength();
			}
			break;
		case 6:
		{
			int getElem(0);
			if (mySqDoubleStack.getTop(getElem))
			{
				cout << "��ȡ��ջ��Ԫ��Ϊ��" << getElem << endl;
			}
			break;
		}
		case 7:
			mySqDoubleStack.show();
			break;
		case 8:
			if (mySqDoubleStack.clear())
			{
				cout << "˫��ջ�ѱ���գ�" << endl;
				mySqDoubleStack.getLength();
			}
			else
			{
				cout << "˫��ջ���ʧ�ܣ�" << endl;
				mySqDoubleStack.getLength();
			}
			break;
		case 9:
		{
			char yesOrNo('\0');
			cout << "��ȷ��Ҫ����һ��ջ��?(����������������(Y/y))";
			cin >> yesOrNo;
			if ((yesOrNo == 'Y') || (yesOrNo == 'y'))
			{
				if (mySqDoubleStack.destroy())
				{
					cout << "˫��ջ�ѱ�����." << endl;
				}
				else
					cout << "˫��ջ����ʧ��." << endl;
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
	testmySqDoubleStack();
	system("pause");
	return 0;
}