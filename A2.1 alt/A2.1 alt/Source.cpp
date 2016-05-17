#include<iostream>
#include<math.h>

using namespace std;

double guess();

int main()
{
	cout << "Denken Sie sich eine Zahl zwischen 1 und 100 aus!" << endl;
	cout << "Antworten Sie auf die folgenden Fragen mit j f\201r Ja und mit n f\201r Nein !" << endl;

	//double zahl1 = 50; // Startwert f�r Zahlenabfrage bei 50

	double zahl1 = guess();

	int y = zahl1 + 0.5; // Die Zahl wird so gerundet, dass die Zahl mit dem geringsten Abstand nach 8 Schritten ausgegeben wird.

	cout << "Ihre Zahl lautet ";
	cout << y << endl;

	//system("pause");
	cout << "\n\nPress Enter to continue..\n->";
	cin.ignore();
	cin.get();
	return 0;
}

double guess()
{
	char jaNein; //Variable zur Eingabe von Antwort (j/n)
	int i;
	double zahl1 = 50;
	for (i = 2; i <= 8; ++i)  // Schleife f�r Ann�herung an gesuchte Zahl --> nach 8 Schritten ist man nah genug dran
	{
		cout << "Ist Ihre Zahl kleiner als " << zahl1 << "?" << endl;
		cin >> jaNein;

		//switch is coooool (nur char & int)
		switch (jaNein)
		{
		case 'j': case 'J': zahl1 -= (100 / pow(2, i)); //-= anstatt +=
			break;
		case 'n': case 'N':  zahl1 += (100 / pow(2, i));
			break;
		default:
			if (cin.fail())
				while (cin.fail())
				{
					cin.clear();
					cin.ignore();
					cout << "Bitte mit j oder n antworten..\n";
				}
			else
			{
				cout << "Bitte mit j oder n antworten..\n";
			}
			--i;
			continue;
		}
	}
	return zahl1;
}