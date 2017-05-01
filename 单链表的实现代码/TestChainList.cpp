#include"ChainList.h"

namespace tt
{
	ChainList::ChainList()
	{
		m_heap = new Node;
		if (!m_heap)
		{
			cout << "�����ڴ����ʧ�ܣ�" << endl;
			system("pause");
			exit(0);
		}
		m_heap->m_next = nullptr;
		m_heap->m_data = 0;
		cout << "********************�������ʼ���ɹ�********************" << "\n" << endl;
	}
	ChainList::~ChainList()
	{
		this->destroy();
	}
	ChainList::Status ChainList::createTail(ElemType *datas, ElemType length)  //�������������,β�巨
	{
		m_heap->m_data = length;
		Node *m = m_heap;    //����һ���ڵ�ָ��ָ��ͷ���
		for (int i = 0; i < length; ++i)
		{
			Node *n = new Node;  //ÿ��ѭ��������Ԫ�ط���ռ�
			n->m_data = datas[i];   //ÿ��ѭ������Ҫ�洢����Ԫ�����δ洢����������
			m->m_next = n;  //��һ��ѭ����ʱ�򣬰��½ڵ�n���ͷ���ĺ�̽ڵ㣬���ǵ�һ��Ԫ�أ�
			m = n;   //Ȼ��ѵ�һ�������m��m������ѭ�����ƶ�
		}
		m->m_next = nullptr;
	}
	/*ChainList::Status ChainList::createHead(ElemType *datum, ElemType extent)  //д��ͷ�巨
	{
	    m_heap->m_data = m_heap->m_data + extent;
	     Node *s = m_heap;
	     for (int i = 0; i < extent; ++i)
	   {
	     Node *p = new Node;
	     p->m_data = datum[i];
	     p->m_next = s->m_next;
	     s->m_next = p;
	   }
	s->m_next = nullptr;
	}*/
	ChainList::ElemType ChainList::insertAt(ElemType i, ElemType elem) //����Ԫ�أ�  �����Ա��е�i��λ��֮ǰ������Ԫ��elem
	{
		Node *q = m_heap;  //���Ȱ�qָ��ָ��ͷ���
		int j = 1;
		while (q && j < i)  //��q��û��Ϊ��ʱ�� ��ǰ��λ���Ѿ�������Ҫ���ҵ�λ�ã�ֱ���˳�ѭ��
		{
			q = q->m_next;
			++j;

		}
		if (!q || j > i)  //q��û��ָ��գ�����ǰ��λ���Ѿ�������Ҫ�ҵ�λ�ã�������û���ҵ����ͷ��ش���
		{
			return TT_ERROR;
		}

		Node *s = new Node;
		s->m_data = elem;
		s->m_next = q->m_next;     //��q�ĺ�̽ڵ���s�ĺ�̽ڵ�
		q->m_next = s;            //��s���q�ĺ�̽ڵ�
		++m_heap->m_data;
		return TT_OK;
	}
	ChainList::ElemType ChainList::removeAt(ElemType i, ElemType &elemOut)
	{

		Node *s = m_heap;
		int j = 1;
		while ((s->m_next) && (j < i))
		{                    //��p�ĺ�̽ڵ㻹û��ָ���ʱ�� ��ǰ��λ���Ѿ�������Ҫ���ҵ�λ�ã�ֱ���˳�ѭ��
			s = s->m_next;  //s��ָ������ƶ�����ָ����һ���ڵ�
			++j;
		}
		if (!(s->m_next) || (j > i))
		{
			return TT_ERROR;
		}
		Node *q = s->m_next;   //��s�ĺ�̽ڵ���q
		s->m_next = q->m_next;    //�ٰ�q�ĺ�̽ڵ���s�ĺ�̽ڵ�
		elemOut = q->m_data;  //��q�ڵ�����ݸ�element
		delete q;   //��ϵͳ���մ˽ڵ㣬�ͷ��ڴ�
		--m_heap->m_data;
		return TT_OK;
	}
	ChainList::ElemType ChainList::getAt(ElemType i, ElemType &elemOut)
	{
		Node *q = m_heap->m_next;    //��qָ������ĵ�һ���ڵ�
		if (i == 0)  //�����ҵ�λ�ò��Ϸ�ʱ���ͷ���false
		{
			return TT_ERROR;
		}
		int j = 1;  //��һ���ڵ㿪ʼѭ�����������ǵ�ǰλ��
		while (q && j < i)
		{                       /*��q��û��Ϊ��ʱ�� ��ǰ��λ���Ѿ�������Ҫ���ҵ�λ�ã�ֱ���˳�ѭ��*/

			q = q->m_next;
			++j;
		}
		if (!q || j < i)   //q��û��ָ��գ�����ǰ��λ���Ѿ�������Ҫ�ҵ�λ�ã�������û���ҵ����ͷ��ش���
		{
			return TT_ERROR;
		}
		elemOut = q->m_data;   //ȡ��i��Ԫ�ص�����
		return TT_OK;
	}
	ChainList::ElemType ChainList::getIndexElemAt(ElemType &i, ElemType elemOut)//�����Ա��в�����elem����ȵ�Ԫ�أ����ص�һ����elem���Ԫ�������Ա��еĵڼ���λ��
	{
		Node *p = m_heap->m_next;    //�ӵ�һ����㿪ʼ����
		int searchLocation = 1;
		while (p && (p->m_data != elemOut))  //ֻҪp��Ϊ�գ� ��û���ҵ�Ԫ�أ�ѭ������
		{
			++searchLocation;
			p = p->m_next;
		}
		if (!p)
		{
			return TT_ERROR;
		}
		i = searchLocation;
		return TT_OK;
	}
	ChainList::ElemType ChainList::clear()
	{
		Node *m = m_heap->m_next;  //��ͷ�ڵ�ĺ�̽ڵ���m
		while (m != nullptr)   //�����нڵ����ʱ����ѭ������
		{
			Node *n = m->m_next;  //Ȼ���m�ĺ�̽ڵ���n
			delete m;   //ɾ����һ���ڵ㣬ÿѭ��һ�ζ�ɾ����һ���ڵ�
			m = n;  //Ȼ���n���m�� n�ͱ���˵�һ���ڵ�
		}
		m_heap->m_next = nullptr;   //ͷ���ָ��ĵ�һ��������
		m_heap->m_data = 0;
		return TT_OK;
	}
	ChainList::Status ChainList::show()
	{
		if (m_heap->m_data == 0)
		{
			cout << "�˵�������û�����ݣ��޷���ʾ��" << "\n" << endl;
		}
		else
		{
			Node *p = m_heap->m_next;
			cout << "��������������Ԫ�أ�";
			while (p)
			{
				cout << p->m_data << ",";
				p = p->m_next;

			}
			cout << endl;
		}
	}
	ChainList::ElemType ChainList::destroy()  //����������
	{
		while (m_heap)
		{
			Node *s = m_heap->m_next;
			delete m_heap;
			m_heap = s;
		}
		m_heap = nullptr;
		return TT_OK;
	}
}

