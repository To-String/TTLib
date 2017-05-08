#include"CirLinkList.h"

namespace tt
{
	CirLinkList::CirLinkList()
	{
		m_heap = new Node;
		if (!m_heap)
		{
			cout << "�����ڴ����ʧ�ܣ�" << endl;
			system("pause");
			exit(0);
		}
		m_heap->m_next = m_heap;  //�����������ͣ�m_heap������ͷ��㣬m_heap�����һ������ָ�룬m_heap->m_next����ͷ��㣬
		cout << "\n********************�����ѭ���б��ʼ���ɹ���************************" << endl;
	}
	CirLinkList::~CirLinkList()
	{
		this->destroy();
	}
	CirLinkList::Status CirLinkList::createTail(ElemType *datas, ElemType length)
	{
		for (int i = 0; i < length; ++i)
		{                    //m_heap�������õ�βָ�룬p�������б������������ָ�롣
			Node *p = new Node;
			p->m_data = datas[i];
			                       //ֱ�ӽ�p��������β�����Ϊ�µ�β��㼴�ɡ�
			p->m_next = m_heap->m_next;
			m_heap = m_heap->m_next = p;
		}
	}
	CirLinkList::ElemType CirLinkList::priorElemAt(int cur_e, int &pri_e)
	{                                 //��cur_e�����������Ԫ�أ��Ҳ��ǵ�һ��������pre_e��������ǰ��

			/*Node *p = m_heap->m_next->m_next;  //pָ�������һ��Ԫ��
			 while (p != m_heap->m_next)
			{
				Node *q= p->m_next;   //qָ��p�ĺ��
			    if (q != m_heap->m_next && q->m_data == cur_e)
			   {
					pri_e = p->m_data;
				    return TT_OK;
			   }
				 p = q;
			}
			  return TT_ERROR;*/

		Node *p = m_heap->m_next->m_next; //pָ���һ�����
		Node *q = p->m_next;
		while (q != m_heap->m_next)
		{
			if (q->m_data == cur_e)
			{
				pri_e = p->m_data;
				return TT_OK;
			}
			p = q;
			q = q->m_next;
		}
		return TT_ERROR;
	}
	CirLinkList::ElemType CirLinkList::nextElemAt(int cur_e, int &Nex_e)
	{                                   //��cur_e�����������Ԫ��,�Ҳ������һ��,����next_e�������ĺ��
			/*Node *p =m_heap->m_next->m_next;  //pָ���һ�����
			 while (p != m_heap->m_next)
			{
				if (p->m_data == cur_e)
			    {
					Nex_e = p->m_next->m_data;
					return TT_OK;
		        }
			        p= p->m_next;
			}
				return TT_ERROR;*/

		Node *p = m_heap->m_next->m_next;  //pָ���һ�����
		while (p != m_heap->m_next)  //p��û��ͷ���
		{
			Node *q = p->m_next; //��һ��ѭ����q�ǵڶ���Ԫ��
			if (q != m_heap->m_next && p->m_data == cur_e)  
			{
				Nex_e = q->m_data;
				return TT_OK;
			}
			p = q;
		}
		return TT_ERROR;
	}
	CirLinkList::ElemType CirLinkList::insertAt(ElemType i, ElemType elem)
	{
		Node *p = m_heap->m_next;    //pָ���ͷ
		if ((i < 1) || (i > getLength() + 1))   //iλ�ò�����ʱ������false
		{
			return TT_ERROR;
		}
		int j = 1;
		while (j < i)   //��jС��iʱ  �ͼ���
		{
			p = p->m_next;
			++j;
		}
		Node *s = new Node;
		s->m_data = elem;
		s->m_next = p->m_next;
		p->m_next = s;
		if (p == m_heap)  //�ڱ�β����ı�βָ��
		{
			m_heap = s;
		}
		return TT_OK;
	}
	CirLinkList::ElemType CirLinkList::removeAt(ElemType i, ElemType &elemOut)
	{
		Node *p = m_heap->m_next;   //pָ���ͷ
		if ((i < 1) || (i > getLength()))   //�ж�ɾ��λ���Ƿ����
		{
			return TT_ERROR;
		}
		int j = 1;
		while (j < i)
		{
			p = p->m_next;
			++j;
		}
		Node *q = p->m_next;    //qָ���ɾ����� 
		p->m_next = q->m_next;
		elemOut = q->m_data;    //������ǰ��Ҳ�ǿ��Եģ�������Ҫ�޸�һ���ж������� ����ǰ�治��Ҫ����һ����ʱ�ڵ�q
		if (m_heap == q) //ɾ�����Ǳ�βԪ�أ���βָ�뷢���ı�
		{
			m_heap = p;
		}
		delete q;
		return TT_OK;
	}
	CirLinkList::ElemType CirLinkList::getIndexElemAt(ElemType &i, ElemType elemOut)
	{
		Node *p = m_heap->m_next->m_next;    //�ӵ�һ����㿪ʼ����
		int searchLocate = 1;
		while ((p != m_heap->m_next) && (p->m_data != elemOut)) //pδ����ͷʱ
		{
			++searchLocate;
			p = p->m_next;
		}
		if (!(p != m_heap->m_next))
		{
			return TT_ERROR;
		}
		i = searchLocate;
		return TT_OK;
	}
	CirLinkList::ElemType CirLinkList::getAt(ElemType i, ElemType &elemOut)
	{
		Node *q = m_heap->m_next->m_next;    //��qָ������ĵ�һ���ڵ�

		if ((i < 1) || (i > getLength()))
		{
			return TT_ERROR;
		}
		int j = 1;
		while ((j < i))
		{

			q = q->m_next;
			++j;
		}
		elemOut = q->m_data;   //ȡ��i��Ԫ�ص�����
		return TT_OK;
	}
	CirLinkList::Status CirLinkList::show()
	{
		if (m_heap->m_next == m_heap)
		{
			cout << "��ǰ������û��Ԫ�أ��޷���ʾ��" << endl;
		}
		else
		{
			Node *p = m_heap->m_next->m_next;   //pָ���һ�����
			int temp(0);  //������ʾ�����еĸ���
			cout << "�������ѭ�������е�����Ԫ�أ�";
			while (p != m_heap->m_next)  //pδ����ͷ
			{
				++temp;
				cout << (p->m_data) << " ";
				p = p->m_next;
			}
			cout << "\n��ǰѭ�������е�Ԫ������Ϊ��" << temp << endl;
		}
	}

