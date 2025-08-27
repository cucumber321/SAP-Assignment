#include<iostream>
#include<string>
#include<iomanip>
#include<vector>

using namespace std;

#pragma region Registration variable needed

//
enum class Status { Pending, Approved , Rejected , Cancelled };

//status of the event
string statusOutput(Status s) {
	switch(s) {
		case Status::Pending:	return "Pending";
		case Status::Approved:	return "Approved ";
		case Status::Rejected:	return "Rejected";
		case Status::Cancelled:	return "Cancelled";
	}
	return "Unknown";
}

//data type of the registration needed
struct eventRegistrationNeeded {
	string eventId{};				//only have a id pattern only, cannot have same id
	string eventName;
	string eventType;
	int date;
	int time;
	string desiredVenue;
	Status stateOfEvent{Status::Pending};//pending or approve or cancel
	string OwnerId;
	string OwnerName;

	bool isEditableByUser() const { return stateOfEvent == Status::Pending; }
	bool isDeletableByUser() const { return stateOfEvent == Status::Pending; }

	//size of each object
	void showRow() const {
		cout << left
			<< setw(10) << eventId
			<< setw(18) << eventName
			<< setw(12) << eventType
			<< setw(12) << date
			<< setw(8) << time
			<< setw(14) << desiredVenue
			<< setw(12) << statusOutput(stateOfEvent)
			<< setw(10) << OwnerId
			<< setw(12) << OwnerName
			<< endl;
	}

	//output object
	void showDetail() const {
		cout << "\n==== Event Detail ====" << endl
			<< "Event ID: " << eventId << endl
			<< "Event Name: " << eventName << endl
			<< "Event Type: " << eventType << endl
			<< "Date: " << date << endl
			<< "Time: " << time << endl
			<< "Venue: " << desiredVenue << endl
			<< "Status: " << statusOutput(stateOfEvent) << endl
			<< "Owner Id: " << OwnerId << endl
			<< "Owner: " << OwnerName << endl;
	}
};

struct userContext {
	string userId;
	string username;
	int penaltyPoints = 0;
};

void showTableHeader() {
	cout << left
		<< setw(10) << "Event Id"
		<< setw(18) << "Event Name"
		<< setw(12) << "eventType"
		<< setw(12) << "date"
		<< setw(8) << "time"
		<< setw(14) << "desiredVenue"
		<< setw(12) << "Status"
		<< setw(10) << "Owner Id"
		<< setw(12) << "Owner Name"
		<< endl;
	cout << string(110, '-') << endl;
}

struct EventValidationCheck {
	vector<eventRegistrationNeeded> event;
	int nextId = 1001;
	eventRegistrationNeeded checkDetail;

	eventRegistrationNeeded& createEvent(string ownerName, string ownerId) {
		eventRegistrationNeeded e;
		e.eventId = to_string(nextId++);
		e.OwnerId = ownerId;
		e.OwnerName = ownerName;
		e.stateOfEvent = Status::Pending;

		event.push_back(e);
		return event.back();
	}

	bool conflictEvent(eventRegistrationNeeded& currentDetail) {
		for (int i = 0; i < event.size();i++) {
			auto& checkDetail = event[i];
			if (currentDetail.time == checkDetail.time && 
				currentDetail.desiredVenue == checkDetail.desiredVenue && 
				currentDetail.date == checkDetail.date
				) {
				if (currentDetail.stateOfEvent == Status::Pending || currentDetail.stateOfEvent == Status::Approved) {
					return true;
				}
			}
		}
		return false;
	}

	eventRegistrationNeeded* findId(string& id) {
		for (auto& e : event) {
			if (e.eventId == id) { 
				return &e;
			}
		}
		return nullptr;
	}
};



#pragma endregion

#pragma region User Function

void userCreate(EventValidationCheck& validationCheck, userContext & userContext) {
	eventRegistrationNeeded& currentEvent = validationCheck.createEvent(userContext.username, userContext.userId);

	if (validationCheck.conflictEvent(currentEvent)) {
		cout << "Conflict detected! Event rejected.\n";
		currentEvent.stateOfEvent = Status::Cancelled;
	}
	else {
		cout << "Event created successfully! Status = Pending\n";
	}
}

void userViewDetail(EventValidationCheck &validationCheck) {
	string currentId;
	cout << "Enter Id to view: ";
	cin >> currentId;
	for (eventRegistrationNeeded& i:validationCheck.event) {
		if (i.eventId == currentId) {
			i.showDetail();
			break;
		}
	}
	cout << "Event is not found" << endl;
}

eventRegistrationNeeded* findId(EventValidationCheck& validationCheck, string& id) {
	for (eventRegistrationNeeded& e : validationCheck.event) {
		if (e.eventId == id) {
			return &e;
		}
	}
	return nullptr;
}

void userDelete(EventValidationCheck& validationCheck) {
	string currentId;
	cout << "Enter Event Id to delete: ";
	string input;
	getline(cin, input);
	
	bool found = false;
	for (auto it = validationCheck.event.begin(); it != validationCheck.event.end(); ++it) {
		if (it->eventId == input) {
			cout << "Deleting Event: " << it->eventName << endl;
			validationCheck.event.erase(it);
			found = true;
			break;
		}
	}

	if (!found) {
		cout << "Event with Id " << input << " not found." << endl;
	}

}

