#include <iostream>
#include <windows.h>					//to use Sleep function
#include "CVPMSystem.h"

using namespace std;


int main()
{
	CVPMSystem obj;
	int option = 0;

	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t     Weclome to Corona Virus Patient Management System";
	Sleep(2000);

	obj.login();						//start login function. User cannot access program without logging in with correct ID nad password
	obj.readFromFile();					//reading patient data from file and making queue aftewr the user successfully logged in

	while (1)
	{
		Sleep(500);
		system("CLS");

		cout << "\n\n\n\n\n\n\n\t\t\t\t\t      Enter 1 to add patient record, "					//Main menu
			<< "\n\n\t\t\t\t\t\t2 to delete patient record, "
			<< "\n\n\t\t\t\t\t        3 to search patient record, "
			<< "\n\n\t\t\t\t\t\t 4 to edit patient record, "
			<< "\n\n\t\t\t\t      5 to find the city with the most COVID-19 cases, "
			<< "\n\n\t\t\t\t      6 to find total number of active COVID-19 cases, "
			<< "\n\n\t\t\t\t      7 to total number of patients on ventilator, or"
			<< "\n\n\t\t\t\t\t\t\t0 to exit.\n\n\n\t\t\t\t\t\t\t     ";
		cin >> option;

		Sleep(500);								//adding a slight delay and clearing screen
		system("CLS");

		if (option == 1)						//starting functions according to user choice
		{
			obj.addPatient();
		}
		else if (option == 2)
		{
			obj.deletePatient();
		}
		else if (option == 3)
		{
			obj.searchPatient();
		}
		else if (option == 4)
		{
			obj.editPatient();
		}
		else if (option == 5)
		{
			obj.mostPatients();
		}
		else if (option == 6)
		{
			obj.activeCases();
		}
		else if (option == 7)
		{
			obj.criticalPatients();
		}
		else
		{
			break;
		}

	}

	Sleep(300);
	system("CLS");
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tGoodbye.\n\n\n\n\n\n\n\n\n\n\n\n";

	obj.writeToFile();					//After user exits, patient record file is truncated and queue data is stored in file
	obj.~CVPMSystem();					//After queue data is stored in file, destructor is invoked to free memory.

}
