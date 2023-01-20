#include <iostream>
#include "User.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "polish");
	loginMenu();

	int userChoice;

	cin >> userChoice;
	cout << endl;

	switch (userChoice)
	{
	case 1:
		break;
	case 2:
		registration();
		main();
	case 3:
		forgotPassword();
		main();
	case 4:
		cout << "\t\t\t Zapraszamy ponownie! \n\n";
		exit(0);

	default:
		main();
	}

	LoggedUser* us{signIn()};
	us->accMenu();

	User* user = us;

	int operation;
	float* ptr{ nullptr };
	
	
	while (true) {
		cin >> operation;
		switch (operation) {
		case 1:
			user->clearScreen();
			user->transfer();
			us->accMenu();
		case 2:
			user->clearScreen();
			ptr = user->exchange();
			us->updateBalance(ptr[0], ptr[1], *us);
			us->updateBalance(ptr[2], ptr[3], *us);
			user->clearScreen();
			us->accMenu();
			continue;
		case 3:
			user->clearScreen();
			main();
		default:
			user->clearScreen();
			us->accMenu();
		}
	}
	
	delete user, us;
	return 0;
}