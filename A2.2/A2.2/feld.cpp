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
	for (int y = 0; y <= 30; ++y)
	{
		for (int x = 0; x <= 50; ++x)
		{
			//top line
			if (y == 0)
			{
				if (x == 0)
				{
					cout << tlcorner;
				}

				if (x != 0 && x != 50)
				{
					cout << flat;
				}

				if (x == 50)
				{
					cout << trcorner << endl;
				}
			}
			
			//middle
			if (y > 1 && y < 30)
			{
				if (x == 0)
				{
					cout << side;
				}

				if (x != 0 && x != 50)
				{
					cout << ' ';
				}

				if (x == 50)
				{
					cout << side << endl;
				}
			}

			//bottom
			if (y == 30)
			{
				if (x == 0)
				{
					cout << blcorner;
				}

				if (x != 0 && x != 50)
				{
					cout << flat;
				}

				if (x == 50)
				{
					cout << brcorner << endl;
				}
			}


		}
		
		//if (y < 50, x)
	}

	/*//build topline
	const string middle(48, flat);
	const string topline = tlcorner + middle + trcorner;

	//build middle line
	const string spaces(48, ' ');
	const string middleline = side + spaces + side;

	//build bottomline
	const string bottomline = blcorner + middle + brcorner; */



}

//bool checkCollision(int markerX, int markerY)

