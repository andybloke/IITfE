#include <iostream>
#include "Fahrzeug.h"
#include "Auto.h"
void printStatustrenner() {
	cout << "----------------------------------------\n\n" << endl;
}
int main() {
	// ein Fahrzeug mit Standardkonstruktor erstellen (Name der Variablen: standardFahrzeug)
	Fahrzeug standardFahrzeug;

	// Statusbericht (standardFahrzeug)
	standardFahrzeug.printStatus();
	printStatustrenner();

	// ein Fahrzeug mit folgenden Eigenschaften erstellen (Name der Variablen: boot): Name: Wasserboot, Aktuelle Insassen : 3, Maximale Insassen 4;	Fahrzeug boot = Fahrzeug("Wasserboot", 4, 3);
	Fahrzeug boot("Wasserboot", 4, 3);

	// Statusbericht (boot)
	boot.printStatus();
	printStatustrenner();

	// drei Leute einsteigen lassen (standardFahrzeug)
	standardFahrzeug.einsteigen(3);

	// drei Leute einsteigen lassen (boot)
	boot.einsteigen(3);

	// vier Leute aussteigen lassen (standardFahrzeug)
	standardFahrzeug.aussteigen(4);

	// drei Leute aussteigen lassen (boot)
	boot.aussteigen(3);

	// Statusbericht (standardFahrzeug)
	standardFahrzeug.printStatus();
	printStatustrenner();

	// Statusbericht (boot)
	boot.printStatus();
	printStatustrenner();

	// ein Auto mit Standardkonstruktor erstellen; Name der Variablen: standardAuto
	Auto standardAuto;

	// Statusbericht (standardAuto)
	standardAuto.printStatus();

	printStatustrenner();
	// ein Auto mit folgenden Eigenschaften erstellen (Name der Variablen:	powerAuto): tankinhaltMaximal = 100; tankinhaltAktuell = 11;
	// verbrauch=10; gefahreneKilometer=123; kraftstoffArt="elektro" (istabsichtlich falsch!--> im Konstruktor
	// muss automatisch "Benzin" gesetzt werden trotz Eingabe "elektro"); Aktuelle Insassen : 1, Maximale Insassen 8;
	Auto powerAuto(100, 11, 10, 123, "elektro", 1, 8);

	// sieben Leute einsteigen lassen (powerAuto)
	powerAuto.einsteigen(7);

	// 100km fahren (powerAuto)
	powerAuto.fahren(100);

	// sieben Leute aussteigen lassen (powerAuto)
	powerAuto.aussteigen(7);

	// 100km fahren (powerAuto)
	powerAuto.fahren(100);

	// volltanken (powerAuto)
	cout << endl << powerAuto.volltanken() << " Liter war getankt\n";

	// Statusbericht (powerAuto)
	powerAuto.printStatus();

	printStatustrenner();
	system("pause");
	return 0;
}