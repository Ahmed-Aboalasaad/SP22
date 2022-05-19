/*   Suggestions
once a patient takes an appointment, the doctor can't change it
every major has a time for the appointment
ascii intro
all dynamic arrays
a function to generate random data to the files
*/

#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
using namespace std;
using std::ifstream;

// Constants
#define doctorLimit 50
#define patientLimit 50

// STRUCTS
struct dateStruct
{
	string day = "0", month = "0", year = "2022";
};
struct timeStruct
{
	string Available = "true";
	dateStruct date;
	string hour = "0", minute = "0";
};
struct appointment
{
	string patientName, doctorName;
	timeStruct time;
};
struct patient
{
	string name = "0", password;
	dateStruct DOB;  // we want to change it to be just the age
	appointment appointments[20];
};
struct doctor
{
	string name = "0", password, major;
	appointment appointments[20];
	timeStruct availableTime[20];
};

// FUNCTIONS prototypes
// Gehad
void logInDoctor(doctor darr[], patient parr[]);
void log_in_patient(patient parr[], doctor darr[]);
void account_patient(patient parr[], doctor darr[]);
void sign_up_patient(patient parr[], doctor darr[]);
void accountDoctor(doctor darr[], patient parr[]);
void signUpDoctor(doctor darr[], patient parr[]);
void start(doctor darr[], patient parr[]);

// DINA
void editDoctorInfo(doctor darr[], int doctorIndex, patient parr[]);
void saveDoctorData(doctor darr[]);
void savePatientData(patient parr[]);

// Ahmed Aboalasaad
void findDoctor(doctor darr[], patient parr[], int patientIndex);
void timeFilter(doctor darr[], patient parr[], int patientIndex, int* result, int resultSize);
void loadDoctorFile(doctor darr[]);
void loadPatientFile(patient parr[]);
void patientMenu(patient parr[], doctor darr[], int patientIndex);


// Safa
void displayPatientAppointments(patient Parr[], int patienIndex);
void editPatientInfo(patient parr[], doctor darr[], int patientIndex);
void clearAppointments(patient Parr[], int patienIndex);

// Seif
void addAppointment(doctor darr[], patient parr[], int patientIndex, int docIndex);
void addAppointment(doctor darr[], patient parr[], int patientIndex, int docIndex, timeStruct timeHolder);
void editAppointment(doctor darr[], patient parr[], int patientIndex);
void deleteAppointments(doctor darr[], patient parr[], int patientIndex);

// Mayar & Malk
void doctorMenu(doctor darr[], int doctorIndex, patient parr[]);

//MAYAR
void editAvailableTime(doctor darr[], int doctorIndex, patient parr[]);
void displayDoctorAppointment(doctor darr[], int doctorIndex);

//MALK
void AddAvailableTime(doctor darr[], int doctorIndex, patient parr[]);
void RemoveAvailabeTime(doctor darr[], int doctorIndex, patient parr[]);

//------------------------------------------------------------------------------
int main() {

	// big arrays for everything
	doctor darr[doctorLimit];
	patient parr[patientLimit];

	// loading data
	loadDoctorFile(darr);
	loadPatientFile(parr);

	// start the interface & services
	string again;
	do {
		start(darr, parr);
		cout << "Quit & Save ?";
		cin >> again;
	} while (again == "no" || again == "No" || again == "n" || again == "N");

	// Saving data
	saveDoctorData(darr);
	savePatientData(parr);

	return 0;
} // END MAIN

