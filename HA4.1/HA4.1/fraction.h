#ifndef FRACTION_H
#define FRACTION_H

void getInput(int* p_zähler, unsigned int* p_nenner);
bool checkWholeNumber(int zähler, unsigned int nenner);

class Fraction {
private:
	unsigned int m_nenner;
	int m_zähler;
public:
	Fraction();
	Fraction(int zähler, unsigned int nenner);
	int getZähler();
	unsigned int getNenner();
	Fraction cancel();
	void add(Fraction fracToAdd);
	void sub(Fraction fracToSub);
	void mult(Fraction fracToMult);
	void div(Fraction fracToDiv);
	void expand(int expNum);
	void print();
};

#endif