//����myChainList
void testChainList()
{
	tt::ChainList myChainList;    //����һ�����������


	int myLength(0);    //�������������,β�巨
	cout << "�봴���������ݵ�����";
	cin >> myLength;
	int *myDatas = new int[myLength];
	cout << "������������" << myLength << "�����ݣ��м��Իس���������" << endl;

	for (int i = 0; i < myLength; ++i)
	{

		cin >> myDatas[i];  //����Ҫ�洢�����ݵ�ֵ
	}
	myChainList.createTail(myDatas, myLength);   //����create���� ����������
	myChainList.getLength();
	myChainList.show();
	cout << "\n\n";

	while (true)
	{
		{
			cout << "*************************************************************" << endl
				<< "*******************   ������Ļ�������չʾ   *******************" << endl
				<< "*****************************************************************" << endl
				<< "********************   ѡ��1�������ݲ���.   **********************" << endl
				<< "********************   ѡ��2��������ɾ��.   **********************" << endl
				<< "********************   ѡ��3������ȡԪ��.   **********************" << endl
				<< "********************   ѡ��4��������Ԫ��.   **********************" << endl
				<< "********************   ѡ��5�����Ƿ�Ϊ��.   **********************" << endl
				<< "********************   ѡ��6������ȡ���Ա�ĳ���.   **********************" << endl
				<< "********************   ѡ��7�������Ԫ��.   **********************" << endl
				<< "********************   ѡ��8�����������Ԫ��. ************************" << endl
				<< "********************   ѡ��9�������ٵ�����. ************************" << endl
				<< "********************   ѡ��10����������      ************************" << endl
				<< "********************   ѡ��0�����˳�����   ************************" << endl
				<< "***********************************************************************" << endl
				<< "***********************************************************************" << endl;
		}
		cout << "\n********************   ����������Ҫʹ�õĵ������ܵ����   ***************" << endl;
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
			if (myChainList.insertAt(indexLocition, pushDatas))
			{
				cout << "����" << pushDatas << "����ɹ���" << "\n" << endl;
				myChainList.getLength();
				myChainList.show();
			}
			else
				cout << "����" << pushDatas << "����ʧ�ܣ������ǵ�������δ����" << endl;
			break;
		}
		case 2:
		{
			int popLocation(0);
			int popElement(0);
			cout << "������Ҫɾ�����ݵڼ���λ�ã�";
			cin >> popLocation;
			if (myChainList.removeAt(popLocation, popElement))
			{
				cout << "����" << popElement << "ɾ���ɹ���" << endl;
				myChainList.getLength();
				myChainList.show();
			}
			else
				cout << "����" << popElement << "ɾ��ʧ�ܣ�" << endl;
			break;
		}
		case 3:
		{
			int getElem(0);        //Ҫ��ȡ��Ԫ��
			int indexLocition(0);
			cout << "����������Ҫ��ȡԪ�ص�λ�ã�";
			cin >> indexLocition;
			if (myChainList.getAt(indexLocition, getElem))
			{
				cout << "��ȡ��Ԫ��Ϊ��" << getElem << "\n" << endl;
				myChainList.getLength();
				myChainList.show();
			}
			else
			{
				cout << "��ǰ������Ϊ�ջ�����δ����������" << getElem << "��ȡʧ�ܣ�" << endl;
				myChainList.getLength();
			}
			break;
		}
		case 4:
		{
			int findElement(0);   //����Ԫ��
			int findLocation(0);
			cout << "������Ҫ���ҵ�Ԫ�أ�";
			cin >> findElement;
			if (myChainList.getIndexElemAt(findLocation, findElement))
			{
				cout << "�ҵ���Ԫ��" << findElement << "�����ڱ��е�����ֵΪ��" << findLocation << "\n" << endl;
				myChainList.getLength();
				myChainList.show();
			}
			else
			{
				cout << "�����в����������ҵ�ֵ��" << "\n" << endl;
				myChainList.getLength();
				myChainList.show();
			}
			break;
		}
		case 5:
			if (myChainList.isEmpty())   //�ж��Ƿ�Ϊ��
			{
				cout << "Ŀǰ�����Ա�Ϊ�գ�" << endl;
				myChainList.getLength();
			}
			else
			{
				cout << "Ŀǰ˳���ǿգ�" << endl;
				myChainList.getLength();
				myChainList.show();
			}
			break;
		case 6:
		{
			myChainList.getLength();
			myChainList.show();
			break;
		}
		case 7:
			if (myChainList.clear())  //��յ�����
			{
				cout << "Ŀǰ�������Ѿ�����գ�" << endl;
				myChainList.getLength();
			}
			else
			{
				cout << "Ŀǰ������ǿգ�" << endl;
				myChainList.getLength();
				myChainList.show();
			}
			break;
		case 8:
			myChainList.show();  //��ʾ����Ԫ��
			myChainList.getLength();
			break;
		case 9:
		{                                                //���ٵ�����
			cout << "��ȷ��Ҫ���ٸõ�������(����������������(Y/y))";
			char yesOrNo;
			cin >> yesOrNo;
			if ((yesOrNo == 'Y') || (yesOrNo == 'y'))
			{
				if (myChainList.destroy())
				{
					cout << "�������ѱ�����." << "\n" << endl;
				}
				else
					cout << "����������ʧ��." << "\n" << endl;
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
	delete[] myDatas;
	myDatas = nullptr;
}
int main()
{
	testChainList();
	system("pause");
	return 0;
}