#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
using namespace std;

// Constants
#define doctorLimit 50
#define patientLimit 50

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

struct info_doctor {
	char names[25], numbers[25], passwords[25], majors[25];
	int ages;
}inf;


// FUNCTIONS prototypes
// Gehad
void sign_up();
void sign_in();
void start();
void account();

// menus
void doctorMenu(doctor darr[], int doctorIndex);
void patientMenu(patient parr[], doctor darr[], int patientIndex);

// DINA
void editDoctorInfo(doctor darr[], int doctorIndex);

// ABO
void findDoctor(doctor darr[], patient parr[], int patientIndex);
void timeFilter(doctor darr[], patient parr[], int patientIndex, int* result, int resultSize);

// Safa
void displayPatientAppointments(appointment applist[], int i);
void editPatientInfo(patient parr[], doctor darr[], int patientIndex);
void clearAppointments(appointment applist[], int i);

// Seif
void addAppointment(doctor darr[], patient parr[], int patientIndex, int docIndex);
void addAppointment(doctor darr[], patient parr[], int patientIndex, int docIndex, timeStruct timeHolder);
void editAppointment(doctor darr[], patient parr[], int patientIndex);
void deleteAppointments(doctor darr[], patient parr[], int patientIndex);

//MAYAR
void editAvailableTime(doctor darr[], int doctorIndex);
void displayDoctorAppointment(doctor darr[], int doctorIndex);

//MALK
void AddAvailableTime(doctor darr[], int doctorIndex);
void RemoveAvailabeTime(doctor darr[], int doctorIndex);

//------------------------------------------------------------------------------

int main() {

	// Loading data from files

	doctor darr[doctorLimit];
	patient parr[patientLimit];
	char ans;
	cout << "------------ Welcome om E7gezly ------------\n";

	// GEHAD : (SIGN UP OR LOG IN)

	int i = 10;               	//just a sample to work with , this part will be done in GEHAD'S part
	darr[i].name = "Malk";     	//just a sample to work with , this part will be done in GEHAD'S part
	/*
	this should be in the sign in function:

	cout << " as a doctor or patient?";
	cin >> ans;
	if (ans == 'd' || ans == 'D')
		doctorMenu(darr, i);
	else if (ans == 'p' || ans == 'P')
		patientMenu(parr, darr, patientIndex);

	*/

	return 0;
} // END MAIN

// Menu
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
			editDoctorInfo(darr, doctorIndex);  // DINA
		}
		else
		{
			cout << "Invalid choice please try again!\n";
			continue;
		}


		// Another Operation ?
		cout << "have a nice day dr." << darr[doctorIndex].name << endl
			<< "1. Go back to the main menu? ( h / H / home )";
		cin >> order;

		// GEHAD, make it case-insensetive checking ,please
	} while (order == "h" || order == "H" || order == "home" || order == "Home");

	cout << "Thank you for using our system, have a nice day doctor " << darr[doctorIndex].name << ":)\n";


}

