#include <iostream>

int main()
{
	//stupid bit
	int ausgabe;
	ausgabe = 100;
	int eingabe;
	eingabe = 50;
	std::cout << "Hello Cruel World" << '\n';
	std::cout << 12345 << '\n';
	std::cout << ausgabe << '\n';
	eingabe = eingabe + ausgabe;
	std::cout << eingabe << '\n';

	//fun bit (if you like that sort of thing)
	char again; //define char for the do-while loop
	do //start of do-while looop
	{
		std::cout << "\nEnter a number:\n";
		std::cin >> eingabe;
		//if it's not a number
		while (std::cin.fail())
		{
			std::cout << "That is not a number. Try again!\n";
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cin >> eingabe;
		}
		//even odd thing
		std::cout << '\n' << eingabe << " ist ";
		if (eingabe % 2 == 0)
		{
			std::cout << "gerade\n";
		}
		else if (!(eingabe % 2 == 0))
		{
			std::cout << "ungerade" << '\n';
		}
		//avoiding system specific system('pause')
		std::cout << '\n' << "Press Enter to continue.\n";
		std::cin.ignore();
		std::cin.get();
		//factors output
		int i;
		std::cout << "Factors of " << eingabe << " are:\n" << '\n';
		for (i = 1; i <= eingabe; ++i)
		{
			if (eingabe%i == 0)
				std::cout << i << " ";
		}
		//again! again!
		std::cout << '\n' << '\n' << "Again? y/n ";
		std::cin >> again;
		//check input
		if (again != 'y' && again != 'n')
		{
			std::cout << "Invalid entry. Try again.\n";
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cin >> again;
		}

	} while (again == 'y');
	if (again == 'n')
	{
		std::cout << '\n' << '\n' << "Thanks! Press Enter to quit.\n";
		//wait
		std::cin.ignore();
		std::cin.get();
		return 0;
	}

}

//add some changes
//add some more
