#include <iostream>
#include <windows.h>					//to use Sleep function
#include <string>						//to use functions like getline
#include <fstream>						//for filing
#include "Doctor.h"
#include "CVPatient.h"
#include "CVPMSystem.h"


using namespace std;


string loginFile = "Credentials.txt";						//the file with all the ID and Passwords used for login

string recordFile = "PatientRecord.txt";					//this file stores all patient data




//Default constructor for Doctor class
Doctor::Doctor() : name(""), city(""), ID(""), password("")
{}

//Paremeterized constructor for Doctor class
Doctor::Doctor(string a, string b, string c, string d) : name(a), city(b), ID(c), password(d)
{}





//Default constructor for CVPatient class
CVPatient::CVPatient() : name(""), gender('M'), city(""), patientID(0), CRPLevel(10.0), fever(0), dryCough(0), tiredness(0), tastelessness(0), positivity(0), severity("NA"), next(NULL)
{}

//Paremeterized constructor for CVPatient class
CVPatient::CVPatient(string a, char b, string c, int d, float e, bool f, bool g, bool h, bool i, bool j, string k) : name(a), gender(b), city(c), patientID(d), CRPLevel(e), fever(f), dryCough(g), tiredness(h), tastelessness(i), positivity(j), severity(k), next(NULL)
{}






//Default constructor for CVSystem class
CVPMSystem::CVPMSystem() : front(NULL), rear(NULL)
{}

//Destructor for CVSystem class
CVPMSystem::~CVPMSystem()
{
	if (front != NULL)
	{
		while (front != NULL)					//loop to delete all nodes
		{
			CVPatient* temp = front;
			front = front->next;
			delete temp;
		}
	}
}

//Function to add new login info in permanent storage
void CVPMSystem::signup()				//can be connected to the databse of hospitals to confirm new signups match with records in database
{
	Sleep(500);
	system("CLS");						//waiting for 0.5 second and then clearing the screen

	cin.ignore();
	cout << "\n\tEnter name: ";
	getline(cin, user.name);
	cin.ignore();
	cout << "\n\tEnter city: ";
	getline(cin, user.city);
	cin.ignore();
	cout << "\n\tEnter ID: ";
	getline(cin, user.ID);
	cin.ignore();
	cout << "\n\tEnter password: ";
	getline(cin, user.password);

	ofstream out(::loginFile, ios::app);
	if (!out)
	{
		cout << "\n\tError opening file.\n";
	}
	else												//sotring new sign up information in file
	{
		out << user.name << endl
			<< user.city << endl
			<< user.ID << endl
			<< user.password << endl;
		out.close();

		cout << "\n\n\n\n\t\t\t\t\t    New login credentials added.\n";
		Sleep(1500);
	}
}

//Function for logging in, signing up or exiting the program. Program won't go ahead of this function until user logs in
void CVPMSystem::login()
{
	int check = 0;

	while (check != 1)
	{
		Sleep(500);
		system("CLS");
		int option;
		Doctor temp;

		while (1)				//loop asking user to login, signup or exit. User cannot go ahead if he does not login with correct ID and pass
		{
			cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t     Enter 1 to login, 2 to sign up, or 0 to exit\n\n\t\t\t\t\t\t\t   ";
			cin >> option;

			if (option == 1)
			{
				break;
			}
			else if (option == 2)		//sign up and then restarting loop so user can login
			{
				signup();
				user.name = "";
				Sleep(500);
				system("CLS");
				continue;
			}
			else if (option == 0)		//exitting
			{
				Sleep(500);
				system("CLS");
				cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tGoodbye.\n\n\n\n\n\n\n\n\n\n\n\n";
				exit(0);
			}
			else									//in case of wrong input
			{
				cout << "\n\n\t\t\t\t\t\tIncorrect input. Try again.\n";
				Sleep(2000);
				system("CLS");
			}
		}

		Sleep(500);
		system("CLS");

		cin.ignore();
		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t  Enter ID: ";			//taking login input
		getline(cin, user.ID);
		cin.ignore();
		cout << "\n\n\t\t\t\t\t\tEnter password: ";
		getline(cin, user.password);

		ifstream in(::loginFile, ios::in);
		while (!in.eof())
		{
			getline(in, temp.name);						//taking input from file
			getline(in, temp.city);
			getline(in, temp.ID);
			getline(in, temp.password);

			if (temp.ID == user.ID && temp.password == user.password)			//if match found in file, program welcomes user
			{
				in.close();
				check = 1;
				user.name = temp.name;
				user.city = temp.city;
				temp.name = temp.name.substr(0, temp.name.find(" "));
				Sleep(500);
				system("CLS");
				cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tWelcome, Dr. " << temp.name << endl;
				Sleep(500);
				break;
			}
		}

		if (in.eof() && user.name == "")						//if no login match found, loop restarts
		{
			Sleep(500);
			system("CLS");
			cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t   Entered username and password don't match any record.\n";
			Sleep(2000);
			system("CLS");
		}
	}
}

