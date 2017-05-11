#include"MyDuLinkList.h"

namespace tt
{
	DuLinkList::DuLinkList()
	{
		m_heap = new DulNode;
		if (!m_heap)
		{
			cout << "�����ڴ����ʧ�ܣ�" << endl;
			system("pause");
			exit(0);
		}
		m_heap->m_next = m_heap;
		m_heap->m_prior = m_heap;
		cout << "\n********************˫���ѭ�������ʼ���ɹ���************************" << endl;
	}
	DuLinkList::~DuLinkList()
	{
		this->destroy();

	}

	DuLinkList::Status DuLinkList::createTail(ElemType *datas, ElemType length)//��������Ϊlength����������ͨ������ָ�����������β�巨
	{
		DulNode *m = m_heap;
		for (int i = 0; i < length; ++i)
		{
			DulNode *p = new DulNode;
			if (!p)
			{
				cout << "�����޷������ڴ棬��������ʧ�ܣ�" << endl;
				system("pause");
				exit(0);
			}
			p->m_data = datas[i];

			m->m_next = p;   //���Ƚ�����һ���ڵ��ʱ��ͷ���ĺ�̽ڵ���p
			p->m_prior = m;   //p��ǰ���ڵ���ͷ���
			p->m_next = m_heap;  //Ȼ���һ���ڵ�ĺ�̱��ͷ���
			m_heap->m_prior = p;  //��ôͷ����ǰ�����p��   �����ͻ��γ�һ����β��ӵ�˫��ѭ������
			m = p;  //���ѵ�һ���ڵ���m��  �����������ϲ���ѭ��
		}
	}
	DuLinkList::ElemType DuLinkList::insertAt(ElemType i, ElemType elem)
	{
		DulNode *p = m_heap;  //pָ��ͷ���
		if ((i < 1) || (i > getLength() + 1))
		{
			return TT_ERROR;
		}
		int j = 1;
		while (j < i)
		{
			p = p->m_next;
			++j;
		}
		DulNode *s = new DulNode;
		s->m_data = elem;     //��Ҫ�洢�����ݷ�����������
		s->m_prior = p;         //���Ȱ�p���s��ǰ�����
		s->m_next = p->m_next;   //��p�ĺ�̽ڵ���s�ĺ�̽ڵ�
		p->m_next->m_prior = s;   //��s���p�ĺ�̽ڵ��ǰ��
		p->m_next = s;   //p�ĺ�̽ڵ���s

		return TT_OK;
	}
	DuLinkList::ElemType DuLinkList::removeAt(ElemType i, ElemType &elemOut)
	{
		DulNode *p = m_heap;  //pָ��ͷ���
		if ((i < 1) || (i >getLength()))
		{
			return TT_ERROR;
		}
		int j = 1;
		while (j <= i)
		{
			p = p->m_next;
			j++;
		}
		elemOut = p->m_data;
		p->m_prior->m_next = p->m_next;  //��p�ĺ�̽ڵ���p��ǰ�����ĺ�̽ڵ�
		p->m_next->m_prior = p->m_prior;   //��p��ǰ�������p�ĺ�̽ڵ��ǰ�����
		delete p;  //�ͷŽڵ���ڴ�
		return TT_OK;
	}
	DuLinkList::ElemType DuLinkList::getAt(ElemType i, ElemType &elemOut)
	{
		DulNode *q = m_heap->m_next;    //��qָ������ĵ�һ���ڵ�
		if ((i < 1) || (i >getLength()))  // �ж�i��λ���Ƿ񳬹�����ĳ���
		{
			return TT_ERROR;
		}
		int j = 1;
		while ((q != m_heap) && (j < i))  //���q�ĺ�̲���m_heap��  ��ǰλ��j=1С��Ҫ���ҵ�λ�ã�ѭ������
		{                               //ɾ����һ��Ԫ��ʱ���˳�ѭ��

			q = q->m_next;
			++j;
		}
		if (!(q != m_heap) || (j > i))   //ɾ����һ��Ԫ��ʱ��  j��û�б�i�� q�ĺ�̲���m_heapȡ�棬  ֱ���˳�ѭ��
		{
			return TT_ERROR;
		}
		elemOut = q->m_data;
		return TT_OK;
	}
	DuLinkList::ElemType DuLinkList::getIndexElemAt(ElemType &i, ElemType elemOut)  //������elem��ȵ�Ԫ�أ����ص�һ����elem���Ԫ���������е����
	{
		DulNode *p = m_heap->m_next;    //�ӵ�һ����㿪ʼ����
		int searchLocate = 1;
		while ((p != m_heap) && (p->m_data != elemOut)) //pδ����ͷʱ��  p��ָ���򲻵���Ҫ���ҵ�Ԫ��
		{
			++searchLocate;
			p = p->m_next;
		}
		if (!(p != m_heap))
		{
			return TT_ERROR;
		}
		i = searchLocate;   //����Ҫ���ҵ�Ԫ�ص�λ�õ����
		return TT_OK;
	}

