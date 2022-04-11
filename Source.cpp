#include <iostream>
#include <string>
using namespace std;

// Using "Visual Studio version 2022" with the latest update
// Please:
//	leave a LOT of comments (we will submit a less-commenty version later)
//	name things in the camel-case way with very discriptive names even if they are long


// FUNCTIONS prototypes


// STRUCTS
struct dateStruct
{
	int day, month, year;
};

struct timeStruct
{
	dateStruct date;
	int hour, minute;
};

struct patient
{
	string name, password;
	dateStruct DOB;
} patients[50];

struct doctor
{
	string name, password;
	timeStruct appointments[20];
} drAli;

struct appointment
{
	string patientName, doctorName;
	timeStruct time;
} appointments[50];

int main() {

	char ans;
	cout << "------------ Welcome om E7gezly ------------";

	// GEHAD : (SIGN UP OR LOG IN)
	cout << " as a doctor or patient?";
	cin >> ans;
	if (ans == 'd' || 'D')
	{
		cout << "1. Edit available time" << endl              // MALAK
			 << "2. Display the your appointments" << endl     // MAYAR
			 << "3. Edit you info" << endl;                    // DINA

		char service;
		cin >> service;
		if (service == '1') {
			timeStruct change;

			// Obtain the old appointment
			cout << "Enter the time you want to change date(day month year), hour, minute";
			cin >> change.date.day >> change.date.month >> change.date.year >> change.hour >> change.minute;

			// loop over this doctor's appointments to find the old one
			for (int i = 0; i < 20;) {
				// if you found it
				if (
						(change.date.day == drAli.appointments[i].date.day) &&
						(change.date.month == drAli.appointments[i].date.month) &&
						(change.date.year == drAli.appointments[i].date.year) &&
						(change.hour == drAli.appointments[i].hour) &&
						(change.minute == drAli.appointments[i].minute)
					) {
					// take the updated appointment
					cout << "Please write the new time date(day month year), hour, minute\n";
					cin >> change.date.day >> change.date.month >> change.date.year >> change.hour >> change.minute;
				}
			}
		}
		else if (service == '2') {
			// Loop over all the appointments
			for (int i = 0; i < 50; i++) {
				// if the doctor name of one of them was the same as the logged in doctor
				if (appointments[i].doctorName == drAli.name) {
					cout << "patient name : " << patients[i].name << "\t"
						 << "appointment day : " << patients[i].appointment.date << "\t" << "the patient time:" << arrP[i].reservation.hours << ":" << arrP[i].reservation.minutes << endl;
				}
			}
		}
		
	return 0;
}
