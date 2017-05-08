#include"MySqList.h"

namespace tt
{
	SqList::SqList(ElemType maxSize)
	{
		assert(maxSize > 0);
		m_data = new ElemType[maxSize];
		if (!m_data)
		{
			cout << "�����ڴ����ʧ�ܣ�" << endl;
			system("pause");
			exit(0);
		}
		m_length = 0;
		m_maxLength = maxSize;
		cout << "********************˳����ʼ���ɹ�********************" << "\n" << endl;
	}
	SqList::~SqList()
	{
		this->destroy();
	}
	SqList::ElemType SqList::priorElemAt(ElemType cur_e, ElemType &pri_e)
	{
		int i;
		int *p = m_data;

		for (i = 0; i < m_length; i++, p++) //˳�������֪������forѭ��
		{
			if ((i == 0) && (*p == cur_e))
			{
				return TT_ERROR;
			}
			if (*p == cur_e)       //�ҵ��˵�ǰԪ���Ҳ��ǵ�һ��Ԫ�أ�
			{
				pri_e = *--p;      //����ǰ���������ò���
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
	SqList::ElemType SqList::insertAt(ElemType i, ElemType elem) //����Ԫ�أ�  �����Ա��е�i��λ��֮ǰ������Ԫ��elem
	{                                               //if(i<0 || i>length)
		if ((i < 1) || (i>m_length + 1))  //�����λ�ò�����ʱ�����ش���
		{
			return TT_ERROR;
		}
		if ((m_length == m_maxLength))   //������
		{
			int *allocateMemory = new int[m_data, m_maxLength + LIST_NCREMENT]; // ��allocateMemoryָ����Ϊ�˱���m_data
			if (!allocateMemory)
			{
				cout << "���󣡼��������ڴ�ʧ�ܣ�" << endl;
				system("pause");
				exit(0);
			}
			m_maxLength += LIST_NCREMENT;   //���Ӵ洢����
		}
		if (i <= m_length)  //�������λ�ò��ڱ�β������ֱ�Ӳ�����Ԫ�أ�ֻ�в����11��λ�ò����Ǳ�β
		{
			for (int k = m_length; k >= i; --k)  /*Ԫ��i��������Ԫ�ض�������һ�����ڳ�i���Ŀռ���Ҫ�����Ԫ��,*/
				m_data[k] = m_data[k - 1];  //����m_length=10,m_maxSize=20;��ô��һ�ξ��ǰ��±�Ϊ9��Ԫ�ر���±�Ϊ10��Ԫ��
											//�൱��Ԫ������ƣ�ÿ��ѭ��������ˣ�kΪΪ���Ա�ǰ���ȣ�ÿ��ѭ����һ
		}
		m_data[i - 1] = elem; //����Ԫ�ز����i��λ��֮ǰ
		++m_length;
		return TT_OK;
	}
	SqList::ElemType SqList::removeAt(ElemType i, ElemType &elemOut)  //ɾ��Ԫ�����Ա��е�i������Ԫ�أ�����elem������ֵ,����һ
	{

		if ((i < 1) || (i > m_length))/*����m_length=10,m_maxSize=20;���Ա����ǵ�һ��λ������û�е�0��λ�ã�
									  ɾ�������Ա��λ�ò��ܴ��ڵ�ǰ���Ա�ĳ���,���ߵ�ǰû��Ԫ�أ�˵���˾���ɾ��λ��
									  ������*/
		{
			return TT_ERROR;
		}
		elemOut = m_data[i - 1];  //�ѵ�ǰ�±��Ԫ����elemOutȡ��
		if (i<m_length)     //���Ҫɾ���Ĳ������λ��
		{
			for (int k = i; k < m_length; ++k)     //��ɾ��λ�ú��Ԫ����ǰ�ƶ���  Ҫɾ����λ�ò��ܴ��ڱ�
				m_data[k - 1] = m_data[k];  //��ô��һ��ѭ�����ǰ��±�Ϊ10��Ԫ�ر���±�Ϊ9��Ԫ�أ�ÿ��ѭ����ǰ�ƶ�
		}
		--m_length;
		return TT_OK;
	}
	SqList::ElemType SqList::getAt(ElemType i, ElemType &elemOut) //���Ԫ�صĲ���,�����Ա��е�i��λ�õ�Ԫ�ص�ֵ���ظ�e
	{
		if ((i<1 )|| (i>m_length))  //�����ȡ��Ԫ�ز������Ա��еķ�Χ���ʹ�����
		{
			return TT_ERROR;
		}
		elemOut = m_data[i - 1];
		return TT_OK;
	}

	SqList::ElemType SqList::getIndexElem(const ElemType elem)//�����Ա��в�����elem����ȵ�Ԫ�أ����ص�һ����elem���Ԫ�������Ա��еĵڼ���λ��
	{
		for (int i = 0; i < m_length; ++i)  //����m_length=10,m_maxSize=20;��ô�±����9
		{
			if (m_data[i] == elem)  /*��elem��ȵ�Ԫ�ط��أ���Ϊ���Ա��Ǵ�1��ʼ�ģ�������±���0��ʼ�ģ��������Ա��i��Ԫ�ش洢��
									�����±�i-1��λ�ã����ص�ʱ��Ҫ��1*/
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
			cout << "˳�������գ�" << endl;
		}
		else
			cout << "˳������ʧ�ܣ�" << endl;
	}
	SqList::Status SqList::show()
	{
		int *p = m_data;
		if (m_length == 0)
		{
			cout << "���󣡵�ǰ���Ա�û��Ԫ�أ��޷���ʾ��" << endl;
		}
		else
		{
			cout << "������Ա������Ԫ��Ϊ��";
			for (int k = 0; k < m_length; ++k, ++p)
			{
				cout << *p << " ";   //data[k] Ҳ�ǿ��Ե� 
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
//���Դ���
void testMySqList()
{
	int sizeCapacity(0);
	cout << "����˳�������������";
	cin >> sizeCapacity;
	tt::SqList mySqList(sizeCapacity);
	while (true)
	{
		{
			cout << "*************************************************************" << endl
				<< "*******************   ˳���Ļ�������չʾ   *******************" << endl
				<< "*****************************************************************" << endl
				<< "********************   ѡ��1�������ݲ���.   **********************" << endl
				<< "********************   ѡ��2��������ɾ��.   **********************" << endl
				<< "********************   ѡ��3������ȡԪ��.   **********************" << endl
				<< "********************   ѡ��4��������Ԫ��.   **********************" << endl
				<< "********************   ѡ��5�����Ƿ�Ϊ��.   **********************" << endl
				<< "********************   ѡ��6������ȡ��ĳ���.   **********************" << endl
				<< "********************   ѡ��7�������Ԫ��.   **********************" << endl
				<< "********************   ѡ��8������ʾ����Ԫ��.   **********************" << endl
				<< "*********************  ѡ��9�����������Ա�.  ************************" << endl
				<< "*********************  ѡ��10�������Ԫ�ص�ǰ��.  *****************" << endl
				<< "*********************  ѡ��11�������Ԫ�صĺ��.  *****************" << endl
				<< "*******************    ѡ��12����������      ************************" << endl
				<< "******************     ѡ��0�����˳�����   ************************" << endl
				<< "***********************************************************************" << endl
				<< "***********************************************************************" << endl;
		}
		cout << "\n********************   ����������Ҫʹ�õ�˳����ܵ����   ***************" << endl;
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
			int pushDatas(0);  //Ҫ�����Ԫ��
			int indexLocition(0);  //Ҫ�����λ��
			cout << "����������Ҫ�����Ԫ��λ�ã�";
			cin >> indexLocition;
			cout << "����������Ҫ�����Ԫ�أ�";
			cin >> pushDatas;
			if (mySqList.insertAt(indexLocition, pushDatas))
			{
				cout << "����" << pushDatas << "����ɹ���" << "\n" << endl;
				mySqList.getLength();
				mySqList.show();
			}
			else
				cout << "��ǰ˳����������߲���λ�ò���������" << pushDatas << "����ʧ�ܣ�" << endl;
			break;
		}
		case 2:
		{
			int popDatas(0);  //Ҫɾ����Ԫ��
			int indexLocition(0);  //Ҫɾ����λ��
			cout << "����������Ҫɾ����Ԫ�ص�λ�ã�";
			cin >> indexLocition;
			if (mySqList.removeAt(indexLocition, popDatas))
			{
				cout << "����" << popDatas << "ɾ���ɹ���" << "\n" << endl;
				mySqList.getLength();
				mySqList.show();
			}
			else
				cout << "��ǰ˳���Ϊ�ջ���ɾ��λ�ò���������" << popDatas << "ɾ��ʧ�ܣ�" << endl;
			break;
		}
		case 3:
		{
			int getElem(0);  //Ҫ��ȡ��Ԫ��
			int indexLocition(0);
			cout << "����������Ҫ��ȡԪ�ص�λ�ã�";
			cin >> indexLocition;
			if (mySqList.getAt(indexLocition, getElem))
			{
				cout << "��ȡ��Ԫ��Ϊ��" << getElem << "\n" << endl;
				mySqList.getLength();
				mySqList.show();
			}
			else
				cout << "��ǰ˳���Ϊ�ջ��߻�ȡ��λ�ò���������" << getElem << "��ȡʧ�ܣ�" << endl;
			break;
		}
		case 4:
		{
			int findElem(0);   //����Ԫ��
			cout << "����������Ҫ���ҵ�Ԫ�ص�ֵ��";
			cin >> findElem;
			if (int indexLocition = mySqList.getIndexElem(findElem))
			{
				cout << "��Ҫ���ҵ�Ԫ��λ�ڱ��е�" << indexLocition << "��λ��" << endl;
				mySqList.getLength();
				mySqList.show();

			}
			else
			{
				cout << "��ǰ�����޴�Ԫ��" << endl;
				mySqList.getLength();
			}
			break;
		}
		case 5:
			if (mySqList.isEmpty())  //�ж��Ƿ�Ϊ��
			{
				cout << "Ŀǰ��˳���Ϊ�գ�" << endl;
				mySqList.getLength();
			}
			else
			{
				cout << "Ŀǰ˳���ǿգ�" << endl;
				mySqList.getLength();
				mySqList.show();

			}
			break;
		case 6:
			mySqList.getLength();  //��ȡ���Ա�ĳ���
			break;
		case 7:
			mySqList.clear();//�������Ԫ��   
			mySqList.getLength();
			break;
		case 8:
			mySqList.show();//��ʾ����Ԫ��
			mySqList.getLength();
			break;
		case 9:
		{
			cout << "��ȷ��Ҫ���ٸ�˳�����(����������������(Y/y))";
			char yesOrNo;
			cin >> yesOrNo;
			if ((yesOrNo == 'Y') || (yesOrNo == 'y'))
			{
				if (mySqList.destroy())
				{
					cout << "˳����ѱ�����." << "\n" << endl;
				}
				else
					cout << "˳���û�б�����." << "\n" << endl;
			}
			break;
		}
		case 10:
		{
			int priorElem(0);
			int getElem(0);
			cout << "��������Ҫ�����һ��Ԫ�ص�ǰ������ע�⣺���ܻ�ȡ��һ��Ԫ�صģ���";
			cin >> priorElem;
			if (mySqList.priorElemAt(priorElem, getElem))
			{
				cout << "����Ԫ��" << priorElem << "�ģ�ǰ��Ԫ���ǣ�" << getElem << endl;
				mySqList.show();
			}
			else
			{
				cout << "��ȡǰ��Ԫ��ʧ�ܣ����ܻ�ȡ��һ��Ԫ�ص�ǰ������������û���������Ԫ�أ�" << endl;
				mySqList.show();
			}
			break;
		}
		case 11:
		{
			int backElem(0);
			int getElem(0);
			cout << "��������Ҫ�����һ��Ԫ�صĺ�̣���ע�⣺���ܻ�ȡ���һ��Ԫ�صģ���";
			cin >> backElem;
			if (mySqList.nextElemAt(backElem, getElem))
			{
				cout << "����Ԫ��" << backElem << "�ģ����Ԫ���ǣ�" << getElem << endl;
				mySqList.show();
			}
			else
			{
				cout << "��ȡ���Ԫ��ʧ�ܣ����ܻ�ȡ���һ��Ԫ�صĺ�̻���������û���������Ԫ�أ�" << endl;
				mySqList.show();
			}
			break;
		}
		case 12:
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
	testMySqList();
	system("pause");
	return 0;
}