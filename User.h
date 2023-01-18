#include <string>
#include <array>
#include <iostream>
#include <vector>
#include <string.h>
#include <fstream>
#include <random>
#include <time.h>

using namespace std;

void clearScreen();
void loginMenu();
void signIn();
void registration();
void forgotPassword();

class User {
public:
	struct currency
	{
	public:
		string name;
		double value;
	};

public:
	friend void registration();
	friend void forgotPassword();
	friend void signIn();
	friend void loginMenu();
	virtual void transfer(); //itd
};

class loggedUser : public User {
private:
	int id;
	int accountNumber;
	string login;
	string firstName;
	string lastName;
	array<currency, 5> account;

public:
	loggedUser(int id, string login, int accountNumber, string firstName, string lastName, int pln, int eur, int usd, int gbp, int czk);
	int getId();
	string getFullName();
	currency getCurrency(int index);
	void accMenu();
	void transfer();
};