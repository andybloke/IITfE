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
	Erstellt ein Auto und �bernimmt die gegebenen Parameter als Memebervariablen;
	Der Name des Fahrzeugs ist: "Auto".
	*/
	Auto(double tankinhaltMaximal, double tankinhaltAktuell, double verbrauch, double gefahreneKilometer, string kraftstoffArt, int anzahlInsassenAktuell, int anzahlInsassenMaximal);
	/* Zerst�rt ein Objekt des Typs Auto*/
	~Auto();
private:
	double tankinhaltMaximal; // maximaler Tankinhalt in Liter
	double tankinhaltAktuell; // aktueller Tankinhalt in Liter
	double verbrauch; // Verbrauch in Liter pro 100 Kilometer
	double gefahreneKilometer; // Anzahl Kilometer, die das Auto bisher zur�ckgelegt hat
	string kraftstoffArt;
	/*
	Hat entweder den Wert "Diesel" oder "Benzin". Wenn der Nutzer
	einen anderen Wert als "Diesel" und "Benzin" eingibt, wird als
	Kraftstoffart "Benzin" eingetragen. Dies muss in allen Konstruktoren
	ber�cksichtigt werden.
	*/
public:
	/*
	L�sst das Auto die "strecke" fahren. Dadurch reduziert sich der aktuelle
	Tankinhalt entsprechend des Verbrauchs
	und die gefahrenen Kilometer erh�hen sich um "strecke". Bevor gefahren wird,
	wird gepr�ft,
	ob der aktuelle Tankinhalt zum Zur�cklegen der Strecke reicht.
	ACHTUNG: Pro Insasse, der Aktuell im Auto ist, erh�ht sich der in der
	Membervariable "verbrauch" gespeicherte Verbrauch
	um 0.66 Liter pro 100 km. Beispiel: verbrauch = 3;
	aktuelleAnzahlInsassen=4; tats�chlicher Verbrauch, der beim
	Fahren ber�cksichtigt werden muss: 3+4*0.66= 5.64 Liter pro 100km
	Wenn der Tankinhalt nicht reicht um
	die "strecke" zur�ckzulegen, werden weder der aktuelle Tankinhalt noch die
	gefahrenen Kilometer ver�ndert.
	Stattdessen gibt die Methode -1 zur�ck und schreibt zuvor auf die Konsole: "Zu
	wenig Kraftstoff!".
	*/
	int fahren(double strecke);
	/*
	F�llt den aktuellen Tankinhalt des Autos auf den maximalen Tankinhalt und gibt
	die getankte Kraftstoffmenge zur�ck.
	*/
	double volltanken();
	/*
	Diese Methode gibt die Werte ALLER Membervariablen (auch die vererbten von der
	Klasse Fahrzeug!)
	in einer verst�ndlichen Form auf der Konsole aus.
	Z.B.: "Der aktuelle F�llstand des Tanks betr�gt: <hier steht der Wert von
	tankinhaltAktuell>"
	*/
	void printStatus();
};
#endif
