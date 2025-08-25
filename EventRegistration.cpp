#include<iostream>
#include<string>
#include<iomanip>

using namespace std;

struct eventRegistrationNeeded {
	string eventType;
	int date;
	int time;
	string desiredVenue;
	bool stateOfEvent;//pending or approve or cancel
};

void EventRegistration() {
	
	do {
		system("CLS");
		cout << setfill('-') << setw(50) << "-" << endl;
		cout << "Welcome to Hotel Events Registration Funciton" << endl;
		cout << setfill('-') << setw(50) << "-" << endl;

	} while (true);
}