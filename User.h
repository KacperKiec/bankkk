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

class User {
public:
	struct currency // klasa zagnie¿d¿ona
	{
	public:
		string name;
		float value;
	};
	
public:
	virtual void transfer() = 0;
	virtual void exchange() = 0;
	virtual void clearScreen() = 0;
};

class LoggedUser : public User {
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
	LoggedUser(int id, string login, int accountNumber, string firstName, string lastName, float pln, float eur, float usd, float gbp, float czk);

	friend void registration();
	friend void forgotPassword();
	friend LoggedUser* signIn();
	friend void loginMenu();

	void accMenu();

	virtual void clearScreen() override;
	virtual void transfer() override;
	virtual void exchange() override;
};