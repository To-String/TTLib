#include<iostream>
#include<math.h>
using namespace std;

class Vector3
{
public:
	Vector3() {};
	~Vector3() {};
	Vector3(const Vector3 &a);
	Vector3(float nx, float ny, float nz);
	void setZero()
	{
		m_x = m_y = m_z = 0.0F;
	}
	void print_v()
	{
		cout << " [" << m_x << ", " << m_y << ", " << m_z << "]" << endl;
	}
	Vector3 &operator=(const Vector3 &a);
	bool operator==(const Vector3 &a)const;
	bool operator!=(const Vector3 &a)const;

	Vector3 operator-()const;  //重载为一元运算符“-”，用来给成员致负  
	Vector3 operator+(const Vector3 &a)const;
	Vector3 operator-(const Vector3 &a)const;  //Vector3 的加减法
	Vector3 operator*(float a)const;
	Vector3 operator/(float a)const;  //Vector3 的乘除法
									  //重载复合赋值运算符的加减乘除
	Vector3 operator+=(const Vector3 &a);
	Vector3 operator-=(const Vector3 &a);  //Vector3 的加减法
	Vector3 operator*=(float a);
	Vector3 operator/=(float a);  //Vector3 的乘除法

	void normaLize();  //标准化 Vector3
	float operator*(const Vector3 &a)const;  //点乘
public:
	float m_x, m_y, m_z;
};
Vector3::Vector3(const Vector3 &a) :m_x(a.m_x), m_y(a.m_y), m_z(a.m_z) {}

Vector3::Vector3(float nx, float ny, float nz) : m_x(nx), m_y(ny), m_z(nz) {}

Vector3 &Vector3::operator=(const Vector3 &a)
{
	m_x = a.m_x;
	m_y = a.m_y;
	m_z = a.m_z;
	return *this;
}
inline bool Vector3::operator==(const Vector3 &a)const  //判断两个 Vector3 class 相等或者不等
{
	return ((m_x == a.m_x) && (m_y == a.m_y) && (m_z == a.m_z));
}
inline bool Vector3::operator!=(const Vector3 &a)const
{
	return ((m_x != a.m_x) || (m_y != a.m_y) || (m_z != a.m_z));
}
inline Vector3 Vector3::operator-()const  //重载为一元运算符“-”，用来给成员致负  
{
	return Vector3(-m_x, -m_y, -m_z);
}
inline Vector3 Vector3::operator+(const Vector3 &a)const   //两个Vector3 的加减法
{
	return Vector3(m_x + a.m_x, m_y + a.m_y, m_z + a.m_z);
}
inline Vector3 Vector3::operator-(const Vector3 &a)const
{
	return Vector3(m_x - a.m_x, m_y - a.m_y, m_z - a.m_z);
}
inline Vector3 Vector3::operator*(float a)const //Vector3 和标量的乘除法
{
	return Vector3(m_x*a, m_y*a, m_z*a);
}
inline Vector3 Vector3::operator/(float a)const
{
	float temp = 1.0F / a;
	if (!temp)
	{
		cout << "错误，除数不能为零！" << endl;
		system("pause");
		exit(0);
	}
	else
	{
		return Vector3(m_x*temp, m_y*temp, m_z*temp);
	}
}
//两个 Vector3 class 加减复合运算符的计算
inline Vector3 Vector3::operator+=(const Vector3 &a)
{
	return Vector3(m_x += a.m_x, m_y += a.m_y, m_z += a.m_z);
}
inline Vector3 Vector3::operator-=(const Vector3 &a)  //Vector3 的加减法
{
	return Vector3(m_x -= a.m_x, m_y -= a.m_y, m_z -= a.m_z);
}
// Vector3 class 和标量的乘除
inline Vector3 Vector3::operator*=(float a)
{
	return Vector3(m_x *= a, m_y *= a, m_z *= a);
}
inline Vector3 Vector3::operator/=(float a)  //Vector3 的乘除法
{
	float temp = 1.0F / a;
	if (!temp)
	{
		cout << "错误，除数不能为零！" << endl;
		system("pause");
		exit(0);
	}
	else
	{
		return Vector3(m_x *= temp, m_y *= temp, m_z *= temp);
	}
}
inline void Vector3::normaLize()  //标准化 Vector3
{
	float magSq = m_x*m_x + m_y*m_y + m_z*m_z;
	if (magSq > 0.0f)  //检查除零
	{
		float oneOverMag = 1.0f / sqrt(magSq);
		m_x *= oneOverMag;
		m_y *= oneOverMag;
		m_z *= oneOverMag;
	}

}
inline float Vector3::operator*(const Vector3 &a)const  //点乘
{
	return (m_x*a.m_x + m_y*a.m_y+m_z*a.m_z);
}


