// CS105 Restaurant Management System.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <fstream>

using namespace std;

class Dish {
private:
    string name;
    double price;
public:
    Dish(string dishName, double dishPrice) {
        name = dishName;
        price = dishPrice;
    }

    string getName() const {
        return name;
    }

    double getPrice() const {
        return price;
    }

    void setName(const string& newName) {
        name = newName;
    }

    void setPrice(double newPrice) {
        price = newPrice;
    }

    string toString() const {
        return name + " - $" + to_string(price);
    }
};

class Menu {
private:
    list<Dish> dishes;
public:
    void addDish(const Dish& toAdd) {
        dishes.push_back(toAdd);
    }

    void showMenu() const {
        if (dishes.empty()) {
            cout << "Menu is empty!\n";
            return;
        }
        cout << "------ Menu ------\n";
        for (const auto& item : dishes) {
            cout << item.toString() << endl;
        }
    }

    // Save dishes to file
    void saveToFile(const string& filename) const {
        ofstream file(filename);
        for (const auto& dish : dishes) {
            file << dish.getName() << "," << dish.getPrice() << "\n";
        }
        file.close();
    }

    // Load dishes from file
    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) return; // no file yet

        string line;
        while (getline(file, line)) {
            size_t commaPos = line.find(',');
            if (commaPos != string::npos) {
                string name = line.substr(0, commaPos);
                double price = stod(line.substr(commaPos + 1));
                dishes.push_back(Dish(name, price));
            }
        }
        file.close();
    }

    bool editDish(const string& oldName, const string& newName, double newPrice) {
        for (auto& dish : dishes) { // loop through each Dish in the list
            if (dish.getName() == oldName) {
                // Found the dish to edit
                dish.setName(newName);
                dish.setPrice(newPrice);
                return true; // success
            }
        }
        return false; // dish not found
    }

    bool deleteDish(const string& dishName) {
        for (auto it = dishes.begin(); it != dishes.end(); ++it) {
            if (it->getName() == dishName) {
                dishes.erase(it); // remove the dish
                return true;      // success
            }
        }
        return false; // not found
    }

    bool getDishByName(const string& name, Dish& foundDish) const {
        for (const auto& dish : dishes) {
            if (dish.getName() == name) {
                foundDish = dish; // copy the dish into foundDish
                return true;
            }
        }
        return false; // return false if dish not found
    }
};

class Order {
private:
    int orderID;
    list <Dish> items;
public:
    Order(int id) : orderID(id) {} // constructor assigns ID

    void additem(const Dish& tableOrder) {
        items.push_back(tableOrder);
    }

    double calculateTotal() const {
        double totalPrice = 0.0;
        for (auto& dish : items) {          // Loop through each dish in the Order
            totalPrice += dish.getPrice();  // add each dish's price
        }
        return totalPrice;
    }

    // View order contents without "processing"
    void viewOrder() const {
        cout << "Order #" << orderID << " (currrent contents):\n";
        cout << "----------------------------\n";

        if (items.empty()) {
            cout << "No items in this order yet!\n";
            return;
        }

        for (const auto& dish : items) {
            cout << dish.getName() << " - $" << dish.getPrice() << "\n";
        }

        cout << "----------------------------\n";
        cout << "Subtotal: $" << calculateTotal() << "\n";
    }

    // Process = finalize the order
    void processOrder() {
        cout << "Processing Order #" << orderID << "\n";
        cout << "----------------------------\n";

        if (items.empty()) {
            cout << "No items in this order!\n";
            return;
        }

        for (const auto& dish : items) {
            cout << dish.getName() << " - $" << dish.getPrice() << "\n";
        }

        cout << "----------------------------\n";
        cout << "Total: $" << calculateTotal() << "\n";
        cout << "Order Complete!\n\n";
    }

    bool deleteItem(const string& dishName) {
        for (auto it = items.begin(); it != items.end(); ++it) {
            if (it->getName() == dishName) {
                items.erase(it);  // remove that dish
                return true;      // success
            }
        }

        return false; // dish not found
    }

