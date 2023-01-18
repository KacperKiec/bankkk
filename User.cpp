#include "User.h"

void clearScreen() {
#if defined (_WIN32) || defined (_WIN64)
	system("cls");
	//clrscr(); // including header file : conio.h
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
	system("clear");
	//std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences 
#elif defined (__APPLE__)
	system("clear");
#endif
}

loggedUser::loggedUser(int id, string login, int accountNumber, string firstName, string lastName, int pln, int eur, int usd, int gbp, int czk)
{
	id = id;
	this->login = login;
	accountNumber = accountNumber;
	this->firstName = firstName;
	this->lastName = lastName;

	currency PLN;
	PLN.name = "PLN";
	PLN.value = pln;

	currency EUR;
	EUR.name = "EUR";
	EUR.value = eur;

	currency USD;
	USD.name = "USD";
	USD.value = usd;

	currency GBP;
	GBP.name = "GBP";
	GBP.value = gbp;

	currency CZK;
	CZK.name = "CZK";
	CZK.value = czk;

	account = { PLN, EUR, USD, GBP, CZK };
}

int loggedUser::getId() {
	return id;
}

string loggedUser::getFullName() {
	return firstName + " " + lastName;
}

User::currency loggedUser::getCurrency(int index) {
	return account[index];
}

void loggedUser::accMenu() {
	cout << "\t\t\tWitaj " + getFullName() << "\n\n\n";
	cout << "\t\t\tTwój stan konta: \n\n";
	for (int i = 0; i < 5; i++)
	{
		cout << "\t\t\t" << getCurrency(i).value << " " << getCurrency(i).name << endl;
	}

	cout << "\n\n\n\t\t\tDostêpne operacje: \n\n";
	cout << "\t\t\t1. Przelew\n\n";
	cout << "\t\t\t2. Wyloguj\n\n";
	cout << "\t\t\t<1-2>: ";

	int operation;
	cin >> operation;
	switch (operation) {
	case 1:
		clearScreen();
		transfer();
	case 2:
		clearScreen();
		loginMenu();
	default:
		clearScreen();
		accMenu();
	}
}

void User::transfer() {

}

void loggedUser::transfer() {
	clearScreen();
	string name, lastname, accNr, text;
	int value;
	bool status1 = false;

	cout << "\t\t\tPodaj numer konta odbiorcy: ";
	cin >> accNr;

	ifstream plik("konta.txt");
	if (plik.good() == false)
	{
		cout << "\t\t\tWyst¹pi³ b³¹d!";
		exit(0);
	}

	while (!plik.eof())
	{
		while (getline(plik, text))
		{
			if (!(string::npos == text.find(accNr))) //sprawdza czy istnieje podany numer konta
			{
				status1 = true;
				break;
			}
		}
		if (status1 == false)
		{
			while (true)
			{
				clearScreen();
				cout << "\t\t\tPodany numer nie jest przypisany do ¿adnego konta!\n\n\n";
				cout << "\t\t\t|Naciœnij 1. aby SPRÓBOWAÆ PONOWNIE.\n\n\n";
				cout << "\t\t\t|Naciœnij 2. aby wróciæ do MENU KONTA.\n\n\n";
				cout << "\t\t\t<1-2>: ";
				int UserChoice;
				cin >> UserChoice;
				switch (UserChoice)
				{
				case 1:
					clearScreen();
					transfer();
				case 2:
					clearScreen();
					accMenu();
				default:
					clearScreen();
					continue;
				}
			}
		}
		break;
	}

	cout << "\n\t\t\tWybierz walute przelewu: ";
}