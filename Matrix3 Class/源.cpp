#include<iostream>
#include<cassert>
#include"Vector3.h"
using namespace std;

constexpr  float kPi = 3.14159265f;   

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
	void setRotate(int axis, float theta);     //����3D ���� x��y��z �����ת ������������ת����
	void setUpScale(const Vector3 &v);  //�������ž���ĺ���
	void setUpProject(const Vector3 &n);  //��������ƽ����׼������ͶӰ�ĺ���
	void setUpReflect(int axis);  //����3D�б�׼�ľ���ƽ�棨x�ᡢ y�ᡢz�ᣩ
	void setUpReflect(const Vector3 &n);  //����3D�����ⷽ��ľ���ƽ��
	void setUpShear(int axis, float s, float t);
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
void Matrix3::setUpShear(int axis, float s, float t)
{
	switch (axis)
	{
	case 1:  //��x�б�y��z
		m11 = 1.0f;  m12 = s;     m13 = t;
		m21 = 0.0f;  m22 = 1.0f;  m23 = 0.0f;
		m31 = 0.0f;  m32 = 0.0f;  m33 = 1.0f;
		break;
	
	case 2:  	//��y�б�x��z
		m11 = 1.0f;  m12 = 0.0f;  m13 = 0.0f;
		m21 = s;     m22 = 1.0f;  m23 = t;
		m31 = 0.0f;  m32 = 0.0f;  m33 = 1.0f;
		break;
	case 3:
		m11 = 1.0f;   m12 = 0.0f;  m13 = 0.0f;
		m21 = 0.0f;   m22 = 1.0f;  m23 = 0.0f;
		m31 = s;      m32 = t;  m33 = 1.0f;
		break;
	default:
		break;
	}
}
void Matrix3::setUpReflect(const Vector3 &n) //����3D�����ⷽ��ľ���ƽ��
{
	//assert(fabs(n*n - 1.0f) < 0.01f);  //���n�Ƿ��ǵ�λ����
	                     
	                  
	float ax = -2.0f*n.m_x;  
	float ay = -2.0f*n.m_y;
	float az = -2.0f*n.m_z;

	//���������ĶԽ����ϵ�Ԫ��
	m11 = 1.0f + ax*n.m_x;
	m22 = 1.0f + ay*n.m_y;
	m33 = 1.0f + az*n.m_z;

	  //  ����Խ��������Ԫ��
	m12 = m21 = ax*n.m_y;
	m13 = m31 = ax*n.m_z;
	m23 = m32 = ay*n.m_z;
}
void Matrix3::setUpReflect(int axis) //����3D�б�׼�ľ���ƽ�棨x�ᡢ y�ᡢz�ᣩ
{
	switch (axis)
	{
	case 1:       //x���귢�����񣨷��䣩
		m11 = -1.0f; m12 = 0.0f;  m13 = 0.0f;
		m21 = 0.0f;  m22 = 1.0f;  m23 = 0.0f;
		m31 = 0.0f;  m32 = 0.0f;  m33 = 1.0f;
		break;

	case 2: //y���귢�����񣨷��䣩
		m11 = 1.0f; m12 = 0.0f;  m13 = 0.0f;
		m21 = 0.0f;  m22 = -1.0f;  m23 = 0.0f;
		m31 = 0.0f;  m32 = 0.0f;  m33 = 1.0f;
		break;
	case 3:   //z���귢�����񣨷��䣩
		m11 = 1.0f; m12 = 0.0f;  m13 = 0.0f;
		m21 = 0.0f;  m22 = 1.0f;  m23 = 0.0f;
		m31 = 0.0f;  m32 = 0.0f;  m33 = -1.0f;
		break;

	default:
		cout << "�������Ų���ȷ�����������룬��ʾ�ӣ�x�ᡢ y�ᡢz�ᣩ���о���" << endl;
	}
}
void Matrix3::setUpScale(const Vector3 &v)  //�������ž���ĺ���
{
	m11 = v.m_x;  m12 = 0.0f;   m13 = 0.0f;
	m21 = 0.0f;   m22 = v.m_y;  m23 = 0.0f;
	m31 = 0.0f;   m32 = 0.0f;   m33 = v.m_z;
}
void Matrix3::setUpProject(const Vector3 &n)   //��������ƽ����׼������ͶӰ�ĺ���
{
	//assert(fabs(n*n - 1.0f) < 0.01);  //���n�Ƿ��ǵ�λ����
	                            //�ȼ��㹫ʽ�Խ����ϵ�Ԫ��
	m11 = 1.0f - n.m_x*n.m_x; 
	m22= 1.0f - n.m_y*n.m_y;
	m33= 1.0f - n.m_z*n.m_z;

	m12 = m21 = -n.m_x*n.m_y;
	m13 = m31 = -n.m_x*n.m_z;
	m23 = m32 = -n.m_y*n.m_z;
}
void Matrix3::print_m()
{
	
	cout << "\n������Ϊ��\n" << m11 << "\t" << m12 << "\t" << m13 << endl
		<< m21 << "\t" << m22 << "\t" << m23 << endl
		<< m31 << "\t" << m32 << "\t" << m33 << "\n" << endl;
}
inline void sinCos(float *const returnSin, float *const returnCos, float theta)
{                       //����Ƕȵ�sinֵ�� cos ֵ
	*returnSin = sin(theta);
	*returnCos = cos(theta);
}
            //����3D ���� x��y��z �����ת ������������ת����
