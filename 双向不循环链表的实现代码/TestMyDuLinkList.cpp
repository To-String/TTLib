#include"MyDuLinkList.h"

namespace tt
{
	DuLinkList::DuLinkList()
	{
		m_heap = new DulNode;
		if (!m_heap)
		{
			cout << "����ͷ���ʱ����ʼ�������ڴ�ʧ�ܣ�" << endl;
			system("pause");
			exit(0);
		}
		m_heap->m_next = nullptr;
		m_heap->m_prior = nullptr;
		m_tail = m_heap;
		cout << "***********************   ˫��ѭ�������ʼ���ɹ�  ***********************" << endl;
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
			m_tail = m = p;  //���ѵ�һ���ڵ���m��m_tail��ָ�����һ��Ԫ�ص�ָ��  �����������ϲ���ѭ��
		}
		m->m_next = nullptr; //����Ǽ�����䣬  ��ʾ��ǰ������������
	}
	DuLinkList::ElemType DuLinkList::insertAt(ElemType i, ElemType elem)
	{
		DulNode *p = m_heap;

		if ((i < 1) || (i > getLength() + 1))  //�����λ�ò�����ʱ������false
		{
			return TT_ERROR;
		}
		int j = 1;
		while ((p) && (j < i))
		{
			p = p->m_next;
			++j;
		}
		if ((!p) || (j > i))
		{
			return TT_ERROR;
		}
		DulNode *s = new DulNode;
		if (p != m_tail)  //�������Ĳ��ڱ�β
		{
			s->m_data = elem;     //��Ҫ�洢�����ݷ�����������
			s->m_prior = p;         //���Ȱ�p���s��ǰ�����
			s->m_next = p->m_next;   //��p�ĺ�̽ڵ���s�ĺ�̽ڵ�
			p->m_next->m_prior = s;   //��s���p�ĺ�̽ڵ��ǰ��
			p->m_next = s;   //p�ĺ�̽ڵ���s
		}
		else
		{
			pushBack(elem);
			/*s->m_data = elem;
			m_tail->m_next = s;
			s->m_prior = m_tail;
			m_tail = s;
			s->m_next = nullptr;  //һ��Ҫ�����䣬���������ʾ���һ��Ԫ�صĺ��Ϊ��*/
		}
		return TT_OK;
	}
	DuLinkList::ElemType DuLinkList::removeAt(ElemType i, ElemType &elemOut)
	{
		DulNode *p = m_heap;

		if ((i < 1) || (i > getLength()))
		{
			return TT_ERROR;
		}
		int j = 1; //q��ָ����к��, ��ǰλ��j��û�д��ڵ��ھ�ѭ������
		while ((p) && (j <= i))
		{
			p = p->m_next;
			j++;
		}
		if (!(p) || (j < i))   //��ǰ��λ��j������Ҫ���ҵ�λ��i�����ش���
		{
			return TT_ERROR;
		}
		if (p != m_tail)   //����ɾ���Ĳ��Ǳ�β
		{
			elemOut = p->m_data;
			p->m_prior->m_next = p->m_next;  //��p�ĺ�̽ڵ���p��ǰ�����ĺ�̽ڵ�
			p->m_next->m_prior = p->m_prior;   //��p��ǰ�������p�ĺ�̽ڵ��ǰ�����

			delete p;  //�ͷŽڵ���ڴ�
		}
		else
		{
			popBack(elemOut);
			/*elemOut = p->m_data;
			m_tail = p->m_prior;   // Ȼ�� �ڰѵ����ڶ���Ԫ�ر��m_tailָ��
			p->m_prior->m_next = nullptr;  //�ڰѵ����ڶ���Ԫ�صĺ��Ϊnull*/
		}
		return TT_OK;
	}
	DuLinkList::ElemType DuLinkList::getAt(ElemType i, ElemType &elemOut)
	{
		DulNode *p = m_heap->m_next;  //ָ���һ���ڵ�

		if ((i < 1) || (i > getLength()))
		{
			return TT_ERROR;
		}
		int j = 1;
		while ((p) && (j < i))
		{
			p = p->m_next;
			++j;
		}
		if ((!p) || (j > i))
		{
			return TT_ERROR;
		}
		elemOut = p->m_data;

		return TT_OK;
	}

	DuLinkList::ElemType DuLinkList::getIndexElemAt(ElemType &i, ElemType elemOut)//������elem��ȵ�Ԫ�أ����ص�һ����elem���Ԫ���������е����
	{
		DulNode *s = m_heap->m_next;
		int searchLocate = 1;
		while (s && (s->m_data != elemOut))
		{
			++searchLocate;
			s = s->m_next;
		}
		if (!s)
		{
			return TT_ERROR;
		}
		i = searchLocate;

		return TT_OK;
	}
	DuLinkList::ElemType DuLinkList::clear()
	{
		DulNode *s = m_heap->m_next;
		while (s)
		{
			DulNode *m = s->m_next;
			delete s;
			s = m;
		}
		m_heap->m_next = m_heap->m_prior = nullptr;
		m_tail = m_heap;
		return TT_OK;
	}
	DuLinkList::ElemType DuLinkList::destroy()
	{
		while (m_heap)
		{
			DulNode *s = m_heap->m_next;
			delete m_heap;
			m_heap = s;
		}
		m_tail = m_heap = nullptr;
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
			while (p)
			{
				++temp;
				cout << (p->m_data) << " ";
				p = p->m_next;
			}
			cout << "\n��ǰ˫��ѭ�������е�Ԫ������Ϊ��" << temp << endl;
		}
	}
	DuLinkList::Status DuLinkList::traverseBack()
	{
		if (isEmpty())
		{
			cout << "��ǰ������û��Ԫ�أ��޷���ʾ��" << endl;
		}
		else
		{
			DulNode *p = m_tail;
			cout << "������������е�����Ԫ�أ�";
			while (p != m_heap)
			{
				cout << (p->m_data) << " ";
				p = p->m_prior;
			}
			cout << endl;
		}
	}
	DuLinkList::ElemType DuLinkList::priorElemAt(ElemType cur_e, ElemType &pri_e)//��cur_e�����������Ԫ�أ��Ҳ��ǵ�һ��������pre_e��������ǰ��
	{
		DulNode *q = m_heap->m_next->m_next;  //ָ��ڶ���Ԫ��-
		while (q)
		{
			if (q->m_data == cur_e)
			{
				pri_e = q->m_prior->m_data;
				return TT_OK;
			}
			q = q->m_next;
		}
		return TT_ERROR;
	}
	DuLinkList::ElemType DuLinkList::nextElemAt(ElemType cur_e, ElemType &Nex_e) //��cur_e�����������Ԫ��,�Ҳ������һ��,����next_e�������ĺ�̣�
	{
		DulNode *p = m_heap->m_next->m_next;   //ָ��ڶ���Ԫ�أ� ���ָ���һ��Ԫ�صĻ���������һ��Ԫ�صĺ�̣��ͻ��������ֵ
		while (p)
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
	DuLinkList::ElemType DuLinkList::pushBack(const ElemType &elem)  //β��
	{
		DulNode *s = new DulNode;
		if (m_heap != m_tail)     //�������Ĳ��ǵ�һ���ڵ㣬������ǵ�n��Ԫ�صı�β
		{
			s->m_data = elem;
			m_tail->m_next = s;
			s->m_prior = m_tail;
			m_tail = s;
			s->m_next = nullptr;  //һ��Ҫ�����䣬���������ʾ���һ��Ԫ�صĺ��Ϊ��
		}
		else
		{
			s->m_data = elem;
			m_heap->m_next = s;
			s->m_prior = m_heap;
			m_tail = s;
			s->m_next = nullptr;
		}
		return TT_OK;
	}
	DuLinkList::ElemType DuLinkList::popBack(ElemType &elemOut) //βɾ
	{
		if (isEmpty())
		{
			return TT_ERROR;
		}
		DulNode *p = m_tail;
		elemOut = p->m_data;
		m_tail = p->m_prior;   // Ȼ�� �ڰѵ����ڶ���Ԫ�ر��m_tailָ��
		p->m_prior->m_next = nullptr;  //�ڰѵ����ڶ���Ԫ�صĺ��Ϊnull
		delete p;
		return TT_OK;
	}
	DuLinkList::ElemType DuLinkList::pushFront(const ElemType &elem)  //ͷ��
	{
		DulNode *m = new DulNode;
		if (m_tail != m_heap)  //����Ĳ��ǵ�һ�����
		{
			m->m_data = elem;
			m->m_prior = m_heap;
			m->m_next = m_heap->m_next;
			m_heap->m_next->m_prior = m;
			m_heap->m_next = m;
		}
		else
		{
			pushBack(elem);
		}
		return TT_OK;
	}
	DuLinkList::ElemType DuLinkList::popFront(ElemType &elemOut)  //ͷɾ
	{
		if (isEmpty())
		{
			return TT_ERROR;
		}
		DulNode *s = m_heap->m_next;
		if (m_heap != m_tail)     //����ɾ���Ĳ��ǵ�һ��Ԫ��
		{
			elemOut = s->m_data;
			m_heap->m_next = s->m_next;
			s->m_next->m_prior = m_heap;
			delete s;
		}
		else
		{
			popBack(elemOut);
		}
		return TT_OK;
	}
	DuLinkList::ElemType DuLinkList::getLength()
	{
		DulNode *p = m_heap->m_next;   //pָ���һ�����
		int i = 0;
		while (p)
		{
			p = p->m_next;
			++i;

		}
		return i;
	}
}

