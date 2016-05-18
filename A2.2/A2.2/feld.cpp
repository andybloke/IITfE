#include <iostream>

using namespace std;

void printPositionInField(int markerX, int markerY)
{
	//define the grid parts
	char tlcorner = 201;
	char trcorner = 187;
	char blcorner = 200;
	char brcorner = 188;
	char side = 186;
	char flat = 205;

	//print grid
	for (int y = 0; y <= 21; ++y)
	{
		for (int x = 0; x <= 21; ++x)
		{
			//top line
			if (y == 0)
			{
				if (x == 0)
				{
					cout << tlcorner;
				}

				if (x != 0 && x != 21)
				{
					cout << flat;
				}

				if (x == 21)
				{
					cout << trcorner << endl;
				}
			}
			
			//middle
			if (y > 1 && y < 21)
			{
				if (x == 0)
				{
					cout << side;
				}

				if (x != 0 && x != 21)
				{
					if (x == markerX && y == markerY)
					{
						cout << "X";
					}
					
					else
					{
						cout << ' ';
					}
					
				}

				if (x == 21)
				{
					cout << side << endl;
				}
			}

			//bottom
			if (y == 21)
			{
				if (x == 0)
				{
					cout << blcorner;
				}

				if (x != 0 && x != 21)
				{
					cout << flat;
				}

				if (x == 21)
				{
					cout << brcorner << endl;
				}
			}
		}	
	}
}

bool checkCollision(int markerX, int markerY)
{
	if ((markerX <= 0 || markerX >= 21) || (markerY <= 0 || markerY >= 21))
		return true;
	else
		return false;
}