    void clearOrder() {
        items.clear();
        cout << ">> Order cleared!\n";
    }
};

class Table {
private:
    int tableID;
    int capacity;
    bool isOccupied;

public:
    Table(int id, int cap, bool occupied = false) : tableID(id), capacity(cap), isOccupied(occupied) {}

    int getID() const { return tableID; }
    int getCapacity() const { return capacity; }
    bool getOccupied() const { return isOccupied; }

    void setCapacity(int cap) { capacity = cap; }
    void setOccupied(bool occ) { isOccupied = occ; }

    void showTable() const {
        cout << "Table #" << tableID
            << " | Capacity: " << capacity
            << " | Occupied: " << (isOccupied ? "Yes" : "No")
            << endl;
    }
};

class TableManagment {
private:
    list<Table> tables;

public:
    // Add
    void addTable(int ID, int capacity) {
        tables.push_back(Table(ID, capacity));
        cout << ">> Table #" << ID << " added successfully!\n";
    }

    // View
    void showTables() const {
        if (tables.empty()) {
            cout << ">> No tables available!\n";
            return;
        }
        for (const auto& table : tables) {
            table.showTable();
        }
    }

    // Edit
    bool editTable(int ID, int newCapacity, bool newOccupied) {
        for (auto& table : tables) {
            if (table.getID() == ID) {
                table.setCapacity(newCapacity);
                table.setOccupied(newOccupied);
                return true;
            }
        }
        return false;
    }

    // Delete
    bool deleteTable(int ID) {
        for (auto it = tables.begin(); it != tables.end(); ++it) {
            if (it->getID() == ID) {
                tables.erase(it);
                return true;
            }
        }
        return false;
    }
};

