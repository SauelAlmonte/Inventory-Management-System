/*
    Author     : Sauel Almonte
    Date       : July 28th, 2025
    Due Date   : July 31st, 2025
    Course     : CSC 237
    Project    : 02 – Inventory Management System
    Program    : Inventory Management System

    Description:
        This program manages an inventory of items using the InventoryItem class.
        It features a command-driven interface that allows users to:
          - Add or remove units from existing items
          - Create new inventory items
          - Load and save inventory data from/to external files
          - Display a formatted list of all items in inventory

        The system enforces input validation (e.g., quantity limits, numeric formats),
        caps inventory size at 100 items, and handles common boundary conditions.
        The project demonstrates structured programming principles,
        modular design with header and source files, and file I/O in C++.
*/

#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <cctype>
#include "InventoryItem.h"
#include "Menu.h"

using namespace std;

// Function prototype for welcome banner
void displayBanner();

int main() {
    vector<InventoryItem> inventory(100);
    int itemCount = 0;
    char command;
    bool running = true;

    // Display welcome banner at program startup
    displayBanner();

    // Prompt user with basic instructions
    cout << "Enter a command (h for help menu, q to quit).\n";

    /*
        Main Command Loop:
        - Prompts the user for a command.
        - Converts the input to lowercase to ensure case-insensitive handling.
        - If the user enters 'q', the program displays a farewell message and exits.
        - Otherwise, the input is routed to handleCommand() in Menu.cpp,
          which performs the requested inventory operation.
        - The input buffer is flushed after each command to ensure clean reads.
    */
    while (running) {
        cout << "Command: ";
        cin >> command;
        command = static_cast<char>(tolower(command));
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush buffer

        if (command == 'q') {
            cout << "Thank you for using the Inventory Management System. Come again.\n";
            running = false;
        } else {
            handleCommand(command, inventory, itemCount);
        }
    }

    return 0;
}

/*
 * Displays a formatted welcome banner.
 *
 * The banner is centered using calculated padding based on a fixed width.
 * - title.length() gets the character count of the message.
 * - Padding is calculated as (width - title length) / 2.
 * - static_cast<int>() ensures type safety during arithmetic.
 *
 * The output includes a top and bottom border made of asterisks,
 * with the centered title printed in between.
 */
void displayBanner() {
    constexpr int width = 50;
    const string title = "Welcome to the Inventory Management System";
    const int pad = (width - static_cast<int>(title.length())) / 2;

    cout << string(width, '*') << endl;
    cout << string(pad, ' ') << title << endl;
    cout << string(width, '*') << endl;
}
