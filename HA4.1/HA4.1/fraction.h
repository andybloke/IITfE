#ifndef FRACTION_H
#define FRACTION_H

class Fraction {
private:
	unsigned int m_nenner;
	int m_zähler;
public:
	Fraction();
	Fraction(int zähler, unsigned int nenner);
	int getZähler();
	unsigned int getNenner();
	Fraction reduce();
	void add(Fraction fracToAdd);
	void sub(Fraction fracToSub);
	void print();
};

#endif