int main() {
    
    Menu menu;
    TableManagment tables;
    menu.loadFromFile("menu.txt");

    bool systemRun = true;
    while (systemRun == true) {
        int choice;

        cout << endl
             << " --- What would you like to manage? --- " << endl
             << "1. Menu" << endl
             << "2. Orders" << endl
             << "3. Tables" << endl
             << "4. Exit" << endl
             << ">> ";
        cin >> choice;
             
        if (choice == 1) {
            bool menuRunning = true;
            while (menuRunning) {
                int choice2;
                cout << endl
                    << "1. Add" << endl
                    << "2. View" << endl
                    << "3. Edit" << endl
                    << "4. Delete" << endl
                    << "5. Exit" << endl
                    << ">> ";
                cin >> choice2;

                switch (choice2) {
                case 1: {
                    string dishName;
                    double dishPrice;
                    cout << "Enter dish name: ";
                    cin >> dishName;
                    cout << "Enter dish price: ";
                    cin >> dishPrice;
                    menu.addDish(Dish(dishName, dishPrice));
                    cout << "\n>> Dish added to Menu\n";
                    break;
                }
                case 2:
                    cout << "Displaying Menu:\n";
                    menu.showMenu();
                    break;
                case 3: {
                    string oldName, newName;
                    double newPrice;

                    cout << "Enter the name of the dish you wish to edit: ";
                    cin >> oldName;

                    cout << "Enter new dish name: ";
                    cin >> newName;

                    cout << "Enter new dish price: ";
                    cin >> newPrice;

                    if (menu.editDish(oldName, newName, newPrice)) {
                        cout << "\n>> Menu Edit Successful\n";
                    }
                    else {
                        cout << "\n>> Dish not found in Menu!\n";
                        systemRun = false;
                    }
                    break;
                }
                case 4: {
                    string dishName;
                    cout << "Enter the name of the dish you want to delete: ";
                    cin >> dishName;

                    if (menu.deleteDish(dishName)) {
                        cout << "Dish deleted from Menu\n";
                    }
                    else {
                        cout << "Dish not found in Menu!\n";
                    }
                    break;
                }
                case 5:
                    cout << "\n>> Exiting to Main Menu\n";
                    menu.saveToFile("menu.txt");  // save before exit
                    menuRunning = false;
                    break;
                default:
                    cout << "ERROR: Invalid Input\n";
                    menuRunning = false;
                    systemRun = false;
                    break;
                }
            }
        }

        if (choice == 2) {
            bool orderRunning = true;
            static int orderCounter = 1;  // keep unique IDs for each order
            Order order1(orderCounter++); // assing counter ID and increment counter
            cout << endl << " ---- Creating Order... ----" << endl
                << ">> Created Order #" << orderCounter - 1 << endl;
            
            while (orderRunning) {
                int choice3;
                cout << endl
                    << "1. Add Item" << endl
                    << "2. View Order" << endl
                    << "3. Process Order" << endl
                    << "4. Remove Dish" << endl
                    << "5. Cancel Order" << endl
                    << "6. Exit to Main Menu" << endl
                    << ">> ";
                cin >> choice3;

                switch (choice3) {
                case 1: {
                    string dishName;
                    char more = 'y';
                    while (more == 'y' || more == 'Y') {
                        // Add dishes to the order
                        cout << "Enter the Dish to add to the order: ";
                        cin >> dishName;

                        Dish dish("", 0.0); // temporary dish
                        if (menu.getDishByName(dishName, dish)) {
                            order1.additem(dish);
                            cout << ">> " << dishName << " added to order\n";
                        }
                        else {
                            cout << "ERROR: " << dishName << " is not on the Menu!\n";
                        }

                        cout << "Add another dish? (y/n): ";
                        cin >> more;
                    }
                    break;
                }
                case 2:
                    order1.viewOrder(); // See current order contents
                    break;
                case 3:
                    order1.processOrder(); // finalize/checkout order
                    break;
                case 4: {
                    string dishName;
                    cout << "Enter the name of the dish to remove from the order: ";
                    cin >> dishName;

                    if (order1.deleteItem(dishName)) {
                        cout << ">> " << dishName << " removed from the order\n";
                    }
                    else {
                        cout << ">> ERROR: " << dishName << " not found in the order\n";
                    }
                    break;
                }
                case 5:
                    order1.clearOrder(); // wipes the order
                    break;
                case 6:
                    cout << "Exiting to Main Menu\n";
                    orderRunning = false; // exit to main menu
                    break;
                default:
                    cout << "Invalid option!\n";
                    break;
                }
            }
        }

        if (choice == 3) {
            bool tableRunning = true;
            while (tableRunning) {
                int choice4;
                cout << endl
                    << "1. Add Table" << endl
                    << "2. View Tables" << endl
                    << "3. Edit Table" << endl
                    << "4. Delete Table" << endl
                    << "5. Exit to Main Menu" << endl
                    << ">> ";
                cin >> choice4;

                switch (choice4) {
                case 1: {
                    int ID, cap;
                    cout << "Enter Table ID: ";
                    cin >> ID;
                    cout << "Enter Capacity: ";
                    cin >> cap;
                    tables.addTable(ID, cap);
                    break;
                }
                case 2:
                    tables.showTables();
                    break;
                case 3: {
                    int ID, cap;
                    char occ;
                    cout << "Enter Table ID to edit: ";
                    cin >> ID;
                    cout << "Enter new Capacity: ";
                    cin >> cap;
                    cout << "Is the table occupied? (y/n): ";
                    cin >> occ;

                    if (tables.editTable(ID, cap, occ == 'y' || occ == 'Y')) {
                        cout << ">> Table updated successfully!\n";
                    }
                    else {
                        cout << ">> Table not found!\n";
                    }
                    break;
                }
                case 4: {
                    int ID;
                    cout << "Enter Table ID to delete: ";
                    cin >> ID;

                    if (tables.deleteTable(ID)) {
                        cout << ">> Table deleted successfully!\n";
                    }
                    else {
                        cout << ">> Table not found!\n";
                    }
                    break;
                }
                case 5:
                    cout << ">> Exiting to Main Menu\n";
                    tableRunning = false;
                    break;
                default:
                    cout << "ERROR: Invalid Input\n";
                    tableRunning = false;
                    systemRun = false;
                    break;
                }
            }
        }
        
        if (choice == 4) {
            cout << "Exiting System, Goodbye!\n";
            systemRun = false;
        }
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file