void Matrix3::setRotate(int axis, float theta) //axis����Ϊ 1��2��3������һ������Ȼ��ֱ�������x�ᡢy�ᡢz�ᣬtheta ��ʾ���� ��ת�Ķ���
{
	float s, c;
	sinCos(&s, &c, theta);

	switch (axis)
	{
	case 1:                        //������X�����ת����
		m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
		m21 = 0.0f; m22 = c; m23 = s;
		m31 = 0.0f; m32 = -s; m33 = c;
		break;

	case 2:                            //������y�����ת����
		m11 = c; m12 = 0.0f; m13 = -s;
		m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
		m31 = s; m32 = 0.0f; m33 = c;
		break;
	case 3:
		                             //������z�����ת����
		m11 = c; m12 = s; m13 = 0.0f;
		m21 = -s; m22 = c; m23 = 0.0f;
		m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
		break;

	default:
		cout << "��������ȷ��x�ᡢy�ᡢz�ᣬ�����޷����м��㣡" << endl;
	}
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
			cout << "***************************************************************************" << endl
				<< "\n**********************   ��ӭ����3*3�������㹦�ܳ���  ********************\n" << endl
				<< "************************  ��1����3*3������3*3����ĳ˷�����.   **************" << endl
				<< "************************  ��2����һά������3*3����ĳ˷�����.  *********" << endl
				<< "************************ ��3���� ������3D�г�������������ת. *********" << endl
				<< "********************************************************************************" << endl
				<< "************************  ��4��������3D���������������.  ***************" << endl
				<< "************************  ��5��������3D������ƽ����׼������ͶӰ  ***************" << endl
				<< "************************  ��6��������3D�б�׼�ľ���ƽ�棨x�ᡢ y�ᡢz�ᣩ  ***************" << endl
				<< "************************  ��7��������3D�����ⷽ��ľ���ƽ��  ***************" << endl
				<< "************************  ��8��������3D�еģ�x�ᡢ y�ᡢz�ᣩ���б�  ***************" << endl
				<< "************************  ��9����������  **************************" << endl
				<< "************************  ��0�����˳�����  ***********************" << endl
				<< "***************************************************************************" << endl;

		}
		cout << "\n**********************  ��������Ӧ���ܵ���ţ�  ***********************" << endl;
		int select(0);
		cout << "��������Ӧ��ѡ��";
	
		if (cin >> select && select == 0)
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
		{
			cout << "\n������Ҫ��ת��һά��������������\n";  
			float num1, num2, num3;               //�����������������3����
			cout << "\n��������������������\n";
			while (cin >> num1 >> num2 >> num3)
			{
				if (num1 != 0 && num2 == 0 && num3 ==0)
				{
					break;
				}
				else if (num1 == 0 && num2 != 0 && num3 == 0)
				{
					break;
				}
				else if (num1 == 0 && num2 == 0 && num3 != 0)
				{
					break;
				}
				else
				{
					cout << "\n�����������ʽ����ȷ�������������ڣ�10,0,0����0,10,0�� ��0,0,10�� �����������������������룡" << endl;
					continue;
				}
			}


			cout << "\n������1��2��3 ����һ������ʾ ��x�ᡢy�ᡢz�ᣬ��һ������ת��\n";
			int temp = 0;
		
			while (cin >> temp)
			{
				if (bool tmp = (temp == 1 || temp == 2 || temp == 3) ? true : false)
				{
					break;
				}
				else
				{
					cout << "\n��������ȷ�����ִ��������ᣬ�����޷����м��㣬���������룡" << endl;
					continue;
				}
			}
			

			cout << "\n������һ���������������ת���ٶȣ�\n";
			float degree = 0.0;
			cin >> degree;

			float radian = degree*kPi / 180; //����һ����ʱ��  �ѽǶ�ת���ɻ���

			Vector3 v3(num1, num2, num3), v4;  //v4��������任�Ժ������
			Matrix3 m5;
			m5.setRotate(temp, radian);   //�ȼ�����ת����

			cout << "\n���ԭ����Ϊ��";
			v3.print_v();

			v4 = v3*m5;  //��������ת������ˣ��õ����������v4��

			cout << "�������ͨ��3*3��ת����ת���������Ľ����";
			v4.print_v();  //�ѽ����ӡ����


			break;
		}

		case 4:

		{
			cout << "\n������Ҫ���ŵ�һά��������������\n";
			float svx, svy, svz;
			cin >> svx >> svy >> svz;
			Vector3 v5(svx, svy, svz);

			cout << "\n������һά����������������ʾҪ����ԭ�����ı�����\n";
			float vx, vy, vz;
			cin >> vx >> vy >> vz;
			Vector3 v6(vx, vy, vz);

			Matrix3 m6;
			m6.setUpScale(v6);  //�������ž���

			Vector3 v7;  //v7�����洢 ԭ����ͨ�����ž�������� ������
			v7 = v5*m6; //Ҫ���ŵ�һά������ 3*3��ת������ˣ� �õ�һ����������Ҳ����һ���µĵ�
			v7.print_v();

			break;

		}
		case 5:
		{
			cout << "\n����ҪͶӰ��һά��������������\n";
			float nx, ny, nz;
			cin >> nx >> ny >> nz;

			Vector3 v8(nx, ny, nz);

			cout << "\n������ a �� b������һ���ֱ��ʾ �ǰ���׼��ͶӰ��������ƽ��ͶӰ!" << endl;
			cout << "\n���������ѡ��";
			char userChoice;
			cin >> userChoice;
			switch (userChoice)
			{
			case 'a':
			{
				cout << "\n���루0,1) (1,0) �ֱ��ʾͶӰ�� x�� ���� y��" << endl
					<< ", ���루0,0,1������0,1,0������1,0,0����ʾͶӰ��xyƽ�桢xzƽ�桢yzƽ�棡" << endl;
				cout << "\n��������������ʾҪͶӰ���ĸ�ƽ����������᣺\n";

				float vx, vy, vz;
				while (cin >> vx >> vy >> vz)
				{
					if ((vx == 0 && vy == 1 && vz == 0) || (vx == 1 && vy == 0 && vz == 0) || ((vx == 0 && vy == 0 && vz == 1)))
					{
						break;
					}
					else
					{
						cout << "\n��������ȷ����ҪͶӰ��ƽ����ᣬ�����޷����м��㣡" << endl;
						cout << "\n���������룺\n";
						continue;
					}
				}

				Vector3 n(vx, vy, vz), v9;  //n����ҪͶӰ�ĵ�λ������Ҫ��ͶӰƽ���ഹֱ��v9�����洢ͶӰ��Ľ��
				Matrix3 m7;
				m7.setUpProject(n);   //����ͶӰ����
				v9 = v8*m7;
				v9.print_v();
				break;
			}

			case 'b':
			{
				cout << "\n�������������ֱ��ʾͶӰ������ƽ��ĵ�λ������\n";
				float vx, vy, vz;
				cin >> vx >> vy >> vz;

				Vector3 n1(vx, vy, vz), v16;
				Matrix3 m11;
				m11.setUpProject(n1);
				v16 = v8*m11;
				v16.print_v();
				break;
			}
			default:
				cout << "\n�������Ų���ȷ�����������룺\n";
				continue;
			}
			break;
		}
		case 6:
		{
			cout << "\n����Ҫ�����һά��������������\n";
			float mx, my, mz;
			cin >> mx >> my >> mz;
			Vector3 v10(mx, my, mz),v11;

			cout << "\n������ 1��2��3 ����һ������ʾ�� ��x�ᡢ y�ᡢz�ᣩ���о���\n";
			int mirror = 0;
			while (cin >> mirror)
			{
				if (mirror == 1 || mirror == 2 || mirror == 3)
				{
					break;
				}
				else
				{
					cout << "\n�������Ų���ȷ�����������룬�����޷����м��㣡" << endl;
					cout << "\n���������� 1��2��3 ����һ������ʾ�� ��x�ᡢ y�ᡢz�ᣩ���о���\n";
					continue;
				}
			}

			Matrix3 m8;
			m8.setUpReflect(mirror); //���㾵�����
			v11 = v10*m8;  //Ҫ�����һά�����뾵�������ˣ��ó�һ��������
			v11.print_v();
			break;
		
		}

		case 7:
		{
			cout << "\n����Ҫ���⾵���һά��������������\n";
			float mx, my, mz;
			cin >> mx >> my >> mz;
			Vector3 v12(mx, my, mz), v13;

			cout << "\n����������������о������������\n";
			float anyX, anyY, anyZ;
			cin >> anyX >> anyY >> anyZ;

			Vector3 n1(anyX, anyY, anyZ);

			Matrix3 m9;
			m9.setUpReflect(n1);
			v13 = v12*m9;
			v13.print_v();

			break;
		}
		case 8:
		{
			cout << "\n����Ҫ�����б��һά��������������\n";
			float sx, sy, sz;
			cin >> sx >> sy >> sz;
			Vector3 v14(sx, sy, sz), v15;

			cout << "\n���������ĸ���ȥ�б䣨����1��2��3 ����һ������ x�ᡢy�ᡢz�ᣩ��";
			int shear = 0;
			while (cin >> shear)
			{
				if (shear == 1 || shear == 2 || shear == 3)
				{
					break;
				}
				else
				{
					cout << "\n��������ȷ����ţ������޷����м��㣬���������룺\n";
					continue;
				}
			}

			cout << "\n����������������Ҫ�б�ı������ӣ�\n";
			float ts = 0.0, tt = 0.0;
			cin >> ts >> tt;

			Matrix3 m10;
			m10.setUpShear(shear, ts, tt);  //�����б����
			v15 = v14*m10; // Ȼ��Ҫ�б���������б������ˣ��ó��б���λ�ã�Ҳ����������
			v15.print_v();
			break;
		}
		case 9:
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