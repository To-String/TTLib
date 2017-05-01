#include"CirQueue.h"

namespace tt
{
	void foo()
	{
		return;
	}
	CirQueue::CirQueue(ElemType INI_SIZE)
	{
		assert(INI_SIZE > 0);
		m_data = new int[INI_SIZE];
		if (!m_data)
		{
			cout << "�ڴ����ʧ�ܣ������·��䣡" << endl;
		}
		m_queueSize = INI_SIZE;  //�Ѷ��еĳ�ʼ�������������ֵ����Ա����
		m_front = m_rear = 0;  //m_front����m_rear ���ǿն���
		cout << "***********     ѭ�����г�ʼ���ɹ���   **************" << endl;
	}
	CirQueue::~CirQueue()
	{
		this->destroy();
	}
	CirQueue::ElemType CirQueue::insert(ElemType elem)  //����Ԫ���¶��е�β��
	{
		if (((m_rear + 1) % m_queueSize) == m_front)//�ж϶����������
		{
			return TT_ERROR;
		}
		m_data[m_rear] = elem;    //��Ԫ��elem  ��ӵ����е�ĩβ
		m_rear = (m_rear + 1) % m_queueSize;  //βָ��Ӧ�Դ��ַ�ʽ��1���Ż�ʵ��ѭ�����У� ����ĩβת�������ͷ��
		return TT_OK;
	}
	CirQueue::ElemType CirQueue::remove(ElemType &elemOut)  //ɾ�����еĶ�ͷԪ��
	{
		if (m_front == m_rear)   //�ж�ѭ�������Ƿ�Ϊ��
		{
			return TT_ERROR;
		}
		elemOut = m_data[m_front];  //����ͷԪ�ظ���elem����
		m_front = (m_front + 1) % m_queueSize;  //m_frontָ������ƶ�һλ�����������ת������ͷ��
		return TT_OK;
	}
	CirQueue::ElemType CirQueue::getHead(ElemType &elemOut) //�����д����ҷǿգ���elem���ض��еĶ�ͷԪ��
	{
		if (m_front == m_rear)   //�ж�ѭ�������Ƿ�Ϊ��
		{
			return TT_ERROR;
		}
		elemOut = m_data[m_front];  //�Ѷ�ͷԪ����elem����
		return TT_OK;
	}

	CirQueue::ElemType CirQueue::destroy() //�����д��ڣ���������
	{
		delete[] m_data;
		m_data = nullptr;
		m_front = m_rear = m_queueSize = 0;
		return ((!m_data) && (m_front == m_rear == m_queueSize == 0));  //��һ���жϿ������Ƿ�����
	}
	void CirQueue::show()  //��ʾ���е�����Ԫ��
	{
		if (m_front == m_rear)
		{
			cout << "���󣬴˶�����û�����ݻ��߶���û�н���,�޷���ʾ��" << endl;
		}
		else
		{
			int count = (m_rear - m_front + m_queueSize) % m_queueSize;  //һ����ʱ�����洢�ö��е�Ԫ�ظ���
			cout << "���дӶ�ͷ����β��������Ϊ��";
			for (int i = m_front; i <m_front + count; ++i)
			{
				cout << m_data[i] << ' ';
			}
			cout << endl;
		}
	}
}

