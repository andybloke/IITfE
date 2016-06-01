#ifndef QUADRAT_H
#define QUADRAT_H

#include <iostream>

class Rechteck {
private:
	int m_laenge;
	int m_breite;

public:
	Rechteck(int laenge, int breite);
	void setToOne();
	void isQuadrat();
	void getDiagonal();
};


#endif
