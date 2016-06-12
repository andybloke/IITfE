#ifndef FAHRZEUG_H
#define FAHRZEUG_H

#include <string>
#include <iostream>
using namespace std;
class Fahrzeug
{
public:
	/*
	Standardkonstruktor. Erstellt ein Fahrzeug mit den Werten:name=Standarfahrzeug,
	anzahlInsassenMaximal = 3, anzahlInsassenAktuell = 1
	*/
	Fahrzeug();
	/*
	Erstellt ein Fahrzeug und �bernimmt die gegebenen Parameter als Memebervariablen
	*/
	Fahrzeug(string name, int anzahlInsassenMaximal, int anzahlInsassenAktuell);
	~Fahrzeug();
protected:
	string name; // Name des Fahrzeugs
	int anzahlInsassenMaximal; // Anzahl der Insassen, die Maximal in das Fahrzeugpassen
	int anzahlInsassenAktuell; // Anzahl der Insassen, die aktuell im Auto sind
public:
	/* Methode "int einsteigen(int anzahlEinsteiger);"
	erh�ht "anzahlInsassenAktuell" um "anzahlEinsteiger";
	gibt 0 zur�ck, wenn genug Platz f�r die einsteigenden Insassen ist.
	Wenn die "anzahlEinsteiger" aufgrund des maximalen Platzes im Fahrzeug
	nicht mehr in das Fahrzeug passt, gibt die Methode "einsteigen" -1 zur�ck,
	schreibt auf die Konsole "Einsteigen nicht m�glich, da zu wenig Platz im
	Fahrzeug!"
	und ver�ndert die aktuelle Anzahl der Insassen des Fahrzeugs nicht.
	*/
	int einsteigen(int anzahlEinsteiger);
	/* Methode "int aussteigen(int anzahlAussteiger);"
	verringert "anzahlInsassenAktuell" um "anzahlAussteiger";
	gibt 0 zur�ck, wenn mindestens so viele Insassen im Fahrzeug sind, wie
	aussteigen sollen.
	Diese Methode verhindert damit, dass mehr Insassen aussteigen, als tats�chlich
	im Fahrzeug sind.
	Somit ist gew�hrleistet, dass "anzahlInsassenAktuell" gr��er oder gleich 0 ist.
	Wenn weniger Insassen als "anzahlAussteiger" im Fahrzeug sind, gibt die Methode
	"aussteigen" -1 zur�ck,
	schreibt auf die Konsole "So viele Insassen sind nicht im Auto!"
	und ver�ndert die aktuelle Anzahl der Insassen des Fahrzeugs nicht.
	*/
	int aussteigen(int anzahlAussteiger);
	/*
	Diese Methode gibt die Werte ALLER der Membervariablen in einer verst�ndlichen
	Form auf der Konsole aus.
	Z.B.: "Die aktuelle Anzahl der Insassen betr�gt: <hier steht der Wert von
	anzahlInsassenAktuell>"
	*/
	void printStatus();
};
#endif // !FAHRZEUG_H