//����ѭ�����еĹ���
void testCirQueue()
{
	int allocMemory(0);
	cout << "��������г�ʼ�������������";
	cin >> allocMemory;
	tt::CirQueue myCirQueue(allocMemory);  //��ʼ��һ������
	while (true)
	{
		{
			cout << ("\n***************************************************") << endl
				<< "***************     ѭ�����еĻ�������չʾ    **************" << endl
				<< "*******************************************************" << endl
				<< "**************      ѡ��1���� ���ݽ�����β.       ************" << endl
				<< "**************      ѡ��2���� ɾ������ͷԪ��.     ************" << endl
				<< "***************     ѡ��3���� ��ʾ����ͷԪ��.     ************" << endl
				<< "***************     ѡ��4���� �ж϶����Ƿ�Ϊ��.   ************" << endl
				<< "***************     ѡ��5���� �ж϶����Ƿ�����.   ************" << endl
				<< "***************************************************************" << endl
				<< "***************     ѡ��6���� ��ʾ���е�Ԫ�ظ���. *************" << endl
				<< "***************     ѡ��7���� ��ն���.           *************" << endl
				<< "****************     ѡ��8���� ���ٶ���.           *************" << endl
				<< "****************     ѡ��9���� ��ʾ�����е�����Ԫ��. ***********" << endl
				<< "****************     ѡ��10���� ����.              *************" << endl
				<< "****************     ѡ��0���� �˳�����         *************" << endl
				<< "***************************************************************" << endl
				<< "***************************************************************" << endl;
		}
		cout << "\n*****************     ����������Ҫʹ�õĶ��й��ܵ����   ***************" << endl;
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
		case 1:
		{
			int pushDatas(0);
			cout << "��������Ҫ��ӵ����ݣ�";
			cin >> pushDatas;
			if (myCirQueue.insert(pushDatas))   //������
			{
				cout << "����" << pushDatas << "�ɹ���������У�" << endl;
				myCirQueue.getLength();
				myCirQueue.show();  //��ʾ����Ԫ��
			}
			else
				cout << "Ŀǰ��������, ����" << pushDatas << "����ʧ�ܣ�" << endl;
			break;
		}
		case 2:
		{
			int popDatas(0);
			if (myCirQueue.remove(popDatas))   //ɾ������ͷԪ��
			{
				cout << "����" << popDatas << "�Ӷ����гɹ�ɾ����" << endl;
				myCirQueue.getLength();
				myCirQueue.show();
			}
			else
			{
				cout << "Ŀǰ����Ϊ�գ� ����" << popDatas << "ɾ��ʧ�ܣ�" << endl;
				myCirQueue.getLength();
			}
			break;
		}
		case 3:
		{
			int disHead(0);
			if (myCirQueue.getHead(disHead))   //��ȡ��ͷԪ��
			{
				cout << "����ͷԪ��Ϊ��" << disHead << endl;
				myCirQueue.getLength();
				myCirQueue.show();
			}
			else
			{
				cout << "Ŀǰ����Ϊ�գ� ����" << disHead << "��ȡʧ�ܣ�" << endl;
				myCirQueue.getLength();
			}
			break;
		}
		case 4:
			if (myCirQueue.isEmpty())  //�ж϶����Ƿ��
			{
				cout << "����Ϊ��,���߶�����δ������" << endl;
				myCirQueue.getLength();
			}
			else
			{
				cout << "���зǿգ�" << endl;
				myCirQueue.getLength();
				myCirQueue.show();
			}
			break;
		case 5:
			if (myCirQueue.isFull())  //�ж϶����Ƿ���
			{
				cout << "Ŀǰ������������������������ˣ�" << endl;
				myCirQueue.getLength();
				myCirQueue.show();
			}
			else
			{
				cout << "Ŀǰ���в����������Լ����������ݽ�ջ!" << "\n" << endl;
				myCirQueue.getLength();
				myCirQueue.show();
			}
			break;
		case 6:
			myCirQueue.getLength();  //��ʾ���е�Ԫ�ظ���
			myCirQueue.show();
			break;

		case 7:
			if (myCirQueue.clear())
			{
				cout << "��������գ�" << endl;
				myCirQueue.getLength();
			}
			else
			{
				cout << "�������ʧ�ܣ�" << endl;
				myCirQueue.getLength();
				myCirQueue.show();
			}
			break;
		case 8:
		{
			cout << "��ȷ��Ҫ����һ��������?(����������������(Y/y))";
			char yesOrNo;
			cin >> yesOrNo;
			if ((yesOrNo == 'Y') || (yesOrNo == 'y'))
			{
				if (myCirQueue.destroy())
				{
					cout << "�����ѱ����٣�" << endl;
				}
				else
					cout << "��������ʧ�ܣ�" << endl;
			}
			break;
		}
		case 9:
			myCirQueue.getLength();
			myCirQueue.show();
			break;
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
	testCirQueue();
	system("pause");
	return 0;
}