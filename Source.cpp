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
	appointment Pappointments[20];
};

struct doctor
{
	string name, password, major;
	appointment DRappointments[20];
	timeStruct availableTime[20];
};


// FUNCTIONS prototypes
// Gehad
void sign_up();
void sign_in();
void start();

void doctorMenu(doctor darr[], int j);
void patientMenu();

// DINA
void editInfo(doctor darr[], int j, int doctorNum);

// ABO
void findDoctor(doctor darr[], int patientIndex);
void timeFilter(doctor darr[], int patientIndex, int* result);

// Safa
void displayPatientAppointments();
void editPatientInfo();

// Seif
void addAppointment(int doctorIndex, int patientIndex);
void editAppointment();
void deleteAppointments();
void clearAppointments();

//MAYAR
void editAvailableTime(doctor darr[], int j);
void displayDoctorAppointments(doctor darr[], int j);

//MALK
void AddAvailableTime(doctor darr[], int j);
void RemoveAvailabeTime(doctor darr[], int doctorIndex, int drNum);


int main() {
	const int doctorNum = 50, PatientNum = 50;

	// Loading data from files
	
	doctor Darr[doctorNum];
	patient Parr[PatientNum];
	char ans;
	cout << "------------ Welcome om E7gezly ------------\n";

	// GEHAD : (SIGN UP OR LOG IN)

	int i = 10;               	//just a sample to work with , this part will be done in GEHAD'S part
	Darr[i].name = "Malk";     	//just a sample to work with , this part will be done in GEHAD'S part

	cout << " as a doctor or patient?";
	cin >> ans;
	if (ans == 'd' || ans == 'D')
		doctorMenu(Darr, i);
	else if (ans == 'p' || ans == 'P')
		patientMenu();

	
	return 0;
} // END MAIN

