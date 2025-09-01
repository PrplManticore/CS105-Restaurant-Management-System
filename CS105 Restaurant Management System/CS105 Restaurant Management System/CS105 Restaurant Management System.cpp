// CS105 Restaurant Management System.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Restaurant {
private:
    string name = "Eats & Treats";
    Menu menu;
    vector<Employee> staffList; // Creates list of Employees
public:
    void addEmployee(const Employee& employee) {
        staffList.push_back(employee); // Adds Employee to list
    }
    int showMenu();
};

class Employee {
private:
    string name;
    int ID;
    double salary;
};

class Menu {
private:
    vector<Dish> dishes; // Creates list of Dishes on the Menu
public:
    void addDish(const Dish& dish) {
        dishes.push_back(dish); // adds Dish to list
    }
    int showMenu() {
        int choice; // variable to store the user's choice
        do {
            // Display the menu options
            cout << "==== Menu ====" << endl << "1. Dish A" << endl << "2. Dish B" << endl << "3. Dish C" << endl << "4. Exit" << endl;
            cout << " >> ";

            // Get user input
            cin >> choice;

            // Input validation: Check for invalid input (non-integer out of range)
            if (cin.fail() || choice < 1 || choice > 4) {
                cout << "Invalid input. Please enter a number between 1 and 4." << endl;
                cin.clear(); // Clear error flags
                // Discard invalid input from the buffer
                cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
            }
            else {
                break; // Valid input, exit the loop
            }
        } while (true); // Loop indefinitely until valid input is recieved

        return choice; // returns the user's valid choice
    }
};

class Dish {
private:
    string name;
    double price;
public:
    string getName() {
        return name;
    }
    double getPrice() {
        return price;
    }
};

class Customer { // Tracks orders per 'Customer' instead of per 'Table'
private:
    string name;
    string contact;
public:
    placeOrder();
};

class Order {
private:
    int orderID;
    vector<Dish> items;
    Customer customer;
public:
    void additem(const Dish& item) {
        items.push_back(item);
    }
    double calculateTotal();
    void processOrder();
};

int main()
{
    std::cout << "Hello World!\n";
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