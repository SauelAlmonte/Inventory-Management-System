// Implementation File -> Menu.cpp
#include "Menu.h"
#include <iostream>

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

void printInventory(const vector<InventoryItem>& inventory, int itemCount) {
    cout << "[printInventory()] called - implementation pending.\n";
}

void createNewItem(vector<InventoryItem>& inventory, int& itemCount) {
    cout << "[createNewItem()] called - implementation pending.\n";
}
