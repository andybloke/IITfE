#ifndef FRACTION_H
#define FRACTION_H

class Fraction {
private:
	unsigned int m_nenner;
	int m_z�hler;
public:
	Fraction();
	Fraction(int z�hler, unsigned int nenner);
	int getZ�hler();
	unsigned int getNenner();
	Fraction reduce();
	void add(Fraction fracToAdd);
	void sub(Fraction fracToSub);
	void print();
};

#endif
