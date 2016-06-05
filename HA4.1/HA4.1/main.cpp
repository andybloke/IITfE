#include "Deutsch.h"
#include "fraction.h"
#include <iostream>

using namespace std;

int main()
{
	unsigned int nenner;
	int z�hler;
	Fraction frac1; //test default konstruktor 

	getInput(&z�hler, &nenner);
	if (checkWholeNumber(z�hler, nenner) == false) //pr�fe auf ganzzahl
		return -1;

	Fraction frac2(z�hler, nenner); //test zweiter konstruktor

	int getnenner = frac2.getNenner(); //test get
	int getz�hler = frac2.getZ�hler();

	cout << "Die eingegebe Bruch lautet: " << getz�hler << "/" << getnenner << endl;

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