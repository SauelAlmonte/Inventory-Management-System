// Implementation File -> Menu.cpp
#include "Menu.h"
#include "InventoryItem.h"
#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

void showMenu() {
    cout << "Supported commands:\n"
         << "  a -> Add parts\n"
         << "  h -> Print Help text\n"
         << "  i -> Input inventory data from a file\n"
         << "  n -> New inventory Item\n"
         << "  o -> Output inventory data to a file\n"
         << "  p -> Print inventory list\n"
         << "  q -> Quit (end the program)\n"
         << "  r -> Remove parts\n";
}

void handleCommand(const char command, vector<InventoryItem>& inventory, int& itemCount) {
    switch (command) {
        case 'a':
            addParts(inventory, itemCount);
            break;
        case 'h':
            showMenu();
            break;
        case 'i':
            inputFromFile(inventory, itemCount);
            break;
        case 'n':
            createNewItem(inventory, itemCount);
            break;
        case 'o':
            outputToFile(inventory, itemCount);
            break;
        case 'p':
            printInventory(inventory, itemCount);
            break;
        case 'r':
            removeParts(inventory, itemCount);
            break;
        case 'q':
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid command.\n";
    }
}

// The below are placeholders. You'll fill these in later.

void addParts(vector<InventoryItem>& inventory, int itemCount) {
    cout << "[addParts()] called - implementation pending.\n";
}

void removeParts(vector<InventoryItem>& inventory, int itemCount) {
    cout << "[removeParts()] called - implementation pending.\n";
}

void inputFromFile(vector<InventoryItem>& inventory, int& itemCount) {
    cout << "[inputFromFile()] called - implementation pending.\n";
}

void outputToFile(const vector<InventoryItem>& inventory, int itemCount) {
    cout << "[outputToFile()] called - implementation pending.\n";
}

void printInventory(const vector<InventoryItem>& inventory, const int itemCount) {
    cout << left << setw(10) << "Item Num"
         << setw(45) << "Description"
         << right << setw(8) << "Cost"
         << setw(10) << "Quantity" << endl;

    cout << string(73, '_') << endl;

    for (int i = 0; i < itemCount; ++i) {
        cout << left << setw(10) << i
             << setw(45) << inventory[i].getDescription()
             << right << fixed << setprecision(2)
             << setw(8) << inventory[i].getCost()
             << setw(10) << inventory[i].getUnits() << endl;
    }

    cout << itemCount << " record" << (itemCount == 1 ? ".\n" : "s.\n");
}

void createNewItem(vector<InventoryItem>& inventory, int& itemCount) {
    if (itemCount >= 100) {
        cout << "Error: Inventory is full (100 items max).\n";
        return;
    }

    string desc;
    double cost;
    int units;

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush leftover input

    cout << "Enter description for new Item: ";
    getline(cin, desc);

    cout << "Enter unit cost for new Item: ";
    cin >> cost;

    cout << "Enter initial quantity for the new Item: ";
    cin >> units;

    while (units < 0 || units > 30) {
        cout << "ERROR: initial quantity must be between 0 - 30.\n"
             << "Please enter an integer between 0 - 30: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> units;
    }

    inventory[itemCount] = InventoryItem(desc, cost, units);
    cout << "Announcing a new inventory Item: " << desc << endl;

    itemCount++;
    cout << "We now have " << itemCount << " different inventory Item"
         << (itemCount == 1 ? ".\n" : "s in stock!\n");
}
