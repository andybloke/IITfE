#include "feld.h"
#include <cstdlib>
// Einstiegspunkt des Programms


int main()
{
	// Die Position unseres Markers auf dem Feld, zum Start
	// setzen wir diese auf 0,0 welches die Mitte des Feldes sein soll
	int markerX = 10;
	int markerY = 10;
	// Solange der Marker im Feld ist soll die Schleife laufen
	while (true)
	{
		// Diese Anweisung l�scht den Inhalt der Konsole
		system("cls");
		// Gib das Feld aus und die Markierung
		printPositionInField(markerX, markerY);
		// Pr�fe ob die Markierung mit dem Rand kollidiert,
		// wenn ja brechen wir die Schleife ab
		if (checkCollision(markerX, markerY))
			break;
		// Verschiebe den Marker in eine beliebige Richtung
		markerX += rand() % 5 - 2;
		markerY += rand() % 5 - 2;
	}
	system("pause");
	return 0;
}
