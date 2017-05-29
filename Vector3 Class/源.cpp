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
	return (m_x*a.m_x + m_y*a.m_y+m_z*a.m_z);
}


//�ǳ�Ա����
inline Vector3 operator*(float n, const Vector3 &v) //ʵ�ֱ�������
{
	return Vector3(v.m_x*n, v.m_y*n, v.m_z*n);
}
//�ǳ�Ա����
inline float vectorMag( const Vector3 &a)  //��ģ
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

int main()
{
	
	float num1, num2, num3;
	cout << "�ֱ�����3�� Vector3 class ���֣���������Ӧ�����㣺\n";
	cin >> num1 >> num2 >> num3;
	Vector3 v1(num1, num2, num3);
	Vector3 v2(num1 - 5.0F, num2 - 5.0F, num3 - 5.0F);
	Vector3 v3= v3.operator=(v1);  //Vector3 v3= v1;  //���Ը�ֵ�����
	v1.print_v(); //���ȷֱ��ӡ���ǵ�ֵ
	v2.print_v();
	v3.print_v();

	if (v1 == v3)  //���� "=="�����
	{
		cout << "v1��v3��ȣ�" << endl;
	}
	else
	{
		cout << "v1��v3����ȣ�" << endl;
	}
	if (v2 == v3)
	{
		cout << "v2��v3��ȣ�" << endl;
	}
	else
	{
		cout << "v2��v3����ȣ�" << endl;
	}

	if (v1 != v3)   //���ԡ���=�������
	{
		cout << "v1��v3����ȣ�" << endl;
	}
	else
	{
		cout << "v1��v3��ȣ�" << endl;
	}
	if (v2 != v3)
	{
		cout << "v2��v3����ȣ�" << endl;
	}
	else
	{
		cout << "v2��v3��ȣ�" << endl;
	}

	Vector3 v4 = -v2;  //����һԪ�������-�� ����Vector3  �¸�
	v4.print_v();

	v4.setZero();  //����Ϊ������
	v4.print_v();

	Vector3 v5 = v1.operator+(v2);       //v1 + v2; �����������
	v5.print_v();

	Vector3 v6 = v5.operator-(v1);       //v5 - v1; �����������
	v6.print_v();

	v6 = v6.operator*(10);                 //v6 * 10;  ���� Vector3  �������˳�
	v6.print_v();

	v6 = v6.operator/(5);  //v6/v5
	v6.print_v();

	v6.operator+=(v5);  //v6 += v5; ���Ը���������ļӷ�����Ϊ�����Ѿ����Թ��ˣ����Բ�һһ������
	v6.print_v();

	v6 = v6.operator/=(5);  //v6/v5  ���� Vector3  �������˳����õ� �Ǹ��������
	v6.print_v();

	v6.normaLize();  //�� v6����׼����
	v6.print_v();

	Vector3 d1(3, -2, 7);                    //����vector3 �ĵ��
	Vector3 d2(0, 4, -1);
	float dotProduct = d1.operator*(d2);  //d1*d2;
	cout << "�������Vector3�ĵ�˵���������" << dotProduct << endl;

	double  angle = acos(dotProduct / (vectorMag(d1)*(vectorMag(d2)))) * 180 / 3.14159;  //����Ļ�����ת���ɽǶ���
	cout << "������� vector3�ĽǶȣ�" << angle << endl;

	float dist = distance(d1, d2);                                  //������vector3�ľ���
	cout << "�������Vector3�ľ���Ϊ��" << dist << endl;

	float temp = vectorMag(v1);            //��v1�Ĵ�С(ģ��
	cout << "���v1�Ĵ�С��" << temp << endl;

	Vector3 vv(1, 3, 4);  //����vector3   ���
	Vector3 vs(2, -5, 8);
	Vector3 v7 = crossProduct(vv, vs);
	v7.print_v();

	v7 = operator*(50, v7);  //ʵ�� v7������������   v7=50*v7;
	v7.print_v();

	cout << endl;
	system("pause");
	return 0;
}