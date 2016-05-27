#include <iostream>
#include <string>

using namespace std;

double getInput() //Nehmme input von Benutzer
{
	cout << "Bitte gebe Sie eine ganze Zahl ein:" << '\n' << "-->";
	double input;
	cin >> input;
	return input;
}

bool test(double longest) //test f�r positiv ganze Zahl
{
	int test = longest; //typecast double >> int

	if ((test != longest) || (cin.fail()) || (longest <= 0))
	{
		system("PAUSE");
		return true;
	}
	else
		return false;
}

void printZerosToPoint(double longest, int max) //Druck 0 bis L�nge=longest
{
	if (longest == 0)
		return;
	else
	{
        string zeros((max - longest), '0');
		cout << zeros << '\n';
		--longest;
		printZerosToPoint(longest, max);
	}   
}

void printZerosToOne(int max) ////Druck 0 von L�nge=(longest-1) bis 1
{
	if (max == 0)
		return;
	else
	{
		string zeros(max, '0');
		cout << zeros << '\n';
		--max;
		printZerosToOne(max);
	}
}

int main()
{
	double longest = getInput();

	if (test(longest))
	{
		return -1;
	}

	int max = longest + 1; //Stelle Referenzpunkt max f�r rekusiv Druck
	printZerosToPoint(longest, max);
	
    max = longest - 1; //Stelle Referenzpunkt max f�r rekusiv Druck
	printZerosToOne(max);

	system("PAUSE");
	return 0;
}
