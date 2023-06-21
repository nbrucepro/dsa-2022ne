#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Item
{
    int item_id;
    string item_name;
    int item_quantity;
    string item_registration_date;
};

void addItem(const string &filename, int item_id, const string &item_name, int item_quantity, const string &item_registration_date)
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
         { return a.item_id < b.item_id; });

    // Display the sorted items
    cout << "Items in alphabetical order:" << endl;
    for (const auto &item : items)
    {
        cout << "ID: " << item.item_id << ", Name: " << item.item_name << ", Quantity: " << item.item_quantity << ", Registration Date: " << item.item_registration_date << endl;
    }
}

int main()
{
    string filename = "inventory.csv";

    while (true)
    {
        string command;
        cout << "Enter a command (itemadd to add a new item, itemslist to list items, quit to exit): ";
        getline(cin, command);

        if (command == "itemadd")
        {
            int item_id, item_quantity;
            string item_name, item_registration_date;

            cout << "Enter item ID: ";
            cin >> item_id;
            cin.ignore();

            cout << "Enter item name: ";
            getline(cin, item_name);

            cout << "Enter item quantity: ";
            cin >> item_quantity;
            cin.ignore();

            cout << "Enter item registration date: ";
            getline(cin, item_registration_date);

            addItem(filename, item_id, item_name, item_quantity, item_registration_date);
        }
        else if (command == "itemslist")
        {

            listItems(filename);
        }
        else if (command == "help") {
            // Display help information
            cout << "Available commands and their syntaxes:" << endl;
            cout << "itemadd <item_id> <item_name> <item_quantity> <item_registration_date>" << endl;
            cout << "itemslist" << endl;
            cout << "help" << endl;
            cout << "quit" << endl;
        }
        else if (command == "quit")
        {
            break;
        }
        else
        {
            cout << "Invalid command. Please try again." << endl;
        }
        cout << endl;
    }

    return 0;
}
// build the system so that the commands and entered data should not be case sensitive