void patientMenu(patient parr[], doctor darr[], int patientIndex) {  // parr -> array of patients & i -> index in that array
	// which service ?
	cout << "1. Find a doctor" << endl     // Abo
		<< "2. your appointments" << endl  // Mohamed displays and clears history & Seif edits
		<< "3. Edit your Info" << endl;    // Mohamed
	char service, appointmentService;
	string order;

	do {
		cin >> service;

		if (service == '1')
			findDoctor(darr, parr, patientIndex);

		else if (service == '2') {

			cout << "1. Display appointments" << endl
				<< "2. Edit appointments" << endl
				<< "3. Cancel appointments" << endl
				<< "4. Return" << endl;
			cin >> appointmentService;

			if (appointmentService == '1') {
				displayPatientAppointments(parr[patientIndex].Pappointments, patientIndex);
			}
			else if (appointmentService == '2') {
				editAppointment(darr, parr, patientIndex);
			}
			else if (appointmentService == '3') {
				deleteAppointments(darr, parr, patientIndex);
			}
			else if (appointmentService == '4') {
				continue;
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
		cout << "have a nice day ," << parr[patientIndex].name << endl
			<< "Main Menu? ( h / H / home )";
		cin >> order;

		// GEHAD, make it case-insensetive checking ,please
	} while (order == "h" || order == "H" || order == "home" || order == "Home");

	cout << "Thank you for using our system, have a nice day ," << parr[patientIndex].name << " :)\n";

}

// Doctor
void editAvailableTime(doctor darr[], int doctorIndex)
{
	// view the old appointments
	displayDoctorAppointment(darr, doctorIndex);

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

void RemoveAvailableTime(doctor darr[], int doctorIndex)
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

	cout << "------------ appointments of dr." << darr[doctorIndex].name << " ------------\n";
	for (int i = 0; i < 20; i++)
	{
		cout << "patient name : " << darr[doctorIndex].DRappointments[i].patientName
			<< "\n Appointment date: "
			<< darr[doctorIndex].DRappointments[i].time.date.day << "/"
			<< darr[doctorIndex].DRappointments[i].time.date.month << "/"
			<< "Appointment time:"
			<< darr[doctorIndex].DRappointments[i].time.hour << ":"
			<< darr[doctorIndex].DRappointments[i].time.minute << endl;
	}


}

// Patient
void findDoctor(doctor darr[], patient parr[], int patientIndex) {
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
	} while (response == "repeat");



	// this is a dynamic array that I store the indeces of the
	// search-resultant doctors in
	int* ptr1, * ptr2, size = 0;
	ptr1 = new int[doctorLimit]();
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
		cout << i + 1 << ". Name\t\t" << darr[ptr1[i]].name; // more details ?
	}


	cout << "Filter by Available Time? ( y / n )\n";
	do {
		cin >> response;
		if (response == "y" || response == "Y")
			timeFilter(darr, parr, patientIndex, ptr1, size);

		else if (response == "n" || response == "N") {
			cout << "which doctor do you want to make an appointment with?\n";
			int choice;
			cin >> choice;
			addAppointment(darr, parr, patientIndex, choice - 1);
		}

		else
			cout << "Invalid input. Please try again!";
	} while (response != "y" && response != "Y" && response != "n" && response != "N");


	delete[] ptr1; // release the memory
	ptr1 = NULL; ptr2 = NULL;  // avoid dangling pointers

	// improve the intelligence of your search later ,dude!
}

