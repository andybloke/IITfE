#include "Deutsch.h"
#include "fraction.h"
#include <iostream>

using namespace std;

int main()
{
	unsigned int nenner;
	int zähler;
	Fraction frac1;
	cout << "\nInput z" << Umlaut::ä << "hler: ";
	cin >> zähler;
	cout << "Input nenner: ";
	cin >> nenner;
	Fraction frac2(zähler, nenner);
	nenner = frac1.getNenner();
	zähler = frac1.getZähler();
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