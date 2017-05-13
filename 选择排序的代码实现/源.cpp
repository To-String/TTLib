#include<iostream>
using namespace std;

void swap(int  &a, int  &b)   //������Ԫ�ص�ֵ
{
	int temp = a;
	a = b;
	b = temp;
}

void printArray(int a[], int count)   //��ӡ����Ԫ��
{
	cout << "�������������ǰ�ĵ�����Ԫ�أ�\n";

	for (int i = 0; i < count; ++i)
	{
		cout<< a[i]<< endl;
	}
}

void selection_Sort(int *arr, int len)
{
	for (int i = 0; i < len - 1; ++i)   //len - 1����Ϊ������±��Ǵ�0��ʼ��
	{
		int min = i;   //ÿ�ν�min���ó�����������ʼ��λ��Ԫ�ص��±�   
		for (int j = i + 1; j < len; ++j) //�����������飬�ҵ���СԪ�ء� �����len����1������Ϊ��һ��ʼ�ڴ��±�һ��ʼ�ģ����ǵڶ�����
		{
			if (arr[min] > arr[j])  
			{
				min = j;      //������ֱȵ�ǰ��СԪ�ػ�С��Ԫ�أ�����¼�¼��СԪ�ص��±꣬minʼ�ռ�¼��ǰ��ѭ����С��Ԫ���±�
			}
		}
		if (min != i)          /*�����СԪ�ز�����������ʼλ��Ԫ�أ�������ʼԪ�ؽ���λ��   ��
							   ������ǰ��С��Ԫ���ǵ���������ĵ�һ�����֣���ôԭ����������ĵ�һ�������򱻽�������ǰ��ǰ��СԪ�ص�λ��*/
		{
			swap(arr[min], arr[i]); 
			/*int temp = arr[min];
			arr[min] = arr[i];
			arr[i] = temp;*/
		}
	}
}

int main()
{
	while (true)
	{
		{
			cout << "\n************************��ӭ��������ѡ����������磡**********************\n" << endl
				<< "����0���˳�����" << endl
				<< "����1������ѡ������" << endl
				<< "����2��������" << endl;
		}
		cout << "\n���������ѡ��";
		int choice(0);
		cin >> choice;
		if (choice == 0)
		{
			cout << "�������˳���" << endl;
			break;
		}
		switch (choice)
		{
		case 1:
		{
			cout << "����������Ҫ�������������ĸ������м��Իس��ֿ���";
			int list_Length(0);
			cin >> list_Length;
			if (list_Length < 1)
			{
				cout << "��������ĳ��ȱ������0�����������룡" << endl;
				continue;
			}

			int *array = new int[list_Length];
			if (!array)
			{
				cout << "���󣬷��������ڴ�ʧ�ܣ�" << endl;
				system("pause");
				break;
			}
			cout << "����������Ҫ�������������Ԫ�أ�\n";
			for (int i = 0; i < list_Length; ++i)
			{
				cin >> array[i];
			}
			printArray(array, list_Length);
			selection_Sort(array, list_Length);

			cout << "�������֮�������Ԫ�أ�\n";
			for (int i = 0; i < list_Length; ++i)
			{
				cout << array[i] << endl;
			}
			delete[]array;
			array = nullptr;
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