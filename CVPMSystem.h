#pragma once
#include <iostream>
#include "Doctor.h"
#include "CVPatient.h"

using namespace std;


class CVPMSystem				//class for entire system. This class acts like queue class
{
public:
	Doctor user;				//Composition. This object stores data of user who is using the program
	CVPatient* front;			//Composition. This pointer points to the first node of the queue
	CVPatient* rear;			//Composition. This pointer points to the last node of the queue

	CVPMSystem();				//constructor and destructor
	~CVPMSystem();
	void signup();				//all function prototypes
	void login();
	void TestPatient(CVPatient* obj);
	void patientInput(CVPatient* obj);
	void addPatient();
	void displayRecord(CVPatient* obj);
	void deletePatient();
	void searchPatient();
	void editPatient();
	void mostPatients();
	void activeCases();
	void criticalPatients();
	void readFromFile();
	void writeToFile();

};
