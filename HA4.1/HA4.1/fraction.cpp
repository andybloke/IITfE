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

Fraction::Fraction() : m_zähler(1), m_nenner(2)
{
}

Fraction::Fraction(int zähler, unsigned int nenner)
{
	this->m_nenner = nenner;
	this->m_zähler = zähler;
}

int Fraction::getZähler()
{
	return m_zähler;
}

unsigned int Fraction::getNenner()
{
	return m_nenner;
}

void Fraction::add(Fraction fracToAdd)
{
	unsigned int addNenner = m_nenner * fracToAdd.m_nenner;
	int addZähler = (m_zähler * fracToAdd.m_nenner) + (m_nenner * fracToAdd.m_zähler);
	Fraction result(addZähler, addNenner);
	result = result.reduce();
	result.print();
	cout << endl << endl;
	this->m_zähler = result.m_zähler;
	this->m_nenner = result.m_nenner;
}

void Fraction::sub(Fraction fracToSub)
{
	unsigned int subNenner = m_nenner * fracToSub.m_nenner;
	int subZähler = (m_zähler * fracToSub.m_nenner) - (m_nenner * fracToSub.m_zähler);
	Fraction result(subZähler, subNenner);
	result = result.reduce();
	result.print();
	cout << endl << endl;
	this->m_zähler = result.m_zähler;
	this->m_nenner = result.m_nenner;
}

Fraction Fraction::reduce()
{
	int lowest = lcd(m_zähler, m_nenner);
	Fraction red(m_zähler / lowest, m_nenner / lowest);
	return red;
}

void Fraction::print()
{
	string nen = to_string(m_nenner); //convert to string
	string zäh = to_string(m_zähler);

	if (nen.size() > zäh.size()) //build middle line based on longest number
	{
		string middle(nen.size(), '-');
		cout << zäh << '\n' << middle << '\n' << nen;
	}
	else
	{
		string middle(zäh.size(), '-');
		cout << zäh << '\n' << middle << '\n' << nen;
	}	
}
