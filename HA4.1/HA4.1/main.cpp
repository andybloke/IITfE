#include "Deutsch.h"
#include "fraction.h"
#include <iostream>

using namespace std;

int main()
{
	unsigned int nenner;
	int zähler;
	Fraction frac1; //test default konstruktor 

	getInput(&zähler, &nenner);
	if (checkWholeNumber(zähler, nenner) == false) //prüfe auf ganzzahl
		return -1;

	Fraction frac2(zähler, nenner); //test zweiter konstruktor

	int getnenner = frac2.getNenner(); //test get
	int getzähler = frac2.getZähler();

	cout << "Die eingegebe Bruch lautet: " << getzähler << "/" << getnenner << endl;

	cout << "Frac1 + Frac2 = \n\n";
	frac1.add(frac2);
	frac1.print();

	cout << "Und gekurzt = \n \n";
	frac1 = frac1.cancel();
	frac1.print();

	system("PAUSE");

	cout << endl << endl << "Und das minus Frac2 = \n\n";
	frac1.sub(frac2);
	frac1.print();

	cout << "Und gekurzt = \n \n";
	frac1 = frac1.cancel();
	frac1.print();

	system("PAUSE");

	cout << endl << endl << "Und das mal Frac2 = \n\n";
	frac1.mult(frac2);
	frac1.print();

	cout << "Und gekurzt = \n \n";
	frac1 = frac1.cancel();
	frac1.print();

	system("PAUSE");

	cout << endl << endl << "Und das dividiert durch Frac2 = \n\n";
	frac1.div(frac2);
	frac1.print();

	cout << "Und gekurzt = \n \n";
	frac1 = frac1.cancel();
	frac1.print();
	
	system("PAUSE");

	cout << "Geben Sie bitte eine Zahl, um zu erweitern: ";
	int expNum;
	cin >> expNum;
	frac1.expand(expNum);
	cout << "\nDas gibt: \n";
	frac1.print();

	system("PAUSE");

	return 0;
}