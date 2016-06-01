#include "quadrat.h"
#include <iostream>

using namespace std;

int main()
{
	int laenge, breite; //initialise and get the length and width
	cout << "Enter width: ";
	cin >> breite;
	cout << endl;
	cout << "Enter length: ";
	cin >> laenge;
	cout << endl;
	
	Rechteck quad1;//make object quad1
	quad1.setSize(laenge, breite); //set length & width given
	quad1.isQuadrat();
	quad1.getDiagonal();

	system("PAUSE");

	return 0;
}