//Function tests patients for COVID19 when reocrd is added or updated
void CVPMSystem::TestPatient(CVPatient* obj)
{
	if ((obj->CRPLevel >= 11.0) && (obj->fever == true || obj->dryCough == true || obj->tiredness == true || obj->tastelessness == true))
	{
		obj->positivity = true;

		if (obj->CRPLevel >= 11.0 && obj->CRPLevel < 15.0)			//CRP tests are used to check if patient has COVID19 or not (10 is normal level, values abve 10 mean patient has virus)
		{
			obj->severity = "Mild";
		}
		else if (obj->CRPLevel >= 15.0 && obj->CRPLevel < 20.0)
		{
			obj->severity = "Moderate";
		}
		else
		{
			obj->severity = "Severe";
		}

		cout << "\n\n\n\tTest results: ";
		cout << "\n\n\tCOVID-19 : Positive";
		cout << "\n\n\tSeverity : " << obj->severity << "\n\n";
	}
	else
	{
		cout << "\n\n\n\tTest results: ";
		cout << "\n\n\tCOVID-19 : Negative";
		cout << "\n\n\tSeverity : NA\n\n";
	}
}

//Utility function to take input from user. Used in Add and Edit functions
void CVPMSystem::patientInput(CVPatient* obj)
{
	string temp;
	int option;
	char symptom;

	cin.ignore();
	cout << "\n\n\n\tEnter name: ";
	getline(cin, temp);
	if (temp != "X" && temp != "x")				//if user enter X or x the value is kept unchanged
	{
		obj->name = temp;
	}

	cin.ignore();
	cout << "\n\tEnter gender (M or F): ";
	cin >> temp;
	if (temp != "X" && temp != "x")
	{
		if (temp == "M" || temp == "m")
		{
			obj->gender = 'M';
		}
		else
		{
			obj->gender = 'F';
		}
	}

	cin.ignore();
	cout << "\n\tEnter 1 if the city is Islamabad, \n\t2 if it's Lahore, \n\t3 if it's Karachi, \n\t4 if it's Peshawar, \n\tor 5 if it's Quetta \n\n\t        ";
	cin >> temp;
	if (temp != "X" && temp != "x")
	{
		option = stoi(temp);

		if (option == 1)
		{
			obj->city = "Islamabad";
		}
		else if (option == 2)
		{
			obj->city = "Lahore";
		}
		else if (option == 3)
		{
			obj->city = "Karachi";
		}
		else if (option == 4)
		{
			obj->city = "Peshawar";
		}
		else
		{
			obj->city = "Quetta";
		}
	}

	cin.ignore();
	cout << "\n\tEnter patient ID : ";
	cin >> temp;
	if (temp != "X" && temp != "x")
	{
		obj->patientID = stoi(temp);				//stoi converts string to integer
	}

	cin.ignore();
	cout << "\n\tEnter patient's Blood CRP (inflammation) level (mg/L) : ";
	cin >> temp;
	if (temp != "X" && temp != "x")
	{
		obj->CRPLevel = stof(temp);				//stoi converts string to float
	}

	cin.ignore();
	cout << "\n\tDoes the patient show signs of fever? (Y or N): ";
	cin >> temp;
	if (temp != "X" && temp != "x")
	{
		if (temp == "Y" || temp == "y")					//setting bool values
		{	
			obj->fever = true;
		}
		else	
		{	
			obj->fever = false;
		}
	}

	cin.ignore();
	cout << "\n\tDoes the patient show signs of dry cough? (Y or N): ";
	cin >> temp;
	if (temp != "X" && temp != "x")
	{
		if (temp == "Y" || temp == "y")
		{
			obj->dryCough = true;
		}
		else
		{
			obj->dryCough = false;
		}
	}

	cin.ignore();
	cout << "\n\tDoes the patient show signs of chronic fatigue? (Y or N): ";
	cin >> temp;
	if (temp != "X" && temp != "x")
	{
		if (temp == "Y" || temp == "y")
		{
			obj->tiredness = true;
		}
		else
		{
			obj->tiredness = false;
		}
	}

	cin.ignore();
	cout << "\n\tDoes the patient show signs of tastelessness? (Y or N): ";
	cin >> temp;
	if (temp != "X" && temp != "x")
	{
		if (temp == "Y" || temp == "y")
		{
			obj->tastelessness = true;
		}
		else
		{
			obj->tastelessness = false;
		}
	}

	this->TestPatient(obj);					//setting positivty and severity of CV

	Sleep(2000);
}

