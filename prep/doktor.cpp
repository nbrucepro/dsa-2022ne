#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
// #include <cctype>

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

class DiseaseDatabase {
private:
  std::vector<Location> locations;

public:
    void addLocation(const Location& locationName) {
        
        locations.push_back(locationName);
        ofstream file("diseases_cases_report.csv",ios::app);    
        for (const auto& location:locations) {
        file << location.getName()<<endl;
        }

        file.close();
        string str= locationName.getName();
        for(char& c : str){
            c= toupper(c);
        }
        cout << "Location " << str << " is successfully added!" << endl;        
    }  
    
    void diseaseToLocation(const string& locationName,const string& disease,const string& cases) {
        ifstream file("diseases_cases_report.csv");
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
            ofstream outfile("diseases_cases_report.csv",ios_base::app);
            outfile << locationName << "," << disease << "," << cases <<endl;
            outfile.close();
            cout << "Disease cases recorded for location: " << locationName << std::endl;
        }
        else {
        cout << "Location not found!";
        }
    }  

    // void listLocations() {

    //     ifstream location("diseases_cases_report.csv");
    //     string line;
    //     // string location;
    //     // while(getline(location,line)){
    //     //     getline(line,location,',');
    //     //     for(char& c:location) {
    //     //         c = toupper(c);
    //     //     }
    //     //  cout<< line<<endl;
    //     // };
    //     location.close();
     };
    void listDiseases() {

        fstream location("diseases_cases_report.csv",ios::in);
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
        ifstream file("diseases_cases_report.csv");
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

    void searchCase(const string& location, const string& disease) {
       ifstream file("diseases_cases_report.csv");
       string line;
       int overalcases = 0;
       while(getline(file,line)) {
           istringstream iss(line);
           string currlocation;
           string currdisease;
           string cases;
           getline(iss,currlocation,',');
           if(currlocation == location ) {
           getline(iss,currdisease,',');

           if(currdisease == disease) {
            getline(iss,cases,',');            
            overalcases += stoi(cases);
            cout << "Cases of " <<currdisease<<" at "<<currlocation<<" are: " << overalcases << endl;            
           }
           }
            else {
            cout<< "Not found!" << endl;
           }
        file.close();
    };
    };
void verallCases(const string& diseasename) {
    ifstream file("diseases_cases_report.csv");
    string line;
    string currlocation;
    string currdisease;
    string currcases;
    int overallcases = 0;
    while(getline(file,line)) {
        istringstream iss(line);
        getline(iss,currlocation,',');
        getline(iss,currdisease,',');
        if(currdisease == diseasename) {
            getline(iss,currcases,',');     
            overallcases += stoi(currcases);       
        }
    }
    if(overallcases > 0) {
        cout << "Total cases of  " <<"'"<< diseasename <<"'"<< "=" << overallcases<<endl;
    }
};
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
    // else if(action == "list") {
    //     string c2;
    //     iss >> c2;
    //     if (c2 == "locations") {
    //     database.listLocations();
    //     }
    //     if (c2 == "diseases") {
    //     database.listDiseases();
    //     }
    // }
    else if(action == "where") {
        string diseasename;
        iss >> diseasename;
        database.searchDisease(diseasename);
    }
    else if(action == "cases") {    
        string location;
        iss >> location;
        string diseases;
        iss >> diseases;
        if(!location.empty()){
            database.verallCases(location);
        if(!diseases.empty()){            
        database.searchCase(location, diseases);
        }
        }
    }
    // else if(action == "")
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