void timeFilter(doctor darr[], patient parr[], int patientIndex, int* result, int resultSize) {
	// what's your desired time for your appointment
	timeStruct timeHolder;
	cout << "You are searching for an appointment :\nat (month day hour minute): ";
	cin >> timeHolder.date.month >> timeHolder.date.day >> timeHolder.hour >> timeHolder.minute;

	// compare appointments with the patient's time
	// for every doctor
	for (int i = 0; i < resultSize; i++) {
		// for his appointments
		for (int j = 0; j < 20; j++) { // taking the index of the result array, accessing the doctor with it and compare with the desired time the user gave me
			if (timeHolder.date.month == darr[result[i]].DRappointments[j].time.date.month &&
				timeHolder.date.day == darr[result[i]].DRappointments[j].time.date.day &&
				timeHolder.hour == darr[result[i]].DRappointments[j].time.hour &&
				timeHolder.minute == darr[result[i]].DRappointments[j].time.minute &&
				darr[result[i]].DRappointments[j].time.Available == true) {
				break;
			}

			result[i] = -1;
		}
	}

	// now, print the doctors any value other than -1
	int counter = 1;
	cout << "\n--------After Filteration--------\n"
		<< "Id\t\tName";
	for (int i = 0; i < resultSize; i++) {
		if (result[i] != -1) {
			cout << counter++ << ". " << darr[result[i]].name << result[i] << endl;
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

	int counter;
	for (int i = 0; i < 20; i++) {
		if (parr[patientIndex].Pappointments[i].time.date.day == 0 &&
			parr[patientIndex].Pappointments[i].time.date.month == 0 &&
			parr[patientIndex].Pappointments[i].time.hour == 0 &&
			parr[patientIndex].Pappointments[i].time.hour == 0) {
			counter = i;
			break;
		}
	}

	int addChoice = 0; //patient will use to choose his desired appointment from available time.
	//showing the user available appointments to book.
	cout << "Available appointments:\n";
	for (int i = 0; i < 20; i++) {
		//if it is available to book
		if (darr[docIndex].availableTime[i].Available) {
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
	} while (addChoice < 0 || addChoice >= 20 || darr[docIndex].availableTime[addChoice].Available == false);
	// >>>> step (2): done.


	//marking the chosen appointment as booked.
	darr[docIndex].availableTime[addChoice].Available = false;
	// >>>> step (3): done.


	//assigning available appointment time to an actual patient appointment.
	parr[patientIndex].Pappointments[counter].doctorName = darr[docIndex].name;
	parr[patientIndex].Pappointments[counter].time.date.day = darr[docIndex].availableTime[addChoice].date.day;
	parr[patientIndex].Pappointments[counter].time.date.month = darr[docIndex].availableTime[addChoice].date.month;
	parr[patientIndex].Pappointments[counter].time.date.year = darr[docIndex].availableTime[addChoice].date.year;
	parr[patientIndex].Pappointments[counter].time.hour = darr[docIndex].availableTime[addChoice].hour;
	parr[patientIndex].Pappointments[counter].time.minute = darr[docIndex].availableTime[addChoice].minute;
	// >>>> step (4): done.


	//assigning available appointment time to an actual doctor appointment.
	darr[docIndex].DRappointments[addChoice].patientName = parr[patientIndex].name;
	darr[docIndex].DRappointments[addChoice].time.date.day = darr[docIndex].availableTime[addChoice].date.day;			//index of doctor appointment = index of available time
	darr[docIndex].DRappointments[addChoice].time.date.month = darr[docIndex].availableTime[addChoice].date.month;
	darr[docIndex].DRappointments[addChoice].time.date.year = darr[docIndex].availableTime[addChoice].date.year;
	darr[docIndex].DRappointments[addChoice].time.hour = darr[docIndex].availableTime[addChoice].hour;
	darr[docIndex].DRappointments[addChoice].time.minute = darr[docIndex].availableTime[addChoice].minute;
	// >>>> step (5): done.

	cout << "Appointment added successfully" << endl;
}

void addAppointment(doctor darr[], patient parr[], int patientIndex, int docIndex, timeStruct timeHolder) {
	//getting number of booked appointments so we can add up on an empty index.
	int counter;
	for (int i = 0; i < 20; i++) {
		if (parr[patientIndex].Pappointments[i].time.date.day == 0 &&
			parr[patientIndex].Pappointments[i].time.date.month == 0 &&
			parr[patientIndex].Pappointments[i].time.hour == 0 &&
			parr[patientIndex].Pappointments[i].time.hour == 0) {
			counter = i;
			break;
		}
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
	darr[docIndex].availableTime[docAppointment].Available = false;

	//assigning available time to an actual appointment for the doctor.
	darr[docIndex].DRappointments[docAppointment].patientName = parr[patientIndex].name;
	darr[docIndex].DRappointments[docAppointment].time.date = darr[docIndex].availableTime[docAppointment].date;
	darr[docIndex].DRappointments[docAppointment].time.hour = darr[docIndex].availableTime[docAppointment].hour;
	darr[docIndex].DRappointments[docAppointment].time.minute = darr[docIndex].availableTime[docAppointment].minute;

	//assigning available time to an actual appointment for the doctor.
	parr[patientIndex].Pappointments[counter].doctorName = darr[docIndex].name;
	parr[patientIndex].Pappointments[counter].time = darr[docIndex].DRappointments[docAppointment].time;

	cout << "Appointment added successfully" << endl;
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

	int counter;
	for (int i = 0; i < 20; i++) {
		if (parr[patientIndex].Pappointments[i].time.date.day == 0 &&
			parr[patientIndex].Pappointments[i].time.date.month == 0 &&
			parr[patientIndex].Pappointments[i].time.hour == 0 &&
			parr[patientIndex].Pappointments[i].time.hour == 0) {
			counter = i;
			break;
		}
	}

	if (counter == 0) {
		cout << "No appointments to edit";
		return;
	}


	int editChoice = 0; //unwanted appointment.
	int docIndex = -1, docAppointment = -1;


	//Displaying booked appointments by the patient ( we will call view appointments functions instead )
	cout << "Your appointments:\n";
	for (int i = 0; i < counter + 1; i++) {
		cout << "\t(" << i + 1 << ")\n";
		cout << "Doctor name: " << parr[patientIndex].Pappointments[i].doctorName << endl;
		cout << "Date: " << parr[patientIndex].Pappointments[i].time.date.day << "/" << parr[patientIndex].Pappointments[i].time.date.month << "/" << parr[patientIndex].Pappointments[i].time.date.year << endl;
		cout << "Time: " << parr[patientIndex].Pappointments[i].time.hour << ":" << parr[patientIndex].Pappointments[i].time.minute << endl;
	}

	cout << "Choose the appointment you want to change:\n";
	cin >> editChoice;
	editChoice--; //to make it zero indexed.

	//finding doctor index.
	for (int i = 0; i < 50; i++) {
		if (parr[patientIndex].Pappointments[editChoice].doctorName == darr[i].name) {
			docIndex = i;
			break;
		}
	}

	//finding DRappointments index
	for (int i = 0; i < 20; i++) {
		if (parr[patientIndex].Pappointments[editChoice].time.date.day == darr[docIndex].DRappointments[i].time.date.day &&
			parr[patientIndex].Pappointments[editChoice].time.date.month == darr[docIndex].DRappointments[i].time.date.month &&
			parr[patientIndex].Pappointments[editChoice].time.hour == darr[docIndex].DRappointments[i].time.hour &&
			parr[patientIndex].Pappointments[editChoice].time.hour == darr[docIndex].DRappointments[i].time.minute) {
			docAppointment = i;
			break;
		}
	}

	//"deleteing" old appointment for doctor.

	darr[docIndex].availableTime[docAppointment].Available = true;
	darr[docIndex].DRappointments[docAppointment].patientName = '\0';
	darr[docIndex].DRappointments[docAppointment].time.date.day = 0;
	darr[docIndex].DRappointments[docAppointment].time.date.month = 0;
	darr[docIndex].DRappointments[docAppointment].time.hour = 0;
	darr[docIndex].DRappointments[docAppointment].time.minute = 0;


	cout << "Choose new appointment time from below\n";
	int choice = 0;
	cout << "Available appointments:\n";
	for (int i = 0; i < 20; i++) {
		//if it is available to book
		if (darr[docIndex].availableTime[i].Available) {
			cout << "\t(" << i + 1 << ")" << endl;
			cout << "Date: " << darr[docIndex].availableTime[i].date.day << "/" << darr[docIndex].availableTime[i].date.month << "/" << darr[docIndex].availableTime[i].date.year << endl;
			cout << "Time: " << darr[docIndex].availableTime[i].hour << ":" << darr[docIndex].availableTime[i].minute << endl;
		}
	}
	cin >> choice;
	choice--;

	darr[docIndex].availableTime[choice].Available = false;

	darr[docIndex].DRappointments[choice].time.date.day = darr[docIndex].availableTime[choice].date.day;
	darr[docIndex].DRappointments[choice].time.date.month = darr[docIndex].availableTime[choice].date.month;
	darr[docIndex].DRappointments[choice].time.date.year = darr[docIndex].availableTime[choice].date.year;
	darr[docIndex].DRappointments[choice].time.hour = darr[docIndex].availableTime[choice].hour;
	darr[docIndex].DRappointments[choice].time.minute = darr[docIndex].availableTime[choice].minute;


	parr[patientIndex].Pappointments[editChoice].time.date = darr[docIndex].availableTime[choice].date;
	parr[patientIndex].Pappointments[editChoice].time.hour = darr[docIndex].availableTime[choice].hour;
	parr[patientIndex].Pappointments[editChoice].time.minute = darr[docIndex].availableTime[choice].minute;

	//addAppointment(darr, parr, patientIndex, patientAppChoice, index);


	cout << "Appointment edited successfully\n";
}

void deleteAppointments(doctor darr[], patient parr[], int patientIndex) {
	int counter;
	for (int i = 0; i < 20; i++) {
		if (parr[patientIndex].Pappointments[i].time.date.day == 0 &&
			parr[patientIndex].Pappointments[i].time.date.month == 0 &&
			parr[patientIndex].Pappointments[i].time.hour == 0 &&
			parr[patientIndex].Pappointments[i].time.hour == 0) {
			counter = i;
			break;
		}
	}
	if (counter == 0) {
		"No Appointments to edit/cancel\n";
		return;
	}

	int docIndex, docAppointment, deleteChoice;

	cout << "Your appointments:\n";
	for (int i = 0; i < counter + 1; i++) {
		cout << "\t(" << i + 1 << ")\n";
		cout << "Doctor name: " << parr[patientIndex].Pappointments[i].doctorName << endl;
		cout << "Date: " << parr[patientIndex].Pappointments[i].time.date.day << "/" << parr[patientIndex].Pappointments[i].time.date.month << "/" << parr[patientIndex].Pappointments[i].time.date.year << endl;
		cout << "Time: " << parr[patientIndex].Pappointments[i].time.hour << ":" << parr[patientIndex].Pappointments[i].time.minute << endl;
	}
	cout << "Choose the appointment you want to canel:\n";
	cin >> deleteChoice;
	deleteChoice--;

	//getting doctor index
	for (int i = 0; i < 50; i++) {
		if (parr[patientIndex].Pappointments[deleteChoice].doctorName == darr[i].name) {
			docIndex = i;
			break;
		}
	}

	//finding DRappointments index
	for (int i = 0; i < 20; i++) {
		if (parr[patientIndex].Pappointments[deleteChoice].time.date.day == darr[docIndex].DRappointments[i].time.date.day &&
			parr[patientIndex].Pappointments[deleteChoice].time.date.month == darr[docIndex].DRappointments[i].time.date.month &&
			parr[patientIndex].Pappointments[deleteChoice].time.hour == darr[docIndex].DRappointments[i].time.hour &&
			parr[patientIndex].Pappointments[deleteChoice].time.hour == darr[docIndex].DRappointments[i].time.minute) {
			docAppointment = i;
			break;
		}
	}


	darr[docIndex].availableTime[docAppointment].Available = true;
	counter--;

	//updating doctor appointment list
	darr[docIndex].DRappointments[docAppointment].patientName = "\0";
	darr[docIndex].DRappointments[docAppointment].time.date.day = 0;
	darr[docIndex].DRappointments[docAppointment].time.date.month = 0;
	darr[docIndex].DRappointments[docAppointment].time.hour = 0;
	darr[docIndex].DRappointments[docAppointment].time.minute = 0;


	//updating patient appointment list index by shifting it.
	for (int i = deleteChoice; i < counter; i++) {
		parr[patientIndex].Pappointments[i].doctorName = parr[patientIndex].Pappointments[i + 1].doctorName;
		parr[patientIndex].Pappointments[i].time = parr[patientIndex].Pappointments[i + 1].time;
	}

	//deleting the last appointment (it was copied to the previous appointment)
	parr[patientIndex].Pappointments[counter].doctorName = "\0";
	parr[patientIndex].Pappointments[counter].time.date.day = 0;
	parr[patientIndex].Pappointments[counter].time.date.month = 0;
	parr[patientIndex].Pappointments[counter].time.hour = 0;
	parr[patientIndex].Pappointments[counter].time.minute = 0;


	cout << "Appointment canceled successfully\n";
}


void editDoctorInfo(doctor darr[], int doctorIndex)
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
		cout << "Please enter the old password you want to change: \n";
		cin >> holder;


		// if you found it
		if (holder == darr[doctorIndex].password)
		{
			cout << "Please write the new password \n";
			cin >> darr[doctorIndex].password;
			cout << "Password Successfully updated \n";
		}
		else
		{
			cout << "This password is not correct, Please kindly try again or contact your system administrator for more details";
		}
		break;
	}

	case 2: // add a do while loop to give the user another chance to enter a name
	{
		bool flag = true;
		do {
			cout << "Please write the new username \n";
			cin >> holder;
			for (int i = 0; i < doctorLimit; i++)
			{
				if (holder == darr[doctorIndex].name)
				{
					cout << "invalid username, try another one \n";
					flag = false;
					break;
				}
			}

			if (flag) {
				cout << "username Successfully updated\n";
				darr[doctorIndex].name = holder;
			}
		} while (flag == false);
		break;
	}

	case 3:
	{
		// return to the main minu 
		doctorMenu(darr, doctorIndex);
		break;
	}

	}
}

void editPatientInfo(patient parr[], doctor darr[], int patientIndex) {
	char response;
	cout << "Want to edit your data? We're here for help\n";
	cout << "1.Edit your password" << endl;
	cout << "2.Edit your username" << endl;
	cout << "3.Main menu" << endl;
	cout << "Enter your choice :";
	cin >> response;

	string holder;
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
			cout << "This password is not correct, Please kindly try again or contact your system administrator for more details";
			patientMenu(parr, darr, patientIndex);
		}
		break;
	}

	case '2':
	{
		bool flag = true;
		do {
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
		cout << "Invalid Input. Please try again!";
		break;
	}

	}

}

