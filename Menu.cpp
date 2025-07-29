// Implementation File -> Menu.cpp
#include "Menu.h"
#include "InventoryItem.h"
#include "SplitLineToArray.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <fstream>

using namespace std;

/*
 * Switch Statement:
 *  - Processes a single-character user command and performs the corresponding action.
 *
 * Parameters:
 *  - command: The user's selected command (as a lowercase character).
 *  - inventory: Reference to the inventory vector storing InventoryItem objects.
 *  - itemCount: Reference to the current number of items in the inventory.
 *
 * Command Actions:
 *  - 'h': Displays the help menu with a list of available commands.
 *  - 'i': Loads inventory items from a file (appends to current inventory).
 *  - 'n': Prompts user to create a new inventory item (with description, cost, and quantity).
 *  - 'a': Adds parts (quantity) to an existing inventory item, ensuring constraints.
 *  - 'r': Removes parts (quantity) from an inventory item, validating the quantity.
 *  - 'p': Prints a formatted list of all current inventory items.
 *  - 'o': Saves the current inventory to a file in a standardized format.
 *  - 'q': Displays exit message (actual program termination is handled in main()).
 *  - default: Displays an error for unrecognized or invalid commands.
 */
void handleCommand(const char command, vector<InventoryItem>& inventory, int& itemCount) {
    switch (command) {
        case 'h':
            showMenu();
            break;
        case 'i':
            inputFromFile(inventory, itemCount);
            break;
        case 'n':
            createNewItem(inventory, itemCount);
            break;
        case 'a':
            addParts(inventory, itemCount);
            break;
        case 'r':
            removeParts(inventory, itemCount);
            break;
        case 'p':
            printInventory(inventory, itemCount);
            break;
        case 'o':
            outputToFile(inventory, itemCount);
            break;
        case 'q':
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid command.\n";
    }
}

/*
 * showMenu function definition:
 *  - Displays the list of supported user commands.
 *
 * This function is called when the user enters 'h' to request help.
 * Each line explains a valid command the program accepts and what it does.
 */
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

/*
 * inputFromFile function definition:
 *  - Loads inventory items from a specified input file into the inventory array.
 *
 * Parameters:
 *  - inventory: Reference to the vector of InventoryItem objects.
 *  - itemCount: Reference to the current number of items in inventory (will be updated).
 *
 * Behavior:
 *  - Prompts the user to enter the name of the input file.
 *  - Repeats prompt until a valid file is successfully opened.
 *  - Reads the file line by line, expecting the format: index|description|cost|units.
 *  - Skips malformed lines or lines with invalid formats.
 *  - Validates:
 *      - Exactly 4 fields must be present.
 *      - Units must be within 0–30.
 *      - File parsing must succeed (no conversion errors).
 *  - Limits total inventory to 100 items.
 *  - Appends successfully loaded items to the inventory array.
 *  - Outputs the number of valid records loaded to the user.
 */
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

        if (int numFields = splitLineToArray(line, "|", fields, 4); numFields != 4) {
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
        }
    }

    inputFile.close();
    cout << linesLoaded << " record(s) loaded to array.\n";
}

/*
 * createNewItem function definition:
 *  - Prompts the user to create and add a new inventory item.
 *
 * Parameters:
 *  - inventory: Reference to the vector of InventoryItem objects.
 *  - itemCount: Reference to the number of current inventory items (will be incremented).
 *
 * Behavior:
 *  - First checks if inventory has reached the 100-item limit.
 *      - If full, displays an error and exits the function.
 *  - Prompts user to enter a description, cost, and quantity.
 *      - Uses getline() for description to allow spaces.
 *      - Validates unit cost:
 *          - Must be numeric and non-negative.
 *      - Validates quantity:
 *          - Must be an integer between 0 and 30.
 *  - Adds the validated item to the inventory array.
 *  - Displays confirmation of the newly added item and updated inventory count.
 */
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

/*
 * addParts function definition:
 *  - Adds parts to an existing inventory item.
 *
 * Parameters:
 *  - inventory: Reference to the vector of InventoryItem objects.
 *  - itemCount: Current number of items in inventory.
 *
 * Behavior:
 *  - If the inventory is empty, displays an error and exits early.
 *  - Prompts user for an item number:
 *      - Validates that the input is numeric and within the valid range (0 to itemCount - 1).
 *  - Prompts user for quantity to add:
 *      - Validates that input is numeric and non-negative.
 *      - Ensures total quantity after addition does not exceed 30.
 *  - Updates the item’s quantity accordingly.
 *  - Displays a confirmation message showing how many units were added and to which item.
 */
void addParts(vector<InventoryItem>& inventory, const int itemCount) {
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

/*
 * removeParts function definition:
 *  - Removes parts (units) from an existing inventory item.
 *
 * Parameters:
 *  - inventory: Reference to the vector of InventoryItem objects.
 *  - itemCount: Current number of items in the inventory.
 *
 * Behavior:
 *  - If the inventory is empty, displays an error and exits early.
 *  - Prompts user to enter an item number:
 *      - Validates that input is numeric and within the valid item index range (0 to itemCount - 1).
 *  - Prompts user to enter quantity to remove:
 *      - Validates that the input is numeric and non-negative.
 *      - Ensures user does not remove more units than currently available.
 *  - Updates the item’s quantity accordingly.
 *  - Displays a confirmation message showing how many units were removed,
 *    from which item, and what the new quantity is.
 */
void removeParts(vector<InventoryItem>& inventory, const int itemCount) {
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

/*
 * printInventory function definition:
 *  - Displays the current inventory list in a tabular format.
 *
 * Parameters:
 *  - inventory: A constant reference to the vector of InventoryItem objects.
 *  - itemCount: The total number of items currently in the inventory.
 *
 * Behavior:
 *  - Prints column headers for item number, description, cost, and quantity.
 *  - Draws a visual separator line beneath the headers.
 *  - Iterates through the inventory vector up to itemCount:
 *      - Formats each record with appropriate spacing and alignment.
 *      - Uses left/right alignment and fixed-point precision for clean output.
 *  - At the end, displays the number of records printed with correct pluralization.
 */
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

/*
 * outputToFile function definition:
 *  - Outputs the current inventory data to a user-specified file in pipe-delimited format.
 *
 * Parameters:
 *  - inventory: A constant reference to the vector of InventoryItem objects.
 *  - itemCount: The total number of items currently in the inventory.
 *
 * Behavior:
 *  - If inventory is empty, notifies the user and aborts the write operation.
 *  - Repeatedly prompts the user until a valid file can be opened for output.
 *  - Each inventory item is written in the format: index|description|cost|units.
 *      - Uses fixed-point notation with 2 decimal places for cost values.
 *  - Once all items are written, the file is closed and a confirmation message is printed.
 */
void outputToFile(const vector<InventoryItem>& inventory, const int itemCount) {
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

        outputFile.open(filename);
        if (outputFile) break;

        cout << "Error: Could not create file \"" << filename << "\". Please try again.\n";
        outputFile.clear(); // Reset error flags
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
