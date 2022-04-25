#include <iostream>
#include <string>
using namespace std;

// Using "Visual Studio version 2022" with the latest update
// Please:
//	leave a LOT of comments (we will submit a less-commenty version later)
//	name things in the camel-case way with very discriptive names even if they are long


// FUNCTIONS prototypes
// DINA
void editInfo();

// ABO
void findDoctor(string patientName);
void timeFilter();
void majorFilter(string patientName);

// Safa
void viewAppointments();
void editPatientInfo();

// Seif
void addAppointment();
void editAppointment();
void deleteAppointments();
void clearAppointments();

// MALAK
void addAbailableTime(string doctorName);



// STRUCTS
struct dateStruct
{
	int day = 0,
		month = 0,
		year = 2022;
};

struct timeStruct
{
	dateStruct date;
	int hour = 0, minute = 0;
};

struct appointment
{
	string patientName, doctorName;
	timeStruct time;
};

struct patient
{
	string name, password;
	dateStruct DOB;
	appointment appointments[20];
};

struct doctor
{
	string name, password, major;

	// 168 half hour a week (0 -> not available || 1 -> avaialble || 2 -> reserved)
	short int weekBlocks[168] = { 0 };  // all zeroes by default
	appointment appointments[20];
	timeStruct availableTime[14];  // start & end of his/her abailable time for a week
} drAli;


int main() {

	char ans;
	cout << "------------ Welcome om E7gezly ------------\n";

	// GEHAD : (SIGN UP OR LOG IN)
	cout << " as a doctor or patient?";
	cin >> ans;
	if (ans == 'd' || ans == 'D') {
		cout << "1. Edit available time" << endl              // MALAK
			<< "2. Display your appointments" << endl     // MAYAR
			<< "3. Edit you info" << endl;                    // DINA

		char service;
		cin >> service;
		string order;

		do {
			// Edit available time
			if (service == '1') {
				timeStruct change;

				// Obtain the old appointment
				cout << "Enter the old appointment you want to change: date(day month year), hour, minute\n";
				cin >> change.date.day >> change.date.month >> change.date.year >> change.hour >> change.minute;

				// loop over this doctor's appointments to find the old one
				for (int i = 0; i < 20;) {
					// if you found it
					if (
						(change.date.day == drAli.appointments[i].time.date.day) &&
						(change.date.month == drAli.appointments[i].time.date.month) &&
						(change.date.year == drAli.appointments[i].time.date.year) &&
						(change.hour == drAli.appointments[i].time.hour) &&
						(change.minute == drAli.appointments[i].time.minute)
						) {
						// take the updated appointment
						cout << "Please write the new time date(day month year), hour, minute\n";
						cin >> change.date.day >> change.date.month >> change.date.year >> change.hour >> change.minute;
					}
				}
			}

			// Display your appointments
			else if (service == '2') {
				cout << "------------ appointments of dr." << drAli.name << " ------------\n";
				for (int i = 0; i < 20; i++) {
					cout << "patient name : " << drAli.appointments[i].patientName
						<< "\ntime : "
						<< drAli.appointments[i].time.date.day
						<< drAli.appointments[i].time.date.month
						<< drAli.appointments[i].time.date.year
						<< drAli.appointments[i].time.hour
						<< drAli.appointments[i].time.minute << endl;
				}
			}

			// Edit you info
			else if (service == '3') {
				editInfo();  // DINA
			}

			// Another Operation ?
			cout << "have a nice day dr." << drAli.name << endl
				<< "1. Go back to the main menu? ( h / H / home )";
			cin >> order;

			// GEHAD, make it case-insensetive checking ,please
		} while (order == "h" || order == "H" || order == "home" || order == "Home");

	}
	else if (ans == 'p' || ans == 'P') {

	}


	return 0;
}

void findDoctor(string patientName) {
	cout << "Search by :\n1.Major\n2. Major & Available Time\n";
	char response;
	cin >> response;
	if (response == '1') {
		majorFilter(patientName);
	}
}

void addAbailableTime(doctor doctor) {
	// which day to set its available time ?
	cout << "Abailable Time: \nDay: ";
	cin >> doctor.availableTime[0].date.day;
	// the start & end of your available time are in the same day
	doctor.availableTime[1].date.day = doctor.availableTime[0].date.day;

	// in that day your are available from .. to ..
	cout << "From: (use blocks of hours or half hours)";
	cin >> doctor.availableTime[0].hour;
	cout << "To: (use blocks of hours or half hours)";
	cin >> doctor.availableTime[1].hour;
}
