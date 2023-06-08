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
    
    void diseaseToLocation(const string& locationName,const string& disease) {
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
            outfile << locationName << "," << disease <<endl;
            outfile.close();
            cout << "Disease cases recorded for location: " << locationName << std::endl;
        }
        else {
        cout << "Location not found!";
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
        iss >> locationName >> disease;
        database.diseaseToLocation(locationName, disease);
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