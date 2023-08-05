#pragma once
#include <iostream>

using namespace std;

class CVPatient					//class to store patient data. This class acts like the node
{
public:
	string name;
	char gender;
	string city;
	int patientID;
	float CRPLevel;
	bool fever;
	bool dryCough;
	bool tiredness;
	bool tastelessness;
	bool positivity;
	string severity;
	CVPatient* next;			//pointer to next node


	CVPatient();					//Constructors
	CVPatient(string a, char b, string c, int d, float e, bool f, bool g, bool h, bool i, bool j, string k);

};
