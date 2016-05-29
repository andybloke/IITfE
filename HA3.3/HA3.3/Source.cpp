#include <iostream>
#include <math.h>
#include <vector>
#include <time.h>
#include <conio.h>

using namespace std;

bool testInputRange(int input)
{
	if (input < 1 || input > 49)
		return false;
	else
		return true;
}

vector<int> getInput(const int MAX_NUM)
{
	vector<int> userNumbers;
	int input;
	for (int i = 0; i < MAX_NUM; ++i)
	{
		cout << "Bitte geben Sie Ihre " << i + 1 << "te Zahl ein." << '\n' << "-->";
		cin >> input;
		cout << '\n';
		while ( testInputRange(input) == false || cin.fail() )
		{
			cout << "Bitte geben Sie eine Zahl zwichen 1 und 49 ein" << '\n' << "-->";
			cin.clear();
			cin.ignore(256, '\n');
			cin >> input;
			cout << '\n';
		} 
				
		userNumbers.push_back(input);
	}
	return userNumbers;
}

bool checkForCopy(vector<int> userNumbers)
{
	for (unsigned int i = 0; i < userNumbers.size(); ++i)
	{
		int control = userNumbers[i];
		int count = 0;
		for (unsigned int x = 0; x < userNumbers.size(); ++x)
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

vector<int> generate(const int MAX_NUM)
{
	srand(time(0)); //seed random number generator
	vector<int> gameNumbers;
	for (int i = 0; i < MAX_NUM; ++i)
	{
		gameNumbers.push_back(rand() % 48 + 1);
	}
	return gameNumbers;
}

void printUserNumbers(vector<int> userNumbers)
{
	cout << "Deine Zahlen sind:" << '\n';

	for (unsigned int i = 0; i < userNumbers.size(); ++i)
	{
		cout << userNumbers[i] << ' ';
	}

	cout << endl;
}

void printGameNumbers(vector<int> gameNumbers)
{
	cout << "Die gezogene Zahlen sind:" << '\n';

	for (unsigned int i = 0; i < gameNumbers.size(); ++i)
	{
		cout << gameNumbers[i] << ' ';
	}

	cout << endl;
}

void checkNumbers(vector<int> userNumbers, vector<int> gameNumbers, const int MAX_NUM)
{
	cout << "\n \n";
	vector<int> correctNumbers;
	int count = 0;
	for (int i = 0; i < MAX_NUM; ++i)
	{
		for (int x = 0; x < MAX_NUM; ++x)
		{
			if (userNumbers[i] == gameNumbers[x])
			{
				correctNumbers.push_back(userNumbers[i]);
				count++;
			}
		}
	}

	cout << "Sie haben " << count << " Zahlen richtig getippt.\n";
	if (count > 1)
	{
		cout << "Sie sind:\n";
		for (int i = 0; i < count; ++i)
		{
			cout << correctNumbers[i] << ' ';
		}
		cout << endl;
	}
	else if (count == 1)
	{
		cout << "Sie sind:\n";
		for (int i = 0; i < count; ++i)
		{
			cout << correctNumbers[i] << ' ';
		}
		cout << endl;
	}
}

bool newGame(vector<int>* p_userNumbers, const int MAX_NUM)
{
	*p_userNumbers = getInput(MAX_NUM);
	if (checkForCopy(*p_userNumbers) == true)
	{
		cout << "FEHLER: Jeder Zahl darf nur ein Mal eingegeben sein" << '\n';
		system("PAUSE");
		return false;
	}
	vector<int> gameNumbers = generate(MAX_NUM);
	printUserNumbers(*p_userNumbers);
	printGameNumbers(gameNumbers);
	checkNumbers(*p_userNumbers, gameNumbers, MAX_NUM);
	return true;
}

bool oldNumbers(vector<int>* p_userNumbers, const int MAX_NUM)
{
	vector<int> gameNumbers = generate(MAX_NUM);
	printUserNumbers(*p_userNumbers);
	printGameNumbers(gameNumbers);
	checkNumbers(*p_userNumbers, gameNumbers, MAX_NUM);
	return true;
}

bool askRestart(vector<int>* p_userNumbers, const int MAX_NUM)
{
	cout << "Drucken Sie:\n 1 - nochmal mit der gleichen Zahlen zu spielen \n 2 - nochmal mit neuen Zahlen zu spielen \n 3 - Quit \n";
	int choice = 0;
	choice = _getch();
	//cin >> choice;
	switch (choice)
	{
	case ('1') :
		system("CLS");
		if (oldNumbers(p_userNumbers, MAX_NUM) == false)
			return false;
		break;
	case ('2') :
		system("CLS");
		vector<int>;
		if (newGame(p_userNumbers, MAX_NUM) == false)
			return false;
		break;
	case ('3') :
		return true;
		break;
	}
	askRestart(p_userNumbers, MAX_NUM);
	return true;
}

int main()
{
	vector<int> userNumbers;
	const int MAX_NUM = 6;
	if (newGame(&userNumbers, MAX_NUM) == false)
		return -1;
	if (askRestart(&userNumbers, MAX_NUM) == false)
		return -1;
	system("PAUSE");
	return 0;
}
