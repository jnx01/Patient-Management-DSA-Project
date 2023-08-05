#pragma once
#include <iostream>

using namespace std;

class Doctor				//class to store login data of the user
{
public:
	string name;
	string city;
	string ID;
	string password;

	Doctor();												//constructors
	Doctor(string a, string b, string c, string d);
};
