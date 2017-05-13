#include<iostream>
using namespace std;

void swap(int  &a, int  &b)   //交换两元素的值
{
	int temp = a;
	a = b;
	b = temp;
}

void printArray(int a[], int count)   //打印数组元素
{
	cout << "输出数组中排序前的的所有元素：\n";

	for (int i = 0; i < count; ++i)
	{
		cout<< a[i]<< endl;
	}
}

void selection_Sort(int *arr, int len)
{
	for (int i = 0; i < len - 1; ++i)   //len - 1是因为数组的下标是从0开始的
	{
		int min = i;   //每次将min设置成无序数组起始的位置元素的下标   
		for (int j = i + 1; j < len; ++j) //遍历无序数组，找到最小元素。 这里的len不减1，是因为是一开始第从下表一开始的，就是第二个数
		{
			if (arr[min] > arr[j])  
			{
				min = j;      //如果发现比当前最小元素还小的元素，则更新记录最小元素的下标，min始终记录当前遵循中最小的元素下标
			}
		}
		if (min != i)          /*如果最小元素不是无序组起始位置元素，则与起始元素交换位置   ，
							   交换后当前最小的元素是到无序数组的第一个数字，那么原来无序数组的第一个数字则被交换到以前当前最小元素的位置*/
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
			cout << "\n************************欢迎来到来到选择排序的世界！**********************\n" << endl
				<< "输入0，退出程序！" << endl
				<< "输入1，进行选择排序！" << endl
				<< "输入2，清屏！" << endl;
		}
		cout << "\n请输入你的选择：";
		int choice(0);
		cin >> choice;
		if (choice == 0)
		{
			cout << "程序已退出！" << endl;
			break;
		}
		switch (choice)
		{
		case 1:
		{
			cout << "请输入你想要进行排序的数组的个数，中间以回车分开：";
			int list_Length(0);
			cin >> list_Length;
			if (list_Length < 1)
			{
				cout << "错误，数组的长度必须大于0，请重新输入！" << endl;
				continue;
			}

			int *array = new int[list_Length];
			if (!array)
			{
				cout << "错误，分配数组内存失败！" << endl;
				system("pause");
				break;
			}
			cout << "请输入你想要进行排序的数组元素：\n";
			for (int i = 0; i < list_Length; ++i)
			{
				cin >> array[i];
			}
			printArray(array, list_Length);
			selection_Sort(array, list_Length);

			cout << "输出排序之后的数组元素：\n";
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
			cout << "屏幕已清屏，可以重新输入！" << endl;
			break;
		default:
			cout << "序号输入错误，请重新输入！" << endl;
		}
	
	}
	system("pause");
	return 0;
}