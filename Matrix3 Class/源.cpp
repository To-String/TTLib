#include<iostream>
#include"Vector3.h"
using namespace std;

class Vector3;

class Matrix3 
{
public:
	Matrix3() {};
	~Matrix3(){};
	Matrix3(float m_11, float m_12, float m_13,
		float m_21, float m_22, float m_23,
		float m_31, float m_32, float m_33);

	void print_m();
public:
	float m11, m12, m13;
	float m21, m22, m23;
	float m31, m32, m33;

	
};

Matrix3::Matrix3(float m_11, float m_12, float m_13,
	float m_21, float m_22, float m_23,
	float m_31, float m_32, float m_33):

	m11(m_11),m12(m_12),m13(m_13),
	m21(m_21),m22(m_22),m23(m_23),
	m31(m_31),m32(m_32),m33(m_33)
{

}
void Matrix3::print_m()
{
	
	cout << "\n输出结果为：\n" << m11 << "\t" << m12 << "\t" << m13 << endl
		<< m21 << "\t" << m22 << "\t" << m23 << endl
		<< m31 << "\t" << m32 << "\t" << m33 << "\n" << endl;
}
 Matrix3 operator *(const Matrix3 &a, const Matrix3 &b)
{
	Matrix3 r;
	                                             //计算矩阵的第一行
	r.m11 = a.m11*b.m11 + a.m12*b.m21 + a.m13*b.m31;  
	r.m12 = a.m11*b.m12 + a.m12*b.m22 + a.m13*b.m32;
	r.m13 = a.m11*b.m13 + a.m12*b.m23 + a.m13*b.m33;
	                                               //计算矩阵的第二行
	r.m21 = a.m21*b.m11 + a.m22*b.m21 + a.m23*b.m31;
	r.m22 = a.m21*b.m12 + a.m22*b.m22 + a.m23*b.m32;
	r.m23 = a.m21*b.m13 + a.m22*b.m23 + a.m23*b.m33;
	                                                //计算矩阵的第三行
	r.m31 = a.m31*b.m11 + a.m32*b.m21 + a.m33*b.m31;
	r.m32 = a.m31*b.m12 + a.m32*b.m22 + a.m33*b.m32;
	r.m33 = a.m31*b.m13 + a.m32*b.m23 + a.m33*b.m33;

	return  r;
	
}



 Vector3 operator *(const Vector3 &p, const Matrix3 &m)
 {
	 return Vector3
	 (p.m_x*m.m11 + p.m_y*m.m21 + p.m_z*m.m31,
		 p.m_x*m.m12+p.m_y*m.m22+p.m_z*m.m32,
		 p.m_x*m.m13+p.m_y*m.m23+p.m_z*m.m33
	 );
 }


int main()
{
	while (true)
	{
		{
			cout<< "***************************************************************************" << endl
			    << "\n**********************   欢迎来到3*3矩阵运算程序！  ********************\n" << endl
				<< "************************  按1——3*3矩阵与3*3矩阵的乘法运算.  **************" << endl
				<< "************************  按2——一维向量和3*3矩阵的乘法运算.  *********" << endl
				<< "************************  按3——清屏！  **************************" << endl
				<< "************************  按0——退出程序！  ***********************" << endl
				<< "***************************************************************************" << endl;

		}
		cout << "\n**********************  请输入相应功能的序号！  ***********************" << endl;
		int select(0);
		cout << "请输入相应的选择：";
		cin >> select;
		if (select == 0)
		{
			cout << "程序已退出，感谢您的使用！" << endl;
			break;
		}
		switch (select)
		{ 
		case 1:
		{
			float num11, num12, num13;
			float num21, num22, num23;
			float num31, num32, num33;

			cout << "\n请输入两个3*3 矩阵的九个数，然后做矩阵与矩阵的乘法!" << endl;
			//这里输入第一个矩阵的九个数字
			cout << "\n请输入3*3 矩阵的第一个矩阵的第1行的3个数：\n";
			cin >> num11 >> num12 >> num13;

			cout << "\n请输入3*3 矩阵的第一个矩阵的第2行的3个数：\n";
			cin >> num21 >> num22 >> num23;

			cout << "\n请输入3*3 矩阵的第一个矩阵的第3行的3个数：\n";
			cin >> num31 >> num32 >> num33;

			cout << "\n*********************分割线*************************" << endl;

			Matrix3 m1(num11, num12, num13,    //把第一个矩阵的九个数用构造函数初始化
				num21, num22, num23,
				num31, num32, num33);
			//输入第二个矩阵的九个数字
			cout << "\n请输入3*3 矩阵的第二个矩阵第1行的3个数：\n";
			cin >> num11 >> num12 >> num13;

			cout << "\n请输入3*3 矩阵的第二个矩阵的第2行的3个数：\n";
			cin >> num21 >> num22 >> num23;

			cout << "\n请输入3*3 矩阵的第二个矩阵的第3行的3个数：\n";
			cin >> num31 >> num32 >> num33;

			Matrix3 m2(num11, num12, num13,       //把第二个矩阵的九个数用构造函数初始化
				num21, num22, num23,
				num31, num32, num33);

			Matrix3 m3;         //两个矩阵进行乘法
			m3 = m1*m2;
			//m3 =operator*(m1, m2);
			m3.print_m();

			break;
		}
		case 2:
		{
			cout << "\n输入向量的3个数和3*3矩阵的9个数，然后做向量与矩阵的乘法！" << endl;

			float num1, num2, num3;               //这里输入的是向量的3个数
			cout << "\n请输入向量的三个数：\n";
			cin >> num1 >> num2 >> num3;

			Vector3 v1(num1, num2, num3);

			float Mnum11, Mnum12, Mnum13;
			float Mnum21, Mnum22, Mnum23;
			float Mnum31, Mnum32, Mnum33;
			 
			cout << "\n*********************分割线*************************" << endl;

			cout << "\n请输入3*3矩阵的9个数字：\n";
			//这里输入的是3*3矩阵的九个数
			cout << "\n请输入3*3 矩阵第1行的3个数：\n";
			cin >> Mnum11 >> Mnum12 >> Mnum13;

			cout << "\n请输入3*3 矩阵第2行的3个数：\n";
			cin >> Mnum21 >> Mnum22 >> Mnum23;

			cout << "\n请输入3*3 矩阵第3行的3个数：\n";
			cin >> Mnum31 >> Mnum32 >> Mnum33;

			Matrix3 m4(Mnum11, Mnum12, Mnum13,
				Mnum21, Mnum22, Mnum23,
				Mnum31, Mnum32, Mnum33);

			Vector3 v2 = v1*m4;  // 向量和3*3 矩阵相乘，最后还是一个向量
			//Vector3 v2 = operator*(v1, m4);
			v2.print_v();
			break;
		}
		case 3:
			system("cls");
			cout << "屏幕已经清屏，可以重新输入!" << endl;
			break;
		default:
			cout << "输入的序号不正确，请重新输入!" << endl;
		}
	}
	system("pause");
	return 0;
}