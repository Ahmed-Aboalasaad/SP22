
#include <iostream>
#include <string>
using namespace std;

// Using "Visual Studio version 2022" with the latest update
// Please:
//	leave a LOT of comments (we will submit a less-commenty version later)
//	name things in the camel-case way with very discriptive names even if they are long



// STRUCTS
struct dateStruct
{
	int day = 0,
		month = 0,
		year = 2022;
};

struct timeStruct
{
	bool Available = true;
	dateStruct date;
	int hour = 0, minute = 0;
}change;

struct appointment
{
	string patientName, doctorName;
	timeStruct time;
};

struct patient
{
	string name, password;
	dateStruct DOB;
	appointment Pappointments[20];
};

struct doctor
{
	string name, password, major;
	appointment DRappointments[20];
	timeStruct availableTime[20];
};



// FUNCTIONS prototypes

void doctorMenu(doctor darr[], int j);
void patientMenu();

// DINA
void editInfo(doctor darr[], int j);

// ABO
void findDoctor();
void timeFilter();
void majorFilter();

// Safa
void viewAppointments();
void editPatientInfo();

// Seif
void addAppointment();
void editAppointment();
void deleteAppointments();
void clearAppointments();


//MAYAR
void editAvailableTime(doctor darr[], int j);
void displayDoctorAppointment(doctor darr[], int j);


//MALK
void AddAvailableTime(doctor darr[], int j);
void RemoveAvailabeTime(doctor darr[], int j);




int main() {
	doctor Darr[50];
	patient Parr[50];
	char ans;
	cout << "------------ Welcome om E7gezly ------------\n";

	// GEHAD : (SIGN UP OR LOG IN)

	int i = 10;               	//just a sample to work with , this part will be done in GEHAD'S part
	Darr[i].name = "Malk";     	//just a sample to work with , this part will be done in GEHAD'S part
	         
	cout << " as a doctor or patient?";
	cin >> ans;
	if (ans == 'd' || ans == 'D') 
	{
		 doctorMenu(Darr,i);

	}
	else if (ans == 'p' || ans == 'P')
	{
		 patientMenu();
	}


	return 0;
}
void doctorMenu(doctor darr[],int j)
{

		cout << "1. Edit available time" << endl              // MAYAR
			<< "2. Add available time" << endl                   //MALK
			<< "3. Remove available time" << endl                //MALK
			<< "4. Display your appointments" << endl     // MAYAR
			<< "5. Edit you info" << endl;                    // DINA

		char service;
		cin >> service;
		string order;

		do {
			// Edit available time
			if (service == '1')
			{

				 editAvailableTime(darr,j);
			}
			//Add available time
			else if (service == '2')
			{
				 AddAvailableTime(darr, j);  //MAlk
			}
			//Remove availble time
			else if (service == '3')
			{
				 RemoveAvailabeTime(darr, j);  //MAlk
			}

			// Display your appointments
			else if (service == '4')
			{
				 displayDoctorAppointment(darr,j);
			}

			// Edit you info
			else if (service == '5')
			{
				editInfo(darr, j);  // DINA
			}
			else
			{
				cout << "Invalid choice please try again!\n";
				continue;
			}


			// Another Operation ?
			cout << "have a nice day dr." << darr[j].name << endl
				<< "1. Go back to the main menu? ( h / H / home )";
			cin >> order;

			// GEHAD, make it case-insensetive checking ,please
		} while (order == "h" || order == "H" || order == "home" || order == "Home");

		cout << "Thank you for using our system, have a nice day doctor " << darr[j].name << ":)\n";


}


