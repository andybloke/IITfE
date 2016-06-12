#include <string>
#include <iostream>
#include "fahrzeug.h"

using namespace std;

Fahrzeug::Fahrzeug() : name("Standarfahrzeug"), anzahlInsassenMaximal(3), anzahlInsassenAktuell(1)
{
	//intialised with a list.
}

Fahrzeug::Fahrzeug(string name, int anzahlInsassenMaximal, int anzahlInsassenAktuell)
{
	cout << "Fahrzeug " << name << " w\x81rde erstellt\n";
	this->name = name;
	this->anzahlInsassenMaximal = anzahlInsassenMaximal;
	this->anzahlInsassenAktuell = anzahlInsassenAktuell;
}

Fahrzeug::~Fahrzeug()
{
	cout << "Fahrzeug " << name << " w\x81rde gel\x94scht";
}

int Fahrzeug::einsteigen(int anzahlEinsteiger)
{
	if (this->anzahlInsassenMaximal <= anzahlEinsteiger + this->anzahlInsassenAktuell)
	{
		this->anzahlInsassenAktuell = this->anzahlInsassenAktuell + anzahlEinsteiger;
		return 0;
	}
	else
	{
		cout << "\nEinsteigen nicht m\x94glich, da zu wenig Platz im Fahrzeug!\n";
		return -1;
	}
}

int Fahrzeug::aussteigen(int anzahlAussteiger)
{
	if (anzahlAussteiger <= this->anzahlInsassenAktuell)
	{
		this->anzahlInsassenAktuell -= anzahlAussteiger;
		return 0;
	}
	else
	{
		cout << "\nSo viele Insassen sind nicht im Auto!\n";
		return -1;
	}

}

void Fahrzeug::printStatus()
{
	cout << "\nF\x81r das Fahrzeug: " << this->name;
	cout << "\nDie aktuelle Anzahl der Insassen betr\x84gt: " << this->anzahlInsassenAktuell;
	cout << "\nDie maximale Anzahl der Insassen betr\x84gt: " << this->anzahlInsassenMaximal << endl;
}