// ���Ժ���
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
	MyDuLinkList.createTail(myDatas, myLength);   //����createTail���� ��������
	MyDuLinkList.show();

	while (true)
	{
		{
			cout << "\n*******************************************************************" << endl
				<< "*******************   ˫��ѭ�������������չʾ   *******************" << endl
				<< "*******************************************************************" << endl
				<< "********************   ѡ��1�������ݲ���.   **********************" << endl
				<< "********************   ѡ��2��������ɾ��.   **********************" << endl
				<< "********************   ѡ��3������ȡԪ��.   **********************" << endl
				<< "********************   ѡ��4��������Ԫ��.   **********************" << endl
				<< "********************   ѡ��5�����Ƿ�Ϊ��.   **********************" << endl
				<< "*******************************************************************" << endl
				<< "********************   ѡ��6������ȡ������.   **********************" << endl
				<< "********************   ѡ��7�������Ԫ��.   **********************" << endl
				<< "********************   ѡ��8�����������Ԫ��. ************************" << endl
				<< "********************   ѡ��9������������. ************************" << endl
				<< "*********************  ѡ��10�������Ԫ�ص�ǰ��.  *****************" << endl
				<< "*******************************************************************" << endl
				<< "*********************  ѡ��11�������Ԫ�صĺ��.  *****************" << endl
				<< "*********************  ѡ��12���������������Ԫ��.  *****************" << endl
				<< "*********************  ѡ��13��������β��Ԫ��.  *****************" << endl
				<< "*********************  ѡ��14��������βɾԪ��.  *****************" << endl
				<< "*******************************************************************" << endl
				<< "*********************  ѡ��15��������ͷ��Ԫ��.  *****************" << endl
				<< "*********************  ѡ��16��������ͷɾԪ��.  *****************" << endl
				<< "*******************************************************************" << endl
				<< "********************   ѡ��17����������      ************************" << endl
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
				cout << "��ǰѭ������Ϊ�գ�" << endl;
				MyDuLinkList.getLength();
			}
			else
			{
				cout << "��ǰ������ǿգ�" << endl;
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
		{
			int addBackElem(0);
			cout << "����������Ҫ��β�������Ԫ�ص�ֵ��";
			cin >> addBackElem;
			if (MyDuLinkList.pushBack(addBackElem))
			{
				cout << "����" << addBackElem << "��β����ӳɹ���" << endl;
				MyDuLinkList.show();
			}
			else
				cout << "����" << addBackElem << "��β�����ʧ�ܣ�" << endl;
			break;
		}
		case 14:
		{
			int cancelBackElem(0);
			if (MyDuLinkList.popBack(cancelBackElem))
			{
				cout << "��β����" << cancelBackElem << "ɾ���ɹ���" << endl;
				MyDuLinkList.show();
			}
			else
				cout << "��β����" << cancelBackElem << "ɾ��ʧ��,������������û��Ԫ�أ�" << endl;
			break;
		}
		case 15:
		{
			int addFirstElem(0);
			cout << "����������Ҫ��ͷ�������Ԫ�ص�ֵ��";
			cin >> addFirstElem;
			if (MyDuLinkList.pushFront(addFirstElem))
			{
				cout << "����" << addFirstElem << "��ͷ����ӳɹ���" << endl;
				MyDuLinkList.show();
			}
			else
				cout << "����" << addFirstElem << "��ͷ�����ʧ�ܣ�" << endl;
			break;
		}
		case 16:
		{
			int cancelFirstElem(0);
			if (MyDuLinkList.popFront(cancelFirstElem))
			{
				cout << "��ͷ����" << cancelFirstElem << "ɾ���ɹ���" << endl;
				MyDuLinkList.show();
			}
			else
				cout << "��ͷ����" << cancelFirstElem << "ɾ��ʧ�ܣ�������������û��Ԫ�أ�" << endl;
			break;
		}
		case 17:
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