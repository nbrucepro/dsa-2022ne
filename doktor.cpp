#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

class Location {
private:
  std::string name;
  std::string address;
  std::string city;
  std::string state;
  std::string disease;

public:
  void setName(const std::string& newName) {
    name = newName;
  }

  std::string getName() const {
    return name;
  }
  void setDisease(const std::string& newDisease) {
    disease = newDisease;
  }

  std::string getDisease() const {
    return disease; 
  }

  // Implement methods for other attributes
};

class DiseaseDatabase{
private:
  std::vector<Location> locations;

public:
    void addLocation(const Location& locationName) {
        
        locations.push_back(locationName);
        ofstream file("locations.csv",ios::app);    
        for (const auto& location:locations) {
        file << location.getName()<<endl;
        }

        file.close();
        cout << "Location added successfully." << endl;
    }  
    
    void diseaseToLocation(const string& locationName,const string& disease,const string& cases) {
        ifstream file("locations.csv");
        bool locationExists = false;
        string line;

        while(getline(file,line)){
            istringstream iss(line);
            string existinglocation;
            getline(iss,existinglocation,',');

            if(existinglocation == locationName){
                locationExists = true;
                break;
            }
        }
        file.close();
        if(locationExists) {
            ofstream outfile("locations.csv",ios_base::app);
            outfile << locationName << "," << disease << "," << cases <<endl;
            outfile.close();
            cout << "Disease cases recorded for location: " << locationName << std::endl;
        }
        else {
        cout << "Location not found!";
        }
    }  

    void listLocations() {

        ifstream location("locations.csv");
        string line;
        while(getline(location,line)){
         cout<< line<<endl;
        };
        location.close();
     };
    void listDiseases() {

        fstream location("locations.csv",ios::in);
        string line;
        while(getline(location,line)) {
         string dis;
         stringstream ss(line);
         getline(ss, dis, ',');

            if (getline(ss, dis, ',')) {
             cout<< dis<<endl;
            }  
          
        };
        location.close();
     };

     void searchDisease(const string& diseaseName) {
        vector<string> locationsWithDiseases;
        ifstream file("locations.csv");
        string line;

        while(getline(file,line)) {
            istringstream iss(line);
            string location;
            string currdisease;

            getline(iss,location,',');
            while(getline(iss,currdisease,',')) {
                if(currdisease == diseaseName ) {
                    locationsWithDiseases.push_back(location);
                    break;
                }
            }
        }
        file.close();
        if(!locationsWithDiseases.empty()) {
            for(const auto& location:locationsWithDiseases) {
                cout<<location<<endl;
            }
        } else {
            cout << "No locations found with that disease"<< endl;
        }
     }
};

void executeCommand(const string& command, DiseaseDatabase database){
    istringstream iss(command);
    string action;
    iss >> action;
    
    if(action == "add") {
        string locationName;
        iss >> locationName;
        Location newLocation;
        newLocation.setName(locationName);
        database.addLocation(newLocation);        
    }    
    else if(action == "record") {
        string locationName;        
        string disease;
        string cases;
        iss >> locationName >> disease >> cases;
        database.diseaseToLocation(locationName, disease, cases);
    }
    else if(action == "list") {
        string c2;
        iss >> c2;
        if (c2 == "locations") {
        database.listLocations();
        }
        if (c2 == "diseases") {
        database.listDiseases();
        }
    }
    else if(action == "where") {
        string diseasename;
        iss >> diseasename;
        database.searchDisease(diseasename);
    }
    else if (command == "exit") {
      return;
    } 
    else {
      cout << "Invalid command." << endl;
      return;
    }

}

int main(){
    string userInput;    
    DiseaseDatabase database;
    
    do {

    cout << "Enter a command (or 'exit' to quit): ";
    getline(cin,userInput);
    executeCommand(userInput,database);
    } while (userInput != "exit");

    return 0;
};