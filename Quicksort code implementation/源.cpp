#include<iostream>
#define TT_OK 1
#define TT_ERROR 0
using namespace std;
void swap(int &x, int &y)
{
	int temp = x;
	x = y;
	y = temp;
}
int quickSort(int *arr, int left, int right)
{
	if (left <= right)
	{
		int i = left;
		int j = right;
		int key = arr[left];  //�ݴ��׼�����
		{

			while (i != j)  //��i��j û������ʱ��ѭ������
			{       //˳�����Ҫ��Ҫ�ȴ���������
				while ((arr[j] >= key) && (i < j))  //j--�������key,��arr[j]С�ڵ�ǰ�Ļ�׼ֵ��˵���ҵ��˱Ȼ�׼ֵС���������˳�
				{
					--j;  //��ǰ�ƶ�һ��λ��
				}
				//�ٴ���������
				while ((arr[i] <= key) && (i < j)) //i++����С��key.��arr[i]���ڻ�׼ֵ��ʱ��˵���ҵ��˱Ȼ�׼ֵ����������˳�
				{                               //��ôͬʱi��iһ��ʼ�ǵ���1�ģ����ܴ���j(j������ĳ���-1)
					++i;    //�����ƶ�һ��λ��
				}
				//�����������������е�λ��
				if (i < j)  //ֻҪi��j û��������ѭ�����������ҽ�����ʱ��������
				{
					swap(arr[i], arr[j]);   //�˳�ѭ���������� �������������׼ֵ���ұߣ���С������������׼ֵ�����
				}
			}
			{//���ս���׼����λ
				swap(arr[left], arr[j]);
				quickSort(arr, left, i - 1); //�ȶԻ�׼����ߵ������п������� i-1�������ͱ�ɻ�׼����ߵ��Ǹ�������׼�����ǵ�һ����
				quickSort(arr, j + 1, right);   //�ٶԻ�׼���ұߵ�����������  i+1,���ǻ�׼���ұߵ��Ǹ�������ô�Ǹ��������ұߵݹ�Ļ�׼��
												//��ôj���Ǵ����ұ���������ұȻ�׼��С������i����ͬ�����Ǵ���߿�ʼ�����ұȻ�׼�������
			}
		}
	}
	return TT_OK;
}
void printArray(int arr[],int count)
{
	cout << "���δ����ǰ�����е�Ԫ�أ�\n";
	for (int i = 0; i < count; ++i)
	{
		cout << arr[i] << " ";
	}
}

int main()
{
	while (true)
	{
		{
			cout << "\n************************ ��ӭ��������������������磡**********************\n" << endl
				<< "����0���˳�����" << endl
				<< "����1�����п�������" << endl
				<< "����2��������" << endl;
		}
		cout << "**************************** ����������Ҫʹ�õĹ��ܵ���� **********************" << endl;
		int select(0);
		cout << "���������ѡ��";
		cin >> select;
		if (select == 0)
		{
			cout << "�������˳�����л���ʹ�ã�" << endl;
			break;
		}
		switch (select)
		{
			{
		case 1:
			int arraySize(0);
			cout << "����������Ҫ���������ĸ�����";
			cin >> arraySize;
			if (arraySize <= 0)
			{
				cout << "���������������ȷ���������(���ٴ���0)�������޷���������" << endl;
				system("pause");
				exit(0);
			}
			int *assignCapacity = new int[arraySize];
			if (!assignCapacity)
			{
				cout << "���󣬷��������ڴ�ʱʧ�ܣ����������г���" << endl;
				system("pause");
				exit(0);
			}
			cout << "����������Ҫ�������������Ԫ�أ�\n";
			for (int i = 0; i < arraySize; ++i)
			{
				cin >> assignCapacity[i];
			}
			printArray(assignCapacity, arraySize); //��ӡδ���������Ԫ��
			quickSort(assignCapacity, 0, arraySize - 1);
			cout << "\n�����������������Ԫ�أ�";
			for (int k = 0; k < arraySize; ++k)
			{
				cout << assignCapacity[k] << " ";
			}
			cout << endl;
			delete[]assignCapacity;
			assignCapacity = nullptr;
			break;
			}
		case 2:
			system("cls");
			cout << "��Ļ�������������������룡" << endl;
			break;
		default:
			cout << "�������������������룡" << endl;

		}
	}
	
	system("pause");
	return 0;
}