void editAvailableTime(doctor darr[], int j)
{

	// Obtain the old appointment
	cout << "Please enter the old appointment you want to change: date(day month year), hour, minute\n";
	cin >> change.date.day >> change.date.month >> change.date.year >> change.hour >> change.minute;

	// loop over this doctor's appointments to find the old one
	for (int i = 0; i < 20; i++) 
	{
		// if you found it
		if (
			(change.date.day == darr[j].DRappointments[i].time.date.day) &&
			(change.date.month == darr[j].DRappointments[i].time.date.month) &&
			(change.date.year == darr[j].DRappointments[i].time.date.year) &&
			(change.hour == darr[j].DRappointments[i].time.hour) &&
			(change.minute == darr[j].DRappointments[i].time.minute)
			)
		{
			//if that time wasn't booked by any patient
			if (darr[j].DRappointments[i].time.Available ==true)
			{
				// take the updated appointment
				cout << "Please write the new time date(day month year), hour, minute\n";
				cin >> darr[j].DRappointments[i].time.date.day >> darr[j].DRappointments[i].time.date.month >> darr[j].DRappointments[i].time.date.year >> darr[j].DRappointments[i].time.hour >> darr[j].DRappointments[i].time.minute;
			}
			else
				cout << "This time had been booked by a patient please choose another time to change";
		}
	}
}


void addAvailableTime(doctor darr[], int j)
{
	char another = 'y';
	int sure;
	cout << "\t\t\t\t------------------------\n\t\t\twelcome\n to *add* a new available time just follow the following instructions\n";
	do
	{
		for (int i = 0; i < 20; i++)
		{

			cout << "write the information of the available time you want to add:\n " <<
				"write \t\t for\n 1\t\tSaturday\n 2\t\tSunday\n 3\t\tMonday\n 4\t\t Tuesday\n 5\t\t Wednesday\n 6\t\tThursday\n 7\t\t Friday\n";
			cout << "Choose the day\n";
			cin >> darr[j].availableTime[i].date.day;
			cout << "enter the month (1 to 12)";
			cin >> darr[j].availableTime[i].date.month;
			cout << "enter the hour (0 to 23)";
			cin >> darr[j].availableTime[i].hour;
			cout << "enter the minute (0 to 59)";
			cin >> darr[j].availableTime[i].minute;

		}
		cout << "The operation done successfully :D\n";


		cout << "\nDo you want to do another operation? (y/Y for yes && any key to stop)\n";
		cin >> another;
	} while (another == 'y' || another == 'Y');
}


void RemoveAvailabeTime(doctor darr[], int j)
{
	char another = 'y';
	int sure;
	cout << "\t\t\t\t------------------------\n\t\t\twelcome\n to *delete* a new available time just follow the following instructions\n";
	do
	{
		for (int i = 0; i < 20; i++)
		{
			cout << "write the information of the available time you want to delete:\n " <<
				"write \t\t for\n 1\t\tSaturday\n 2\t\tSunday\n 3\t\tMonday\n 4\t\t Tuesday\n 5\t\t Wednesday\n 6\t\tThursday\n 7\t\t Friday\n";
			cout << "Choose the day\n";
			cin >> darr[j].availableTime[i].date.day;
			cout << "enter the month (1 to 12)";
			cin >> darr[j].availableTime[i].date.month;
			cout << "enter the hour (0 to 23)";
			cin >> darr[j].availableTime[i].hour;
			cout << "enter the minute (0 to 59)";
			cin >> darr[j].availableTime[i].minute;
		}
		cout << "The operation done successfully :D\n";

		cout << "\nDo you want to do another operation? (y/Y for yes && any key to stop)\n";
		cin >> another;
	} while (another == 'y' || another == 'Y');
}


void displayDoctorAppointment(doctor darr[], int j)
{

	cout << "------------ appointments of dr." << darr[j].name << " ------------\n";
	for (int i = 0; i < 20; i++)
	{
		cout << "patient name : " << darr[j].DRappointments[i].patientName
			<< "\n Appointment date: "
			<< darr[j].DRappointments[i].time.date.day << "/"
			<< darr[j].DRappointments[i].time.date.month << "/"
			<< darr[j].DRappointments[i].time.date.year << endl
			<< "Appointment time:"
			<< darr[j].DRappointments[i].time.hour << ":"
			<< darr[j].DRappointments[i].time.minute << endl;
	}


}
