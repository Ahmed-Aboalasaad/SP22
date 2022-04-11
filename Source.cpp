#include <iostream>
#include <string>
using namespace std;

// Using "Visual Studio version 2022" with the latest update
// Please:
//	leave a LOT of comments (we will submit a less-commenty version later)
//	name things in the camel-case way

// FUNCTIONS prototypes


// STRUCTS
struct dateOfBirth
{
	int day, month, year;
};

struct patient
{
	string username, password;
	dateOfBirth DOB;
};

int main() {

	//------------------------------------------------------------------------------//
	// Storing Hub (usernames, passwords, history, ...)
	string usernames = {}, passwords{};
	int sizeOfUsernames = sizeof(usernames) / sizeof(usernames[0]),
		sizeOfPasswords = sizeof(passwords) / sizeof(passwords[0]);
	//------------------------------------------------------------------------------//


	//------------------------------------------------------------------------------//
	// Write The Log In Code Here
	string nameHolder = "", passHOlder = "";
	cout << "User Name: ";
	cin >> nameHolder >> passHOlder;

	for (int i = 0; i < sizeOfUsernames; i++) {
		if (nameHolder == usernames[i]) {
			cout << "Beeb Boob!" << endl << "Welcome ," << usernames[i] << endl;
		}
	}
	//------------------------------------------------------------------------------//
	return 0;
}