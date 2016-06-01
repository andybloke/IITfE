#include <iostream>

using namespace std;

class Point3d
{
private:
	int m_x;
	int m_y;
	int m_z;

public:
	void setValues(int x, int y, int z)
	{
		this->m_x = x;
		this->m_y = y;
		this->m_z = z;
	}

	void print()
	{
		cout << m_x << ' ' << m_y << ' ' << m_z;
	}
};



int main()
{
	Point3d point;
	point.setValues(1.0, 2.0, 3.0);

	point.print();
	system("PAUSE");
	return 0;
}