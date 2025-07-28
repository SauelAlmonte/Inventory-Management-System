// Specification File -> Menu.h
#ifndef MENU_H
#define MENU_H

#include <vector>
#include "InventoryItem.h"

using namespace std;

// Display help text with available commands
void showMenu();

/*
    handleCommand
    -----------------------------
    Description:
    This function takes a character input representing the user's command and dispatches control
    to the appropriate command handler (e.g., add, remove, load, save). It operates on a reference
    to the inventory container and item count to ensure in-place modification and prevent unnecessary copying.

    Parameters:
    - char command: user input command character
    - vector<InventoryItem>& inventory: reference to the current inventory collection
    - int& itemCount: reference to the count of items currently in inventory

    Purpose:
    Acts as a command router inside the main loop, maintaining separation of concerns and
    supporting modular function delegation.

    In Simpler Terms:
    This function reads what the user wants to do (like add parts or print the list),
    and then sends the program to do that job. It keeps track of the list of items and
    how many are in the list, updating them as needed.
*/
void handleCommand(char command, vector<InventoryItem>& inventory, int& itemCount);

/*
    Inventory Command Functions
    -----------------------------
    Description:
    These functions implement core inventory operations. They handle user-initiated commands
    such as adding/removing item units, importing/exporting data from files, printing the inventory,
    and appending new items. Vectors are passed by reference to maintain consistency and performance.
    itemCount is passed by reference when the function may modify the inventory size.

    In Simpler Terms:
    These are the main actions the program can do when the user types a command.
    They let you change item quantities, load or save items to a file, show the list,
    or add something new to the inventory.
*/
void addParts(vector<InventoryItem>& inventory, int itemCount);
void removeParts(vector<InventoryItem>& inventory, int itemCount);
void inputFromFile(vector<InventoryItem>& inventory, int& itemCount);
void outputToFile(const vector<InventoryItem>& inventory, int itemCount);
void printInventory(const vector<InventoryItem>& inventory, int itemCount);
void createNewItem(vector<InventoryItem>& inventory, int& itemCount);

#endif
