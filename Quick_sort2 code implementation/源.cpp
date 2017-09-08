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
		while (i < j)   //假如进行排序的数只有一个的话，直接跳过
		{
			while ((i < j) && (arr[j] >= temp)) // 从右向左找第一个小于temp的数  
			{
				--j;
			}
			if (i < j)
			{
				arr[i++] = arr[j];  //把右边第一个比基准数小的数赋值到基准数的位置，然后i往右移动一次
									//i++
			}
			while ((i < j) && (arr[i] < temp)) // 从左向右找第一个大于等于temp的数  
			{
				++i;
			}
			if (i < j)
			{
				arr[j--] = arr[i];  //把左边第一个比基准数大的数赋值到arr[j]的位置，然后j在往前移动一次
									//j--
			}
		}
		arr[i] = temp; //把基准数放到中间去，小的在左边，大的在右边
		quick_Sort(arr, left, i - 1);  //先对基准点左边的数进行快速排序， i-1这样，就变成基准数左边的那个数，基准数还是第一个数
		quick_Sort(arr, j + 1, right); //再对基准点右边的数进行排序  j+1,就是基准数右边的那个数，那么那个数就是右边递归的基准数第一个数
									   //那么j还是从最右边往最左边找比基准数小的数，i还是同样还是从左边开始往右找比基准数大的数
	}
	return TT_OK;
}
void print_Array(const int *const arr, const int count)
{
	cout << "\n输出排序前的数据元素：\n";
	for (int j = 0; j < count; ++j)
	{
		cout << arr[j] << " ";
	}
}
#undef TT_OK
#undef TT_ERROR       //取消宏
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
		cout << "请输入你的选择：";
		int select(0);
		cin >> select;
		if (select == 0)
		{
			cout << "程序已退出，感谢你的使用！" << endl;
			break;
		}
		switch (select)
		{
		case 1:
		{
			int arrLength(0);
			cout << "请输入你想添加多少个元素进行快速排序：";
			
			if ((cin >> arrLength) && (arrLength <= 0))
			{
				cout << "输入错误，请输入正确的数组个数(至少大于0)，否则无法进行排序,请重新输入！" << endl;
				continue;
			}
			int *assignCapacityElem = new int[arrLength];
			if (!assignCapacityElem)
			{
				cout << "给数组分配内存失败，请重启程序，可再次分配！" << endl;
				system("pause");
				exit(0);
			}
			cout << "请分别输入你想要进行排序的" << arrLength << "个元素，分别用回车键分开即可：\n";
			for (int i = 0; i < arrLength; ++i)
			{
				cin >> assignCapacityElem[i];
			}
			print_Array(assignCapacityElem, arrLength);
			quick_Sort(assignCapacityElem, 0, arrLength - 1);
			cout << "\n输出快速排序后的数组元素：\n";
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
			cout << "屏幕已清屏，可以重新输入！" << endl;
			break;
		default:
			cout << "序号输入错误，请重新输入！" << endl;
		}
	}
	system("pause");
	return 0;
}