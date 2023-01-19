#include <string>
#include <array>
#include <iostream>
#include <vector>
#include <string.h>
#include <fstream>
#include <random>
#include <time.h>
#include <iomanip>

using namespace std;

void clearScreen();
void loginMenu();
void signIn();
void registration();
void forgotPassword();

class User {
public:
	struct currency // klasa zagnie¿d¿ona
	{
	public:
		string name;
		float value;
	};

public:
	friend void registration();
	friend void forgotPassword();
	friend void signIn();
	friend void loginMenu();
	virtual void transfer() = 0; //itd
	virtual void exchange() = 0;
};

class loggedUser : public User {
private:
	int id;
	int accountNumber;
	string login;
	string firstName;
	string lastName;
	array<currency, 5> account;
	void updateAcc(int currencyIndexInFile, float value, int id); //indexy w pliku textowym PLN-6, EUR-7, USD-8, GBP-9, CZK-10
	int getId();
	string getFullName();
	currency getCurrency(int index);
	int getAccNumber();
public:
	loggedUser(int id, string login, int accountNumber, string firstName, string lastName, float pln, float eur, float usd, float gbp, float czk);
	void accMenu();
	virtual void transfer() override;
	virtual void exchange() override;
};