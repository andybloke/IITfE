#include <iostream>
#include <string>

using namespace std;
double getInput()
{
	double input;
	cin >> input;
	return input;
}

main()
{
	double longest = getInput;

	int test = longest;

	if ((test != longest) || (cin.fail()) || (longest <= 0)
	{
		cout << "PRESS A KEY";
		cin.ignore();
		cin.get();
		return -1;
	}

	for (int i = 1; i <= longest; ++i)
	{
		string zeros(i, '0');
		cout << zeros << '\n';
	}

	for (int i = longest - 1; i > 0; --i)
	{
		string zeros(i, '0');
		cout << zeros << '\n';
	}

	return 0;
}
