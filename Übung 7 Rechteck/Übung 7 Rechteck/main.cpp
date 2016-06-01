#include "quadrat.h"
#include <iostream>

using namespace std;

int main()
{
	int laenge, breite;
	cout << "Enter width: ";
	cin >> breite;
	cout << endl;
	cout << "Enter length: ";
	cin >> laenge;
	cout << endl;
	
	Rechteck quad1(laenge, breite);
	quad1.isQuadrat();
	quad1.getDiagonal();

	system("PAUSE");

	return 0;
}