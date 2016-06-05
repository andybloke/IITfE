#include "Deutsch.h"
#include "fraction.h"
#include <iostream>

using namespace std;

int main()
{
	unsigned int nenner;
	int z�hler;
	Fraction frac1;
	cout << "\nInput z" << Umlaut::� << "hler: ";
	cin >> z�hler;
	cout << "Input nenner: ";
	cin >> nenner;
	Fraction frac2(z�hler, nenner);
	nenner = frac1.getNenner();
	z�hler = frac1.getZ�hler();
	cout << "Frac1 = \n";
	frac1.print();
	cout << endl;
	cout << "Frac2 = \n";
	frac2.print();
	cout << endl;
	frac1.add(frac2);
	cout << endl;
	frac1.print();
	cout << endl;
	frac1.sub(frac2);
	cout << endl;
	system("PAUSE");
	return 0;
}