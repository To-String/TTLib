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
	void setRotate(int axis, float theta);     //设置3D 中绕 x、y、z 轴的旋转 函数，计算旋转矩阵
	void setUpScale(const Vector3 &v);  //进行缩放矩阵的函数
	void setUpProject(const Vector3 &n);  //进行任意平面或标准坐标轴投影的函数
	void setUpReflect(int axis);  //计算3D中标准的镜像平面（x轴、 y轴、z轴）
	void setUpReflect(const Vector3 &n);  //计算3D中任意方向的镜像平面
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
	case 1:  //用x切变y，z
		m11 = 1.0f;  m12 = s;     m13 = t;
		m21 = 0.0f;  m22 = 1.0f;  m23 = 0.0f;
		m31 = 0.0f;  m32 = 0.0f;  m33 = 1.0f;
		break;
	
	case 2:  	//用y切变x，z
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
void Matrix3::setUpReflect(const Vector3 &n) //计算3D中任意方向的镜像平面
{
	//assert(fabs(n*n - 1.0f) < 0.01f);  //检查n是否是单位向量
	                     
	                  
	float ax = -2.0f*n.m_x;  
	float ay = -2.0f*n.m_y;
	float az = -2.0f*n.m_z;

	//先求镜像矩阵的对角线上的元素
	m11 = 1.0f + ax*n.m_x;
	m22 = 1.0f + ay*n.m_y;
	m33 = 1.0f + az*n.m_z;

	  //  再求对角线以外的元素
	m12 = m21 = ax*n.m_y;
	m13 = m31 = ax*n.m_z;
	m23 = m32 = ay*n.m_z;
}
void Matrix3::setUpReflect(int axis) //计算3D中标准的镜像平面（x轴、 y轴、z轴）
{
	switch (axis)
	{
	case 1:       //x坐标发生镜像（反射）
		m11 = -1.0f; m12 = 0.0f;  m13 = 0.0f;
		m21 = 0.0f;  m22 = 1.0f;  m23 = 0.0f;
		m31 = 0.0f;  m32 = 0.0f;  m33 = 1.0f;
		break;

	case 2: //y坐标发生镜像（反射）
		m11 = 1.0f; m12 = 0.0f;  m13 = 0.0f;
		m21 = 0.0f;  m22 = -1.0f;  m23 = 0.0f;
		m31 = 0.0f;  m32 = 0.0f;  m33 = 1.0f;
		break;
	case 3:   //z坐标发生镜像（反射）
		m11 = 1.0f; m12 = 0.0f;  m13 = 0.0f;
		m21 = 0.0f;  m22 = 1.0f;  m23 = 0.0f;
		m31 = 0.0f;  m32 = 0.0f;  m33 = -1.0f;
		break;

	default:
		cout << "输入的序号不正确，请重新输入，表示从（x轴、 y轴、z轴）进行镜像！" << endl;
	}
}
void Matrix3::setUpScale(const Vector3 &v)  //进行缩放矩阵的函数
{
	m11 = v.m_x;  m12 = 0.0f;   m13 = 0.0f;
	m21 = 0.0f;   m22 = v.m_y;  m23 = 0.0f;
	m31 = 0.0f;   m32 = 0.0f;   m33 = v.m_z;
}
void Matrix3::setUpProject(const Vector3 &n)   //进行任意平面或标准坐标轴投影的函数
{
	//assert(fabs(n*n - 1.0f) < 0.01);  //检查n是否是单位向量
	                            //先计算公式对角线上的元素
	m11 = 1.0f - n.m_x*n.m_x; 
	m22= 1.0f - n.m_y*n.m_y;
	m33= 1.0f - n.m_z*n.m_z;

	m12 = m21 = -n.m_x*n.m_y;
	m13 = m31 = -n.m_x*n.m_z;
	m23 = m32 = -n.m_y*n.m_z;
}
void Matrix3::print_m()
{
	
	cout << "\n输出结果为：\n" << m11 << "\t" << m12 << "\t" << m13 << endl
		<< m21 << "\t" << m22 << "\t" << m23 << endl
		<< m31 << "\t" << m32 << "\t" << m33 << "\n" << endl;
}
inline void sinCos(float *const returnSin, float *const returnCos, float theta)
{                       //计算角度的sin值和 cos 值
	*returnSin = sin(theta);
	*returnCos = cos(theta);
}
            //设置3D 中绕 x、y、z 轴的旋转 函数，计算旋转矩阵
