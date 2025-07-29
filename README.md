# Inventory Management System

A modular C++ application for managing hardware inventory using file I/O, input validation, and structured data management.

---

### Author
**Sauel Almonte**  
[LinkedIn Profile](https://www.linkedin.com/in/sauel-almonte)
<br>
[My Portfolio](https://s-almonte.vercel.app/)

---

## Features

- Add, remove, and create new inventory items.
- Load inventory data from a text file.
- Save current inventory to a text file.
- Enforces business rules:
    - Max 100 items
    - Quantity range: 0–30 units
    - Validates numeric and logical input
- Modular architecture:
    - **Menu.h / Menu.cpp** – Command routing and interface
    - **InventoryItem.h / InventoryItem.cpp** – Item data model
    - **Inventory.cpp** – Main entry point and command loop

---

## Project Structure
```text
/inventory-management-system
├── Inventory.cpp # Main function and program loop
├── Menu.cpp # Command handlers (add, remove, input, output, etc.)
├── Menu.h # Function declarations
├── InventoryItem.cpp # InventoryItem class implementation
├── InventoryItem.h # InventoryItem class definition
├── electrical.txt # Sample input file (pipe-delimited)
├── output.txt # Generated output file
├── CMakeLists.txt # CMake build configuration
├── .gitignore # Git ignore rules
└── README.md # Project documentation
```

---

## Build & Run Instructions

### Prerequisites
- A C++17 compatible compiler
- An IDE or terminal environment:
    - JetBrains CLion
    - Visual Studio Code
    - Visual Studio (Windows)
    - Terminal/Command Prompt

---

### Option 1: Compile & Run via Terminal
```bash

g++ -std=c++17 -o inventory Inventory.cpp Menu.cpp InventoryItem.cpp
./inventory
```

---

---

### Option 2: Using CLion

1. **Open** CLion and load the project folder.
2. CLion auto-configures **CMake**.
3. Click **Build** or press `Shift + F9`.
4. Click **Run** or press `Shift + F10`.

---

### Usage

1. **Launch** the program.
2. **Enter one of the following commands**:

| Command | Description                          |
|---------|--------------------------------------|
| `h`     | Print help menu                      |
| `i`     | Input inventory from a file          |
| `n`     | Create a new inventory item          |
| `a`     | Add parts to an existing item        |
| `r`     | Remove parts from an existing item   |
| `p`     | Display the current inventory list   |
| `o`     | Output inventory data to a text file |
| `q`     | Quit the program                     |

---

### Example Output

```text
**************************************************
     Welcome to the Inventory Management System
**************************************************
Enter a command (or h for help menu - q to quit).
Command: p

Item #    Description                              Cost  Quantity
_________________________________________________________________________
0         Stainless Steel Screws                   6.95       20
1         PVC Elbow Joint                          1.25       15

2 records.

```

---

## License

This project is licensed under the [MIT License](LICENSE).  
Feel free to modify, reuse, or distribute with proper attribution.

---

## Disclaimer

This project is for educational and demonstrative purposes.  
Use it responsibly. No warranties or guarantees are provided.

---