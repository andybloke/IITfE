#include "fraction.h"
#include "Deutsch.h"
#include <iostream>
#include <string>

using namespace std;

void getInput(int* p_z�hler, unsigned int* p_nenner)
{
	cout << "\nInput z" << Umlaut::� << "hler: ";
	cin >> *p_z�hler;
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
bool checkWholeNumber(int z�hler, unsigned int nenner)
{
	double intPart(0);
	double fracPartZ�hler(0.0);
	double fracPartNenner(0.0);
	fracPartZ�hler = modf(z�hler, &intPart); //extract whole number and decimal
	fracPartNenner = modf(nenner, &intPart);
	if ((fracPartZ�hler || fracPartNenner) != 0)
	{
		cout << "Nur ganzzahlige Werte erlaubt!";
		return false;
	}
	else
		return true;
}

Fraction::Fraction() : m_z�hler(1), m_nenner(1)
{
}

Fraction::Fraction(int z�hler, unsigned int nenner)
{
	m_nenner = nenner;
	m_z�hler = z�hler;
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
	m_z�hler = addZ�hler;
	m_nenner = addNenner;
}

void Fraction::sub(Fraction fracToSub)
{
	unsigned int subNenner = m_nenner * fracToSub.m_nenner;
	int subZ�hler = (m_z�hler * fracToSub.m_nenner) - (m_nenner * fracToSub.m_z�hler);
	m_z�hler = subZ�hler;
	m_nenner = subNenner;
}

void Fraction::mult(Fraction fracToMult)
{
	unsigned int multNenner = m_nenner * fracToMult.m_nenner;
	int multZ�hler = m_z�hler * fracToMult.m_z�hler;
	m_z�hler = multZ�hler;
	m_nenner = multNenner;
}

void Fraction::div(Fraction fracToDiv)
{
	unsigned int divNenner = m_nenner * fracToDiv.m_z�hler;
	int divZ�hler = m_z�hler * fracToDiv.m_nenner;
	cout << endl << endl;
	m_z�hler = divZ�hler;
	m_nenner = divNenner;
}

void Fraction::expand(int expNum)
{
	m_z�hler = m_z�hler * expNum;
	m_nenner = m_nenner * expNum;
}

Fraction Fraction::cancel()
{
	int lowest = ggt(m_z�hler, m_nenner);
	Fraction reduced(m_z�hler / lowest, m_nenner / lowest);
	return reduced;
}

void Fraction::print()
{
	string nen = to_string(m_nenner); //convert to string
	string z�h = to_string(m_z�hler);

	if (nen.size() > z�h.size()) //build middle line based on longest number
	{
		string middle(nen.size(), '-');
		cout << z�h << '\n' << middle << '\n' << nen << endl;
	}
	else
	{
		string middle(z�h.size(), '-');
		cout << z�h << '\n' << middle << '\n' << nen << endl;
	}	
}
