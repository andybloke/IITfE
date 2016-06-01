#include "quadrat.h"
#include <iostream>
#include <math.h>

using namespace std;

Rechteck::Rechteck(int laenge, int breite)
{
	cout << "Rechteck mit laenge " << laenge << " und breite " << breite << " wurde erstellt\n" << endl;
	this->m_laenge = laenge;
	this->m_breite = breite;
}

void Rechteck::setToOne()
{
	this->m_breite = 1;
	this->m_laenge = 1;
}

void Rechteck::isQuadrat()
{
	if (m_laenge == m_breite)
		cout << "Its a square!\n";
}

void Rechteck::getDiagonal()
{
	double diag = sqrt(pow(m_breite, 2) + pow(m_breite, 2));
	cout << "The length of the diagonal is: " << diag << endl;
}