void displayPatientAppointments(patient Parr[], int patienIndex) {
	cout << "Your Appointments\n";
	for (int i = 0; i < 50; i++) {
		cout << "Doctor Name: ";
		cout << Parr[patienIndex].Pappointments[i].doctorName << "\n ";
		cout << "Time of Appointment:\n";
		cout << "Date:" << Parr[patienIndex].Pappointments[i].time.date.day << "/" << Parr[patienIndex].Pappointments[i].time.date.month << "/" << Parr[patienIndex].Pappointments[i].time.date.year << "\n";
		cout << "Time" << Parr[patienIndex].Pappointments[i].time.hour << ":" << Parr[patienIndex].Pappointments[i].time.minute << "\n";
	}
}
void clearAppointment(patient Parr[], int patienIndex) {
	for (int i = 0; i < 50; i++) {
		Parr[patienIndex].Pappointments[i].time.hour = 0;
		Parr[patienIndex].Pappointments[i].time.minute = 0;
		Parr[patienIndex].Pappointments[i].time.Available = true;
		Parr[patienIndex].Pappointments[i].time.date.day = 0;
		Parr[patienIndex].Pappointments[i].time.date.month = 0;   //مش هنساوي السنة بصفر عشان هي 2022
		Parr[patienIndex].Pappointments[i].doctorName = "-1";
		Parr[patienIndex].Pappointments[i].patientName = "-1";

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