	CirLinkList::ElemType CirLinkList::getLength()const
	{
		Node *p = m_heap->m_next->m_next;   //pָ���һ�����
		int i = 0;
		while (p != m_heap->m_next) //pδ����ͷʱ
		{
			p = p->m_next;
			++i;
		}
		return i;
	}
	CirLinkList::ElemType CirLinkList::clear()
	{
		m_heap = m_heap->m_next;       //�Ȱ�βָ��ָ��ͷ��㣬��Ȼ�ͷ����һ�����ʱβָ�룬�޷�ָ��ͷ��� 
		Node *p = m_heap->m_next;   //pָ���һ�����
		while (p != m_heap)   //p�����ڱ�ͷʱ
		{
			Node *q = p->m_next;
			delete p;
			p = q;
		}
		m_heap->m_next = m_heap; //ͷ���ָ����ָ���䱾��
		return TT_OK;
	}
	CirLinkList::ElemType CirLinkList::destroy()
	{
		this->clear();  //ȥ����clear()������  �������Ԫ�أ� �ڴκ����У���Ϊֻʣ��һ��m_heap��  ����ֱ������ֱ���ͷ�m_heap
		delete m_heap;
		m_heap = nullptr;
		return TT_OK;
	}
}

//���Ե���ѭ������
void testMyCirLinkList()
{
	tt::CirLinkList myCirLinkList;

	int myLength(0);    //�������������,β�巨
	cout << "�봴���������ݵ�����";
	cin >> myLength;
	int *myDatas = new int[myLength];
	cout << "������������" << myLength << "�����ݣ��м��Իس���������" << endl;

	for (int i = 0; i < myLength; ++i)
	{

		cin >> myDatas[i];  //����Ҫ�洢�����ݵ�ֵ
	}
	myCirLinkList.createTail(myDatas, myLength);   //����createTail���� ����������
	myCirLinkList.show();

	while (true)
	{
		{
			cout << "\n*************************************************************" << endl
				<< "*******************   ����ѭ������Ļ�������չʾ   *******************" << endl
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
				<< "********************   ѡ��12����������      ************************" << endl
				<< "********************   ѡ��0�����˳�����   ************************" << endl
				<< "***********************************************************************" << endl
				<< "***********************************************************************" << endl;
		}
		cout << "\n********************   ����������Ҫʹ�õ�ѭ�������ܵ����   ***************" << endl;
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
			if (myCirLinkList.insertAt(pushLocate, pushElement))
			{
				cout << "����" << pushElement << "����ɹ���" << endl;
				myCirLinkList.show();
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
			if (myCirLinkList.removeAt(cancelLocate, cancelElem))
			{
				cout << "����" << cancelElem << "ɾ���ɹ���" << endl;
				myCirLinkList.show();
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
			if (myCirLinkList.getAt(getLocate, getElem))
			{
				cout << "��ȡ��Ԫ��Ϊ��" << getElem << endl;
				myCirLinkList.show();
			}
			else
			{
				cout << "��ȡ��λ�ò��������������û��Ԫ�أ���ȡ����ʧ�ܣ�" << endl;
				myCirLinkList.getLength();
			}
			break;
		}
		case 4:
		{                                             //����Ԫ��
			int getLocate(0);
			int findElem(0);
			cout << "����������Ҫ���ҵ�Ԫ�ص�ֵ��";
			cin >> findElem;
			if (myCirLinkList.getIndexElemAt(getLocate, findElem))
			{
				cout << "�ҵ���Ԫ��" << findElem << "�����ڱ��е�����ֵΪ��" << getLocate << "\n" << endl;
				myCirLinkList.show();
			}
			else
			{
				cout << "�����в����������ҵ�ֵ��" << "\n" << endl;
				myCirLinkList.show();
			}
			break;
		}
		case 5:
			if (myCirLinkList.isEmpty())
			{
				cout << "��ǰѭ������Ϊ�գ�" << endl;
				myCirLinkList.getLength();
			}
			else
			{
				cout << "��ǰ��ѭ������ǿգ�" << endl;
				myCirLinkList.show();
			}
			break;
		case 6:
		{                                         //��ȡ����
			int temp = myCirLinkList.getLength();
			cout << "ѭ������ǰ�ĳ���Ϊ��" << temp << endl;
			break;
		}
		case 7:
			if (myCirLinkList.clear())
			{
				cout << "ѭ�������ѱ���գ�" << endl;
				myCirLinkList.show();
			}
			else
			{
				cout << "ѭ���������ʧ�ܣ�" << endl;
				myCirLinkList.show();
			}
			break;
		case 8:
			myCirLinkList.show();
			break;
		case 9:
		{
			cout << "��ȷ��Ҫ���ٸõ�������(����������������(Y/y))";
			char yesOrNo;
			cin >> yesOrNo;
			if ((yesOrNo == 'Y') || (yesOrNo == 'y'))
			{
				if (myCirLinkList.destroy())
				{
					cout << "�������ѱ�����." << "\n" << endl;
				}
				else
					cout << "����������ʧ��." << "\n" << endl;
			}
			break;
		}
		case 10:
		{
			int frontElem(0);
			int getElem(0); //���ص���Ҫ�����һ��Ԫ�ص�ǰ����Ԫ��
			cout << "��������Ҫ�����һ��Ԫ�ص�ǰ������ע�⣺���ܻ�ȡ��һ��Ԫ�صģ���";
			cin >> frontElem;
			if (myCirLinkList.priorElemAt(frontElem, getElem))
			{
				cout << "����Ԫ��" << frontElem << "�ģ�ǰ��Ԫ���ǣ�" << getElem << endl;
			}
			else
				cout << "��ȡǰ��Ԫ��ʧ�ܣ����ܻ�ȡ��һ��Ԫ�ص�ǰ������������û���������Ԫ�أ�" << endl;
			break;
		}
		case 11:
		{
			int rearElem(0);
			int getElem(0);
			cout << "��������Ҫ�����һ��Ԫ�صĺ�̣���ע�⣺���ܻ�ȡ���һ��Ԫ�صģ���";
			cin >> rearElem;
			if (myCirLinkList.nextElemAt(rearElem, getElem))
			{
				cout << "����Ԫ��" << rearElem << "�ģ����Ԫ���ǣ�" << getElem << endl;
			}
			else
				cout << "��ȡ���Ԫ��ʧ�ܣ����ܻ�ȡ���һ��Ԫ�صĺ�̻���������û���������Ԫ�أ�" << endl;
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
	delete[]myDatas;
	myDatas = nullptr;
}
int main()
{
	testMyCirLinkList();
	system("pause");
	return 0;
}