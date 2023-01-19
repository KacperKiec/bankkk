#include "User.h"

using namespace std;

void loginMenu();
void registration();
void signIn();
void forgotPassword();

void loginMenu()
{
	int userChoice;
	cout << "\t\t\t_______________________________________________\n\n\n";
	cout << "\t\t\t             WITAMY W NASZYM BANKU             \n\n\n";
	cout << "\t\t\t____________          MENU         ____________\n\n\n";
	cout << "\t\t\t                                               \n\n\n";
	cout << "\t| Naciœnij 1. aby siê ZALOGOWAÆ					  \n\n\n";
	cout << "\t| Naciœnij 2. aby sie ZAREJESTROWAÆ                 \n\n\n";
	cout << "\t| Naciœnij 3. je¿eli zapomni³eœ/aœ swojego HAS£A    \n\n\n";
	cout << "\t| Naciœnij 4. aby wyjœæ                             \n\n\n";
	cout << "\t<1-4>: ";
	cin >> userChoice;
	cout << endl;

	switch (userChoice)
	{
	case 1:
		signIn();
		break;

	case 2:
		registration();
		break;

	case 3:
		forgotPassword();
		break;

	case 4:
		cout << "\t\t\t Zapraszamy ponownie! \n\n";
		exit(0);
		break;

	default:
		clearScreen();
		loginMenu();
	}
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
		cout << "\t\t\tWyst¹pi³ problem! ";
		exit(0);
	}


	int n{ 2 };
	if (pos.size() >= 11) {	// jesli mamy wiêcej niz jedno konto 
		while (n < pos.size() && pos.at(n) == to_string(accNr)) { //tworzymy numer konta dopuki nie bedzie on inny od pozostalych, co 11 indexow mamy nasz numer konta 
			srand(time(NULL));
			accNr = rand() % 9000000 + 1000000;
			n += 11;
		}
	}


	clearScreen();
	cout << "\t\t\tPodaj swój login: ";
	cin >> login;

	for (int i = 1; i < pos.size(); i += 11) {
		while (login == pos.at(i)) {
			clearScreen();
			cout << "\t\t\tPodany login juz istnieje!\n";
			cout << "\t\t\tPodaj inny login: ";
			cin >> login;
		}
	}

	while (login.length() < 4 || login.length() > 12) {
		clearScreen();
		cout << "\t\t\tLogin musi zawieraæ od 4 do 12 znaków\n";
		cout << "\t\t\tPodaj inny login: ";
		cin >> login;
	}


	cout << endl;
	cout << "\t\t\tPodaj swoje imiê: ";
	cin >> name;
	cout << endl;
	cout << "\t\t\tPodaj swoje nazwisko: ";
	cin >> lastname;
	cout << endl;
	cout << "\t\t\tPodaj swoje has³o: ";
	cin >> password;

	while (password.length() < 4 || password.length() > 12) {
		clearScreen();
		cout << "\t\t\tHas³o musi zawieraæ od 4 do 12 znaków\n";
		cout << "\t\t\tPodaj inne has³o: ";
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
		cout << "\t\t\tWyst¹pi³ problem! ";
		exit(0);
	}

	cout << "\t\t\tZarejestrowano pomyœlnie.\n\n\n";
	cout << "\t\t\tNaciœnij Enter aby wróciæ do MENU G£ÓWNE.....";
	cin.ignore();
	getline(cin, press);

	clearScreen();

	loginMenu();
}

void signIn()
{
	clearScreen();
	string login, password, userpassword, text;
	string id, name, lastname, pln, eur, usd, gbp, czk, accNr;
	int x = 0;
	bool statusl = false, statusp = false;

	cout << "\n\n\t\t\tLogin: ";
	cin >> login;

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
			if (!(string::npos == text.find(login))) //sprawdza czy istnieje uzytkownik o podanym loginie
			{
				statusl = true;
				break;
			}
		}
		if (statusl == false)
		{
			while (true)
			{
				clearScreen();
				cout << "\t\t\tKonto o podanym loginie nie istnieje!\n\n\n";
				cout << "\t\t\t|Naciœnij 1. aby SPRÓBOWAÆ PONOWNIE.\n\n\n";
				cout << "\t\t\t|Naciœnij 2. aby wróciæ do MENU G£ÓWNE.\n\n\n";
				cout << "\t\t\t<1-2>: ";
				int UserChoice;
				cin >> UserChoice;
				switch (UserChoice)
				{
				case 1:
					signIn();
				case 2:
					clearScreen();
					loginMenu();
				default:
					clearScreen();
					continue;
				}
			}
		}
		break;
	}

	for (int j = 0; j < text.length(); j++)
	{
		if (x == 5)
		{
			password += text[j]; //pobiera zapisane haslo z pliku
		}
		if (text[j] == char(59)) x++;
	}
	password.pop_back();

	cout << "\n\t\t\tPodaj has³o: ";
	cin >> userpassword;

	if (userpassword == password) statusp = true; //sprawdza czy podane haslo jest zgodne z zapisanym
	clearScreen();
	while (statusp == false)
	{
		cout << "\t\t\tNiepoprawne has³o! SPRÓBUJ JESZCZE RAZ\n\n\n";
		cout << "\t\t\tPodaj has³o: ";
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

	plik.close();

	loggedUser loggedUsr(stoi(id), login, stoi(accNr), name, lastname, stof(pln), stof(eur), stof(usd), stof(gbp), stof(czk));

	loggedUsr.accMenu(); // przejscie do menu w profilu

}

void forgotPassword()
{
	vector<string> pos, lines;
	string login, text, accNr, opass, line, press;
	bool matchA{ false }, matchL{ false };
	int npass{};

	clearScreen();
	cout << "\t\t\tAby odzyskaæ swoje has³o\n\n";
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
		cout << "Wyst¹pi³ problem!";
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
			cout << "\t\t\tSpróbuj jeszcze raz: ";
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
			cout << "\t\t\tZ³y login!\n\n";
			cout << "\t\t\tSpróbuj jeszcze raz: ";
			cin >> login;
		}
	}

	//tworzenie nowego has³a
	if (matchA && matchL) {
		clearScreen();
		srand(time(NULL));
		cout << "\n\t\t\tTwoje nowe has³o to: ";
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
				cout << "Wyst¹pi³ problem!";
			}

			file.open("konta.txt", ios::app);

			if (file.is_open()) {
				for (int i = 0; i < lines.size(); i++) {
					file << lines.at(i) << endl;
				}
				file.close();
			}
			else {
				cout << "Wyst¹pi³ problem!";
			}
		}
		else {
			cout << "Wyst¹pi³ problem!";
		}

	}
	cout << "\n\t\t\tNaciœnij Enter aby przejœæ do logowania.....";
	cin.ignore();
	getline(cin, press);
	clearScreen();
	signIn();
}