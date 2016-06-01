#include "quadrat.h"
#include <iostream>
#include <math.h>

using namespace std;

Rechteck::Rechteck() //default constructor
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

void Rechteck::setSize(int laenge, int breite)
{
	this->m_breite = breite;
	this->m_laenge = laenge;
}
