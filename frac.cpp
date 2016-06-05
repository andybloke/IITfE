#include <iostream>

using namespace std;

int LCD(int a, int b)
{
	int temp(0);
	while (b != 0)
	{
		temp = a % b;
		a = b;
		b = temp;
	}
	return a;
}

class Fraction
{
	private:
		int m_num;
		int m_den;
	public:
		Fraction() : m_num(1), m_den(1)
		{
		}
		Fraction(int den,  int num)
		{
			this->m_num=num;
			this->m_den=den;
		}
		Fraction reduce()
		{
			int lcd = LCD (m_num, m_den);
			Fraction red(m_den/ lcd, m_num / lcd);
			return red;
		}
		void print()
		{
			cout << endl << m_den << "/" << m_num;
		}
			
};



int main()
{
	int a(0), b(0);
	cin >> a;
	cout << endl;
	cin >> b;
	cout << "LCD is " << LCD(a,b);
	Fraction frac(a,b);
	Fraction red=frac.reduce();
	red.print();
	return 0;
}