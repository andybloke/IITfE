#ifndef QUADRAT_H
#define QUADRAT_H

#include <iostream>

class Rechteck
{
private: //define member variables
	int m_laenge;
	int m_breite;

public: //define member functions
	Rechteck();
	void setSize(int laenge, int breite);
	void setToOne();
	void isQuadrat();
	void getDiagonal();
};


#endif
