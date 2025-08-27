#include <iostream>
#include <iomanip>
#include <limits>
#include <list>
#include <cstring>   
using namespace std;

struct Facility {
    char facilityName[50];  
    char facilityModel[20];  
    int quantity;
    bool availability;
    double rentalFee;
};

struct Venue {
    char venueName[50];     
    double width;
    double length;
    list<Facility> facilityProvided;
};

list<Venue> venueList;
list<Facility> facilityList;

void addFacility();
void addVenue();
void generateFloorPlan();
void viewVenue();
void updateStatus();
void deleteFacility();

void addFacility() {
    Facility facility;
    bool found = false;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    do {
        cout << "Enter facility name (max 49 chars)(0 to exit): ";
        cin.getline(facility.facilityName, 50);
        if (strlen(facility.facilityName) == 0) {
            cout << "Facility name cannot be empty.\n";
        }
        else if((facility.facilityName=='0')){
            return;
        }
    } while (strlen(facility.facilityName) == 0);

    do {
        cout << "Enter facility model (max 19 chars): ";
        cin.getline(facility.facilityModel, 20);
        if (strlen(facility.facilityModel) == 0) {
            cout << "Facility model cannot be empty.\n";
        }
        else if((facility.facilityModel=='0')){
            return;
        }
    } while (strlen(facility.facilityModel) == 0);

    while (true) {
        cout << "Enter quantity (0 to exit): ";
        cin >> facility.quantity;
        if (cin.fail() || facility.quantity < 0) {
            cout << "Invalid input. Quantity must be a positive integer.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } 
        else if(facility.quantity==0){
            return;
        }
        else break;
    }

    facility.availability = true;

    while (true) {
        cout << "Enter rental fee: ";
        cin >> facility.rentalFee;
        if (cin.fail() || facility.rentalFee < 0) {
            cout << "Invalid input. Rental fee must be a non-negative number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } 
        else if(facility.rentalFee==0){
            return;
        }
        else break;
    }

    for (auto it = facilityList.begin(); it != facilityList.end(); ++it) {
        if (strcmp(it->facilityName, facility.facilityName) == 0 &&
            strcmp(it->facilityModel, facility.facilityModel) == 0) {
            it->quantity += facility.quantity;
            found = true;
            break;
        }
    }

    if (!found) {
        facilityList.push_back(facility);
    }

    cout << "\nCurrent facilities:\n";
    for (const Facility& i : facilityList) {
        cout << i.facilityName << " " << i.facilityModel << " "
             << i.quantity << " " << (i.availability ? "Available" : "Unavailable")
             << " " << i.rentalFee << endl;
    }
}

void addVenue() {
    Venue venue;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    do {
        cout << "Enter venue name (max 49 chars): ";
        cin.getline(venue.venueName, 50);
        if (strlen(venue.venueName) == 0) {
            cout << "Venue name cannot be empty.\n";
        }
        else if((venue.venueName=='0')){
            return;
        }
    } while (strlen(venue.venueName) == 0);

    while (true) {
        cout << "Enter venue width (m): ";
        cin >> venue.width;
        if (cin.fail() || venue.width < 0) {
            cout << "Invalid input. Width must be a positive number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } 
        else if(venue.width==0){
            return;
        }
        else break;
    }

    while (true) {
        cout << "Enter venue length (m): ";
        cin >> venue.length;
        if (cin.fail() || venue.length < 0) {
            cout << "Invalid input. Length must be a positive number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } 
        else if(venue.length==0){
            return;
        }
        else break;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    while (true) {
        Facility facility;
        string choice;

        do {
        cout << "Enter facility name (max 49 chars)(x to exit): ";
        cin.getline(facility.facilityName, 50);
        if (strlen(facility.facilityName) == 0) {
            cout << "Facility name cannot be empty.\n";
        }
        else if((facility.facilityName=='0')||(facility.facilityName=='0')){
            return;
        }
        } while (strlen(facility.facilityName) == 0);
    
        do {
            cout << "Enter facility model (max 19 chars): ";
            cin.getline(facility.facilityModel, 20);
            if (strlen(facility.facilityModel) == '0') {
                cout << "Facility model cannot be empty.\n";
            }
            else if((facility.facilityModel=='0')){
                return;
            }
        } while (strlen(facility.facilityModel) == 0);
    
        while (true) {
            cout << "Enter quantity (0 to exit): ";
            cin >> facility.quantity;
            if (cin.fail() || facility.quantity < 0) {
                cout << "Invalid input. Quantity must be a positive integer.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } 
            else if(facility.quantity==0){
                return;
            }
            else break;
        }
        
        facility.availability = false;

       while (true) {
            cout << "Enter rental fee: ";
            cin >> facility.rentalFee;
            if (cin.fail() || facility.rentalFee < 0) {
                cout << "Invalid input. Rental fee must be a non-negative number.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } 
            else if(facility.rentalFee==0){
                return;
            }
            else break;
        }

        venue.facilityProvided.push_back(facility);

        do {
            cout << "Any facility? (Y/N): ";
            cin >> choice;
            if (choice != "Y" && choice != "N") {
                cout << "Please enter only Y or N.\n";
            }
        } while (choice != "Y" && choice != "N");

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (choice == "N") break;
    }

    venueList.push_back(venue);
}

void generateFloorPlan() {
    char venueName[50];
    bool hasVenue=false;
    
    cout << "Enter venue: ";
    cin >> setw(50) >> venueName;
    
    for (auto it = venueList.begin(); it != venueList.end(); ++it) {
        if (strcmp(it->venueName, venueName) == 0) {
            cout << setw(static_cast<int>(it->length / 2)) << "Floor Plan of " << it->venueName << endl;
            for (int i = static_cast<int>(it->width / 2); i >= 0; i--) {
                for (int j = static_cast<int>(it->length); j >= 0; j--) {
                    if ((j == static_cast<int>(it->length / 2)) || (j == 0) ||
                        (i == static_cast<int>(it->width)) || (i == 0)) {
                        cout << "+";
                    } else {
                        cout << " ";
                    }
                }
                cout << endl;
            }
            cout << "*Note: 1\"+\"=2 meters" << endl;
            hasVenue=true;
        }
    }
    if(!(hasVenue)){
        cout<<"Venue not found";
    }
}

void viewVenue() {
    for (Venue i : venueList) {
        cout << i.venueName << " " << i.width << " " << i.length << endl;
        for (Facility j : i.facilityProvided) {
            cout << j.facilityName << " " << j.facilityModel << " "
                 << j.quantity << " " << (j.availability ? "Available" : "Unavailable")
                 << " " << j.rentalFee << endl;
        }
    }
}

void updateStatus() {
    char facility[50];
    cout << "Enter the facility name you want to change its status: ";
    cin >> setw(50) >> facility;

    for (auto it = facilityList.begin(); it != facilityList.end(); ++it) {
        if (strcmp(it->facilityName, facility) == 0) {
            char response;
            cout << "Currently the status of " << it->facilityName << " is "
                 << (it->availability ? "Available" : "Unavailable")
                 << ", do you want to change it? (Y/N): ";
            do {
                cin >> response;
                if (response != 'Y' && response != 'N') {
                    cout << "Please enter Y or N: ";
                }
            } while (response != 'Y' && response != 'N');

            if (response == 'Y') {
                it->availability = !(it->availability);
                cout << "Status updated.\n";
            }
            return;
        }
    }

    cout << "Facility not found\n";
}

void deleteFacility() {
    char name[50], model[20];
    bool found = false;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    do {
        cout << "Enter facility name to remove: ";
        cin.getline(name, 50);
        if (strlen(name) == 0) {
            cout << "Facility name cannot be empty.\n";
        }
        else if(facility.facilityName=='0'){
            return;
        }
    } while (strlen(name) == 0);

    do {
        cout << "Enter facility model to remove: ";
        cin.getline(model, 20);
        if (strlen(model) == 0) {
            cout << "Facility model cannot be empty.\n";
        }
    } while (strlen(model) == 0);

    for (auto it = facilityList.begin(); it != facilityList.end(); ++it) {
        if (strcmp(it->facilityName, name) == 0 &&
            strcmp(it->facilityModel, model) == 0) {
            facilityList.erase(it);
            found = true;
            cout << "Facility removed successfully.\n";
            break;
        }
    }

    if (!found) {
        cout << "Facility not found.\n";
    }

    cout << "\nUpdated facility list:\n";
    for (const Facility& f : facilityList) {
        cout << f.facilityName << " " << f.facilityModel << " "
             << f.quantity << " " << (f.availability ? "Available" : "Unavailable")
             << " " << f.rentalFee << endl;
    }
}

int main() {
    while (true) {
        int choice;

        cout << "\nVenue management" << endl;
        cout << "----------------" << endl;
        cout << "1. Add new facility" << endl;
        cout << "2. Add new venue" << endl;
        cout << "3. View venue" << endl;
        cout << "4. Display floor plan" << endl;
        cout << "5. Update status" << endl;
        cout << "6. Delete facility" << endl;
        cout << "0. Exit" << endl;

        while (true) {
            cout << endl << "Enter choice: ";
            cin >> choice;
            if ((cin.fail()) || (choice < 0) || (choice > 9)) {
                cout << "Invalid input! Expected an integer from 0 to 9." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else break;
        }

        switch (choice) {
            case 1:
                addFacility();
                break;
            case 2:
                addVenue();
                break;
            case 3:
                viewVenue();
                break;
            case 4:
                generateFloorPlan();
                break;
            case 5:
                updateStatus();
                break;
            case 6:
                deleteFacility();
                break;
            case 0:
                return 0;
        }
    }
    return 0;
}
