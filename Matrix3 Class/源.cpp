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
	
	cout << "\n������Ϊ��\n" << m11 << "\t" << m12 << "\t" << m13 << endl
		<< m21 << "\t" << m22 << "\t" << m23 << endl
		<< m31 << "\t" << m32 << "\t" << m33 << "\n" << endl;
}
 Matrix3 operator *(const Matrix3 &a, const Matrix3 &b)
{
	Matrix3 r;
	                                             //�������ĵ�һ��
	r.m11 = a.m11*b.m11 + a.m12*b.m21 + a.m13*b.m31;  
	r.m12 = a.m11*b.m12 + a.m12*b.m22 + a.m13*b.m32;
	r.m13 = a.m11*b.m13 + a.m12*b.m23 + a.m13*b.m33;
	                                               //�������ĵڶ���
	r.m21 = a.m21*b.m11 + a.m22*b.m21 + a.m23*b.m31;
	r.m22 = a.m21*b.m12 + a.m22*b.m22 + a.m23*b.m32;
	r.m23 = a.m21*b.m13 + a.m22*b.m23 + a.m23*b.m33;
	                                                //�������ĵ�����
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
			    << "\n**********************   ��ӭ����3*3�����������  ********************\n" << endl
				<< "************************  ��1����3*3������3*3����ĳ˷�����.  **************" << endl
				<< "************************  ��2����һά������3*3����ĳ˷�����.  *********" << endl
				<< "************************  ��3����������  **************************" << endl
				<< "************************  ��0�����˳�����  ***********************" << endl
				<< "***************************************************************************" << endl;

		}
		cout << "\n**********************  ��������Ӧ���ܵ���ţ�  ***********************" << endl;
		int select(0);
		cout << "��������Ӧ��ѡ��";
		cin >> select;
		if (select == 0)
		{
			cout << "�������˳�����л����ʹ�ã�" << endl;
			break;
		}
		switch (select)
		{ 
		case 1:
		{
			float num11, num12, num13;
			float num21, num22, num23;
			float num31, num32, num33;

			cout << "\n����������3*3 ����ľŸ�����Ȼ�������������ĳ˷�!" << endl;
			//���������һ������ľŸ�����
			cout << "\n������3*3 ����ĵ�һ������ĵ�1�е�3������\n";
			cin >> num11 >> num12 >> num13;

			cout << "\n������3*3 ����ĵ�һ������ĵ�2�е�3������\n";
			cin >> num21 >> num22 >> num23;

			cout << "\n������3*3 ����ĵ�һ������ĵ�3�е�3������\n";
			cin >> num31 >> num32 >> num33;

			cout << "\n*********************�ָ���*************************" << endl;

			Matrix3 m1(num11, num12, num13,    //�ѵ�һ������ľŸ����ù��캯����ʼ��
				num21, num22, num23,
				num31, num32, num33);
			//����ڶ�������ľŸ�����
			cout << "\n������3*3 ����ĵڶ��������1�е�3������\n";
			cin >> num11 >> num12 >> num13;

			cout << "\n������3*3 ����ĵڶ�������ĵ�2�е�3������\n";
			cin >> num21 >> num22 >> num23;

			cout << "\n������3*3 ����ĵڶ�������ĵ�3�е�3������\n";
			cin >> num31 >> num32 >> num33;

			Matrix3 m2(num11, num12, num13,       //�ѵڶ�������ľŸ����ù��캯����ʼ��
				num21, num22, num23,
				num31, num32, num33);

			Matrix3 m3;         //����������г˷�
			m3 = m1*m2;
			//m3 =operator*(m1, m2);
			m3.print_m();

			break;
		}
		case 2:
		{
			cout << "\n����������3������3*3�����9������Ȼ�������������ĳ˷���" << endl;

			float num1, num2, num3;               //�����������������3����
			cout << "\n��������������������\n";
			cin >> num1 >> num2 >> num3;

			Vector3 v1(num1, num2, num3);

			float Mnum11, Mnum12, Mnum13;
			float Mnum21, Mnum22, Mnum23;
			float Mnum31, Mnum32, Mnum33;
			 
			cout << "\n*********************�ָ���*************************" << endl;

			cout << "\n������3*3�����9�����֣�\n";
			//�����������3*3����ľŸ���
			cout << "\n������3*3 �����1�е�3������\n";
			cin >> Mnum11 >> Mnum12 >> Mnum13;

			cout << "\n������3*3 �����2�е�3������\n";
			cin >> Mnum21 >> Mnum22 >> Mnum23;

			cout << "\n������3*3 �����3�е�3������\n";
			cin >> Mnum31 >> Mnum32 >> Mnum33;

			Matrix3 m4(Mnum11, Mnum12, Mnum13,
				Mnum21, Mnum22, Mnum23,
				Mnum31, Mnum32, Mnum33);

			Vector3 v2 = v1*m4;  // ������3*3 ������ˣ������һ������
			//Vector3 v2 = operator*(v1, m4);
			v2.print_v();
			break;
		}
		case 3:
			system("cls");
			cout << "��Ļ�Ѿ�������������������!" << endl;
			break;
		default:
			cout << "�������Ų���ȷ������������!" << endl;
		}
	}
	system("pause");
	return 0;
}