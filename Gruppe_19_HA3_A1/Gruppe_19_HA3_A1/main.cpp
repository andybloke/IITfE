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

bool test(double longest) //test für positiv ganze Zahl
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

void printZeros(double longest) 
{
	for (int i = 1; i <= longest; ++i) //Druck 0 bis spitze
	{
		string zeros(i, '0');
		cout << zeros << '\n';
	}

	for (int i = longest - 1; i > 0; --i) //Druck 0 von Spitze 
	{
		string zeros(i, '0');
		cout << zeros << '\n';
	}
}

int main()
{
	double longest = getInput();

	if (test(longest))
	{
		return -1;
	}

	printZeros(longest);
	
	system("PAUSE");
	return 0;
}