//Function to add new patient record. It calls the Input function then connects new node in the end
void CVPMSystem::addPatient()
{
	CVPatient* newPatient = new CVPatient;
	patientInput(newPatient);

	if (front == NULL && rear == NULL)
	{
		front = rear = newPatient;
	}
	else
	{
		rear->next = newPatient;
		rear = newPatient;
	}
	cout << "\n\n\t\t\t\t\t\tNew patient record added.\n";
	Sleep(1500);
		
}

//Utility function used in Edit, Delete and Search
void CVPMSystem::displayRecord(CVPatient* obj)
{
	cout << "\n\n\n\t\t\t\t\t\tPatient name: " << obj->name
		<< "\n\n\t\t\t\t\t\tGender: " << obj->gender
		<< "\n\n\t\t\t\t\t\tCity: " << obj->city
		<< "\n\n\t\t\t\t\t\tPatient ID: " << obj->patientID
		<< "\n\n\t\t\t\t\t\tBlood CRP level (mg/L) : " << obj->CRPLevel;

	cout << "\n\n\t\t\t\t\t\tFever: ";
	if (obj->fever == true)
	{
		cout << "Y";
	}
	else
	{
		cout << "N";
	}

	cout << "\n\n\t\t\t\t\t\tDry cough: ";
	if (obj->dryCough == true)
	{
		cout << "Y";
	}
	else
	{
		cout << "N";
	}

	cout << "\n\n\t\t\t\t\t\tChronic Fatigue: ";
	if (obj->tiredness == true)
	{
		cout << "Y";
	}
	else
	{
		cout << "N";
	}

	cout << "\n\n\t\t\t\t\t\tTastelessness: ";
	if (obj->tastelessness == true)
	{
		cout << "Y";
	}
	else
	{
		cout << "N";
	}

	cout << "\n\n\t\t\t\t\t\tCOVID-19 test: ";
	if (obj->positivity == true)
	{
		cout << "Positive";
	}
	else
	{
		cout << "Negative";
	}

	cout << "\n\n\t\t\t\t\t\tSeverity: " << obj->severity << "\n\n";

}

