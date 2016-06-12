#include "Auto.h"
#include "fahrzeug.h"

Auto::Auto() : tankinhaltMaximal(50), verbrauch(10), tankinhaltAktuell(20), gefahreneKilometer(0), kraftstoffArt("Diesel"), Fahrzeug("Standard Auto", 5, 1)
{
	//list initialised
}

Auto::Auto(double tankinhaltMaximal, double tankinhaltAktuell, double verbrauch, double gefahreneKilometer, string kraftstoffArt, int anzahlInsassenAktuell, int anzahlInsassenMaximal)
	: tankinhaltMaximal(tankinhaltMaximal), tankinhaltAktuell(tankinhaltAktuell), verbrauch(verbrauch), gefahreneKilometer(gefahreneKilometer), Fahrzeug("Auto", anzahlInsassenMaximal, anzahlInsassenAktuell)
{
	if (kraftstoffArt != "Diesel" || "Benzin")
		this->kraftstoffArt = "Diesel";
	else
		this->kraftstoffArt = kraftstoffArt;
}

Auto::~Auto()
{
	Fahrzeug::~Fahrzeug();
}

int Auto::fahren(double strecke)
{
	double aktuelleVerbrauch = verbrauch + anzahlInsassenAktuell * 0.66;
	double spritStrecke = strecke * aktuelleVerbrauch;
	if (spritStrecke > tankinhaltAktuell)
	{
		cout << "\nZu wenig Kraftstoff!";
		return -1;
	}
	else
	{
		tankinhaltAktuell -= spritStrecke;
		gefahreneKilometer += strecke;
		return 0;
	}
}

double Auto::volltanken()
{
	double getankt = tankinhaltMaximal - tankinhaltAktuell;
	tankinhaltAktuell = tankinhaltMaximal;
	return getankt;
}

void Auto::printStatus()
{
	Fahrzeug::printStatus();
	cout << "\nDer aktuelle F\x81llstand des Tanks in Liter betr\x84gt: " << tankinhaltAktuell;
	cout << "\nDer maximalle F\x81llstand des Tanks in Liter betr\x84gt: " << tankinhaltMaximal;
	cout << "\nDer Verbrauch in Liter pro 100 Kilometer betr\x84gt: " << verbrauch;
	cout << "\nDer Kilometer stand betr\x84gt: " << gefahreneKilometer;
	cout << "\nDer Kraftstoff ist: " << kraftstoffArt << endl;
}