void doctorMenu(doctor darr[], int doctorIndex)
{

	char service;
	string order;

	do {
		cout << "1. Edit available time" << endl              // MAYAR
			<< "2. Add available time" << endl                   //MALK
			<< "3. Remove available time" << endl                //MALK
			<< "4. Display your appointments" << endl     // MAYAR
			<< "5. Edit you info" << endl;                    // DINA

		cin >> service;

		// Edit available time
		if (service == '1')
		{

			editAvailableTime(darr, doctorIndex);
		}
		//Add available time
		else if (service == '2')
		{
			AddAvailableTime(darr, doctorIndex);  //MAlk
		}
		//Remove availble time
		else if (service == '3')
		{
			RemoveAvailabeTime(darr, doctorIndex);  //MAlk
		}

		// Display your appointments
		else if (service == '4')
		{
			displayDoctorAppointment(darr, doctorIndex);
		}

		// Edit you info
		else if (service == '5')
		{
			editInfo(darr, doctorIndex);  // DINA
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

void editAvailableTime(doctor darr[], int doctorIndex)
{
	// view the old appointments
	displayDoctorAppointments(darr, doctorIndex);

	timeStruct change;
	// Obtain the old appointment
	cout << "Please enter the old appointment you want to change: date(day month year), hour, minute\n";
	cin >> change.date.day >> change.date.month >> change.hour >> change.minute;

	// loop over this doctor's appointments to find the old one
	for (int i = 0; i < 20; i++)
	{
		// if you found it
		if (
			(change.date.day == darr[doctorIndex].DRappointments[i].time.date.day) &&
			(change.date.month == darr[doctorIndex].DRappointments[i].time.date.month) &&
			(change.hour == darr[doctorIndex].DRappointments[i].time.hour) &&
			(change.minute == darr[doctorIndex].DRappointments[i].time.minute)
			)
		{
			//if that time wasn't booked by any patient
			if (darr[doctorIndex].DRappointments[i].time.Available == true)
			{
				// take the updated appointment
				cout << "Please write the new time date(day month), hour, minute\n";
				cin >> darr[doctorIndex].DRappointments[i].time.date.day 
					>> darr[doctorIndex].DRappointments[i].time.date.month 
					>> darr[doctorIndex].DRappointments[i].time.hour 
					>> darr[doctorIndex].DRappointments[i].time.minute;
			}
			else
				cout << "This time had been booked by a patient please choose another time to change";
		}
	}
}

void addAvailableTime(doctor darr[], int doctorIndex)
{
	char another = 'y';
	cout << "\t\t\t\t------------------------\n\t\t\twelcome\n to *add* a new available time just follow the following instructions\n";
	do
	{
		for (int i = 0; i < 20; i++)
		{
			if (darr[doctorIndex].availableTime[i].date.day == 0) {
				cout << "write the information of the available time you want to add:\n ";
				cout << "Choose the day (1 to 30)\n";
				cin >> darr[doctorIndex].availableTime[i].date.day;
				cout << "enter the month (1 to 12)";
				cin >> darr[doctorIndex].availableTime[i].date.month;
				cout << "enter the hour (0 to 23)";
				cin >> darr[doctorIndex].availableTime[i].hour;
				cout << "enter the minute (0 to 59)";
				cin >> darr[doctorIndex].availableTime[i].minute;
				break;
			}
			else
				continue;
		}
		cout << "The operation done successfully :D\n";


		cout << "\nDo you want to add another time? (y/Y for yes && any key to stop)\n";
		cin >> another;
	} while (another == 'y' || another == 'Y');
}

void RemoveAvailableTime(doctor darr[], int doctorIndex, int drNum)
{
	timeStruct Delete;
	char another = 'y';
	int check = 1;
	cout << "\t\t\t\t------------------------\n\t\t\twelcome\n to delete a new available time just follow the following instructions\n";
	do
	{
		// show him first
		displayDoctorAppointment(darr, doctorIndex);

		cout << "write the information of the available time you want to delete:\n ";
		cout << "Choose the day(1 to 30)\n";
		cin >> Delete.date.day;
		cout << "enter the month (1 to 12)";
		cin >> Delete.date.month;
		cout << "enter the hour (0 to 23)";
		cin >> Delete.hour;
		cout << "enter the minute (0 to 59)";
		cin >> Delete.minute;

		for (int i = 0; i < 20; i++)
		{
			if (darr[doctorIndex].availableTime[i].date.day == Delete.date.day
				&& darr[doctorIndex].availableTime[i].date.month == Delete.date.month
				&& darr[doctorIndex].availableTime[i].hour == Delete.hour
				&& darr[doctorIndex].availableTime[i].minute == Delete.minute
				&& darr[doctorIndex].availableTime[i].Available == true)
			{
				darr[doctorIndex].availableTime[i].date.day = 0;
				darr[doctorIndex].availableTime[i].date.month = 0;
				darr[doctorIndex].availableTime[i].hour = 0;
				darr[doctorIndex].availableTime[i].minute = 0;
				check = -1;
				break;
			}
		}
		if (check == -1)
			cout << "Operation done successfully :D\n";
		else
			cout << "This time doesn't exists or this time already taken :D\n";



		cout << "\nDo you want to delet another time? (y/Y for yes && any key to stop)\n";
		cin >> another;
	} while (another == 'y' || another == 'Y');
}

void displayDoctorAppointment(doctor darr[], int doctorIndex)
{

	cout << "------------ appointments of dr." << darr[j].name << " ------------\n";
	for (int i = 0; i < 20; i++)
	{
		cout << "patient name : " << darr[j].DRappointments[i].patientName
			<< "\n Appointment date: "
			<< darr[doctorIndex].DRappointments[i].time.date.day << "/"
			<< darr[doctorIndex].DRappointments[i].time.date.month << "/"
			<< "Appointment time:"
			<< darr[doctorIndex].DRappointments[i].time.hour << ":"
			<< darr[doctorIndex].DRappointments[i].time.minute << endl;
	}


}

void patientMenu(patient parr[], doctor darr[], int i) {  // parr -> array of patients & i -> index in that array
	// which service ?
	cout << "1. Find a doctor" << endl     // Abo
		<< "2. your appointments" << endl  // Mohamed displays and clears history & Seif edits
		<< "3. Edit your Info" << endl;    // Mohamed
	char service;
	string order;

	do {
		cin >> service;

		if (service == '1')
			findDoctor(darr, i);

		else if (service == '2')
			displayPatientAppointments();

		else if (service == '3')
			editPatientInfo();

		else {
			cout << "Invalid choice please try again!\n";
			continue;
		}

		// Another Operation ?
		cout << "have a nice day ," << parr[i].name << endl
			<< "Main Menu? ( h / H / home )";
		cin >> order;

		// GEHAD, make it case-insensetive checking ,please
	} while (order == "h" || order == "H" || order == "home" || order == "Home");

	cout << "Thank you for using our system, have a nice day ," << parr[i].name << " :)\n";

}

void findDoctor (doctor darr[], int patientIndex) {
	// search by major
	cout << "Choose a Major: \n"
		<< "1. Dentist\t\t2. Pediatrician\n"
		<< "3. Internist\t\t4. Neurologist\n"
		<< "5. Dermatologist\t\t6. Cardiologist\n"
		<< "7. Ophthalmologist\t\t8. Otolaryngologist\n"
		<< "9. Orthopedist\t\t10. Gynecologist/Obstetrician\n"
		<< "11. Psychologist";
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
	} while(response == "repeat");  // use swtich instead ?

	

	// this is a dynamic array that I store the indeces of the
	// search-resultant doctors in
	int* ptr1, * ptr2, size = 0;
	ptr1 = new int[]();
	ptr2 = ptr1;
	// loop over doctors searching for the desired major
	for (int i = 0; i < 50; i++) {
		if (darr[i].major == major) {
			*(ptr2++) = i;
			size++;
		}
	}	
	// Now, I have the research result

	// print it
	for (int i = 0; i < size; i++) {
		cout << i+1 << ". Name\t\t" << darr[ptr1[i]].name; // more details ?
	}
	//_________________________________________________________
	cout << "Filter by Available Time? ( y / n )\n";
	do {
		cin >> response;
		if (response == "y" || response == "Y")
			timeFilter(darr, patientIndex, ptr1);
		
		else if (response == "n" || response == "N") {
			cout << "which doctor do you want to make an appointment with?\n";
			int choice;
			cin >> choice;
			addAppointment(choice - 1, patientIndex);
		}

		else
			cout << "Invalid input. Please try again!";
	} while (response != "y" && response != "Y" && response != "n" && response != "N");
	

	delete[] ptr1; // release the memory
	ptr1 = NULL; ptr2 = NULL;  // avoid dangling pointers
	//_________________________________________________________
	
	

	// improve the intelligence of your search later ,dude!
}

void timeFilter(doctor darr[], int patientIndex, int* result) {
	// what's your desired time for your appointment
	timeStruct start, end;
	cout << "You are searching for an appointment :\nat (month day hour minute): ";
	cin >> start.date.month >> start.date.day >> start.hour >> start.minute;

	// compare appointments with the patient's time
	// for every doctor
	for () {
		// for his appointments
		for () {

		}
	}
}

void editInfo(doctor darr[], int doctorIndex, int doctorNum)
{
	// Variable used to asssign editing the username or password
	int editinfochoice;

	string change;
	// Obtain the old username or password
	cout << "Want to edit your data? We're here for help\n";
	cout << "1.Edit your password" << endl;
	cout << "2.Edit your username" << endl;
	cout << "3.Main menu" << endl;
	cout << "Enter your choice :";
	cin >> editinfochoice;

	switch (editinfochoice)
	{
	case 1:
	{
		cout << "Please enter the old password you want to change: \n";
		cin >> change.password;

		// loop over this doctor's database to find the old one
		for (int i = 0; i < doctorNum; i++)
		{
			// if you found it
			if (change.password == darr[j].password)
			{
				cout << "Please write the new password \n";
				cin >> darr[j].password;
				cout << "Password Successfully updated \n";
			}
			else
			{
				cout << "This password is not correct, Please kindly try again or contact your system administrator for more details";
			}

		}


	}


	case 2:
	{
		cout << "Please enter the old username you want to change: \n";
		cin >> change;

		// loop over this doctor's database to find the old one
		for (int i = 0; i < doctorNum; i++)
		{
			// if you found it
			if (change == darr[doctorIndex].name)
			{
				cout << "Please write the new username \n";
				cin >> change;
				bool flag = true;
				for (int i = 0; i < doctorNum; i++)
				{
					if (change == darr[doctorIndex].name)
					{
						cout << "invalid username, try another one \n";
						flag = false;
						break;
					}

				}
				if (flag) {
					cout << "username Successfully updated\n";
					darr[doctorIndex].name = change;
				}
				

			}
			else
			{
				cout << "This username is not correct, Please kindly try again or contact your system administrator for more details";
			}

		}


	}

	case 3:
	{
		// return to the main minu 
		doctorMenu();
	}


	}
}
//_______________________________________________________

void account()
{
	string acc;
	cout << "Do you have an account ? \n";
	cin >> acc;
	if (acc == "Yes" || acc == "yes") {
		sign_in();
	}
	if (acc == "No" || acc == "no") {
		sign_up();

	}
}
void sign_up()
{
	string again;
	cout << " Let's create a new email for you. \n";
	fstream information;
	information.open("User info.txt", ios::app);
	fstream info;
	info.open("doctor info.txt", ios::app);
	cout << " Please enter your  First Name \n";
	cin.ignore();
	cin.getline(inf.names, 25);
	cout << "Please enter your Password \n";
	cin.getline(inf.passwords, 25);
	cout << "Please enter you phone number \n";
	cin.getline(inf.numbers, 25);
	cout << " Please enter your Age \n";
	cin >> inf.ages;
	cout << "Please enter your Major \n";
	cin.ignore();
	cin.getline(inf.majors, 25);
	information << inf.names << '|' << inf.passwords << '|' << inf.ages << '|' << inf.numbers << '|' << inf.majors << '|' << "\n";
	cout << "Created successfully \n";
	do {
		string username, password;
		cout << "Now please enter your username \n";
		cin >> username;
		cout << "Now please enter your password \n";
		cin >> password;
		if (inf.names == username && inf.passwords == password) {
			cout << "Log in succescded   ";			break;

		}
		if (inf.names != username || inf.passwords != password) {
			cout << "Log in failed! Please try again  ";			break;

		}
		cout << "Do you want to try again \n";
		cin >> again;
	} while (again == "yes" || again == "Yes");

}
void sign_in() {
	string again;
	do {
		char username[25], password[25];
		fstream information;
		information.open("User info.txt", ios::in);
		cout << "Please enter your username\n";
		cin.ignore();
		cin.getline(username, 25);
		cout << "Please enter your password \n";
		cin.getline(password, 25);
		//int x = 0;
		while (!information.eof()) {
			information.getline(inf.names, 25, '|');
			if (strcmp(inf.names, username) == 0) {
				information.getline(inf.passwords, 25, '|');
				if (strcmp(inf.passwords, password) == 0) {
					cout << "Log in succeded \n";
					break;
				}
			}
			if (strcmp(inf.names, username) != 0) {
				//x = 1;
				cout << "Log in failed \n";
				break;
			}
		}
		//std::getline(std::cin, names);


		cout << "Do you want to try again \n";
		cin >> again;
	} while (again == "yes" || again == "Yes");
}
void start() {
	string username, password, response, exit;
	cout << "Hello! Are you a Doctor or a Patient ? \n";
	cin >> response;
	do
	{
		if (response == "doctor" || response == "Doctor") {
			account();
			cout << "Do you want to exit \n";
			cin >> exit;
		}
	} while (exit == "No" || exit == "no");
	do {
		if (response == "patient" || response == "Patient") {
			account(); cout << "Do you want to exit \n"; cin >> exit;
		}
	} while (exit == "No" || exit == "no");
}
