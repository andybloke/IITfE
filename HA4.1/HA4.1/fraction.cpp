#include "fraction.h"
#include "Deutsch.h"
#include <iostream>
#include <string>

using namespace std;

void getInput(int* p_zähler, unsigned int* p_nenner)
{
	cout << "\nInput z" << Umlaut::ä << "hler: ";
	cin >> *p_zähler;
	while (true)
	{
		cout << "\nInput nenner: ";
		cin >> *p_nenner;
		if (*p_nenner == 0)
		{
			cout << "Teilen durch Null ist nicht erlaubt. Bitte probieren noch Mal.\n";
			continue;
		}
		else
			break;
	}


}
int ggt(int a, int b)
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
bool checkWholeNumber(int zähler, unsigned int nenner)
{
	double intPart(0);
	double fracPartZähler(0.0);
	double fracPartNenner(0.0);
	fracPartZähler = modf(zähler, &intPart); //extract whole number and decimal
	fracPartNenner = modf(nenner, &intPart);
	if ((fracPartZähler || fracPartNenner) != 0)
	{
		cout << "Nur ganzzahlige Werte erlaubt!";
		return false;
	}
	else
		return true;
}

Fraction::Fraction() : m_zähler(1), m_nenner(1)
{
}

Fraction::Fraction(int zähler, unsigned int nenner)
{
	m_nenner = nenner;
	m_zähler = zähler;
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
	m_zähler = addZähler;
	m_nenner = addNenner;
}

void Fraction::sub(Fraction fracToSub)
{
	unsigned int subNenner = m_nenner * fracToSub.m_nenner;
	int subZähler = (m_zähler * fracToSub.m_nenner) - (m_nenner * fracToSub.m_zähler);
	m_zähler = subZähler;
	m_nenner = subNenner;
}

void Fraction::mult(Fraction fracToMult)
{
	unsigned int multNenner = m_nenner * fracToMult.m_nenner;
	int multZähler = m_zähler * fracToMult.m_zähler;
	m_zähler = multZähler;
	m_nenner = multNenner;
}

void Fraction::div(Fraction fracToDiv)
{
	unsigned int divNenner = m_nenner * fracToDiv.m_zähler;
	int divZähler = m_zähler * fracToDiv.m_nenner;
	cout << endl << endl;
	m_zähler = divZähler;
	m_nenner = divNenner;
}

void Fraction::expand(int expNum)
{
	m_zähler = m_zähler * expNum;
	m_nenner = m_nenner * expNum;
}

Fraction Fraction::cancel()
{
	int lowest = ggt(m_zähler, m_nenner);
	Fraction reduced(m_zähler / lowest, m_nenner / lowest);
	return reduced;
}

void Fraction::print()
{
	string nen = to_string(m_nenner); //convert to string
	string zäh = to_string(m_zähler);

	if (nen.size() > zäh.size()) //build middle line based on longest number
	{
		string middle(nen.size(), '-');
		cout << zäh << '\n' << middle << '\n' << nen << endl;
	}
	else
	{
		string middle(zäh.size(), '-');
		cout << zäh << '\n' << middle << '\n' << nen << endl;
	}	
}