//Function for deleting node of a patient
void CVPMSystem::deletePatient()
{
	if (front == NULL)
	{
		cout << "\nNo data in queue.\n";
	}
	else
	{
		CVPatient* curr = front;				//used to find the node to delete and the node before it
		CVPatient* prev = front;

		int IDnum;
		int check = 0;

		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tEnter identification number of patient: ";
		cin >> IDnum;

		while (curr != NULL)					//finding node to delete
		{
			if (curr->patientID == IDnum)		//match found
			{
				break;
			}
			else								//match not found yet
			{
				prev = curr;
				curr = curr->next;
			}
		}

		if (curr == NULL)						//no match found in all the records
		{
			cout << "\n\n\t\t\t\t\t\tNo match found.\n";
		}
		else												//match found
		{
			displayRecord(curr);
			cout << "\n\n\n\n\t\t\t\t   Enter 1 to confirm deletion or 2 to cancel: \n\n\t\t\t\t\t\t\t";		//taking user confirmation after displaying record
			cin >> check;

			if (check == 1)
			{
				if (front == rear)			//only one node in queue
				{
					front = rear = NULL;
				}
				else if (curr == front && front != rear)		//first node to be deleted
				{
					front = front->next;
				}
				else if (curr == rear && front != front)		//last node to be deleted
				{
					prev->next = NULL;
					rear = prev;
				}
				else											//deleting from the middle
				{
					prev->next = curr->next;
				}

				delete curr;
				cout << "\n\n\n\t\t\t\t\t\tRecord deleted.\n";
			}
			else
			{
				cout << "\n\n\n\t\t\t\t\t\tOperation cancelled.\n";
			}
			Sleep(500);
		}
	}
}

//Function to find and display record of a patient. It looks for the record in the queue
void CVPMSystem::searchPatient()
{
	if (front == NULL)
	{
		cout << "\nNo data in queue.\n";
	}
	else
	{

		CVPatient* curr = front;
		int IDnum;

		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tEnter identification number of patient: ";
		cin >> IDnum;

		while (curr != NULL)						//loop to find node with matching ID number
		{
			if (curr->patientID == IDnum)
			{
				break;
			}
			else
			{
				curr = curr->next;
			}
		}

		if (curr == NULL)					//in case no match is found
		{
			cout << "\n\n\n\t\t\t\t\t\t     No match found.\n";
			Sleep(500);
		}
		else
		{
			cout << "\n\n\tRecord match found: \n\n";		//displaying record if match found
			displayRecord(curr);
			Sleep(4500);
		}
	}
}

//Function to edit the record of a patient. It looks for the record in the queue.
void CVPMSystem::editPatient()
{
	if (front == NULL)
	{
		cout << "\nNo data in queue.\n";
	}
	else
	{

		CVPatient* curr = front;

		int IDnum;

		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tEnter identification number of patient: ";
		cin >> IDnum;

		while (curr != NULL)					//loop to find the node to be edited
		{
			if (curr->patientID == IDnum)
			{
				break;
			}
			else
			{
				curr = curr->next;
			}
		}

		if (curr == NULL)							//if no match is found in the queue
		{
			cout << "\n\n\n\t\t\t\t\t\t     No match found.\n";
		}
		else										//if match found, show record, take new input and then show modified record
		{
			cout << "\n\n\tRecord match found: \n\n";
			displayRecord(curr);
			cout << "\n\n\n\tStarting new input. Enter 'X' for the values you want to keep the same.\n";
			patientInput(curr);
			cout << "\n\n\tAfter modification: \n\n";
			displayRecord(curr);
			Sleep(4500);
		}
	}
}

//Function to find the city with the highest number of cases
void CVPMSystem::mostPatients()
{
	if (front == NULL)
	{
		cout << "\nNo data in queue.\n";
	}
	else
	{
		CVPatient* ptr = front;
		string cities[5] = { "Islamabad" , "Lahore" , "Karachi" , "Peshawar" , "Quetta" };		//array with city names
		int patients[5];																		// array to store patients for each city
		int largestIndex = 0;
		int largest = 0;

		for (int i = 0; i < 5; ++i)				//initializing patient array with 0
		{
			patients[i] = 0;
		}

		while (ptr != NULL)						//counting patients for each city
		{
			if (ptr->city == "Islamabad")
			{
				++patients[0];
			}
			else if (ptr->city == "Lahore")
			{
				++patients[1];
			}
			else if (ptr->city == "Karachi")
			{
				++patients[2];
			}
			else if (ptr->city == "Peshawar")
			{
				++patients[3];
			}
			else
			{
				++patients[4];
			}
			ptr = ptr->next;
		}

		for (int i = 0; i < 5; ++i)				//finding highest patient count and the city
		{
			if (largest < patients[i])
			{
				largest = patients[i];
				largestIndex = i;
			}
		}

		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t   The city with the most COVID-19 patients is '" << cities[largestIndex] << "' with '" << largest << "' patients.\n\n";
		Sleep(3000);
	}
}

