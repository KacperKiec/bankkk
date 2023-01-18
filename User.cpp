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

void loggedUser::transfer() {
	clearScreen();
	string name, lastname, accNr, text;
	bool status1 = false;

	cout << "\t\t\tPodaj numer konta odbiorcy: ";
	cin >> accNr;
	if (accNr.length() != 7) {
		while (true) {
			cout << "\n\t\t\tPodany numer konta jest nieprawid³owy\n\n\n";
			cout << "\t\t\t|Naciœnij 1. aby SPRÓWBOWAÆ PONOWNIE\n\n\n";
			cout << "\t\t\t|Naciœniej 2. aby wróciæ do MENU KONTA\n\n\n";
			cout << "\t\t\t<1-2>: ";
			int UserChoice1;
			cin >> UserChoice1;
			switch (UserChoice1) {
			case 1:
				clearScreen();
				transfer();
				break;
			case 2:
				clearScreen();
				accMenu();
				break;
			default:
				continue;
			}
		}
	}

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
				int UserChoice2;
				cin >> UserChoice2;
				switch (UserChoice2)
				{
				case 1:
					clearScreen();
					transfer();
					break;
				case 2:
					clearScreen();
					accMenu();
					break;
				default:
					continue;
				}
			}
		}
		break;
	}

	cout << "\n\t\t\tWybierz walute przelewu: ";
	cout << "\n\t\t\t|1. PLN\n";
	cout << "\t\t\t|2. EUR\n";
	cout << "\t\t\t|3. USD\n";
	cout << "\t\t\t|4. GBP\n";
	cout << "\t\t\t|5. CZK\n";
	cout << "\t\t\t<1-5>: ";

	int UserChoice3, i;
	cin >> UserChoice3;
	if (UserChoice3 == 1) i = 6;
	else if (UserChoice3 == 2) i = 7;
	else if (UserChoice3 == 3) i = 8;
	else if (UserChoice3 == 4) i = 9;
	else if (UserChoice3 == 5) i = 10;


	double budget;
	budget = account[i - 6].value;
	cout << budget;
	cout << "\n\t\t\tPodaj kwote przelewu: ";
	double value;
	cin >> value;
	if (value > budget) {
		cout << "\n\t\t\tNie masz wystarczaj¹cych œrodków na koncie!\n";
		cout << "\t\t\t|Naciœni 1. aby SPRÓBOWAÆ PONOWNIE.\n";
		cout << "\t\t\t|Naciœnij dowolny przycisk aby powróciæ do MENU KONTA.\n";
		cout << "\t\t\t<1-2>: ";
		int UserChoice4;
		string press;
		cin >> UserChoice4;
		switch (UserChoice4) {
		case 1:
			clearScreen();
			transfer();
		default:
			cin.ignore();
			getline(cin, press);
			clearScreen();
			accMenu();
		}
	}

	int x = 0;
	string sum, resault;
	double newSum;
	for (int j = 0; j < text.length(); j++) {
		if (x == i) {
			i = j;
			while (text[i] != char(59)) {
				sum += text[i];
				i++;
			}
			newSum = stod(sum) + value;
			resault = to_string(newSum);
			resault.pop_back();
			resault.pop_back();
			resault.pop_back();
			resault.pop_back();
			resault += ";";
			text.replace(j, i, resault);
		}
		if (text[j] == char(59)) x++;
	}
	cout << newSum << endl;
	cout << resault << endl;
	cout << text;
	int a;
	cin >> a;

	plik.close();
}