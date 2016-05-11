#include <iostream>
#include <math.h>

using namespace std;

double umrechnungBogenmass(double steigungswinkel);
double berechneWegNachOben(double wegGesamt, double steigungswinkelInRad);
double berechneWegParallel(double wegGesamt, double steigungswinkelInRad);
double berechneGeschwindigkeitParallelZuBoden(double wegParallelZuBoden, double flugzeitInMinuten);


int main()
{
	double wegGesamt, steigungswinkel, flugzeitInMinuten = 1.0;

	cout << "Bitte zurueckzulegenden Gesamtweg angaben in meter:  \n";
	cin >> wegGesamt;
	cout << "Bitte Steigungswinkel in Grad angaben in meter:  \n";
	cin >> steigungswinkel;

	double steigungswinkelInRad = umrechnungBogenmass(steigungswinkel);

	double wegNachoben = berechneWegNachOben(wegGesamt, steigungswinkelInRad);
	double wegParallelZuBoden = berechneWegParallel(wegGesamt, steigungswinkelInRad);
	double geschwindigkeit = berechneGeschwindigkeitParallelZuBoden(wegParallelZuBoden, flugzeitInMinuten);
	
	cout << "Weg nach oben: " << wegNachoben << '\n';
	cout << "Weg Parallel: " << wegParallelZuBoden << '\n';
	cout << "Geschwindigkeit: " << geschwindigkeit << "m/s \n";
	cin.ignore();
	cin.get();
	return 0;

}

double umrechnungBogenmass(double steigungswinkel)
{
	double steigungswinkelInRad;
	const double PI = 3.14159;
	steigungswinkelInRad = steigungswinkel *  (PI / 180);
	return steigungswinkelInRad;
}

double berechneWegNachOben(double wegGesamt, double steigungswinkelInRad)
{
	double Oben;
	Oben = sin(steigungswinkelInRad) * wegGesamt;
	return Oben;
}

double berechneWegParallel(double wegGesamt, double steigungswinkelInRad)
{
	double Paralell;
	Paralell = cos(steigungswinkelInRad) * wegGesamt;
	return Paralell;
}

double berechneGeschwindigkeitParallelZuBoden(double wegParallelZuBoden, double flugzeitInMinuten)
{
	double speed;
	speed = wegParallelZuBoden * (flugzeitInMinuten * 60);
	return speed;
}

