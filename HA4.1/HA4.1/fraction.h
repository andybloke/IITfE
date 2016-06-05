#ifndef FRACTION_H
#define FRACTION_H

void getInput(int* p_z�hler, unsigned int* p_nenner);
bool checkWholeNumber(int z�hler, unsigned int nenner);

class Fraction {
private:
	unsigned int m_nenner;
	int m_z�hler;
public:
	Fraction();
	Fraction(int z�hler, unsigned int nenner);
	int getZ�hler();
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