void userList(EventValidationCheck& validationCheck) {
	if (validationCheck.event.empty()) {
		cout << "No events found." << endl;
		return;
	}

	cout << left << setw(10) << "ID"
		<< setw(30) << "Name"
		<< setw(15) << "Type"
		<< setw(10) << "Date"
		<< setw(10) << "Time"
		<< setw(20) << "Venue"
		<< setw(10) << "Status" << endl;


	for (auto& e : validationCheck.event) {
		cout << left << setw(10) << e.eventId
			<< setw(30) << e.eventName
			<< setw(15) << e.eventType
			<< setw(10) << e.date
			<< setw(10) << e.time
			<< setw(20) << e.desiredVenue;

		switch (e.stateOfEvent) {
		case Status::Pending: cout << "Pending"; break;
		case Status::Approved: cout << "Approved"; break;
		case Status::Cancelled: cout << "Cancelled"; break;
		}
		cout << endl;
	}
}

void userUpdate(EventValidationCheck& vc) {
	cout << "Enter Event Id to update: ";
	string input;
	getline(cin, input);


	eventRegistrationNeeded* currentEvent = vc.findId(input);
	if (currentEvent == nullptr) {
		cout << "Event with Id " << input << " is not found." << endl;
		return;
	}

	if (!currentEvent->isEditableByUser()) {
		cout << "Only Pending events can be updated." << endl;
		return;
	}

	cout << "Updating Event: " << currentEvent->eventName << endl;
	string temp;

	cout << "Enter new Event Name (current: " << currentEvent->eventName << "): ";
	getline(cin, temp);
	if (!temp.empty()) currentEvent->eventName = temp;

	cout << "Enter new Event Type (current: " << currentEvent->eventType << "): ";
	getline(cin, temp);
	if (!temp.empty()) currentEvent->eventType = temp;

	cout << "Enter new Desired Venue (current: " << currentEvent->desiredVenue << "): ";
	getline(cin, temp);
	if (!temp.empty()) currentEvent->desiredVenue = temp;

	cout << "Enter new Date (current: " << currentEvent->date << "): ";
	getline(cin, temp);
	if (!temp.empty()) currentEvent->date = stoi(temp);

	cout << "Enter new Time (current: " << currentEvent->time << "): ";
	getline(cin, temp);
	if (!temp.empty()) currentEvent->time = stoi(temp);

	cout << "Event updated successfully!" << endl;
}

void userCancel(EventValidationCheck& vc) {
	cout << "Enter Event Id to cancel: ";
	string input;
	getline(cin, input);

	eventRegistrationNeeded* currentEvent = vc.findId(input);
	if (currentEvent == nullptr) {
		cout << "Event with Id " << input << " is not found." << endl;
		return;
	}

	if (currentEvent->stateOfEvent == Status::Cancelled) {
		cout << "Event is already cancelled." << endl;
		return;
	}

	if (currentEvent->stateOfEvent == Status::Approved) {
		cout << " Warning: Cancelling a Confirmed event will cause penalty!" << endl;
	}

	cout << "Are you sure you want to cancel this event? (y/n): ";
	string confirm;
	getline(cin, confirm);
	if (confirm != "y" && confirm != "Y") {
		cout << "Cancel operation aborted." << endl;
		return;
	}

	currentEvent->stateOfEvent = Status::Cancelled;
	cout << "Event has been cancelled successfully." << endl;
}

#pragma endregion

void EventRegistration() {
	EventValidationCheck vc;
	userContext user{ "lim0001","Lim Wei Bo" };

	auto& e1 = vc.createEvent(user.username, user.userId);
	e1.eventName = "Programming Workshop";
	e1.eventType = "Workshop";
	e1.date = 20250828;
	e1.time = 1400;
	e1.desiredVenue = "Hall A";

	auto& e2 = vc.createEvent(user.username, user.userId);
	e2.eventName = "AI Seminar";
	e2.eventType = "Seminar";
	e2.date = 20250829;
	e2.time = 1000;
	e2.desiredVenue = "Conference Room";

	auto& e3 = vc.createEvent(user.username, user.userId);
	e3.eventName = "Team Building";
	e3.eventType = "Recreation";
	e3.date = 20250830;
	e3.time = 1600;
	e3.desiredVenue = "Garden";

	string choice;
	bool validInput = true;

	do {
		system("CLS");
		cout << setfill('-') << setw(50) << "-" << endl;
		cout << "Welcome to Hotel Events Registration Funciton" << endl;
		cout << setfill('-') << setw(50) << "-" << endl;
		cout << "== User Menu (" << user.username << ") penalty: " << user.penaltyPoints << " ==\n";
		cout << "1. Create " << endl;
		cout << "2. List Mine" << endl;
		cout << "3. View Detail " << endl;
		cout << "4. Update (only Pending)" << endl;
		cout << "5. Delete (only Pending)" << endl;
		cout << "6. Cancel (Confirmed status will cause penalty)" << endl;
		cout << "0. Exit  " << endl;

		if (!validInput) {
			cout << "Invalid Input. Please try again." << endl;
			validInput = true; 

		}

		cout << "Enter choice: ";
		getline(cin, choice);

		if (choice == "0") {
			break;
		}

		else if (choice == "1") {
			userCreate(vc, user);
			system("pause");
			return;
		}

		else if (choice == "2") {
			userList(vc);
			system("pause");
			return;
		}

		else if (choice == "3") {
			userViewDetail(vc);
			system("pause");
			return;
		}

		else if (choice == "4") {
			userUpdate(vc);
			system("pause");
			return;
		}

		else if (choice == "5") {
			userDelete(vc);
			system("pause");
			return;
		}

		else if (choice == "6") {
			userCancel(vc);
			system("pause");
			return;
		}

		else {
			validInput = false;
		}

	} while (true);
}
