#include "fraction.h"
#include <iostream>
#include <string>

using namespace std;

int lcd(int a, int b)
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

Fraction::Fraction() : m_z�hler(1), m_nenner(2)
{
}

Fraction::Fraction(int z�hler, unsigned int nenner)
{
	this->m_nenner = nenner;
	this->m_z�hler = z�hler;
}

int Fraction::getZ�hler()
{
	return m_z�hler;
}

unsigned int Fraction::getNenner()
{
	return m_nenner;
}

void Fraction::add(Fraction fracToAdd)
{
	unsigned int addNenner = m_nenner * fracToAdd.m_nenner;
	int addZ�hler = (m_z�hler * fracToAdd.m_nenner) + (m_nenner * fracToAdd.m_z�hler);
	Fraction result(addZ�hler, addNenner);
	result = result.reduce();
	result.print();
	cout << endl << endl;
	this->m_z�hler = result.m_z�hler;
	this->m_nenner = result.m_nenner;
}

void Fraction::sub(Fraction fracToSub)
{
	unsigned int subNenner = m_nenner * fracToSub.m_nenner;
	int subZ�hler = (m_z�hler * fracToSub.m_nenner) - (m_nenner * fracToSub.m_z�hler);
	Fraction result(subZ�hler, subNenner);
	result = result.reduce();
	result.print();
	cout << endl << endl;
	this->m_z�hler = result.m_z�hler;
	this->m_nenner = result.m_nenner;
}

Fraction Fraction::reduce()
{
	int lowest = lcd(m_z�hler, m_nenner);
	Fraction red(m_z�hler / lowest, m_nenner / lowest);
	return red;
}

void Fraction::print()
{
	string nen = to_string(m_nenner); //convert to string
	string z�h = to_string(m_z�hler);

	if (nen.size() > z�h.size()) //build middle line based on longest number
	{
		string middle(nen.size(), '-');
		cout << z�h << '\n' << middle << '\n' << nen;
	}
	else
	{
		string middle(z�h.size(), '-');
		cout << z�h << '\n' << middle << '\n' << nen;
	}	
}