	DuLinkList::ElemType DuLinkList::getLength()const
	{
		DulNode *p = m_heap->m_next;   //pָ���һ�����
		int i = 0;
		while (p != m_heap) //pδ����ͷʱ
		{
			++i;
			p = p->m_next;

		}
		return i;
	}

	DuLinkList::ElemType DuLinkList::destroy()
	{
		DulNode *p = m_heap->m_next; //pָ���һ�����
		while (p != m_heap)   //pû����ͷ
		{
			DulNode *q = p->m_next;  //��һ��ѭ�����ѵڶ���Ԫ�ر��q
			delete p;  //��һ��ѭ����  �ͷŵ�һ��Ԫ��
			p = q;   //��һ��ѭ����  �ѵڶ���Ԫ�ر��p��  ��ô����p���ǵ�һ��Ԫ��
		}
		delete m_heap;  //����Ԫ��ɾ�����  ��Ϊ�����Ǵӵ�һ���ڵ㿪ʼɾ���ģ�  ͷ���û��ɾ����  �������Ҫɾ��ͷ���
		m_heap = nullptr;
		return TT_OK;
	}
	DuLinkList::ElemType DuLinkList::clear()
	{
		DulNode *p = m_heap->m_next; //pָ���һ�����
		while (p != m_heap) //pû����ͷ
		{
			DulNode *q = p->m_next;
			delete p;
			p = q;
		}
		m_heap->m_next = m_heap->m_prior = m_heap; //ͷ��������ָ�����ָ������
		return TT_OK;
	}

