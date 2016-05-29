#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

bool testInputRange(int input)
{

}

vector<int> getInput()
{
	const int MAX_NUM = 6;
	vector<int> userNumbers;
	int input;
	for (int i = 0; i < MAX_NUM; ++i)
	{
		do
		{
			cout << "Bitte geben Sie Ihre " << i + 1 << "te Zahl ein." << '\n' << "-->";
			cin >> input;
		} while (testInputRange(input) = false);
				
		userNumbers.push_back(input);
	}
	return userNumbers;
}

int main()
{
	vector<int> userNumbers = getInput();
}
