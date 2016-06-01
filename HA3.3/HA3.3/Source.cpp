#include <iostream>
#include <math.h>
#include <vector>
#include <time.h> //Zeitpunkt für srand seed

using namespace std;

const int MAX_NUM = 6; //Global Konstante fuer Anzahl der einzugeben Zahlen
const int HIGHEST = 49; //globale Konstante für Zahlenbereich

bool testInputRange(int input) //pruefe, dass eingabe innerhalb erlaubtem bereich liegt
{
	return (input > 0 && input < HIGHEST + 1);
}

vector<int> getInput() //Nimm Benutzer Zahlen
{
	vector<int> userNumbers;
	cout << "Lotto Spiel!\n Bitte geben Sie " << MAX_NUM << " Zahlen zwischen 1 und " << HIGHEST << " ein!\n Jede Zahl darf nat\201rlich nur ein Mal vorkommen!\n \n";
	int input;
	for (int i = 0; i < MAX_NUM; ++i)
	{
		cout << "Bitte geben Sie Ihre " << i + 1 << "te Zahl ein." << '\n' << "-->";
		cin >> input;
		cout << '\n';
		while (testInputRange(input) == false || cin.fail()) //pruefe eingabe
		{
			cout << "Bitte geben Sie eine Zahl zwichen 1 und " << HIGHEST << " ein" << '\n' << "-->";
			cin.clear();
			cin.ignore(256, '\n'); //lösche cin puffer
			cin >> input;
			cout << '\n';
		}
		userNumbers.push_back(input); //Stelle Eingabe in Vector
	}
	return userNumbers;
}

bool checkForCopy(vector<int> userNumbers) //prufe, dass jede Eingabe nur einmal vorkommt
{
	for (unsigned int i = 0; i < MAX_NUM; ++i)
	{
		int control = userNumbers[i];
		int count = 0;
		for (unsigned int x = 0; x < MAX_NUM; ++x)
		{
			if (control == userNumbers[x])
				count++;
			else
				continue;
		}
		if (count > 1) //falls eine Zahl mehrfach vorkommt
			return true;
		else
			continue;
	}
	return false;
}

vector<int> generate() //ziehe zufallige Zahlen
{
	vector<int> gameNumbers;
	while (true)
	{
		gameNumbers.clear();
		for (int i = 0; i < MAX_NUM; ++i)
		{
			gameNumbers.push_back(rand() % (HIGHEST - 1) + 1); //zufallige Zahl zwischen 0 & (HIGHEST -1) + 1, gibt Zahl zwichen 1 und HIGHEST
		}
		int count = 0;
		for (int i = 0; i < MAX_NUM; ++i) //prufe, das jeder Zahl nur ein Mal vorkommt
		{
			int control = gameNumbers[i];
			for (int x = 0; x < MAX_NUM; ++x)
			{
				if (control == gameNumbers[x])
					count++;
				else
					continue;
			}
		}
		if (count > MAX_NUM) //falls eine Zahl mehrfach vorkommt
			continue;
		else
			break;
	}
	return gameNumbers;
}

void printUserNumbers(vector<int> userNumbers) //drucke eingegebene Zahlen auf Bildschirm
{
	cout << "Deine Zahlen sind:" << '\n';
	for (unsigned int i = 0; i < MAX_NUM; ++i)
	{
		cout << userNumbers[i] << ' ';
	}
	cout << endl;
}
void printGameNumbers(vector<int> gameNumbers) //drucke gezogene Zahlen auf Bildschirm
{
	cout << "Die gezogene Zahlen sind:" << '\n';
	for (unsigned int i = 0; i < MAX_NUM; ++i)
	{
		cout << gameNumbers[i] << ' ';
	}
	cout << endl;
}

void checkNumbers(vector<int> userNumbers, vector<int> gameNumbers) //pruefe wie viel und welche zahlen passen
{
	cout << "\n \n"; //macht platz (optisch)
	vector<int> correctNumbers;
	int count = 0;
	for (int i = 0; i < MAX_NUM; ++i)
	{
		for (int x = 0; x < MAX_NUM; ++x)
		{
			if (userNumbers[i] == gameNumbers[x])
			{
				correctNumbers.push_back(userNumbers[i]); //fuelle vector mit den richtig getippten Zahlen
				count++;
			}
		}
	}
	//zeige wie viel und welche Zahlen richtig getippt war
	if (count > 1)
	{
		cout << "Sie haben " << count << " Zahlen richtig getippt.\n";
		cout << "Sie sind:\n";
		for (int i = 0; i < count; ++i)
		{
			cout << correctNumbers[i] << ' ';
		}
		cout << endl;
	}
	else if (count == 1)
	{
		cout << "Sie haben " << count << " Zahl richtig getippt.\n";
		cout << "Es ist:\n";
		for (int i = 0; i < count; ++i)
		{
			cout << correctNumbers[i] << ' ';
		}
		cout << endl;
	}
	else if (count == 0)
	{
		cout << "Sie haben keine Zahl richtig getippt.\n";
		for (int i = 0; i < count; ++i)
		{
			cout << correctNumbers[i] << ' ';
		}
		cout << endl;
	}
}

bool newGame(vector<int>* p_userNumbers) //spiel mit neuer Zahlen
{
	*p_userNumbers = getInput(); //fuellt userNumbers mit eingabe
	if (checkForCopy(*p_userNumbers) == true) //prueft userNumbers
	{
		cout << "FEHLER: Jede Zahl darf nur ein Mal eingegeben werden" << '\n';
		system("PAUSE");
		return false;
	}
	vector<int> gameNumbers = generate(); // generiert zufaellige Zahlen
	printUserNumbers(*p_userNumbers); //druckt alles auf Bildschirm
	printGameNumbers(gameNumbers);
	checkNumbers(*p_userNumbers, gameNumbers); //pruefe nach richtig getippten Zahlen
	return true;
}

bool oldNumbers(vector<int>* p_userNumbers) //spiel mit alten Zahlen (ohne eingabe)
{
	vector<int> gameNumbers = generate();
	printUserNumbers(*p_userNumbers);
	printGameNumbers(gameNumbers);
	checkNumbers(*p_userNumbers, gameNumbers);
	return true;
}

bool askRestart(vector<int>* p_userNumbers) //frag ob Spieler wieder spielen will
{
	cout << "Drucken Sie:\n 1 - um nochmal mit den gleichen Zahlen zu spielen \n 2 - um nochmal mit neuen Zahlen zu spielen \n 3 - Quit \n";
	cout << ": ";
	int choice = 0;
	cin >> choice;
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(256, '\n');
		askRestart(p_userNumbers);
	}
	switch (choice)
	{
	case (1):
		system("CLS");
		if (oldNumbers(p_userNumbers) == false)
			return false;
		break;
	case (2):
		system("CLS");
		vector<int>;
		if (newGame(p_userNumbers) == false)
			return false;
		break;
	case (3):
		return true;
		break;
	default:
		break;
	}
	askRestart(p_userNumbers); //rekursion
	return true;
}

int main()
{
	srand(time(0)); //seed random number generator
	vector<int> userNumbers;
	if (newGame(&userNumbers) == false)
		return -1;
	if (askRestart(&userNumbers) == false)
		return -1;
	system("PAUSE");
	return 0;
}