// Specification File -> Menu.h
#ifndef MENU_H
#define MENU_H

#include <vector>
#include "InventoryItem.h"

using namespace std;

/*
 * showMenu function declaration:
 *  - Declares the function that displays supported command options (help menu)
 *  - Calls the showMenu function definition located in Menu.cpp
 */
void showMenu();

/*
    handleCommand
    -----------------------------
    Description:
    Routes the user's command to the appropriate function handler
    (e.g., adding parts, removing items, loading from file, etc.).

    Parameters:
    - command: Single-character command input by the user.
    - inventory: Reference to the vector storing inventory items.
    - itemCount: Reference to the number of items currently in inventory.

    Purpose:
    Acts as the command dispatcher inside the main loop, promoting modular design
    and maintaining clear separation of responsibilities between logic and execution.

    In Simpler Terms:
    This function figures out what the user wants to do (like add or print items),
    and calls the function that does the job. It keeps track of the list and updates
    it when needed.
*/
void handleCommand(char command, vector<InventoryItem>& inventory, int& itemCount);

/*
    Inventory Command Functions
    -----------------------------
    Description:
    These functions define the core operations for interacting with the inventory system.
    They allow the user to modify item quantities, create new items, read from files,
    write to files, and view the current inventory. All functions operate on the inventory
    vector by reference to ensure direct, in-place modifications.

    In Simpler Terms:
    These are the main things the program can do when a user types a command.
    They're how the program changes or shows what's in the inventory.
*/

// Adds units to an existing inventory item.
void addParts(vector<InventoryItem>& inventory, int itemCount);

// Removes units from an existing inventory item.
void removeParts(vector<InventoryItem>& inventory, int itemCount);

// Loads inventory data from a file (appends to current list).
void inputFromFile(vector<InventoryItem>& inventory, int& itemCount);

// Saves inventory data to a file in pipe-delimited format.
void outputToFile(const vector<InventoryItem>& inventory, int itemCount);

// Displays all inventory items in a formatted table view.
void printInventory(const vector<InventoryItem>& inventory, int itemCount);

// Creates and appends a new inventory item from user input.
void createNewItem(vector<InventoryItem>& inventory, int& itemCount);

#endif // MENU_H
