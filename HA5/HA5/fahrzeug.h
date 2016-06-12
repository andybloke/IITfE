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
	Erstellt ein Fahrzeug und übernimmt die gegebenen Parameter als Memebervariablen
	*/
	Fahrzeug(string name, int anzahlInsassenMaximal, int anzahlInsassenAktuell);
	~Fahrzeug();
protected:
	string name; // Name des Fahrzeugs
	int anzahlInsassenMaximal; // Anzahl der Insassen, die Maximal in das Fahrzeugpassen
	int anzahlInsassenAktuell; // Anzahl der Insassen, die aktuell im Auto sind
public:
	/* Methode "int einsteigen(int anzahlEinsteiger);"
	erhöht "anzahlInsassenAktuell" um "anzahlEinsteiger";
	gibt 0 zurück, wenn genug Platz für die einsteigenden Insassen ist.
	Wenn die "anzahlEinsteiger" aufgrund des maximalen Platzes im Fahrzeug
	nicht mehr in das Fahrzeug passt, gibt die Methode "einsteigen" -1 zurück,
	schreibt auf die Konsole "Einsteigen nicht möglich, da zu wenig Platz im
	Fahrzeug!"
	und verändert die aktuelle Anzahl der Insassen des Fahrzeugs nicht.
	*/
	int einsteigen(int anzahlEinsteiger);
	/* Methode "int aussteigen(int anzahlAussteiger);"
	verringert "anzahlInsassenAktuell" um "anzahlAussteiger";
	gibt 0 zurück, wenn mindestens so viele Insassen im Fahrzeug sind, wie
	aussteigen sollen.
	Diese Methode verhindert damit, dass mehr Insassen aussteigen, als tatsächlich
	im Fahrzeug sind.
	Somit ist gewährleistet, dass "anzahlInsassenAktuell" größer oder gleich 0 ist.
	Wenn weniger Insassen als "anzahlAussteiger" im Fahrzeug sind, gibt die Methode
	"aussteigen" -1 zurück,
	schreibt auf die Konsole "So viele Insassen sind nicht im Auto!"
	und verändert die aktuelle Anzahl der Insassen des Fahrzeugs nicht.
	*/
	int aussteigen(int anzahlAussteiger);
	/*
	Diese Methode gibt die Werte ALLER der Membervariablen in einer verständlichen
	Form auf der Konsole aus.
	Z.B.: "Die aktuelle Anzahl der Insassen beträgt: <hier steht der Wert von
	anzahlInsassenAktuell>"
	*/
	void printStatus();
};
#endif // !FAHRZEUG_H
