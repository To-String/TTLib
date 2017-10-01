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
		cout << "\n������Ϊ��" << " [ " << ((abs(m_x) < 0.00001) ? 0 : m_x) << ", " << ((abs(m_y) < 0.00001) ? 0 : m_y) << ", " << ((abs(m_z) < 0.00001) ? 0 : m_z) << " ] " << "\n" << endl;
	}
	Vector3 &operator=(const Vector3 &a);
	bool operator==(const Vector3 &a)const;
	bool operator!=(const Vector3 &a)const;

	Vector3 operator-()const;  //����ΪһԪ�������-������������Ա�¸�  
	Vector3 operator+(const Vector3 &a)const;
	Vector3 operator-(const Vector3 &a)const;  //Vector3 �ļӼ���
	Vector3 operator*(float a)const;
	Vector3 operator/(float a)const;  //Vector3 �ĳ˳���
									  //���ظ��ϸ�ֵ������ļӼ��˳�
	Vector3 operator+=(const Vector3 &a);
	Vector3 operator-=(const Vector3 &a);  //Vector3 �ļӼ���
	Vector3 operator*=(float a);
	Vector3 operator/=(float a);  //Vector3 �ĳ˳���

	void normaLize();  //��׼�� Vector3
	float operator*(const Vector3 &a)const;  //���
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
inline bool Vector3::operator==(const Vector3 &a)const  //�ж����� Vector3 class ��Ȼ��߲���
{
	return ((m_x == a.m_x) && (m_y == a.m_y) && (m_z == a.m_z));
}
inline bool Vector3::operator!=(const Vector3 &a)const
{
	return ((m_x != a.m_x) || (m_y != a.m_y) || (m_z != a.m_z));
}
inline Vector3 Vector3::operator-()const  //����ΪһԪ�������-������������Ա�¸�  
{
	return Vector3(-m_x, -m_y, -m_z);
}
inline Vector3 Vector3::operator+(const Vector3 &a)const   //����Vector3 �ļӼ���
{
	return Vector3(m_x + a.m_x, m_y + a.m_y, m_z + a.m_z);
}
inline Vector3 Vector3::operator-(const Vector3 &a)const
{
	return Vector3(m_x - a.m_x, m_y - a.m_y, m_z - a.m_z);
}
inline Vector3 Vector3::operator*(float a)const //Vector3 �ͱ����ĳ˳���
{
	return Vector3(m_x*a, m_y*a, m_z*a);
}
inline Vector3 Vector3::operator/(float a)const
{
	float temp = 1.0F / a;
	if (!temp)
	{
		cout << "���󣬳�������Ϊ�㣡" << endl;
		system("pause");
		exit(0);
	}
	else
	{
		return Vector3(m_x*temp, m_y*temp, m_z*temp);
	}
}
//���� Vector3 class �Ӽ�����������ļ���
inline Vector3 Vector3::operator+=(const Vector3 &a)
{
	return Vector3(m_x += a.m_x, m_y += a.m_y, m_z += a.m_z);
}
inline Vector3 Vector3::operator-=(const Vector3 &a)  //Vector3 �ļӼ���
{
	return Vector3(m_x -= a.m_x, m_y -= a.m_y, m_z -= a.m_z);
}
// Vector3 class �ͱ����ĳ˳�
inline Vector3 Vector3::operator*=(float a)
{
	return Vector3(m_x *= a, m_y *= a, m_z *= a);
}
inline Vector3 Vector3::operator/=(float a)  //Vector3 �ĳ˳���
{
	float temp = 1.0F / a;
	if (!temp)
	{
		cout << "���󣬳�������Ϊ�㣡" << endl;
		system("pause");
		exit(0);
	}
	else
	{
		return Vector3(m_x *= temp, m_y *= temp, m_z *= temp);
	}
}
inline void Vector3::normaLize()  //��׼�� Vector3
{
	float magSq = m_x*m_x + m_y*m_y + m_z*m_z;
	if (magSq > 0.0f)  //������
	{
		float oneOverMag = 1.0f / sqrt(magSq);
		m_x *= oneOverMag;
		m_y *= oneOverMag;
		m_z *= oneOverMag;
	}

}
inline float Vector3::operator*(const Vector3 &a)const  //���
{
	return (m_x*a.m_x + m_y*a.m_y + m_z*a.m_z);
}


//�ǳ�Ա����
inline Vector3 operator*(float n, const Vector3 &v) //ʵ�ֱ�������
{
	return Vector3(v.m_x*n, v.m_y*n, v.m_z*n);
}
//�ǳ�Ա����
inline float vectorMag(const Vector3 &a)  //��ģ
{
	return sqrt(a.m_x*a.m_x + a.m_y*a.m_y + a.m_z*a.m_z);
}

Vector3 crossProduct(const Vector3 &a, const Vector3 &b)  //���
{
	return Vector3
	(
		a.m_y*b.m_z - a.m_z*b.m_y,
		a.m_z*b.m_x - a.m_x*b.m_z,
		a.m_x*b.m_y - a.m_y*b.m_x
	);
}

float distance(const Vector3 &a, const Vector3 &b)  //���������ľ���
{
	float dx = a.m_x - b.m_x;
	float dy = a.m_y - b.m_y;
	float dz = a.m_z - b.m_z;
	return sqrt(dx * dx + dy * dy + dz * dz);
}
#endif