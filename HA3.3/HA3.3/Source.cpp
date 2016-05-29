#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

bool testInputRange(int input)
{
	if (input < 1 || input > 49)
		return false;
	else
		return true;
}

bool checkForCopy(vector<int> userNumbers)
{
	for (int i = 0; i < userNumbers.size(); ++i)
	{
		int control = userNumbers[i];
		int count = 0;
		for (int x = 0; x < userNumbers.size(); ++x)
		{
			if (control == userNumbers[x])
				count++;
			else
				continue;
		}
		if (count > 1)
			return true;
		else
			continue;
	}

	return false;
}

vector<int> getInput()
{
	const int MAX_NUM = 6;
	vector<int> userNumbers;
	int input;
	for (int i = 0; i < MAX_NUM; ++i)
	{
		cout << "Bitte geben Sie Ihre " << i + 1 << "te Zahl ein." << '\n' << "-->";
		cin >> input;
		cout << '\n';
		while (testInputRange(input) == false)
		{
			cout << "Bitte geben Sie eine Zahl zwichen 1 und 49 ein" << '\n' << "-->";
			cin.clear();
			cin >> input;
			cout << '\n';
		} 
				
		userNumbers.push_back(input);
	}
	return userNumbers;
}

int main()
{
	vector<int> userNumbers = getInput();
	if (checkForCopy(userNumbers) == true)
	{
		cout << "FEHLER: Jeder Zahl darf nur ein Mal eingegeben sein" << '\n';
		system("PAUSE");
		return -1;
	}
}
