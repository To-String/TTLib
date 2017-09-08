#include<iostream>
#define TT_OK 1
#define TT_ERROR 0
using namespace std;
int quick_Sort( int *const arr, const int left, const int right)
{
	if (left < right)
	{
		int i = left, j = right;
		int temp = arr[left];
		while (i < j)   //��������������ֻ��һ���Ļ���ֱ������
		{
			while ((i < j) && (arr[j] >= temp)) // ���������ҵ�һ��С��temp����  
			{
				--j;
			}
			if (i < j)
			{
				arr[i++] = arr[j];  //���ұߵ�һ���Ȼ�׼��С������ֵ����׼����λ�ã�Ȼ��i�����ƶ�һ��
									//i++
			}
			while ((i < j) && (arr[i] < temp)) // ���������ҵ�һ�����ڵ���temp����  
			{
				++i;
			}
			if (i < j)
			{
				arr[j--] = arr[i];  //����ߵ�һ���Ȼ�׼���������ֵ��arr[j]��λ�ã�Ȼ��j����ǰ�ƶ�һ��
									//j--
			}
		}
		arr[i] = temp; //�ѻ�׼���ŵ��м�ȥ��С������ߣ�������ұ�
		quick_Sort(arr, left, i - 1);  //�ȶԻ�׼����ߵ������п������� i-1�������ͱ�ɻ�׼����ߵ��Ǹ�������׼�����ǵ�һ����
		quick_Sort(arr, j + 1, right); //�ٶԻ�׼���ұߵ�����������  j+1,���ǻ�׼���ұߵ��Ǹ�������ô�Ǹ��������ұߵݹ�Ļ�׼����һ����
									   //��ôj���Ǵ����ұ���������ұȻ�׼��С������i����ͬ�����Ǵ���߿�ʼ�����ұȻ�׼�������
	}
	return TT_OK;
}
void print_Array(const int *const arr, const int count)
{
	cout << "\n�������ǰ������Ԫ�أ�\n";
	for (int j = 0; j < count; ++j)
	{
		cout << arr[j] << " ";
	}
}
#undef TT_OK
#undef TT_ERROR       //ȡ����
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
		cout << "���������ѡ��";
		int select(0);
		cin >> select;
		if (select == 0)
		{
			cout << "�������˳�����л���ʹ�ã�" << endl;
			break;
		}
		switch (select)
		{
		case 1:
		{
			int arrLength(0);
			cout << "������������Ӷ��ٸ�Ԫ�ؽ��п�������";
			
			if ((cin >> arrLength) && (arrLength <= 0))
			{
				cout << "���������������ȷ���������(���ٴ���0)�������޷���������,���������룡" << endl;
				continue;
			}
			int *assignCapacityElem = new int[arrLength];
			if (!assignCapacityElem)
			{
				cout << "����������ڴ�ʧ�ܣ����������򣬿��ٴη��䣡" << endl;
				system("pause");
				exit(0);
			}
			cout << "��ֱ���������Ҫ���������" << arrLength << "��Ԫ�أ��ֱ��ûس����ֿ����ɣ�\n";
			for (int i = 0; i < arrLength; ++i)
			{
				cin >> assignCapacityElem[i];
			}
			print_Array(assignCapacityElem, arrLength);
			quick_Sort(assignCapacityElem, 0, arrLength - 1);
			cout << "\n�����������������Ԫ�أ�\n";
			for (int k = 0; k < arrLength; ++k)
			{
				cout << assignCapacityElem[k] << " ";
			}
			cout << endl;
			delete[]assignCapacityElem;
			assignCapacityElem = nullptr;
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