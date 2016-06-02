#include <iostream>
#include <math.h>

using namespace std;

const int KM_TO_DEG = 111;
const int DEG_TO_MIN = 60;
const int MIN_TO_SEC = 60;

void convertToLongitude(int* p_deg, int* p_min, int* p_sec, double distance)
{
	double temp = distance / KM_TO_DEG; //convert to degrees
	double intPart(0);
	double fracPart(0.0);
	fracPart = modf (temp, &intPart); //extract whole number and decimal
	*p_deg = intPart; //place whole number in p_deg
	temp = fracPart * DEG_TO_MIN; //convert to minutes
	fracPart = modf(temp, &intPart); //extract whole number and decimal
	*p_min = intPart; //place whole number in p_min
	temp = fracPart * MIN_TO_SEC; //convert to seconds
	fracPart = modf(temp, &intPart); //extract whole number and decimal
	*p_sec = intPart; //place whole number in p_sec
}

int main()
{
	cout << "Bitte geben Sie die Distance vom Aequator in km ein: ";
	double distance(0.0);
	cin >> distance;
	int deg(0), min(0), sec(0);
	convertToLongitude(&deg, &min, &sec, distance);
	cout << "\n \n" << distance << "km in Breitengrad ist: " << deg << " degrees " << min << " minuten " << sec << " sekunden. \n";
	system("PAUSE");
	return 0;
}