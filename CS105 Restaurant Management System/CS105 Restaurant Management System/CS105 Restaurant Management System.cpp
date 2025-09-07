// CS105 Restaurant Management System.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

class Restaurant {
private:
    string name = "Eats & Treats";  
};

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
};

int main() {
    
    Menu menu;
    bool systemRun = true;
    
    while (systemRun == true) {
        int choice;
        cout << endl 
             << "1. Add" << endl 
             << "2. View" << endl 
             << "3. Edit" << endl 
             << "4. Delete" << endl 
             << "5. Exit" << endl 
             << ">> ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string dishName;
            double dishPrice;
            cout << "Enter dish name: ";
            cin >> dishName;
            cout << "Enter dish price: ";
            cin >> dishPrice;
            menu.addDish(Dish(dishName, dishPrice));
            cout << "Dish added to Menu\n";
            break;
        }
        case 2:
            cout << "Displaying Menu:\n";
            menu.showMenu();
            break;
        case 3:
            cout << "\nMenu Edit Successfull\n"; // Not Implemented Yet
            break;
        case 4:
            cout << "\nDish deleted from Menu\n"; // Not Implemented Yet
            break;
        case 5:
            cout << "\nExiting System, Goodbye!\n";
            systemRun = false;
            break;
        default:
            cout << "ERROR: Invalid Input\n";
            break;
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