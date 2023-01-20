#include "User.h"


void LoggedUser::clearScreen() {
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

void loginMenu()
{
	clearScreen();
	cout << "\t\t\t_______________________________________________\n\n\n";
	cout << "\t\t\t             WITAMY W NASZYM BANKU             \n\n\n";
	cout << "\t\t\t____________          MENU         ____________\n\n\n";
	cout << "\t\t\t                                               \n\n\n";
	cout << "\t| Naci�nij 1. aby si� ZALOGOWA�					  \n\n\n";
	cout << "\t| Naci�nij 2. aby sie ZAREJESTROWA�                 \n\n\n";
	cout << "\t| Naci�nij 3. je�eli zapomni�e�/a� swojego HAS�A    \n\n\n";
	cout << "\t| Naci�nij 4. aby wyj��                             \n\n\n";
	cout << "\t<1-4>: ";
}

void registration() {
	srand(time(NULL));
	int accNr = rand() % 9000000 + 1000000;	//numer konta
	vector<string> pos;

	int id{ 0 }, idTemp{ 0 };
	string login, name, lastname, password, text, press;

	ifstream f2("konta.txt");

	if (f2.good()) {
		while (getline(f2, text, ';')) {
			pos.push_back(text);	//potrzebne do sprawdzenia pozstalych numerow kont
			idTemp++;
			if (idTemp % 11 == 0) id++;		//obliczanie id 
		}
		f2.close();
	}

	else {	//w przypadku kiedy plik tekstowy sie nie otworzy
		cout << "\t\t\tWyst�pi� problem! ";
		exit(0);
	}


	int n{ 2 };
	if (pos.size() >= 11) {	// jesli mamy wi�cej niz jedno konto 
		while (n < pos.size() && pos.at(n) == to_string(accNr)) { //tworzymy numer konta dopuki nie bedzie on inny od pozostalych, co 11 indexow mamy nasz numer konta 
			srand(time(NULL));
			accNr = rand() % 9000000 + 1000000;
			n += 11;
		}
	}


	clearScreen();
	cout << "\n\n\t\t\tPodaj sw�j login: ";
	cin >> login;

	for (int i = 1; i < pos.size(); i += 11) {
		while (login == pos.at(i)) {
			clearScreen();
			cout << "\n\n\t\t\tPodany login juz istnieje!\n";
			cout << "\t\t\tPodaj inny login: ";
			cin >> login;
		}
	}

	while (login.length() < 4 || login.length() > 12) {
		clearScreen();
		cout << "\n\n\t\t\tLogin musi zawiera� od 4 do 12 znak�w\n";
		cout << "\t\t\tPodaj inny login: ";
		cin >> login;
	}


	cout << endl;
	cout << "\t\t\tPodaj swoje imi�: ";
	cin >> name;
	cout << endl;
	cout << "\t\t\tPodaj swoje nazwisko: ";
	cin >> lastname;
	cout << endl;
	cout << "\t\t\tPodaj swoje has�o: ";
	cin >> password;

	while (password.length() < 4 || password.length() > 12) {
		clearScreen();
		cout << "\n\n\t\t\tHas�o musi zawiera� od 4 do 12 znak�w\n";
		cout << "\t\t\tPodaj inne has�o: ";
		cin >> password;
	}

	cout << endl;


	ofstream f1("konta.txt", ios::app);

	if (f1.good()) {	//wpisuje konto do pliku textowego zera to stan poczatkowy konta dla kazdej waluty
		f1 << id << ";" << login << ";" << accNr << ";" << name << ";" << lastname << ";" << password
			<< ";" << 0 << ";" << 0 << ";" << 0 << ";" << 0 << ";" << 0 << ";" << endl;
		f1.close();
	}
	else {
		cout << "\t\t\tWyst�pi� problem! ";
		exit(0);
	}

	cout << "\t\t\tZarejestrowano pomy�lnie.\n\n\n";
	cout << "\t\t\tNaci�nij Enter aby wr�ci� do MENU G��WNE.....";
	cin.ignore();
	getline(cin, press);

	clearScreen();
}

LoggedUser* signIn()
{
	clearScreen();
	string login, password, userpassword, text;
	string id, name, lastname, pln, eur, usd, gbp, czk, accNr;
	bool statusl = false, statusp = false;
	int x = 0;
	vector<string>pos;

	ifstream file("konta.txt");

	if (file.good()) {	//wpisywanie danych do wektora
		while (getline(file, text, ';')) {
			pos.push_back(text);
		}
		file.close();
	}
	else {
		cout << "Wyst�pi� problem!";
	}
	file.close();

	cout << "\n\n\t\t\tLogin: ";
	cin >> login;

	while (!statusl) {
		for (int i = 1; i < pos.size(); i += 11) {
			if (pos.at(i) == login) {
				statusl = true;
				break;
			}
			x++;
		}
		if (!statusl) {
			
			clearScreen();
			cout << "\t\t\tKonto o podanym loginie nie istnieje!\n\n\n";
			cout << "\t\t\tSpr�buj ponownie: ";
			cin >> login;
			x = 0;
		}
	}

	ifstream plik("konta.txt");
	if (!plik.good()) {
		cout << "Wyst�pi� b�ad!";
		exit(0);
	}

	for (int i = 0; i <= x; i++) {
		getline(plik, text);
	}
	plik.close();
	
	x = 0;
	for (int j = 0; j < text.length(); j++)
	{
		if (x == 5)
		{
			password += text[j]; //pobiera zapisane haslo z pliku
		}
		if (text[j] == char(59)) x++;
	}
	password.pop_back();

	cout << "\n\t\t\tPodaj has�o: ";
	cin >> userpassword;

	if (userpassword == password) statusp = true; //sprawdza czy podane haslo jest zgodne z zapisanym
	clearScreen();
	while (statusp == false)
	{
		cout << "\t\t\tNiepoprawne has�o! SPR�BUJ JESZCZE RAZ\n\n\n";
		cout << "\t\t\tPodaj has�o: ";
		cin >> userpassword;
		if (userpassword == password) statusp = true;
		clearScreen();
	}

	x = 0;
	for (int i = 0; i < text.length(); i++) //wydobywanie danych z pliku
	{
		if (x == 0) id += text[i];
		else if (x == 2) accNr += (text[i]);
		else if (x == 3)name += text[i];
		else if (x == 4)lastname += text[i];
		else if (x == 6)pln += text[i];
		else if (x == 7)eur += text[i];
		else if (x == 8)usd += text[i];
		else if (x == 9)gbp += text[i];
		else if (x == 10)czk += text[i];
		if (text[i] == char(59)) x++;
	}
	id.pop_back(); //usuwanie ; ze zmiennych
	accNr.pop_back();
	name.pop_back();
	lastname.pop_back();
	pln.pop_back();
	eur.pop_back();
	usd.pop_back();
	gbp.pop_back();
	czk.pop_back();


	LoggedUser* user = new LoggedUser(stoi(id), login, stoi(accNr), name, lastname, stof(pln), stof(eur), stof(usd), stof(gbp), stof(czk));
	return user;
}

void forgotPassword()
{
	vector<string> pos, lines;
	string login, text, accNr, opass, line, press;
	bool matchA{ false }, matchL{ false };
	int npass{};

	clearScreen();
	cout << "\t\t\tAby odzyska� swoje has�o\n\n";
	cout << "\t\t\tPodaj numer swojego konta: ";
	cin >> accNr;

	ifstream file("konta.txt");

	if (file.good()) {	//wpisywanie danych do wektora
		while (getline(file, text, ';')) {
			pos.push_back(text);
		}
		file.close();
	}
	else {
		cout << "Wyst�pi� problem!";
	}

	while (!matchA) {
		for (int i = 2; i < pos.size(); i += 11) {
			if (pos.at(i) == accNr) {
				matchA = true;
			}
		}
		if (!matchA) {
			clearScreen();
			cout << "\t\t\tPodany numer konta nie istnieje!\n\n";
			cout << "\t\t\tSpr�buj jeszcze raz: ";
			cin >> accNr;
		}
	}
	cout << endl;

	cout << "\t\t\tPodaj login: ";
	cin >> login;

	while (!matchL) {
		for (int i = 1; i < pos.size(); i += 11) {
			if (pos.at(i) == login) {
				matchL = true;
			}
		}
		if (!matchL) {
			clearScreen();
			cout << "\t\t\tZ�y login!\n\n";
			cout << "\t\t\tSpr�buj jeszcze raz: ";
			cin >> login;
		}
	}

	//tworzenie nowego has�a
	if (matchA && matchL) {
		clearScreen();
		srand(time(NULL));
		cout << "\n\t\t\tTwoje nowe has�o to: ";
		npass = rand() % 9000000 + 1000000;
		cout << "\033[32m";
		cout << npass << endl;
		cout << "\033[0m";
		string newpass = to_string(npass);

		for (int i = 2; i < pos.size(); i += 11) {
			if (pos.at(i) == accNr) {
				opass = pos.at(i + 3); //stare haslo
				break;
			}
		}
		//wpisywanie nowego hasla do "bazy danych"
		fstream file;
		file.open("konta.txt", ios::in);
		if (file.is_open()) {
			while (getline(file, line)) {
				if (line.find(opass) != string::npos) {
					line.replace(line.find(opass), opass.length(), newpass);
				}
				lines.push_back(line);
			}
			file.close();

			file.open("konta.txt", ios::out);

			if (file.is_open()) {
				file << "";
				file.close();
			}
			else {
				cout << "Wyst�pi� problem!";
			}

			file.open("konta.txt", ios::app);

			if (file.is_open()) {
				for (int i = 0; i < lines.size(); i++) {
					file << lines.at(i) << endl;
				}
				file.close();
			}
			else {
				cout << "Wyst�pi� problem!";
			}
		}
		else {
			cout << "Wyst�pi� problem!";
		}

	}
	cout << "\n\t\t\tNaci�nij Enter aby przej�� do logowania.....";
	cin.ignore();
	getline(cin, press);
	clearScreen();
}

LoggedUser::LoggedUser(int id, string login, int accountNumber, string firstName, string lastName, float pln, float eur, float usd, float gbp, float czk)
{
	this->id = id;
	this->login = login;
	this->accountNumber = accountNumber;
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

int LoggedUser::getId() {
	return id;
}

string LoggedUser::getFullName() {
	return firstName + " " + lastName;
}

User::currency LoggedUser::getCurrency(int index) {
	return account[index];
}

int LoggedUser::getAccNumber() {
	return accountNumber;
}

void LoggedUser::accMenu() {
	cout << "\t\t\tWitaj " + getFullName() << "\t\tTw�j numer konta to: " << getAccNumber() << "\n\n\n";
	cout << "\t\t\tTw�j stan konta: \n\n";
	for (int i = 0; i < 5; i++)
	{
		cout << "\t\t\t"<< fixed <<setprecision(2) <<getCurrency(i).value << " " << getCurrency(i).name << endl;
	}

	cout << "\n\n\n\t\t\tDost�pne operacje: \n\n";
	cout << "\t\t\t1. Przelew\n\n";
	cout << "\t\t\t2. Przewalutowanie\n\n";
	cout << "\t\t\t3. Wyloguj\n\n";
	cout << "\t\t\t<1-3>: ";
}

void LoggedUser::transfer() {
	clearScreen();
	string accNr, text;
	bool status1 = false, matchA = false;
	vector<string> pos;

	cout << "\t\t\tPodaj numer konta odbiorcy: ";
	cin >> accNr;

	ifstream file("konta.txt");

	if (file.good()) {	//wpisywanie danych do wektora
		while (getline(file, text, ';')) {
			pos.push_back(text);
		}
		file.close();
	}
	else {
		cout << "Wyst�pi� problem!";
	}

	while (!matchA) {
		for (int i = 2; i < pos.size(); i += 11) {
			if (pos.at(i) == accNr) {
				matchA = true;
			}
		}
		if (!matchA) {
			clearScreen();
			cout << "\t\t\tPodany numer konta nie istnieje!\n\n";
			cout << "\t\t\tSpr�buj jeszcze raz: ";
			cin >> accNr;
		}
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


	float budget;
	budget = account[i - 6].value;
	cout << budget;
	cout << "\n\t\t\tPodaj kwote przelewu: ";
	float value;
	cin >> value;
	if (value > budget) {
		cout << "\n\t\t\tNie masz wystarczaj�cych �rodk�w na koncie!\n";
		cout << "\t\t\t|Naci�ni 1. aby SPR�BOWA� PONOWNIE.\n";
		cout << "\t\t\t|Naci�nij dowolny przycisk aby powr�ci� do MENU KONTA.\n";
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
	float newSum;
	for (int j = 0; j < text.length(); j++) {
		if (x == i) {
			i = j;
			while (text[i] != char(59)) {
				sum += text[i];
				i++;
			}
			newSum = stof(sum) + value;
			resault = to_string(newSum);
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

}

void LoggedUser::exchange() {
	unsigned int option1, option2, operation;
	float value, afterOperation, newValue{};
	double pln{ getCurrency(0).value };
	string line, choice;
	vector<string> rate;

	cout << "\n\n\t\t\tDost�pne operacje:\n\n\t\t\t1.Sprzeda�\n\n\t\t\t2.Kupno\n\n\t\t\t3.Wr�� do menu\n\n\t\t\t<1-3>: ";
	cin >> option1;

	clearScreen();
	if (option1 == 1) choice = "sprzeda�";
	if (option1 == 2) choice = "kupi�";
	if (option1 == 3) { choice = "kupi�"; accMenu(); }
	cout << "\t\t\t\t\t\t\t" << fixed << setprecision(2) << getCurrency(0).value << " " << getCurrency(0).name << endl;
	cout << "\t\t\tTw�j stan walut:\n";
	for (int i = 1; i < 5; i++)
	{
		cout << "\t\t\t"<< i <<") " << fixed << setprecision(2) << getCurrency(i).value << " " << getCurrency(i).name << endl;
	}
	cout << "\n\n\t\t\tWybierz walute kt�r� chcesz " << choice << "\n\t\t\t<1 - 4>: ";
	cin >> option2;
	cout << "\n\n\t\t\tJak� sum� pieni�dzy chcesz " << choice << "\n\t\t\t(aby pomin�� wybierz 0)\n\t\t\t<ilo�� w wybranej walucie>: ";
	while (cin >> value) {
		if (option1 == 1 && (value < 0 || value > getCurrency(option2).value)) {
			clearScreen();
			cout << "\n\t\t\tWpisz poprawn� sum� pieni�dzy!\n\t\t\t(aby pomin�� wybierz 0)\n\t\t\t<ilo�� w wybranej walucie>: ";
		}

		else if (option1 == 2 && (pln - value < 0 || value < 0)) {
			clearScreen();
			cout << "\n\t\t\tWpisz poprawn� sum� pieni�dzy!\n\t\t\t<ilo�� w wybranej walucie>: ";
		}

		else break;
	}

	ifstream plik("exchangeRate.txt");
	if (plik.good() == false)
	{
		cout << "\t\t\tWyst�pi� b��d!";
		exit(0);
	}

	while (!plik.eof()) {
		getline(plik, line, '/');
		rate.push_back(line);

	}
	plik.close();

	operation = stoi(rate.at((option2 - 1) * 2 + option1 + 2));
	afterOperation = value * (operation / static_cast<float>(100)); //w przeliczeniu na z�ot�wki

	newValue = getCurrency(option2).value;

	if (option1 == 1) {
		pln += afterOperation;
		newValue -= value;
	}
	if (option1 == 2) {
		pln -= afterOperation;
		newValue += value;
	}

}

void LoggedUser::updateAcc(int currencyIndexInFile, float value, int id) {
	string text;
	vector<string> data;
	int temp{ 0 };

	fstream file;
	file.open("konta.txt", ios::in);

	if (file.good() == false)
	{
		cout << "\t\t\tWyst�pi� b��d!";
		exit(0);
	}
	while (!file.eof()) {
		while (getline(file, text, ';')) {
			data.push_back(text);
		}
	}

	temp = id * 11 + currencyIndexInFile;
	data.at(temp) = to_string(value);
	cout << temp;

	file.close();

	file.open("konta.txt", ios::out);
	if (file.is_open()) {
		file << "";
		file.close();
	}
	else {
		cout << "Wyst�pi� problem!";
		exit(0);
	}

	file.open("konta.txt", ios::app);
	if (file.good() == false) {
		cout << "Wyst�pi� problem";
		exit(0);
	}
	else {
		for (int i = 0; i < data.size(); i++) {
			file << data.at(i) << ";";
		}
		file.close();
	}
}