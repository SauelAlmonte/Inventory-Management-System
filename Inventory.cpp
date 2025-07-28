/*
Author     : Sauel Almonte
    Date       : July 28th, 2025
    Due Date   : July 31st, 2025
    Course     : CSC 237
    Project    : 02 – Inventory Management System
    Program    : Inventory Management System

    Description:
        This program manages an inventory of items using the InventoryItem class.
        It implements a command loop that allows the user to add/remove parts,
        create new items, load and save inventory data from/to files, and display
        the current inventory. The program uses dynamic data structures and
        ensures input constraints such as maximum unit limits. The application
        demonstrates structured programming, modular design, and file I/O in C++.
*/

#include <iostream>
#include <vector>
#include <cctype>
#include "InventoryItem.h"
#include "Menu.h"

using namespace std;

void displayBanner();

int main() {
    vector<InventoryItem> inventory(100);
    int itemCount = 0;
    char command;
    bool running = true;

    displayBanner();
    cout << "Enter h for help menu or q to quit.\n";

    while (running) {
        cout << "Command: ";
        cin >> command;
        command = static_cast<char>(tolower(command));

        if (command == 'q') {
            cout << "Thank you for using the Inventory Management System. Come again.\n";
            running = false;
        } else {
            handleCommand(command, inventory, itemCount);
        }
    }

    return 0;
}

void displayBanner() {
    constexpr int width = 50;
    const string title = "Welcome to the Inventory Management System";
    const int pad = (width - static_cast<int>(title.length())) / 2;

    cout << string(width, '*') << endl;
    cout << string(pad, ' ') << title << endl;
    cout << string(width, '*') << endl;
}
