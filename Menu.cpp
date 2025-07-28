// Implementation File -> Menu.cpp
#include "Menu.h"
#include "InventoryItem.h"
#include "SplitLineToArray.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <fstream>

using namespace std;

void showMenu() {
    cout << "Supported commands:\n"
     << "  h -> Print Help text\n"
     << "  i -> Input inventory data from a file\n"
     << "  n -> New inventory Item\n"
     << "  a -> Add parts\n"
     << "  r -> Remove parts\n"
     << "  p -> Print inventory list\n"
     << "  o -> Output inventory data to a file\n"
     << "  q -> Quit (end the program)\n";
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
void inputFromFile(vector<InventoryItem>& inventory, int& itemCount) {
    string filename;
    ifstream inputFile;

    // Loop until a valid file is opened
    while (true) {
        cout << "Enter name of input file: ";
        cin >> filename;

        inputFile.open(filename);
        if (inputFile.is_open()) {
            break; // valid file found, exit loop
        }

        cout << "Error: Could not open file \"" << filename << "\". Please try again.\n";
        inputFile.clear(); // reset any error state
    }

    string line;
    int linesLoaded = 0;

    while (getline(inputFile, line)) {
        if (itemCount >= 100) {
            cout << "Inventory full (100 items max). Remaining file data ignored.\n";
            break;
        }

        string fields[4];
        int numFields = splitLineToArray(line, "|", fields, 4);

        if (numFields != 4) {
            cout << "Warning: Skipping malformed line: " << line << '\n';
            continue;
        }

        try {
            string description = fields[1];
            double cost = stod(fields[2]);
            int units = stoi(fields[3]);

            if (units < 0 || units > 30) {
                cout << "Warning: Invalid units (" << units << ") on line: " << line << '\n';
                continue;
            }

            inventory[itemCount] = InventoryItem(description, cost, units);
            itemCount++;
            linesLoaded++;
        } catch (...) {
            cout << "Warning: Skipping line with invalid number format: " << line << '\n';
            continue;
        }
    }

    inputFile.close();
    cout << linesLoaded << " record(s) loaded to array.\n";
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

    // Validate cost input
    cout << "Enter unit cost for new Item: ";
    cin >> cost;
    while (cin.fail() || cost < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "ERROR: Unit cost must be a valid non-negative number.\n"
             << "Please enter unit cost: ";
        cin >> cost;
    }

    // Validate quantity input
    cout << "Enter initial quantity for the new Item: ";
    cin >> units;
    while (cin.fail() || units < 0 || units > 30) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "ERROR: Initial quantity must be an integer between 0 - 30.\n"
             << "Please enter initial quantity: ";
        cin >> units;
    }

    inventory[itemCount] = InventoryItem(desc, cost, units);
    cout << "Announcing a new inventory Item: " << desc << endl;

    itemCount++;
    cout << "We now have " << itemCount << " different inventory Item"
         << (itemCount == 1 ? ".\n" : "s in stock!\n");
}

void addParts(vector<InventoryItem>& inventory, int itemCount) {
    if (itemCount == 0) {
        cout << "Error: Inventory is empty. No items to modify.\n";
        return;
    }

    int itemNum;
    cout << "Choose an Item Number: ";
    cin >> itemNum;

    while (cin.fail() || itemNum < 0 || itemNum >= itemCount) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Error: Invalid item number.\n"
             << "Please enter a valid item number (0 to " << itemCount - 1 << "): ";
        cin >> itemNum;
    }

    int quantityToAdd;
    cout << "How many parts to add? ";
    cin >> quantityToAdd;

    while (cin.fail() || quantityToAdd < 0 || inventory[itemNum].getUnits() + quantityToAdd > 30) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (cin.fail() || quantityToAdd < 0) {
            cout << "Error: Quantity must be a non-negative integer.\n";
        } else {
            cout << "Error: Total quantity would exceed 30 units.\n";
        }

        cout << "Please enter a valid quantity to add: ";
        cin >> quantityToAdd;
    }

    inventory[itemNum].setUnits(inventory[itemNum].getUnits() + quantityToAdd);
    cout << quantityToAdd << " units added to item #" << itemNum << ".\n";
}

void removeParts(vector<InventoryItem>& inventory, int itemCount) {
    if (itemCount == 0) {
        cout << "Error: Inventory is empty. No items to modify.\n";
        return;
    }

    int itemNum;
    cout << "Enter item number: ";
    cin >> itemNum;

    while (cin.fail() || itemNum < 0 || itemNum >= itemCount) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Error: Invalid item number.\n"
             << "Please enter a valid item number (must be between 0 and " << itemCount - 1 << "): ";
        cin >> itemNum;
    }

    int quantityToRemove;
    cout << "Enter quantity to remove: ";
    cin >> quantityToRemove;

    while (cin.fail() || quantityToRemove < 0 || quantityToRemove > inventory[itemNum].getUnits()) {
        if (cin.fail()) {
            cout << "Error: Invalid input. Please enter a numeric value.\n";
        } else if (quantityToRemove < 0) {
            cout << "Error: Quantity must be a non-negative integer.\n";
        } else {
            cout << "Error: Cannot remove more units than currently available.\n";
        }

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Please enter a valid quantity to remove: ";
        cin >> quantityToRemove;
    }

    const int newUnits = inventory[itemNum].getUnits() - quantityToRemove;
    inventory[itemNum].setUnits(newUnits);
    cout << quantityToRemove << " unit(s) removed from item #" << itemNum
         << ". New quantity: " << newUnits << ".\n";
}

void printInventory(const vector<InventoryItem>& inventory, const int itemCount) {
    cout << left << setw(10) << "Item #"
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

void outputToFile(const vector<InventoryItem>& inventory, int itemCount) {
    if (itemCount == 0) {
        cout << "Inventory is empty. Nothing to write.\n";
        return;
    }

    string filename;
    ofstream outputFile;

    // Prompt until a valid file is successfully opened for writing
    while (true) {
        cout << "Enter name of output file: ";
        cin >> filename;

        outputFile.open(filename);

        if (outputFile) {
            break;
        } else {
            cout << "Error: Could not create file \"" << filename << "\". Please try again.\n";
            outputFile.clear(); // Reset error flags
        }
    }

    // Write each inventory item to the file in pipe-delimited format
    for (int i = 0; i < itemCount; ++i) {
        outputFile << i << "|"
                   << inventory[i].getDescription() << "|"
                   << fixed << setprecision(2) << inventory[i].getCost() << "|"
                   << inventory[i].getUnits() << '\n';
    }

    outputFile.close();
    cout << itemCount << " record(s) written to \"" << filename << "\".\n";
}