void Matrix3::setRotate(int axis, float theta) //axis参数为 1、2、3中任意一个数，然后分别代表的是x轴、y轴、z轴，theta 表示的是 旋转的度数
{
	float s, c;
	sinCos(&s, &c, theta);

	switch (axis)
	{
	case 1:                        //计算绕X轴的旋转矩阵
		m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
		m21 = 0.0f; m22 = c; m23 = s;
		m31 = 0.0f; m32 = -s; m33 = c;
		break;

	case 2:                            //计算绕y轴的旋转矩阵
		m11 = c; m12 = 0.0f; m13 = -s;
		m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
		m31 = s; m32 = 0.0f; m33 = c;
		break;
	case 3:
		                             //计算绕z轴的旋转矩阵
		m11 = c; m12 = s; m13 = 0.0f;
		m21 = -s; m22 = c; m23 = 0.0f;
		m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
		break;

	default:
		cout << "请输入正确的x轴、y轴、z轴，否则无法进行计算！" << endl;
	}
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
			cout << "***************************************************************************" << endl
				<< "\n**********************   欢迎来到3*3矩阵运算功能程序！  ********************\n" << endl
				<< "************************  按1——3*3矩阵与3*3矩阵的乘法运算.   **************" << endl
				<< "************************  按2——一维向量和3*3矩阵的乘法运算.  *********" << endl
				<< "************************ 按3—— 计算绕3D中常规的坐标轴的旋转. *********" << endl
				<< "********************************************************************************" << endl
				<< "************************  按4——计算3D中沿坐标轴的缩放.  ***************" << endl
				<< "************************  按5——计算3D中任意平面或标准坐标轴投影  ***************" << endl
				<< "************************  按6——计算3D中标准的镜像平面（x轴、 y轴、z轴）  ***************" << endl
				<< "************************  按7——计算3D中任意方向的镜像平面  ***************" << endl
				<< "************************  按8——计算3D中的（x轴、 y轴、z轴）的切变  ***************" << endl
				<< "************************  按9——清屏！  **************************" << endl
				<< "************************  按0——退出程序！  ***********************" << endl
				<< "***************************************************************************" << endl;

		}
		cout << "\n**********************  请输入相应功能的序号！  ***********************" << endl;
		int select(0);
		cout << "请输入相应的选择：";
	
		if (cin >> select && select == 0)
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
		{
			cout << "\n请输入要旋转的一维向量的三个数：\n";  
			float num1, num2, num3;               //这里输入的是向量的3个数
			cout << "\n请输入向量的三个数：\n";
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
					cout << "\n输入的三个格式不正确，请输入类似于（10,0,0）（0,10,0） （0,0,10） 这样的三个数，请重新输入！" << endl;
					continue;
				}
			}


			cout << "\n请输入1、2、3 任意一个数表示 按x轴、y轴、z轴，哪一个轴旋转：\n";
			int temp = 0;
		
			while (cin >> temp)
			{
				if (bool tmp = (temp == 1 || temp == 2 || temp == 3) ? true : false)
				{
					break;
				}
				else
				{
					cout << "\n请输入正确的数字代表坐标轴，否则无法进行计算，请重新输入！" << endl;
					continue;
				}
			}
			

			cout << "\n请输入一个数代表按这个轴旋转多少度：\n";
			float degree = 0.0;
			cin >> degree;

			float radian = degree*kPi / 180; //声明一个临时量  把角度转换成弧度

			Vector3 v3(num1, num2, num3), v4;  //v4用来保存变换以后的向量
			Matrix3 m5;
			m5.setRotate(temp, radian);   //先计算旋转矩阵

			cout << "\n输出原向量为，";
			v3.print_v();

			v4 = v3*m5;  //向量和旋转矩阵相乘，得到结果，存入v4中

			cout << "输出向量通过3*3旋转矩阵转换新向量的结果，";
			v4.print_v();  //把结果打印出来


			break;
		}

		case 4:

		{
			cout << "\n请输入要缩放的一维向量的三个数：\n";
			float svx, svy, svz;
			cin >> svx >> svy >> svz;
			Vector3 v5(svx, svy, svz);

			cout << "\n请输入一维向量的三个数，表示要缩放原向量的倍数：\n";
			float vx, vy, vz;
			cin >> vx >> vy >> vz;
			Vector3 v6(vx, vy, vz);

			Matrix3 m6;
			m6.setUpScale(v6);  //计算缩放矩阵

			Vector3 v7;  //v7用来存储 原向量通过缩放矩阵计算后的 新向量
			v7 = v5*m6; //要缩放的一维向量跟 3*3旋转矩阵相乘， 得到一个新向量，也就是一个新的点
			v7.print_v();

			break;

		}
		case 5:
		{
			cout << "\n输入要投影的一维向量的三个数：\n";
			float nx, ny, nz;
			cin >> nx >> ny >> nz;

			Vector3 v8(nx, ny, nz);

			cout << "\n请输入 a 或 b，任意一个分别表示 是按标准轴投影还是任意平面投影!" << endl;
			cout << "\n请输入你的选择：";
			char userChoice;
			cin >> userChoice;
			switch (userChoice)
			{
			case 'a':
			{
				cout << "\n输入（0,1) (1,0) 分别表示投影到 x轴 或者 y轴" << endl
					<< ", 输入（0,0,1）、（0,1,0）、（1,0,0）表示投影到xy平面、xz平面、yz平面！" << endl;
				cout << "\n请输入三个数表示要投影到哪个平面或者坐标轴：\n";

				float vx, vy, vz;
				while (cin >> vx >> vy >> vz)
				{
					if ((vx == 0 && vy == 1 && vz == 0) || (vx == 1 && vy == 0 && vz == 0) || ((vx == 0 && vy == 0 && vz == 1)))
					{
						break;
					}
					else
					{
						cout << "\n请输入正确的需要投影的平面或轴，否则无法进行计算！" << endl;
						cout << "\n请重新输入：\n";
						continue;
					}
				}

				Vector3 n(vx, vy, vz), v9;  //n是需要投影的单位向量，要于投影平面相垂直。v9用来存储投影后的结果
				Matrix3 m7;
				m7.setUpProject(n);   //计算投影矩阵
				v9 = v8*m7;
				v9.print_v();
				break;
			}

			case 'b':
			{
				cout << "\n请输入三个数分别表示投影到任意平面的单位向量：\n";
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
				cout << "\n输入的序号不正确，请重新输入：\n";
				continue;
			}
			break;
		}
		case 6:
		{
			cout << "\n输入要镜像的一维向量的三个数：\n";
			float mx, my, mz;
			cin >> mx >> my >> mz;
			Vector3 v10(mx, my, mz),v11;

			cout << "\n请输入 1、2、3 任意一个数表示在 （x轴、 y轴、z轴）进行镜像：\n";
			int mirror = 0;
			while (cin >> mirror)
			{
				if (mirror == 1 || mirror == 2 || mirror == 3)
				{
					break;
				}
				else
				{
					cout << "\n输入的序号不正确，请重新输入，否则无法进行计算！" << endl;
					cout << "\n请重新输入 1、2、3 任意一个数表示在 （x轴、 y轴、z轴）进行镜像：\n";
					continue;
				}
			}

			Matrix3 m8;
			m8.setUpReflect(mirror); //计算镜像矩阵
			v11 = v10*m8;  //要镜像的一维向量与镜像矩阵相乘，得出一个新向量
			v11.print_v();
			break;
		
		}

		case 7:
		{
			cout << "\n输入要任意镜像的一维向量的三个数：\n";
			float mx, my, mz;
			cin >> mx >> my >> mz;
			Vector3 v12(mx, my, mz), v13;

			cout << "\n请输入沿任意轴进行镜像的三个数：\n";
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
			cout << "\n输入要进行切变的一维向量的三个数：\n";
			float sx, sy, sz;
			cin >> sx >> sy >> sz;
			Vector3 v14(sx, sy, sz), v15;

			cout << "\n请输入用哪个轴去切变（输入1、2、3 任意一个代表 x轴、y轴、z轴）：";
			int shear = 0;
			while (cin >> shear)
			{
				if (shear == 1 || shear == 2 || shear == 3)
				{
					break;
				}
				else
				{
					cout << "\n请输入正确的序号，否则无法进行计算，请重新输入：\n";
					continue;
				}
			}

			cout << "\n请输入另外两个轴要切变的倍数因子：\n";
			float ts = 0.0, tt = 0.0;
			cin >> ts >> tt;

			Matrix3 m10;
			m10.setUpShear(shear, ts, tt);  //计算切变矩阵
			v15 = v14*m10; // 然后要切变的向量跟切变矩阵相乘，得出切变后的位置，也就是新向量
			v15.print_v();
			break;
		}
		case 9:
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