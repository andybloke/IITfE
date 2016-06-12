#ifndef AUTO_H
#define AUTO_H
#include "Fahrzeug.h"
class Auto : public Fahrzeug
{
public:
	/*
	Standardkonstruktor. Erstellt ein Auto mit den Werten: tankinhaltMaximal = 50,
	verbrauch = 10, tankinhaltAktuell = 20,
	gefahreneKilometer = 0; kraftstoffArt = "Diesel"; anzahlInsassenAktuell=1,
	anzahlInsassenMaximal=5;
	*/
	Auto();
	/*
	Erstellt ein Auto und übernimmt die gegebenen Parameter als Memebervariablen;
	Der Name des Fahrzeugs ist: "Auto".
	*/
	Auto(double tankinhaltMaximal, double tankinhaltAktuell, double verbrauch, double gefahreneKilometer, string kraftstoffArt, int anzahlInsassenAktuell, int anzahlInsassenMaximal);
	/* Zerstört ein Objekt des Typs Auto*/
	~Auto();
private:
	double tankinhaltMaximal; // maximaler Tankinhalt in Liter
	double tankinhaltAktuell; // aktueller Tankinhalt in Liter
	double verbrauch; // Verbrauch in Liter pro 100 Kilometer
	double gefahreneKilometer; // Anzahl Kilometer, die das Auto bisher zurückgelegt hat
	string kraftstoffArt;
	/*
	Hat entweder den Wert "Diesel" oder "Benzin". Wenn der Nutzer
	einen anderen Wert als "Diesel" und "Benzin" eingibt, wird als
	Kraftstoffart "Benzin" eingetragen. Dies muss in allen Konstruktoren
	berücksichtigt werden.
	*/
public:
	/*
	Lässt das Auto die "strecke" fahren. Dadurch reduziert sich der aktuelle
	Tankinhalt entsprechend des Verbrauchs
	und die gefahrenen Kilometer erhöhen sich um "strecke". Bevor gefahren wird,
	wird geprüft,
	ob der aktuelle Tankinhalt zum Zurücklegen der Strecke reicht.
	ACHTUNG: Pro Insasse, der Aktuell im Auto ist, erhöht sich der in der
	Membervariable "verbrauch" gespeicherte Verbrauch
	um 0.66 Liter pro 100 km. Beispiel: verbrauch = 3;
	aktuelleAnzahlInsassen=4; tatsächlicher Verbrauch, der beim
	Fahren berücksichtigt werden muss: 3+4*0.66= 5.64 Liter pro 100km
	Wenn der Tankinhalt nicht reicht um
	die "strecke" zurückzulegen, werden weder der aktuelle Tankinhalt noch die
	gefahrenen Kilometer verändert.
	Stattdessen gibt die Methode -1 zurück und schreibt zuvor auf die Konsole: "Zu
	wenig Kraftstoff!".
	*/
	int fahren(double strecke);
	/*
	Füllt den aktuellen Tankinhalt des Autos auf den maximalen Tankinhalt und gibt
	die getankte Kraftstoffmenge zurück.
	*/
	double volltanken();
	/*
	Diese Methode gibt die Werte ALLER Membervariablen (auch die vererbten von der
	Klasse Fahrzeug!)
	in einer verständlichen Form auf der Konsole aus.
	Z.B.: "Der aktuelle Füllstand des Tanks beträgt: <hier steht der Wert von
	tankinhaltAktuell>"
	*/
	void printStatus();
};
#endif
