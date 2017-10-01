#ifndef TT_VECTOR3_H_INCLUDED_
#define TT_VECTOR3_H_INCLUDED_
using namespace std;
#include<math.h>

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
		cout << "\n输出结果为：" << " [ " << ((abs(m_x) < 0.00001) ? 0 : m_x) << ", " << ((abs(m_y) < 0.00001) ? 0 : m_y) << ", " << ((abs(m_z) < 0.00001) ? 0 : m_z) << " ] " << "\n" << endl;
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
	return (m_x*a.m_x + m_y*a.m_y + m_z*a.m_z);
}


//非成员函数
inline Vector3 operator*(float n, const Vector3 &v) //实现标量的左晨
{
	return Vector3(v.m_x*n, v.m_y*n, v.m_z*n);
}
//非成员函数
inline float vectorMag(const Vector3 &a)  //求模
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
#endif