//BONUS function: displays total active cases in the country
void CVPMSystem::activeCases()
{
	float MPatients = 0.0;
	float active = 0.0;
	CVPatient* curr = front;

	while (curr != NULL)						//loop to find to total active cases and how many of those are male
	{
		if (curr->positivity == true)
		{
			++active;
			if (curr->gender == 'M')
			{
				++MPatients;
			}
		}
		curr = curr->next;
	}

	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t  Total number of active cases in Pakistan: " << active		//displaying total active cases, percentage of male patients and percentage of female patients
		<< "\n\n\t\t\t\t\t\t   Male percentage: " << (float)((MPatients / active) * 100) << " %"
		<< "\n\n\t\t\t\t\t\t  Female percentage: " << (float)(((active – MPatients) / active) * 100)) <<" %\n\n";
	Sleep(3500);
}

//BONUS function: displays total patients using ventilator (in the country)
void CVPMSystem::criticalPatients()
{
	float MPatients = 0.0;
	float critical = 0.0;
	CVPatient* curr = front;

	while (curr != NULL)						//loop to find to total patients on ventilator and how many of those are male
	{
		if (curr->severity == "Severe")
		{
			++critical;
			if (curr->gender == 'M')
			{
				++MPatients;
			}
		}
		curr = curr->next;
	}

	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t  Total number of patients on ventilator : " << (int)critical 		//displaying total patients on ventilator, percentage of male patients and percentage of female patients
		<< "\n\n\t\t\t\t\t\t   Male percentage: " << (float)((MPatients / critical) * 100) << " %"
		<< "\n\n\t\t\t\t\t\t  Female percentage: " << (float)(((critical – MPatients) / critical) * 100)) << " %\n\n";
	Sleep(4000);
}

//Utility function to read patient records from file and make a queue
void CVPMSystem::readFromFile()
{
	ifstream in(::recordFile, ios::in);
	string line;
	CVPatient* newPatient;

	if (!in)
	{
		cout << "\nError opening file.\n";
	}
	else
	{
		while (!in.eof())
		{
			newPatient = new CVPatient;				//taking input from file and makling records

			getline(in, newPatient->name);
			getline(in, line);
			newPatient->gender = line[0];
			getline(in, newPatient->city);
			getline(in, line);
			newPatient->patientID = stoi(line);
			getline(in, line);
			newPatient->CRPLevel = stof(line);
			getline(in, line);
			if (line == "1")
			{
				newPatient->fever = true;
			}
			getline(in, line);
			if (line == "1")
			{
				newPatient->dryCough = true;
			}
			getline(in, line);
			if (line == "1")
			{
				newPatient->tiredness = true;
			}
			getline(in, line);
			if (line == "1")
			{
				newPatient->tastelessness = true;
			}
			getline(in, line);
			if (line == "1")
			{
				newPatient->positivity = true;
			}
			getline(in, newPatient->severity);


			if (front == NULL && rear == NULL)						//if queue is empty
			{
				front = rear = newPatient;
			}
			else													//if queue is not empty
			{
				if (newPatient->name != "")							//checking if record has data or not (due to empty line in end of file)
				{
					rear->next = newPatient;
					rear = newPatient;
				}
				else												//if record is empty delete it
				{
					delete newPatient;
				}
			}
		}

		in.close();
	}
}

//utility function to truncate data from file and write all data in the queue in the file
void CVPMSystem::writeToFile()
{
	ofstream out(::recordFile, ios::trunc);
	CVPatient* obj = front;

	if (!out)
	{
		cout << "\nError opening file.\n";
	}
	else
	{
		while (obj != NULL)										//storign all queue data in file
		{
			out << obj->name << endl
				<< obj->gender << endl
				<< obj->city << endl
				<< obj->patientID << endl
				<< obj->CRPLevel << endl
				<< obj->fever << endl
				<< obj->dryCough << endl
				<< obj->tiredness << endl
				<< obj->tastelessness << endl
				<< obj->positivity << endl
				<< obj->severity << endl;

			obj = obj->next;
		}

		out.close();
	}
}