	DuLinkList::Status DuLinkList::show()
	{
		if (isEmpty())
		{
			cout << "��ǰ������û��Ԫ�أ��޷���ʾ��" << endl;
		}
		else
		{
			DulNode *p = m_heap->m_next;   //pָ���һ�����
			int temp(0);  //������ʾ�����еĸ���
			cout << "���˫��ѭ�������е�����Ԫ�أ�";
			while (p != m_heap)  //pδ����ͷ
			{
				++temp;
				cout << (p->m_data) << " ";
				p = p->m_next;
			}
			cout << "\n��ǰ˫��ѭ�������е�Ԫ������Ϊ��" << temp << endl;
		}
	}
	DuLinkList::Status DuLinkList::traverseBack()  //����������������Ԫ��
	{
		if (isEmpty())
		{
			cout << "��ǰ������û��Ԫ�أ��޷���ʾ��" << endl;
		}
		else
		{
			DulNode *m = m_heap->m_prior;  //��mָ�����һ��Ԫ��
			cout << "�������˫�������е�����Ԫ�أ�";
			while (m != m_heap)
			{
				cout << (m->m_data) << " ";
				m = m->m_prior;   //���Ԫ�غ�m��ǰǰ��
			}
			cout << endl;
		}

	}
	DuLinkList::ElemType DuLinkList::priorElemAt(ElemType cur_e, ElemType &pri_e)//��cur_e�����������Ԫ�أ��Ҳ��ǵ�һ��������pre_e��������ǰ��
	{
		DulNode *p = m_heap->m_next->m_next;  //pָ��ڶ���Ԫ��
		while (p != m_heap)
		{
			if (p->m_data == cur_e)  //pָ�����������cur_eֵ���бȽ��ж�
			{
				pri_e = p->m_prior->m_data;  //��p��ǰ������ֵ����pre_e��pre_e���淵��
				return TT_OK;;
			}
			p = p->m_next;
		}
		return TT_ERROR;
	}
	DuLinkList::ElemType DuLinkList::nextElemAt(ElemType cur_e, ElemType &Nex_e) //��cur_e�����������Ԫ��,�Ҳ������һ��,����next_e�������ĺ�̣�
	{
		DulNode *p = m_heap->m_next->m_next;   //ָ��ڶ���Ԫ�أ� ���ָ���һ��Ԫ�صĻ���������һ��Ԫ�صĺ�̣��ͻ��������ֵ
		while (p != m_heap)
		{
			if (p->m_prior->m_data == cur_e)
			{
				Nex_e = p->m_data;         //��p��ָ����ֵ����Nex_e��Nex_e���淵��
				return TT_OK;
			}
			p = p->m_next;
		}
		return TT_ERROR;
	}
}
// MyDuLinkList �Ĳ��Ժ���
void testMyDuLinkList()
{
	tt::DuLinkList  MyDuLinkList;

	int myLength(0);    //�����������,β�巨
	cout << "�봴���������ݵ�����";
	cin >> myLength;
	int *myDatas = new int[myLength];
	cout << "������������" << myLength << "�����ݣ��м��Իس���������" << endl;

	for (int i = 0; i < myLength; ++i)
	{

		cin >> myDatas[i];  //����Ҫ�洢�����ݵ�ֵ
	}
	MyDuLinkList.createTail(myDatas, myLength);   //����createTail���� ����������
	MyDuLinkList.show();

	while (true)
	{
		{
			cout << "\n*************************************************************" << endl
				<< "*******************   ˫��ѭ�������������չʾ   *******************" << endl
				<< "*****************************************************************" << endl
				<< "********************   ѡ��1�������ݲ���.   **********************" << endl
				<< "********************   ѡ��2��������ɾ��.   **********************" << endl
				<< "********************   ѡ��3������ȡԪ��.   **********************" << endl
				<< "********************   ѡ��4��������Ԫ��.   **********************" << endl
				<< "********************   ѡ��5�����Ƿ�Ϊ��.   **********************" << endl
				<< "********************   ѡ��6������ȡ������.   **********************" << endl
				<< "********************   ѡ��7�������Ԫ��.   **********************" << endl
				<< "********************   ѡ��8�����������Ԫ��. ************************" << endl
				<< "********************   ѡ��9������������. ************************" << endl
				<< "*********************  ѡ��10�������Ԫ�ص�ǰ��.  *****************" << endl
				<< "*********************  ѡ��11�������Ԫ�صĺ��.  *****************" << endl
				<< "*********************  ѡ��12���������������Ԫ��.  *****************" << endl
				<< "********************   ѡ��13����������      ************************" << endl
				<< "********************   ѡ��0�����˳�����   ************************" << endl
				<< "***********************************************************************" << endl
				<< "***********************************************************************" << endl;
		}
		cout << "\n*******************   ����������Ҫʹ�õ�˫��ѭ�������ܵ����  ***************" << endl;
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
		{                                 //����Ԫ��
			int pushLocate(0);
			int pushElement;
			cout << "�����������Ԫ�ص�λ�ã�";
			cin >> pushLocate;
			cout << "����������ӵ�Ԫ�أ�";
			cin >> pushElement;
			if (MyDuLinkList.insertAt(pushLocate, pushElement))
			{
				cout << "����" << pushElement << "����ɹ���" << endl;
				MyDuLinkList.show();
			}
			else
				cout << "�����λ�ò���������" << pushElement << "����ʧ�ܣ�" << endl;
			break;
		}
		case 2:
		{                                                //ɾ��Ԫ��
			int cancelElem(0);  //Ҫɾ����Ԫ��
			int cancelLocate(0);  //Ҫɾ����λ��
			cout << "��������Ҫɾ����λ�ã�";
			cin >> cancelLocate;
			if (MyDuLinkList.removeAt(cancelLocate, cancelElem))
			{
				cout << "����" << cancelElem << "ɾ���ɹ���" << endl;
				MyDuLinkList.show();
			}
			else
				cout << "ɾ����λ�ò��������������û��Ԫ�أ�����ɾ��ʧ�ܣ�" << endl;
			break;
		}
		case 3:                                   //��ȡԪ��
		{
			int getLocate(0);
			int getElem(0);
			cout << "��������Ҫ��ȡ��λ�ã�";
			cin >> getLocate;
			if (MyDuLinkList.getAt(getLocate, getElem))
			{
				cout << "��ȡ��Ԫ��Ϊ��" << getElem << endl;
				MyDuLinkList.show();
			}
			else
			{
				cout << "��ȡ��λ�ò��������������û��Ԫ�أ���ȡ����ʧ�ܣ�" << endl;
				MyDuLinkList.getLength();
			}
			break;
		}
		case 4:
		{                                             //����Ԫ��
			int getLocate(0);
			int findElem(0);
			cout << "����������Ҫ���ҵ�Ԫ�ص�ֵ��";
			cin >> findElem;
			if (MyDuLinkList.getIndexElemAt(getLocate, findElem))
			{
				cout << "�ҵ���Ԫ��" << findElem << "�����ڱ��е�����ֵΪ��" << getLocate << "\n" << endl;
				MyDuLinkList.show();
			}
			else
			{
				cout << "�����в����������ҵ�ֵ��" << "\n" << endl;
				MyDuLinkList.show();
			}
			break;
		}
		case 5:
			if (MyDuLinkList.isEmpty())
			{
				cout << "��ǰ˫��ѭ������Ϊ�գ�" << endl;
				MyDuLinkList.getLength();
			}
			else
			{
				cout << "��ǰ��˫��ѭ������ǿգ�" << endl;
				MyDuLinkList.show();
			}
			break;
		case 6:
		{                                         //��ȡ����
			cout << "˫��ѭ������ǰ�ĳ���Ϊ��" << MyDuLinkList.getLength() << endl;
			break;
		}
		case 7:
			if (MyDuLinkList.clear())
			{
				cout << "˫��ѭ�������ѱ���գ�" << endl;
				MyDuLinkList.show();
			}
			else
			{
				cout << "˫��ѭ���������ʧ�ܣ�" << endl;
				MyDuLinkList.show();
			}
			break;
		case 8:
			MyDuLinkList.show();
			break;
		case 9:
		{
			cout << "��ȷ��Ҫ���ٸ�˫��ѭ��������(����������������(Y/y))";
			char yesOrNo;
			cin >> yesOrNo;
			if ((yesOrNo == 'Y') || (yesOrNo == 'y'))
			{
				if (MyDuLinkList.destroy())
				{
					cout << "˫��ѭ�������ѱ�����." << "\n" << endl;
				}
				else
					cout << "˫��ѭ����������ʧ��." << "\n" << endl;
			}
			break;
		}
		case 10:
		{
			int frontElem(0);
			int getElem(0); //���ص���Ҫ�����һ��Ԫ�ص�ǰ����Ԫ��
			cout << "��������Ҫ�����һ��Ԫ�ص�ǰ������ע�⣺���ܻ�ȡ��һ��Ԫ�صģ���";
			cin >> frontElem;
			if (MyDuLinkList.priorElemAt(frontElem, getElem))
			{
				cout << "����Ԫ��" << frontElem << "�ģ�ǰ��Ԫ���ǣ�" << getElem << endl;
				MyDuLinkList.show();
			}
			else
			{
				cout << "��ȡǰ��Ԫ��ʧ�ܣ����ܻ�ȡ��һ��Ԫ�ص�ǰ������������û���������Ԫ�أ�" << endl;
				MyDuLinkList.show();
			}
			break;
		}
		case 11:
		{
			int rearElem(0);
			int getElem(0);
			cout << "��������Ҫ�����һ��Ԫ�صĺ�̣���ע�⣺���ܻ�ȡ���һ��Ԫ�صģ���";
			cin >> rearElem;
			if (MyDuLinkList.nextElemAt(rearElem, getElem))
			{
				cout << "����Ԫ��" << rearElem << "�ģ����Ԫ���ǣ�" << getElem << endl;
				MyDuLinkList.show();
			}
			else
			{
				cout << "��ȡ���Ԫ��ʧ�ܣ����ܻ�ȡ���һ��Ԫ�صĺ�̻���������û���������Ԫ�أ�" << endl;
				MyDuLinkList.show();
			}
			break;
		}
		case 12:
			MyDuLinkList.traverseBack();
			break;
		case 13:
			system("cls");
			cout << "��Ļ�Ѿ�������������������!" << "\n" << endl;
			break;
		default:
			cout << "�������Ų���ȷ������������!" << "\n" << endl;
		}
	}
	delete[]myDatas;
	myDatas = nullptr;
}
int main()
{
	testMyDuLinkList();
	system("pause");
	return 0;
}