//非成员函数
inline Vector3 operator*(float n, const Vector3 &v) //实现标量的左晨
{
	return Vector3(v.m_x*n, v.m_y*n, v.m_z*n);
}
//非成员函数
inline float vectorMag( const Vector3 &a)  //求模
{
	return sqrt(a.m_x*a.m_x + a.m_y*a.m_y + a.m_z*a.m_z);
}

Vector3 crossProduct(const Vector3 &a, const Vector3 &b)  //叉乘
{
	return Vector3
	(
		a.m_y*b.m_z - a.m_z*b.m_y,
		a.m_z*b.m_x - a.m_x*b.m_z,
		a.m_x*b.m_y - a.m_y*b.m_x
	);
}

float distance(const Vector3 &a, const Vector3 &b)  //计算两点间的距离
{
	float dx = a.m_x - b.m_x;
	float dy = a.m_y - b.m_y;
	float dz = a.m_z - b.m_z;
	return sqrt(dx * dx + dy * dy + dz * dz);
}

int main()
{
	
	float num1, num2, num3;
	cout << "分别输入3个 Vector3 class 数字，用来做相应的运算：\n";
	cin >> num1 >> num2 >> num3;
	Vector3 v1(num1, num2, num3);
	Vector3 v2(num1 - 5.0F, num2 - 5.0F, num3 - 5.0F);
	Vector3 v3= v3.operator=(v1);  //Vector3 v3= v1;  //测试赋值运算符
	v1.print_v(); //首先分别打印它们的值
	v2.print_v();
	v3.print_v();

	if (v1 == v3)  //测试 "=="运算符
	{
		cout << "v1和v3相等！" << endl;
	}
	else
	{
		cout << "v1和v3不相等！" << endl;
	}
	if (v2 == v3)
	{
		cout << "v2和v3相等！" << endl;
	}
	else
	{
		cout << "v2和v3不相等！" << endl;
	}

	if (v1 != v3)   //测试“！=”运算符
	{
		cout << "v1和v3不相等！" << endl;
	}
	else
	{
		cout << "v1和v3相等！" << endl;
	}
	if (v2 != v3)
	{
		cout << "v2和v3不相等！" << endl;
	}
	else
	{
		cout << "v2和v3相等！" << endl;
	}

	Vector3 v4 = -v2;  //测试一元运算符“-” 来给Vector3  致负
	v4.print_v();

	v4.setZero();  //设置为零向量
	v4.print_v();

	Vector3 v5 = v1.operator+(v2);       //v1 + v2; 两个向量相加
	v5.print_v();

	Vector3 v6 = v5.operator-(v1);       //v5 - v1; 两个向量相减
	v6.print_v();

	v6 = v6.operator*(10);                 //v6 * 10;  测试 Vector3  与标量相乘除
	v6.print_v();

	v6 = v6.operator/(5);  //v6/v5
	v6.print_v();

	v6.operator+=(v5);  //v6 += v5; 测试复合运算符的加法，因为上面已经测试过了，所以不一一测试了
	v6.print_v();

	v6 = v6.operator/=(5);  //v6/v5  测试 Vector3  与标量相乘除，用的 是复合运算符
	v6.print_v();

	v6.normaLize();  //给 v6给标准化了
	v6.print_v();

	Vector3 d1(3, -2, 7);                    //两个vector3 的点乘
	Vector3 d2(0, 4, -1);
	float dotProduct = d1.operator*(d2);  //d1*d2;
	cout << "输出两个Vector3的点乘的运算结果：" << dotProduct << endl;

	double  angle = acos(dotProduct / (vectorMag(d1)*(vectorMag(d2)))) * 180 / 3.14159;  //先求的弧度在转化成角度了
	cout << "输出两个 vector3的角度：" << angle << endl;

	float dist = distance(d1, d2);                                  //求两个vector3的距离
	cout << "输出两个Vector3的距离为：" << dist << endl;

	float temp = vectorMag(v1);            //求v1的大小(模）
	cout << "输出v1的大小：" << temp << endl;

	Vector3 vv(1, 3, 4);  //两个vector3   叉乘
	Vector3 vs(2, -5, 8);
	Vector3 v7 = crossProduct(vv, vs);
	v7.print_v();

	v7 = operator*(50, v7);  //实现 v7的与标量的左乘   v7=50*v7;
	v7.print_v();

	cout << endl;
	system("pause");
	return 0;
}