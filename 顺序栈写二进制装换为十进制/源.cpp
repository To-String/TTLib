#include<iostream>
using namespace std;

#define TT_OK 1
#define TT_ERROR 0
#define STACK_INCREMENT 5   //�洢�ռ��������
typedef int ElemType;
typedef void Status;

class sqStack
{
public:
	sqStack(ElemType iniSize);
	~sqStack();
	ElemType push(ElemType elem);
	ElemType pop(ElemType &elemOut);
	ElemType getLength();
private:
	ElemType *m_base;
	ElemType *m_top;
	ElemType m_stackSize;  //ջ���������
};
sqStack::sqStack(ElemType iniSize)
{
	m_base = new ElemType[iniSize];
	if (!m_base)
	{
		cout << "��ʼ��ջ���ڴ�ʧ��!" << endl;
		system("pause");
		exit(0);
	}
	m_top = m_base;
	m_stackSize = iniSize;
	cout << "***********************   ˳��ջ��ʼ���ɹ���  ***********************" << endl;
}
sqStack::~sqStack()
{
	delete[]m_base;
}
ElemType sqStack::push(ElemType elem)
{
	if (m_top - m_base >= m_stackSize)
	{
		int *assignCapacity = new int[m_base, m_stackSize + STACK_INCREMENT];
		if (!assignCapacity)
		{
			cout << "��������ջ�ڴ�ʧ�ܣ�" << endl;
			system("pause");
			exit(0);
		}
		m_stackSize += STACK_INCREMENT;
	}
	*(m_top++) = elem;
	return TT_OK;
}
ElemType sqStack::pop(ElemType &elemOut)
{
	if (m_top == m_base)
	{
		return TT_ERROR;
	}
	elemOut = *--(m_top);
	return TT_OK;
}
ElemType sqStack::getLength()
{
	return (m_top - m_base);
}

int main()
{
	int assignCapacity(0);
	cout << "��������Ϊջ������ڴ��С��";
	cin >> assignCapacity;
	if (assignCapacity <= 0)
	{
		cout << "�����������ȷ���ڴ棡" << endl;
		system("pause");
		exit(0);
	}
	sqStack myStack(assignCapacity);

	char insertElem('\0');
	cout << "�������������������#���ű�ʾ������" << endl;
	
	while (cin >> insertElem)
	{
		if (insertElem == '#')
		{
			break;
		}
		myStack.push(insertElem);
	}
	getchar();  //��"\n"�ӻ�����ȥ��
	int length = myStack.getLength();
	cout << "ջ�ĵ�ǰԪ�ظ���Ϊ��" << length << endl;
	int cancelElem(0), sum(0);
	for (int i = 0; i < length; ++i)
	{
		myStack.pop(cancelElem);
		sum = sum + (cancelElem - 48)*pow(2, i);  //��48����ΪASCIIֵ��Ӧ����0�������0�ͣ� 0*2��0���ݣ���ջ����ʼ
	}                                          //��ʵ���Ǽ��������תʮ���ƵĹ�ʽ
	cout << "ת��Ϊʮ������Ϊ��\n" << sum << endl;

	cout << endl;
	system("pause");
	return 0;
}