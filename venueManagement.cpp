#include <iostream>
#include <limits>
#include <list>
#include <algorithm>

using namespace std;

struct Facility{
  string facilityName;
  string facilityModel;
  int quantity;
  bool availability;
  double rentalFee;
};

struct Venue{
  string venueName;
  double width;
  double length;
  list<Facility> facilityProvided; 
};

list<Venue> venueList;
list<Facility> facilityList;

void addFacility();

void addFacility() {
    Facility facility;
    bool found = false;
    cout << "Enter facility name: ";
    getline(cin, facility.facilityName);
    cout << "Enter facility model: ";
    getline(cin, facility.facilityModel);
    cout << "Enter quantity: ";
    cin >> facility.quantity;
    facility.availability = true;
    cout << "Enter rental fee: ";
    cin >> facility.rentalFee;
    for (auto it = facilityList.begin(); it != facilityList.end(); ++it) {
        if (it->facilityName == facility.facilityName && it->facilityModel == facility.facilityModel) {
            it->quantity += facility.quantity;  
            found = true;
            break;
        }
    }
    if (!found) {
        facilityList.push_back(facility); 
    }
    cout << "\nCurrent facilities:\n";
    for (const Facility& f : facilityList) {
        cout << f.facilityName << " " << f.facilityModel << " "
             << f.quantity << " " << (f.availability ? "Available" : "Unavailable")
             << " " << f.rentalFee << endl;
    }
}

void addVenue(){
    Venue venue;
    cout<<"Enter venue name: ";
    getline(cin,venue.venueName);
    cout<<"Enter venue width: ";
    cin>>venue.width;
    cout<<"Enter venue length: ";
    cin>>venue.length;
    while(true){
        Facility facility;
        cout << "Enter facility name: ";
        getline(cin, facility.facilityName);
        cout << "Enter facility model: ";
        getline(cin, facility.facilityModel);
        cout << "Enter quantity: ";
        cin >> facility.quantity;
        cout << "Enter rental fee: ";
        cin >> facility.rentalFee;
        bool found = false;
    }
}

void generateFloorPlan(){
    string venueName="";
    cout<<"Enter venue";
    cin>>venueName;
    for(auto it=venueList.begin();it!=venueList.end();++it){
        if(it->venueName==venueName){
            for(double i=it->width;i>=0;i--){
                for(double j=it->length;j>=0;j--){
                    if((j==it->length)||(j==0)||(i==it->width)||(i==0)){
                        cout<<"+";
                    }
                }
            }
        }
    }
}

void viewVenue(){
    for(Venue i: venueList){
        cout<<i.venueName<<" "<<i.width<<" "<<i.length;
        for(Facility j: i.facilityProvided){
            cout << j.facilityName << " " << j.facilityModel << " "
             << j.quantity << " " << (j.availability ? "Available" : "Unavailable")
             << " " << j.rentalFee << endl;
        }
    }
}

void updateStatus(){
    string facility="";
    cout<<"Enter the facility name you want to change its status: ";
    cin>>facility;
    for(auto it=facilityList.begin();it!=facilityList.end();++it){
        if(it->facilityName==facility){
            char response;
            cout<<"Currently the status of "<<it->facilityName<<" is "<<it->availability<<", do you want to change it? (Y/N)";
            cin>>response;
            if(response=='Y'){
                it->availability=!(it->availability);
            }
            return;
        }
        cout<<"Facility not found";
    }
}

void deleteFacility() {
    string name, model;
    bool found = false;
    cout << "Enter facility name to remove: ";
    getline(cin, name);
    cout << "Enter facility model to remove: ";
    getline(cin, model);
    for (auto it = facilityList.begin(); it != facilityList.end(); ++it) {
        if (it->facilityName == name && it->facilityModel == model) {
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



int main() 
{
    while(true){
        int choice;
        
        cout<<"Venue management"<<endl;
        cout<<"----------------"<<endl;
        cout<<"1. Add new facility"<<endl;
        cout<<"2. Add new venue"<<endl;
        cout<<"3. View venue"<<endl;
        cout<<"4. Display floor plan"<<endl;
        cout<<"5. Update status"<<endl;
        cout<<"6. Delete facility"<<endl;
        cout<<"0. Exit"<<endl;
        
        while(true)
        {
            cout<<endl<<"Enter choice: ";
            cin>>choice;
            cin.ignore();
            
            if((cin.fail())||(choice<0)||(choice>9)){
                cout << "Invalid input! Expected an integer from 0 to 9."<< endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
            }
            else break;
        }
            
        switch(choice)
        {
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
            case 6:

            case 0:
                return 0;
        }
    }
	return 0;
}
