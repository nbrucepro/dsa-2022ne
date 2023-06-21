#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

struct Item
{
    int item_id;
    string item_name;
    int item_quantity;
    string item_registration_date;
};

void addItemLogics(const string &filename, int item_id, const string &item_name, int item_quantity, const string &item_registration_date)
{
    // Create an instance of the Item structure
    Item item;
    item.item_id = item_id;
    item.item_name = item_name;
    item.item_quantity = item_quantity;
    item.item_registration_date = item_registration_date;

    // Open the CSV file in append mode
    ofstream file(filename, ios::app);
    if (!file.is_open())
    {
        cout << "Failed to open the file." << endl;
        return;
    }

    // Write the item data to the CSV file
    file << item.item_id << "," << item.item_name << "," << item.item_quantity << "," << item.item_registration_date << endl;

    // Close the file
    file.close();

    cout << "Item added successfully." << endl;
}

void addItem(const string &filename, const string &input)
{
    istringstream iss(input);
    int item_id;
    string item_name;
    int item_quantity;
    string item_registration_date;

    if (!(iss >> item_id >> item_name >> item_quantity >> item_registration_date))
    {
        cout << "Invalid input format. Please provide item_id, item_name, item_quantity, and item_registration_date separated by spaces." << endl;
        return;
    }

    addItemLogics(filename, item_id, item_name, item_quantity, item_registration_date);
}
void listItems(const string &filename)
{
    // Open the CSV file
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Failed to open the file." << endl;
        return;
    }

    // Read and store items from the CSV file
    vector<Item> items;
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string item_id_str, item_name, item_quantity_str, item_registration_date;
        getline(ss, item_id_str, ',');
        getline(ss, item_name, ',');
        getline(ss, item_quantity_str, ',');
        getline(ss, item_registration_date, ',');

        Item item;
        item.item_id = stoi(item_id_str);
        item.item_name = item_name;
        item.item_quantity = stoi(item_quantity_str);
        item.item_registration_date = item_registration_date;

        items.push_back(item);
    }

    // Close the file
    file.close();

    // Sort items by item name in alphabetical order
    sort(items.begin(), items.end(), [](const Item &a, const Item &b)
         { return a.item_name < b.item_name; });

    // Display the sorted items
    cout << "Items in alphabetical order:" << endl;
    for (const auto &item : items)
    {
        cout << "Item ID: " << item.item_id << ", Item Name: " << item.item_name << ", Quantity: " << item.item_quantity << ", Reg Date: " << item.item_registration_date << endl;
    }
}
void executeCommand(const string &filename, const string &input)
{
    istringstream iss(input);
    string command;
    iss >> command;

    // Convert the command to lowercase
    transform(command.begin(), command.end(), command.begin(), ::tolower);

    if (command == "itemadd")
    {
        int item_id;
        string item_name;
        int item_quantity;

        if (!(iss >> item_id >> item_name >> item_quantity))
        {
            cout << "Invalid input format. Please provide item_id, item_name, and item_quantity." << endl;
            return;
        }

        // Get the current date as the item_registration_date
        time_t now = time(0);
        tm *date = localtime(&now);
        string item_registration_date = to_string(1900 + date->tm_year) + "-" +
                                        to_string(1 + date->tm_mon) + "-" +
                                        to_string(date->tm_mday);

        // Add the item to the inventory
        // ... your code for adding the item to the inventory ...
        // addItem(filename,)
        addItemLogics(filename, item_id, item_name, item_quantity, item_registration_date);
    }
    else if (command == "itemslist")
    {
        // ... code for listing items ...
        listItems(filename);
    }
    else if (command == "help")
    {
        // ... code for displaying help information ...
            cout<< "-------------------------------------------------"<<endl;
            cout << "*               Commands Syntaxes               *" << endl;
            cout<< "-------------------------------------------------"<<endl;
            cout << "itemadd <item_id> <item_name> <item_quantity> <item_registration_date>" << endl;
            cout << "itemslist" << endl;
            cout << "help" << endl;
            cout << "exit" << endl;
    }
    else if (command == "exit" || command == "exit ")
    {
        // ... code for quitting the program ...
        return;
    }
    else
    {
        cout << "Invalid command. Please try again." << endl;
        return;
    }
}

int main()
{
    string filename = "inventory.csv";

    while (true)
    {
        string input;
        cout << "Enter a command with details on the same line (itemadd id name quantity, itemslist, help, exit): ";
        getline(cin, input);

        executeCommand(filename, input);
        if( input == "exit") {
            break;
        }
        cout << endl;
    }

    return 0;
}
