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
		int i = left + 1;
		int j = right;
		int key = arr[left];  //暂存基准点的数
		{

			while (true)
			{
				while (arr[j] > key)  //j--方向大于key,当arr[j]小于当前的基准值，说明找到了比基准值小的数，就退出
				{
					j--;  //往前移动一个位置
				}
				while ((arr[i] < key) && (i < j)) //i++方向小于key.当arr[i]大于基准值的时候，说明找到了比基准值大的数，就退出
				{                               //那么同时i（i一开始是等于1的）不能大于j(j是数组的长度-1)
					i++;    //后移动一个位置
				}
				if (i >= j)  //只要i和j 没有相遇，循环继续
				{
					break;
				}
				swap(arr[i], arr[j]);   //把退出循环后数组中 大的数交换到基准值的右边，把小的数交换到基准值的左边
				if (arr[i] == key)  //如果搞好等于基准数的话，那么j再次移动，否则的话就是i移动
				{
					j--;
				}
				else
					i++;
			}
		}
	}
}
//最终将基准数归位
	swap(arr[left], arr[j]);

	if (left < i - 1) //对基准点左边的数进行快速排序，这里是一个递归的过程
	{
		quickSort(arr, left, i - 1);
	}
	if (j + 1 < right)  //对基准点右边的数进行排序，这里是一个递归的过程
	{
		quickSort(arr, j + 1, right);
	}

	return TT_OK;
}
void printArray(int arr[],int count)
{
	cout << "输出未排序前数组中的元素：\n";
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
			cout << "\n************************ 欢迎来到来到快速排序的世界！**********************\n" << endl
				<< "输入0，退出程序！" << endl
				<< "输入1，进行快速排序！" << endl
				<< "输入2，清屏！" << endl;
		}
		cout << "**************************** 请输入你想要使用的功能的序号 **********************" << endl;
		int select(0);
		cout << "请输入你的选择：";
		cin >> select;
		if (select == 0)
		{
			cout << "程序已退出，感谢你的使用！" << endl;
			break;
		}
		switch (select)
		{
			{
		case 1:
			int arraySize(0);
			cout << "请输入你想要排序的数组的个数：";
			cin >> arraySize;
			if (arraySize <= 0)
			{
				cout << "输入错误，请输入正确的数组个数，否则无法进行排序！" << endl;
				system("pause");
				exit(0);
			}
			int *assignCapacity = new int[arraySize];
			if (!assignCapacity)
			{
				cout << "错误，分配数组内存时失败，请重新运行程序！" << endl;
				system("pause");
				exit(0);
			}
			cout << "请输入你想要进行排序的数组元素：\n";
			for (int i = 0; i < arraySize; ++i)
			{
				cin >> assignCapacity[i];
			}
			printArray(assignCapacity, arraySize); //打印未排序的数组元素
			quickSort(assignCapacity, 0, arraySize - 1);
			cout << "\n输出快速排序后的数组元素：";
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
			cout << "屏幕已清屏，可以重新输入！" << endl;
			break;
		default:
			cout << "序号输入错误，请重新输入！" << endl;

		}
	}
	
	system("pause");
	return 0;
}