// Files
void loadDoctorFile(doctor darr[]) {
	// I'll take input from a file (input file stream) & I'll use readf
	// readf is an input object. it has methods(functions)
	// .. you don't have to fully understand it
	ifstream readf;

	// open the file
	readf.open("doctors.txt");

	// if it was open successfully ..
	if (readf) {
		// read as long as it's not the end of the file
		while (!readf.eof()) {
			// getine() takes 2 parameters: the cin object and the string variable(where to store it)
			// it has one downside : it only reads strings
			// this for loop iterates over the doctors
			for (int i = 0; i < doctorLimit; i++) {
				getline(readf, darr[i].name);
				getline(readf, darr[i].password);
				getline(readf, darr[i].major);
				// this loop reads the appointments array
				for (int j = 0; j < 20; j++) {
					getline(readf, darr[i].appointments[j].doctorName);
					getline(readf, darr[i].appointments[j].patientName);
					getline(readf, darr[i].appointments[j].time.Available);
					getline(readf, darr[i].appointments[j].time.hour);
					getline(readf, darr[i].appointments[j].time.minute);
					getline(readf, darr[i].appointments[j].time.date.day);
					getline(readf, darr[i].appointments[j].time.date.month);
					getline(readf, darr[i].appointments[j].time.date.year);
				}
				// this loop reads the availableTime array
				for (int j = 0; j < 20; j++) {
					getline(readf, darr[i].appointments[j].time.Available);
					getline(readf, darr[i].appointments[j].time.hour);
					getline(readf, darr[i].appointments[j].time.minute);
					getline(readf, darr[i].appointments[j].time.date.day);
					getline(readf, darr[i].appointments[j].time.date.month);
					getline(readf, darr[i].appointments[j].time.date.year);
				}
			}
		}
	}
	else { // else it's not opened so display this error
		cout << "Error .. (file couldn't be opened) (was trying loadDoctorFile)\n";
	}
	readf.close();
}
void loadPatientFile(patient parr[]) {
	// I'll take input from a file (input file stream) & I'll use readf
	// readf is an input object. it has methods(functions)
	// .. you don't have to fully understand it
	ifstream readf;

	// open the file
	readf.open("patients.txt");

	// if it was opened successfully ..
	if (readf) {
		// read as long as it's not the end of the file
		while (!readf.eof()) {
			// getine() takes 2 parameters: the cin object and the string variable(where to store it)
			// it has one downside : it only reads strings
			// this for loop iterates over the patients
			for (int i = 0; i < 3; i++) {
				getline(readf, parr[i].name);
				getline(readf, parr[i].password);
				// read the date of birth
				getline(readf, parr[i].DOB.day);
				getline(readf, parr[i].DOB.month);
				getline(readf, parr[i].DOB.year);
				// read the appointments array
				for (int j = 0; j < 3; j++) {
					getline(readf, parr[i].appointments[j].doctorName);
					getline(readf, parr[i].appointments[j].patientName);
					getline(readf, parr[i].appointments[j].time.Available);
					getline(readf, parr[i].appointments[j].time.hour);
					getline(readf, parr[i].appointments[j].time.minute);
					getline(readf, parr[i].appointments[j].time.date.day);
					getline(readf, parr[i].appointments[j].time.date.month);
					getline(readf, parr[i].appointments[j].time.date.year);
				}
			}
		}
	}
	else { // else it's not opened so display this error
		cout << "Error .. (file couldn't be opened) (was trying loadPatientFile)\n";
	}
	readf.close();
}
void saveDoctorData(doctor darr[]) {
	// I'll take input from a struct & I'll use ofstream 
	// ofstram is ofstream This data type represents the 
	// output file stream and is used to create files 
	// and to write information to files.
	// .. you don't have to fully understand it
	ofstream doctorFile;

	// open the file
	doctorFile.open("doctors.txt");


	if (doctorFile) {
		// to write to a file we use "<<" as the cout

	   // this for loop iterates over the doctors
		for (int i = 0; i < doctorLimit; i++) {
			doctorFile << darr[i].name << endl;
			doctorFile << darr[i].password << endl;
			doctorFile << darr[i].major << endl;


			// this loop iterate over the appointments array
			for (int j = 0; j < 20; j++) {
				doctorFile << darr[i].appointments[j].doctorName << endl;
				doctorFile << darr[i].appointments[j].patientName << endl;
				doctorFile << darr[i].appointments[j].time.Available << endl;
				doctorFile << darr[i].appointments[j].time.hour << endl;
				doctorFile << darr[i].appointments[j].time.minute << endl;
				doctorFile << darr[i].appointments[j].time.date.day << endl;
				doctorFile << darr[i].appointments[j].time.date.month << endl;
				doctorFile << darr[i].appointments[j].time.date.year << endl;
			}


			// his loop iterate over available time array
			for (int j = 0; j < 20; j++) {
				doctorFile << darr[i].appointments[j].time.Available << endl;
				doctorFile << darr[i].appointments[j].time.hour << endl;
				doctorFile << darr[i].appointments[j].time.minute << endl;
				doctorFile << darr[i].appointments[j].time.date.day << endl;
				doctorFile << darr[i].appointments[j].time.date.month << endl;
				doctorFile << darr[i].appointments[j].time.date.year << endl;
			}
		}

		// close the file stream
		doctorFile.close();
	}
	else {
		cout << "This file can't be open" << endl;
	}

}
void savePatientData(patient parr[]) {
	// I'll take input from a struct & I'll use ofstream 
	// ofstram is ofstream This data type represents the 
	// output file stream and is used to create files 
	// and to write information to files.
	// .. you don't have to fully understand it
	ofstream patientFile;


	// open the file
	patientFile.open("patients.txt");

	// to write to a file we use "<<" as the cout
	if (patientFile) {

		// this for loop iterates over the patient
		for (int i = 0; i < patientLimit; i++) {
			patientFile << parr[i].name << endl;
			patientFile << parr[i].password << endl;

			// read the date of birth

			patientFile << parr[i].DOB.day << endl;
			patientFile << parr[i].DOB.month << endl;
			patientFile << parr[i].DOB.year << endl;


			// read the appointments array
			for (int j = 0; j < patientLimit; j++) {
				patientFile << parr[i].appointments[j].doctorName << endl;
				patientFile << parr[i].appointments[j].patientName << endl;
				patientFile << parr[i].appointments[j].time.Available << endl;
				patientFile << parr[i].appointments[j].time.hour << endl;
				patientFile << parr[i].appointments[j].time.minute << endl;
				patientFile << parr[i].appointments[j].time.date.day << endl;
				patientFile << parr[i].appointments[j].time.date.month << endl;
				patientFile << parr[i].appointments[j].time.date.year << endl;
			}

		}

		// close the file stream
		patientFile.close();
	}
	else {
		cout << "This file can't be open" << endl;
	}
}
// Menu
void doctorMenu(doctor darr[], int doctorIndex, patient parr[])
{
	cout << "\t\tWelcome Doctor." << darr[doctorIndex].name << " :)\n";

	char service;
	int order = -1;

	do {
		cout << "1. Edit available time" << endl              // MAYAR
			<< "2. Add available time" << endl                   //MALK
			<< "3. Remove available time" << endl                //MALK
			<< "4. Display your appointments" << endl     // MAYAR
			<< "5. Edit your info" << endl                    // DINA
			<< "6. Log Out" << endl;

		cin >> service;

		// Edit available time
		if (service == '1') {
			editAvailableTime(darr, doctorIndex, parr);
		}
		//Add available time
		else if (service == '2') {
			AddAvailableTime(darr, doctorIndex, parr);  //MAlk
		}
		//Remove availble time
		else if (service == '3') {
			RemoveAvailabeTime(darr, doctorIndex, parr);  //MAlk
		}

		// Display your appointments
		else if (service == '4') {
			displayDoctorAppointment(darr, doctorIndex);
		}

		// Edit you info
		else if (service == '5') {
			editDoctorInfo(darr, doctorIndex, parr);  // DINA
		}
		// Log out
		else if (service == '6') {
			return;
		}
		else {
			cout << "Invalid choice please try again!\n";
			continue;
		}


		// Another Operation ?
		cout << "1. Another operation\n2. Log Out\n";
		cin >> order;
		if (order == 2)
			start(darr, parr); //add parr!!!

	} while (order == 1);
}
void patientMenu(patient parr[], doctor darr[], int patientIndex) {  // parr -> array of patients & i -> index in that array
	// which service ?

	cout << "\t\tWelcome " << parr[patientIndex].name << " :)\n";

	char service, appointmentService;
	int order = 1;

	do {
		cout << "1. Find a doctor" << endl     // Abo
			<< "2. your appointments" << endl  // Mohamed displays and clears history & Seif edits
			<< "3. Edit your Info" << endl;    // Mohamed
		cin >> service;

		if (service == '1')
			findDoctor(darr, parr, patientIndex);

		else if (service == '2') {

			cout << "1. Display appointments" << endl
				<< "2. Edit appointments" << endl
				<< "3. Cancel appointments" << endl
				<< "4. clear all appointments" << endl;
			cin >> appointmentService;

			if (appointmentService == '1') {
				displayPatientAppointments(parr, patientIndex);
			}
			else if (appointmentService == '2') {
				editAppointment(darr, parr, patientIndex);
			}
			else if (appointmentService == '3') {
				deleteAppointments(darr, parr, patientIndex);
			}
			else if (appointmentService == '4') {
				clearAppointments(parr, patientIndex);
			}
			else {
				cout << "Invaild choice please try again!\n";
				continue;
			}


		}
		else if (service == '3')
			editPatientInfo(parr, darr, patientIndex);

		else {
			cout << "Invalid choice please try again!\n";
			continue;
		}


		// Another Operation ?
		cout << "1.Another operation\n2.Logout\n\n";
		cin >> order;
		if (order == 2)
			start(darr, parr);

		// GEHAD, make it case-insensetive checking ,please
	} while (order == 1);
}
// Doctor
void editAvailableTime(doctor darr[], int doctorIndex, patient parr[])
{
	cout << "\t\t\t\t------------------------\n\t\t\twelcome\n to (edit) an available time just follow the following instructions\n";

	bool availableTimeExist = false;
	// view the old available times 
	for (int i = 0; i < 20; i++)
	{
		if (darr[doctorIndex].availableTime[i].Available == "true" && darr[doctorIndex].availableTime[i].date.day != "0")
		{
			availableTimeExist = true;
			cout << "\n Available date: "
				<< darr[doctorIndex].availableTime[i].date.day << "/"
				<< darr[doctorIndex].availableTime[i].date.month << "/"
				<< darr[doctorIndex].availableTime[i].date.year
				<< "\n time -> "
				<< darr[doctorIndex].availableTime[i].hour << ":"
				<< darr[doctorIndex].availableTime[i].minute << endl;
		}
	}
	if (!availableTimeExist) {
		cout << "There is no available time to work in\n";
		return;
	}

	timeStruct change;
	char again;
	// Obtain the old appointment
	do
	{
		cout << "\nPlease enter the old appointment you want to change: date(day month), hour, minute\n";
		cin >> change.date.day >> change.date.month >> change.hour >> change.minute;

		int switcher = -1;
		// loop over this doctor's appointments to find the old one
		for (int i = 0; i < 20; i++)
		{
			// if you found it
			if (
				(change.date.day == darr[doctorIndex].availableTime[i].date.day) &&
				(change.date.month == darr[doctorIndex].availableTime[i].date.month) &&
				(change.hour == darr[doctorIndex].availableTime[i].hour) &&
				(change.minute == darr[doctorIndex].availableTime[i].minute)
				) {
				switcher = 0;
				//if that time wasn't booked by any patient
				if (darr[doctorIndex].appointments[i].time.Available == "true") {
					switcher = 2;
					// take the updated appointment
					cout << "Please write the new time date(day month), hour, minute\n";
					cin >> darr[doctorIndex].availableTime[i].date.day
						>> darr[doctorIndex].availableTime[i].date.month
						>> darr[doctorIndex].availableTime[i].hour
						>> darr[doctorIndex].availableTime[i].minute;
				}
			}
		}
		if (switcher == -1) {
			cout << "This time doesn't exist please choose another one!!\n";
		}
		else if (switcher == 0) {
			cout << "This time had been booked by a patient. You can't change it. \nPlease choose another time to change\n";
		}



		cout << "Do you want to edit another time? (y/Y for yes)  ";
		cin >> again;
	} while (again == 'y' || again == 'Y');
}
void AddAvailableTime(doctor darr[], int doctorIndex, patient parr[])
{
	char another = 'y';
	cout << "\t\t\t\t------------------------\n\t\t\twelcome\n to (add) a new available time just follow the following instructions\n";
	doctor holder;

	do
	{
		cout << "write the information of the available time you want to add:\n ";
		cout << "Choose the day (1 to 30) ";
		cin >> holder.availableTime[0].date.day;
		cout << "enter the month (1 to 12) ";
		cin >> holder.availableTime[0].date.month;
		cout << "enter the hour (0 to 23) ";
		cin >> holder.availableTime[0].hour;
		cout << "enter the minute (0 to 59) ";
		cin >> holder.availableTime[0].minute;

		for (int i = 0; i < 20; i++)
		{
			if (
				holder.availableTime[0].date.day == darr[doctorIndex].availableTime[i].date.day
				&& holder.availableTime[0].date.month == darr[doctorIndex].availableTime[i].date.month
				&& holder.availableTime[0].hour == darr[doctorIndex].availableTime[i].hour
				&& holder.availableTime[0].minute == darr[doctorIndex].availableTime[i].minute
				)
				cout << "This time exists before!!\n";

			else
			{
				if (darr[doctorIndex].availableTime[i].date.day == "0")
				{
					darr[doctorIndex].availableTime[i].date.day = holder.availableTime[0].date.day;
					darr[doctorIndex].availableTime[i].date.month = holder.availableTime[0].date.month;
					darr[doctorIndex].availableTime[i].hour = holder.availableTime[0].hour;
					darr[doctorIndex].availableTime[i].minute = holder.availableTime[0].minute;
					cout << "The operation done successfully :D\n";
					break;
				}
				else
					continue;
			}
		}


		cout << "\nDo you want to add another time? (y/Y for yes && any key to stop)\n";
		cin >> another;
	} while (another == 'y' || another == 'Y');
	doctorMenu(darr, doctorIndex, parr);
}
void RemoveAvailabeTime(doctor darr[], int doctorIndex, patient parr[])
{
	timeStruct Delete;
	char another = 'y';
	int check = 1;
	cout << "\t\t\t\t------------------------\n\t\t\twelcome\n to *delete* a new available time just follow the following instructions\n";
	do {
		// view the old available times 
		bool availableTimeExist = false;
		for (int i = 0; i < 20; i++) {
			if (darr[doctorIndex].availableTime[i].Available == "true" && darr[doctorIndex].availableTime[i].date.day != "0") {
				availableTimeExist = true;
				cout << "\n Available date: "
					<< darr[doctorIndex].availableTime[i].date.day << "/"
					<< darr[doctorIndex].availableTime[i].date.month << "/"
					<< darr[doctorIndex].availableTime[i].date.year
					<< "\Available time:"
					<< darr[doctorIndex].availableTime[i].hour << ":"
					<< darr[doctorIndex].availableTime[i].minute << endl;

			}
		}
		if (!availableTimeExist) {
			cout << "There is no available time to work in\n";
			return;
		}

		// take the time which is wanted to delete
		cout << "write the information of the available time you want to delete:\n ";
		cout << "Choose the day(1 to 30)";
		cin >> Delete.date.day;
		cout << "enter the month (1 to 12)";
		cin >> Delete.date.month;
		cout << "enter the hour (0 to 23)";
		cin >> Delete.hour;
		cout << "enter the minute (0 to 59)";
		cin >> Delete.minute;

		// 
		int switcher = -1;
		for (int i = 0; i < 20; i++)
		{
			// if you found it
			if (
				(Delete.date.day == darr[doctorIndex].availableTime[i].date.day) &&
				(Delete.date.month == darr[doctorIndex].availableTime[i].date.month) &&
				(Delete.hour == darr[doctorIndex].availableTime[i].hour) &&
				(Delete.minute == darr[doctorIndex].availableTime[i].minute)
				) {
				switcher = 0;
				//if that time wasn't booked by any patient
				if (darr[doctorIndex].appointments[i].time.Available == "true") {
					switcher = 2;
					darr[doctorIndex].availableTime[i].date.day = "0";
					darr[doctorIndex].availableTime[i].date.month = "0";
					darr[doctorIndex].availableTime[i].hour = "0";
					darr[doctorIndex].availableTime[i].minute = "0";
				}
			}
			if (switcher == -1) {  // not found
				cout << "This time doesn't exist please choose another one!!\n";
			}
			else if (switcher == 0) { // found and booked
				cout << "This time had been booked by a patient. You can't change it. \nPlease choose another time to change\n";
			}
		}

		cout << "\nDo you want to delete another time? (y/Y for yes && any key to stop)\n";
		cin >> another;

	} while (another == 'y' || another == 'Y');
}
void displayDoctorAppointment(doctor darr[], int doctorIndex)
{
	cout << "------------ appointments of dr." << darr[doctorIndex].name << " ------------\n";
	bool exist = false;
	for (int i = 0; i < 20; i++)
	{
		if (darr[doctorIndex].availableTime[i].Available == "false" || darr[doctorIndex].appointments[i].time.date.day != "0") {
			exist = true;
			cout << "patient name : " << darr[doctorIndex].appointments[i].patientName
				<< "\nAppointment date:"
				<< darr[doctorIndex].appointments[i].time.date.day << "/"
				<< darr[doctorIndex].appointments[i].time.date.month << "/"
				<< darr[doctorIndex].appointments[i].time.date.year << endl
				<< "Appointment time:"
				<< darr[doctorIndex].appointments[i].time.hour << ":"
				<< darr[doctorIndex].appointments[i].time.minute << endl;
		}
	}
	if (!exist) {
		cout << "No appointments to show \n";
	}
}
void editDoctorInfo(doctor darr[], int doctorIndex, patient parr[])
{
	// Variable used to asssign editing the username or password
	int choice;
	string holder;

	cout << "Want to edit your data? We're here for help\n";
	cout << "1.Edit your password" << endl;
	cout << "2.Edit your username" << endl;
	cout << "3.Main menu" << endl;
	cout << "Enter your choice :";
	cin >> choice;

	switch (choice)
	{
	case 1:
	{
		string answer;
		do {
			cout << "Please enter the old password you want to change: \n";
			cin >> holder;


			// if you found it
			if (holder == darr[doctorIndex].password)
			{
				answer = "n";
				cout << "Please write the new password \n";
				cin >> darr[doctorIndex].password;
				cout << "Password Successfully updated \n";
			}
			else
			{
				cout << "This password is not correct!\n Do you want to try again?\n";
				cin >> answer;
			}
		} while (answer == "y" || answer == "Y" || answer == "yes" || answer == "Yes");
		break;
	}

	case 2: // add a do while loop to give the user another chance to enter a name
	{
		bool flag;
		do {
			flag = true;
			cout << "Please write the new username \n";
			cin >> holder;
			for (int i = 0; i < doctorLimit; i++)
			{
				if (holder == darr[i].name)       // <<<<<<<<<<<< edited here.
				{
					cout << "invalid username, try another one \n";
					flag = false;
					break;
				}
			}

			if (flag) {
				cout << "username Successfully updated\n";
				// this assigns the text from the holder to the name array of chars
				darr[doctorIndex].name = holder;
			}
		} while (flag == false);
		break;
	}

	case 3:
	{
		// return to the main minu 
		doctorMenu(darr, doctorIndex, parr);
		break;
	}

	}
}
// Patient (findDoctor() & timeFilter() use pointers and dynamic arrays)
void findDoctor(doctor darr[], patient parr[], int patientIndex) {
	// search by major
	cout << "Choose a Major: \n"
		<< "1. Dentist\t\t\t2. Pediatrician\n"
		<< "3. Internist\t\t\t4. Neurologist\n"
		<< "5. Dermatologist\t\t\t6. Cardiologist\n"
		<< "7. Ophthalmologist\t\t\t8. Otolaryngologist\n"
		<< "9. Orthopedist\t\t\t10. Gynecologist/Obstetrician\n"
		<< "11. Psychologist\n";
	string response, major;
	do {
		cin >> response;
		if (response == "1")
			major = "Dentist";
		else if (response == "2")
			major = "Pediatrician";
		else if (response == "3")
			major = "Internist";
		else if (response == "4")
			major = "Neurologist";
		else if (response == "5")
			major = "Dermatologist";
		else if (response == "6")
			major = "Cardiologist";
		else if (response == "7")
			major = "Ophthalmologist";
		else if (response == "8")
			major = "Otolaryngologist";
		else if (response == "9")
			major = "Orthopedist";
		else if (response == "10")
			major = "Gynecologist/Obstetrician";
		else if (response == "11")
			major = "Psychologist";
		else {
			cout << "Invalid input.. Please try again.";
			response = "repeat";
		}
	} while (response == "repeat");



	// this is a dynamic array that I store the indeces of the
	// search-resultant doctors in
	int* ptr, size = 0;
	ptr = new int[patientLimit]();
	// loop over doctors searching for the desired major
	for (int i = 0; i < patientLimit; i++) {
		if (darr[i].major == major) {
			// store his/her index in the dynamic array
			*(ptr++) = i;
			size++;
		}
	}
	// Now, I have the research result
	ptr -= (size);
	// print it
	for (int i = 0; i < size; i++) {
		cout << i + 1 << ". dr. " << darr[ptr[i]].name << endl; // more details ?
	}



	do {
		cout << "Filter by Available Time? ( y / n )\n";
		cin >> response;
		if (response == "y" || response == "Y" || response == "yes" || response == "Yes") {
			timeFilter(darr, parr, patientIndex, ptr, size);
			break;
		}


		else if (response == "n" || response == "N" || response == "no" || response == "Np") {
			cout << "which doctor do you want to make an appointment with?\n";
			int choice;
			cin >> choice;
			addAppointment(darr, parr, patientIndex, ptr[choice - 1]);
			break;
		}
		else {
			cout << "Invalid input. Please try again!\n";
		}
	} while (true);


	delete[] ptr; // release the memory
	ptr = NULL; // avoid dangling pointers
}
void timeFilter(doctor darr[], patient parr[], int patientIndex, int* result, int resultSize) {
	// what's your desired time for your appointment
	timeStruct timeHolder;
	cout << "You are searching for an appointment :\n";
	cout << "month: ";
	cin >> timeHolder.date.month;
	cout << "day :";
	cin >> timeHolder.date.day;
	cout << "hour :";
	cin >> timeHolder.hour;
	cout << "minute :";
	cin >> timeHolder.minute;

	// compare appointments with the patient's time
	// for every doctor
	for (int i = 0; i < resultSize; i++) {
		// for his appointments
		for (int j = 0; j < 20; j++) { // taking the index of the result array, accessing the doctor with it and compare with the desired time the user gave me
			if (timeHolder.date.month == darr[result[i]].availableTime[j].date.month &&
				timeHolder.date.day == darr[result[i]].availableTime[j].date.day &&
				timeHolder.hour == darr[result[i]].availableTime[j].hour &&
				timeHolder.minute == darr[result[i]].availableTime[j].minute &&
				darr[result[i]].availableTime[j].Available == "true") {
				break;
			}
			result[i] = -1;
		}

	}

	// now, print the doctors any value other than -1
	cout << "\n-------- After Filteration --------\n"
		<< "name\t\tID\n";
	for (int i = 0; i < resultSize; i++) {
		if (result[i] != -1) {
			cout << darr[result[i]].name << "\t\t" << result[i] << endl;
			// alternative solution : make a function to "shift" the rest of the dynamic array
		}
	}
	int doctorID;
	cout << "Enter the ID you chose :";
	cin >> doctorID;

	addAppointment(darr, parr, patientIndex, doctorID, timeHolder);
}
void addAppointment(doctor darr[], patient parr[], int patientIndex, int docIndex) {
	// 1. get number of appointments booked by patient so we can add on an empty index.
	// 2. choose available time.
	// 3. mark it booked.
	// 4. assign that available time to an actual appointment for the patient.
	// 5. assign that available time to an actual appointment for the doctor.


	int counter = -1; // a variable that holds the index of the first empty appoitment
					  //which is equal to the number of booked appointments.
	for (int i = 0; i < 20; i++) {
		if (parr[patientIndex].appointments[i].time.date.day == "0" &&
			parr[patientIndex].appointments[i].time.date.month == "0" &&
			parr[patientIndex].appointments[i].time.hour == "0" &&
			parr[patientIndex].appointments[i].time.minute == "0") {
			counter = i;
			break;
		}
	}
	if (counter == -1) {
		"You have booked your maximum number of appointments! you should cancel an appointment of yours to add another one.\n";
		patientMenu(parr, darr, patientIndex);
		return;
	}
	int addChoice = 0; //patient will use to choose his desired appointment from available time.
	//showing the user available appointments to book.
	cout << "Available appointments:\n";
	for (int i = 0; i < 20; i++) {
		//if it is available to book
		if (darr[docIndex].availableTime[i].Available == "true" &&
			darr[docIndex].availableTime[i].date.day != "0" &&
			darr[docIndex].availableTime[i].date.month != "0" &&
			darr[docIndex].availableTime[i].hour != "0" &&
			darr[docIndex].availableTime[i].minute != "0") {
			cout << "\t(" << i + 1 << ")" << endl;
			cout << "Date: " << darr[docIndex].availableTime[i].date.day << "/" << darr[docIndex].availableTime[i].date.month << "/" << darr[docIndex].availableTime[i].date.year << endl;
			cout << "Time: " << darr[docIndex].availableTime[i].hour << ":" << darr[docIndex].availableTime[i].minute << endl;
		}
	}

	//asking user to choose his desired appointment.
	do {
		cout << "Choose the appointment you want from above:\n" << endl;
		cin >> addChoice;
		addChoice--;
	} while (addChoice < 0 || addChoice >= 20 || darr[docIndex].availableTime[addChoice].Available == "false");
	// >>>> step (2): done.


	//marking the chosen appointment as booked.
	darr[docIndex].availableTime[addChoice].Available = "false";
	// >>>> step (3): done.


	//assigning available appointment time to an actual patient appointment.
	parr[patientIndex].appointments[counter].doctorName = darr[docIndex].name;
	parr[patientIndex].appointments[counter].time.date.day = darr[docIndex].availableTime[addChoice].date.day;
	parr[patientIndex].appointments[counter].time.date.month = darr[docIndex].availableTime[addChoice].date.month;
	parr[patientIndex].appointments[counter].time.date.year = darr[docIndex].availableTime[addChoice].date.year;
	parr[patientIndex].appointments[counter].time.hour = darr[docIndex].availableTime[addChoice].hour;
	parr[patientIndex].appointments[counter].time.minute = darr[docIndex].availableTime[addChoice].minute;
	// >>>> step (4): done.


	//assigning available appointment time to an actual doctor appointment.
	darr[docIndex].appointments[addChoice].patientName = parr[patientIndex].name;
	darr[docIndex].appointments[addChoice].time.date.day = darr[docIndex].availableTime[addChoice].date.day;			//index of doctor appointment = index of available time
	darr[docIndex].appointments[addChoice].time.date.month = darr[docIndex].availableTime[addChoice].date.month;
	darr[docIndex].appointments[addChoice].time.date.year = darr[docIndex].availableTime[addChoice].date.year;
	darr[docIndex].appointments[addChoice].time.hour = darr[docIndex].availableTime[addChoice].hour;
	darr[docIndex].appointments[addChoice].time.minute = darr[docIndex].availableTime[addChoice].minute;
	// >>>> step (5): done.
	cout << "Appointment added successfully" << endl;
	patientMenu(parr, darr, patientIndex);
}
void addAppointment(doctor darr[], patient parr[], int patientIndex, int docIndex, timeStruct timeHolder) {
	//getting number of booked appointments so we can add up on an empty index.
	int counter = -1;
	for (int i = 0; i < 20; i++) {
		if (parr[patientIndex].appointments[i].time.date.day == "0" &&
			parr[patientIndex].appointments[i].time.date.month == "0" &&
			parr[patientIndex].appointments[i].time.hour == "0" &&
			parr[patientIndex].appointments[i].time.minute == "0") {
			counter = i;
			break;
		}
	}

	if (counter == -1) {
		"You have booked your maximum number of appointments! you should cancel an appointment of yours to add another one.\n";
		patientMenu(parr, darr, patientIndex);
		return;
	}

	//getting appointment index for the dr.
	int docAppointment;
	for (int i = 0; i < 20; i++) {
		if (timeHolder.date.day == darr[docIndex].availableTime[i].date.day &&
			timeHolder.date.month == darr[docIndex].availableTime[i].date.month &&
			timeHolder.hour == darr[docIndex].availableTime[i].hour &&
			timeHolder.minute == darr[docIndex].availableTime[i].minute) {
			docAppointment = i;
		}
	}

	//booking available time into an appointment.
	darr[docIndex].availableTime[docAppointment].Available = "false";

	//assigning available time to an actual appointment for the doctor.
	darr[docIndex].appointments[docAppointment].patientName = parr[patientIndex].name;
	darr[docIndex].appointments[docAppointment].time.date = darr[docIndex].availableTime[docAppointment].date;
	darr[docIndex].appointments[docAppointment].time.hour = darr[docIndex].availableTime[docAppointment].hour;
	darr[docIndex].appointments[docAppointment].time.minute = darr[docIndex].availableTime[docAppointment].minute;

	//assigning available time to an actual appointment for the doctor.
	parr[patientIndex].appointments[counter].doctorName = darr[docIndex].name;
	parr[patientIndex].appointments[counter].time = darr[docIndex].appointments[docAppointment].time;

	cout << "Appointment added successfully" << endl;
	patientMenu(parr, darr, patientIndex);
}
void editAppointment(doctor darr[], patient parr[], int patientIndex) {
	// 1. get patient appointments count.
	// 1. show the patient all his booked appointments (from all doctors)
	// 2. ask him to choose the one he wants to edit. (which will be excluded)
	// 3. get index of the appointment for the dr.
	// 4. mark it unbooked (available = true)
	// 5. remove dr appointment.
	// 6. show him available appointments by the same doctor.
	// 7. make him choose his new desired one.
	// 8. mark it booked (available = false)
	// 9. assign available time he choosed to an actual patient appointment.
	// 10. assign available time he choosed to an actual doctor appointment.

	int counter = 19;
	for (int i = 0; i < 20; i++) {
		if (parr[patientIndex].appointments[i].time.date.day == "0" &&
			parr[patientIndex].appointments[i].time.date.month == "0" &&
			parr[patientIndex].appointments[i].time.hour == "0" &&
			parr[patientIndex].appointments[i].time.minute == "0") {
			counter = i;
			break;
		}
	}

	if (counter == 0) {
		cout << "No appointments to edit" << endl;
		patientMenu(parr, darr, patientIndex);
	}


	int editChoice = 0; //unwanted appointment.
	int docIndex = 0, docAppointment = 0;


	//Displaying booked appointments by the patient 
	displayPatientAppointments(parr, patientIndex);
	do {
		cout << "Choose the appointment you want to change:\n";
		cin >> editChoice;
		editChoice--; //to make it zero indexed.
	} while (editChoice < 0 || editChoice >= counter);

	//finding doctor index.
	for (int i = 0; i < 50; i++) {
		if (parr[patientIndex].appointments[editChoice].doctorName == darr[i].name) {
			docIndex = i;
			break;
		}
	}

	//finding appointments index for doctor
	for (int i = 0; i < 20; i++) {
		if (parr[patientIndex].appointments[editChoice].time.date.day == darr[docIndex].appointments[i].time.date.day &&
			parr[patientIndex].appointments[editChoice].time.date.month == darr[docIndex].appointments[i].time.date.month &&
			parr[patientIndex].appointments[editChoice].time.hour == darr[docIndex].appointments[i].time.hour &&
			parr[patientIndex].appointments[editChoice].time.minute == darr[docIndex].appointments[i].time.minute) {
			docAppointment = i;
			break;
		}
	}

	//"deleteing" old appointment for doctor.

	darr[docIndex].availableTime[docAppointment].Available = "true";
	darr[docIndex].appointments[docAppointment].patientName = "0";
	darr[docIndex].appointments[docAppointment].time.date.day = "0";
	darr[docIndex].appointments[docAppointment].time.date.month = "0";
	darr[docIndex].appointments[docAppointment].time.hour = "0";
	darr[docIndex].appointments[docAppointment].time.minute = "0";


	cout << "Choose new appointment time from below\n";
	int choice = 0;
	cout << "Available appointments:\n";
	for (int i = 0; i < 20; i++) {
		//if it is available to book
		if (darr[docIndex].availableTime[i].Available == "true" &&
			darr[docIndex].availableTime[i].date.day != "0" &&
			darr[docIndex].availableTime[i].date.month != "0" &&
			darr[docIndex].availableTime[i].hour != "0" &&
			darr[docIndex].availableTime[i].minute != "0") {
			cout << "\t(" << i + 1 << ")" << endl;
			cout << "Date: " << darr[docIndex].availableTime[i].date.day << "/" << darr[docIndex].availableTime[i].date.month << "/" << darr[docIndex].availableTime[i].date.year << endl;
			cout << "Time: " << darr[docIndex].availableTime[i].hour << ":" << darr[docIndex].availableTime[i].minute << endl;
		}
	}
	cin >> choice;
	choice--;

	darr[docIndex].availableTime[choice].Available = "false";

	darr[docIndex].appointments[choice].time.date.day = darr[docIndex].availableTime[choice].date.day;
	darr[docIndex].appointments[choice].time.date.month = darr[docIndex].availableTime[choice].date.month;
	darr[docIndex].appointments[choice].time.date.year = darr[docIndex].availableTime[choice].date.year;
	darr[docIndex].appointments[choice].time.hour = darr[docIndex].availableTime[choice].hour;
	darr[docIndex].appointments[choice].time.minute = darr[docIndex].availableTime[choice].minute;


	parr[patientIndex].appointments[editChoice].time.date = darr[docIndex].availableTime[choice].date;
	parr[patientIndex].appointments[editChoice].time.hour = darr[docIndex].availableTime[choice].hour;
	parr[patientIndex].appointments[editChoice].time.minute = darr[docIndex].availableTime[choice].minute;
	cout << "Appointment edited successfully\n";
	patientMenu(parr, darr, patientIndex);
}
void deleteAppointments(doctor darr[], patient parr[], int patientIndex) {
	int counter = 19;
	for (int i = 0; i < 20; i++) {
		if (parr[patientIndex].appointments[i].time.date.day == "0" &&
			parr[patientIndex].appointments[i].time.date.month == "0" &&
			parr[patientIndex].appointments[i].time.hour == "0" &&
			parr[patientIndex].appointments[i].time.minute == "0") {
			counter = i;
			break;
		}
	}
	if (counter == 0) {
		cout << "No Appointments to cancel\n";
		return;
	}

	int docIndex = 0, docAppointment = 0, deleteChoice = 0;

	displayPatientAppointments(parr, patientIndex);
	do {
		cout << "Choose the appointment you want to canel:\n";
		cin >> deleteChoice;
		deleteChoice--;
	} while (deleteChoice < 0 || deleteChoice >= counter);

	//getting doctor index
	for (int i = 0; i < 50; i++) {
		if (parr[patientIndex].appointments[deleteChoice].doctorName == darr[i].name) {
			docIndex = i;
			break;
		}
	}

	//finding appointments index
	for (int i = 0; i < 20; i++) {
		if (parr[patientIndex].appointments[deleteChoice].time.date.day == darr[docIndex].appointments[i].time.date.day &&
			parr[patientIndex].appointments[deleteChoice].time.date.month == darr[docIndex].appointments[i].time.date.month &&
			parr[patientIndex].appointments[deleteChoice].time.hour == darr[docIndex].appointments[i].time.hour &&
			parr[patientIndex].appointments[deleteChoice].time.minute == darr[docIndex].appointments[i].time.minute) {
			docAppointment = i;
			break;
		}
	}


	darr[docIndex].availableTime[docAppointment].Available = "true";
	counter--;

	//updating doctor appointment list
	darr[docIndex].appointments[docAppointment].patientName = "0";
	darr[docIndex].appointments[docAppointment].time.date.day = "0";
	darr[docIndex].appointments[docAppointment].time.date.month = "0";
	darr[docIndex].appointments[docAppointment].time.hour = "0";
	darr[docIndex].appointments[docAppointment].time.minute = "0";


	//updating patient appointment list index by shifting it.
	for (int i = deleteChoice; i < counter; i++) {
		parr[patientIndex].appointments[i].doctorName = parr[patientIndex].appointments[i + 1].doctorName;
		parr[patientIndex].appointments[i].time = parr[patientIndex].appointments[i + 1].time;
	}

	//deleting the last appointment (it was copied to the previous appointment)
	parr[patientIndex].appointments[counter].doctorName = "0";
	parr[patientIndex].appointments[counter].time.date.day = "0";
	parr[patientIndex].appointments[counter].time.date.month = "0";
	parr[patientIndex].appointments[counter].time.hour = "0";
	parr[patientIndex].appointments[counter].time.minute = "0";


	cout << "Appointment canceled successfully\n";
}
void editPatientInfo(patient parr[], doctor darr[], int patientIndex) {
	char response;
	string holder;

	cout << "Want to edit your data? We're here for help\n";
	cout << "1.Edit your password" << endl;
	cout << "2.Edit your username" << endl;
	cout << "3.Main menu" << endl;
	cout << "Enter your choice :";
	cin >> response;

	switch (response)
	{
	case '1':
	{
		cout << "Please enter the old password you want to change: \n";
		cin >> holder;

		if (holder == parr[patientIndex].password)
		{
			cout << "Please write the new password \n";
			cin >> parr[patientIndex].password;
			cout << "Password Successfully updated \n";
		}
		else
		{
			cout << "Incorrect Password. Please try again.\n";
		}
		break;
	}

	case '2':
	{
		bool flag;
		do {
			flag = true;
			cout << "Please write the new username \n";
			cin >> holder;
			for (int i = 0; i < patientLimit; i++)
			{
				if (holder == parr[i].name)
				{
					cout << "invalid username, try another one \n";
					flag = false;
					break;
				}
			}

			if (flag) {
				cout << "username Successfully updated\n";
				parr[patientIndex].name = holder;
			}
		} while (flag == false);
		break;
	}

	case '3':
	{
		patientMenu(parr, darr, patientIndex);
	}

	default:
	{
		cout << "Invalid Input. Please try again!\n";
		break;
	}

	}

}
void displayPatientAppointments(patient parr[], int patientIndex) {
	int counter = 20; // IN CASE THERE WAS NO EMPTY APPOINTMENT
	for (int i = 0; i < 20; i++) {
		if (parr[patientIndex].appointments[i].time.date.day == "0" &&
			parr[patientIndex].appointments[i].time.date.month == "0" &&
			parr[patientIndex].appointments[i].time.hour == "0" &&
			parr[patientIndex].appointments[i].time.minute == "0") {
			counter = i; // you have i appointments.
			break;
		}
	}

	if (counter == 0) {
		cout << "You don't have any appointments\n";
		return;
	}




	cout << "Your Appointments\n";
	for (int i = 0; i < counter; i++) {
		cout << "\t(" << i + 1 << ")\n";
		cout << "Doctor Name: ";
		cout << parr[patientIndex].appointments[i].doctorName << endl;
		cout << "Time of Appointment:\n";
		cout << "Date: " << parr[patientIndex].appointments[i].time.date.day << "/" << parr[patientIndex].appointments[i].time.date.month << "/" << parr[patientIndex].appointments[i].time.date.year << "\n";
		cout << "Time: " << parr[patientIndex].appointments[i].time.hour << ":" << parr[patientIndex].appointments[i].time.minute << "\n";
	}
}
void clearAppointments(patient parr[], int patientIndex) {
	for (int i = 0; i < 20; i++) {
		parr[patientIndex].appointments[i].time.hour = "0";
		parr[patientIndex].appointments[i].time.minute = "0";
		parr[patientIndex].appointments[i].time.Available = "true";
		parr[patientIndex].appointments[i].time.date.day = "0";
		parr[patientIndex].appointments[i].time.date.month = "0";
		parr[patientIndex].appointments[i].doctorName = "0";
		parr[patientIndex].appointments[i].patientName = "0";

	}
}
// Registeration & log in
void accountDoctor(doctor darr[], patient parr[])
{
	string response;
	cout << "Do you have an account ? \n";
	cin >> response;
	if (response == "Yes" || response == "yes" || response == "y" || response == "Y") {
		logInDoctor(darr, parr);
	}
	if (response == "No" || response == "no" || response == "n" || response == "N") {
		signUpDoctor(darr, parr);
	}
}
void signUpDoctor(doctor darr[], patient parr[])
{
	string response;
	char username[50], password[50];
	int doctorIndex = -1;
	for (int i = 0; i < doctorLimit; i++) {
		if (darr[i].name == "0") {
			doctorIndex = i;
			break;
		}
	}
	if (doctorIndex == -1) {
		cout << "Full database\n";
		return;
	}

	cout << "Let's create a new email for you. \n";

	bool found;
	cout << "Please enter your name: ";
	cin.ignore();
	do {
		found = false;
		cin.getline(username, 50);
		for (int i = 0; i < patientLimit; i++) {
			if (username == darr[i].name) {
				found = true;
				cout << "This username is taken, please enter another username\n";
				break;
			}
		}
	} while (found == true);

	cout << "Please enter your Password: ";
	cin.getline(password, 50);

	cout << "Choose a Major: \n"
		<< "1. Dentist\t\t2. Pediatrician\n"
		<< "3. Internist\t\t4. Neurologist\n"
		<< "5. Dermatologist\t\t6. Cardiologist\n"
		<< "7. Ophthalmologist\t\t8. Otolaryngologist\n"
		<< "9. Orthopedist\t\t10. Gynecologist/Obstetrician\n"
		<< "11. Psychologist\n\n";
	string major;
	do {
		cin >> response;
		if (response == "1")
			major = "Dentist";
		else if (response == "2")
			major = "Pediatrician";
		else if (response == "3")
			major = "Internist";
		else if (response == "4")
			major = "Neurologist";
		else if (response == "5")
			major = "Dermatologist";
		else if (response == "6")
			major = "Cardiologist";
		else if (response == "7")
			major = "Ophthalmologist";
		else if (response == "8")
			major = "Otolaryngologist";
		else if (response == "9")
			major = "Orthopedist";
		else if (response == "10")
			major = "Gynecologist/Obstetrician";
		else if (response == "11")
			major = "Psychologist";
		else {
			cout << "Invalid input.. Please try again.";
			response = "repeat";
		}
	} while (response == "repeat");


	darr[doctorIndex].major = major;
	darr[doctorIndex].name = username;
	darr[doctorIndex].password = password;
	cout << "Created successfully \n";

	cout << "Now you're signed up, do you want to log in?(y/n)  -> ";
	cin >> response;
	if (response == "y" || response == "Y" || response == "yes" || response == "Yes") {
		logInDoctor(darr, parr);
	}
	else {
		start(darr, parr);
	}

}
void logInDoctor(doctor darr[], patient parr[]) {
	string response;
	bool found;
	do {
		char username[50], password[50];
		cout << "Username: ";
		cin.ignore();
		cin.getline(username, 50);
		cout << "Password: ";
		cin.getline(password, 50);

		int doctorIndex;
		found = false;
		for (int i = 0; i < doctorLimit; i++) {
			if (username == darr[i].name && password == darr[i].password) {
				doctorIndex = i;
				found = true;
				cout << "Login succeeded!\n";
				doctorMenu(darr, doctorIndex, parr);
				break;
			}
		}
		if (!found) {
			cout << "Sorry! Login Failed. Do you want to try again.\n";
			cin >> response;
			if (response == "yes" || response == "y" || response == "Yes" || response == "Y") {
				continue;
			}
			else {
				start(darr, parr);
			}
		}
		break;
	} while (true);
}
void start(doctor darr[], patient parr[]) {
	//saying hi
	cout << "----------- Welcome To E7gzly -----------\n";

	//doctor Or patient
	string username, password, response, exit;
	cout << "Hello! Are you a Doctor or a Patient ?  (quit/Quit to exit) \n";
	cin >> response;


	if (response == "doctor" || response == "Doctor") {
		accountDoctor(darr, parr);
	}

	else if (response == "patient" || response == "Patient") {
		account_patient(parr, darr);
	}
	else if (response == "quit" || response == "Quit") {
		return;
	}

}
void account_patient(patient parr[], doctor darr[])
{
	string acc;
	cout << "Do you have an account ? \n";
	cin >> acc;
	if (acc == "Yes" || acc == "yes" || acc == "Y" || acc == "y") {
		log_in_patient(parr, darr);
	}
	if (acc == "No" || acc == "no" || acc == "n" || acc == "N") {
		sign_up_patient(parr, darr);

	}
}
void log_in_patient(patient parr[], doctor darr[]) {
	string response;
	bool found;
	do {
		char username[50], password[50];
		cout << "Username: ";
		//we used getline so we can take spaces
		cin.ignore();
		cin.getline(username, 50);
		cout << "Password: ";
		cin.getline(password, 50);

		int patientIndex;
		found = false;
		for (int i = 0; i < patientLimit; i++) {
			if (username == parr[i].name && password == parr[i].password) {
				patientIndex = i;
				found = true;
				cout << "Login succeeded\n";
				patientMenu(parr, darr, patientIndex);
				break;
			}
		}
		if (!found) {
			cout << "Sorry! Login Failed. Do you want to try again.\n";
			cin >> response;
			if (response == "yes" || response == "y" || response == "Yes" || response == "Y") {
				continue;
			}
			else {
				start(darr, parr);
			}
		}
		break;
	} while (true);
}
void sign_up_patient(patient parr[], doctor darr[]) {
	char username[50], password[50];
	string response;

	int patientIndex = -1;
	for (int i = 0; i < patientLimit; i++) {
		if (parr[i].name == "0") {
			patientIndex = i;
			break;
		}
	}
	if (patientIndex == -1) {
		cout << "Full database\n";
		return;
	}

	// 15/7/2002

	cout << " Let's create a new email for you. \n";

	bool found;

	cout << "Username: ";
	cin.ignore();
	do {
		found = false;
		cin.getline(username, 50);
		for (int i = 0; i < patientLimit; i++) {
			if (username == parr[i].name) {
				found = true;
				cout << "This username is taken, please enter another username\n";
				break;
			}
		}
	} while (found == true);

	cout << "Password: ";
	cin.getline(password, 50);

	parr[patientIndex].name = username;
	parr[patientIndex].password = password;
	cout << "Created successfully \n";

	cout << "Now you're signed up, do you want to log in?(y/n)  -> ";
	cin >> response;
	if (response == "y" || response == "Y" || response == "yes" || response == "Yes") {
		log_in_patient(parr, darr);
	}
	else {
		start(darr, parr);
	}
}
