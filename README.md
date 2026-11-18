🏥 Hospital Pharmacy Stock System (C)

A fast, lightweight, console-based inventory management system written in C. Designed for hospital pharmacies, this application tracks medication stock, monitors expiration dates, and enables real-time restocking using C structures and pointer arithmetic.

📋 Table of Contents

Features

Core C Concepts Demonstrated

Data Structure

Getting Started

Usage & Sample Output

Input Guidelines & Limitations

Roadmap & Future Enhancements

✨ Features

Add New Medications: Register up to 100 unique drugs (MAX_DRUGS) with an ID, name, expiration date, unit price, and initial stock count.

Tabular Inventory View: Displays all registered medications in an aligned, easy-to-read CLI table.

Automated Expiry Alerts: Scans the entire inventory against the system's reference date (2026-10-27) and flags expired medications for immediate shelf removal.

Real-Time Dynamic Restocking: Look up any medication by its unique Drug ID and increment stock levels directly in memory via pointers.

Input & Boundary Validation: Guards against array overflow, negative/zero restock quantities, empty inventories, and invalid menu selections.

🧠 Core C Concepts Demonstrated

This project serves as a clean, practical reference for fundamental and intermediate C programming techniques:

Concept

Implementation in Project

Structures (struct)

Encapsulates heterogeneous drug attributes (int, char[], float) into a cohesive struct Drug data type.

Pointer Arithmetic

Traverses arrays using offset notation ((drugs + i)->member) rather than standard array indexing.

Pass-by-Reference

Passes &drugCount to addDrug() and direct struct pointers to restockDrug() for in-place memory updates.

const Correctness

Protects read-only operations (displayInventory() and checkExpiry()) using const struct Drug * parameters.

Modular Design

Separates program logic into clean, single-responsibility functions with explicit prototypes.

🗂️ Data Structure

Each medication record is represented by the following structure:

struct Drug {
    int id;          // Unique numeric identifier
    char name[50];   // Medication name (up to 49 characters)
    int expYear;     // Expiration year (YYYY)
    int expMonth;    // Expiration month (MM)
    int expDay;      // Expiration day (DD)
    float price;     // Unit price in USD ($)
    int stock;       // Available quantity in inventory
};


🚀 Getting Started

Prerequisites

Ensure you have a standard C compiler installed on your machine:

GCC (gcc --version)

Clang (clang --version)

MinGW / MSVC (for Windows)

Compilation & Execution

Save the source code as pharmacy_system.c.

Open your terminal and navigate to the project directory.

Compile the program with warning flags enabled:

gcc -Wall -Wextra pharmacy_system.c -o pharmacy_system


Run the executable:

Linux / macOS:

./pharmacy_system


Windows (Command Prompt / PowerShell):

pharmacy_system.exe


💻 Usage & Sample Output

Main Menu

=========================================
    HOSPITAL PHARMACY STOCK SYSTEM       
=========================================
1. Add New Drug
2. Display All Inventory
3. Check for Expired Products
4. Restock Drug (Dynamic Update)
5. Exit
Enter your choice:


Example Workflow

1. Viewing Inventory (Option 2):

-----------------------------------------------------------------
ID    | Name                 | Expiry Date  | Price    | Stock 
-----------------------------------------------------------------
101   | Paracetamol          | 2027-08-15   | $4.50    | 250   
102   | Amoxicillin          | 2026-05-10   | $12.00   | 80    
-----------------------------------------------------------------


2. Checking Expired Products (Option 3):

--- EXPIRY ALERTS ---
[ALERT] Drug ID: 102 (Amoxicillin) expired on 2026-05-10! Remove from shelf.


3. Restocking a Medication (Option 4):

Enter Drug ID to restock: 101
Current Stock for Paracetamol: 250
Enter quantity to add: 50

[Success] Stock updated! New stock for Paracetamol is 300.


⚠️ Input Guidelines & Limitations

No Spaces in Drug Names: Input is read using scanf("%s", ...), which stops at whitespace. Use underscores or hyphens for multi-word names (e.g., Vitamin_C or Ibuprofen-400mg).

Date Format: Enter expiration dates separated by spaces in YYYY MM DD format (e.g., 2027 11 30).

Simulated System Date: The reference date in main() is currently hardcoded to 2026-10-27 for deterministic testing of the expiry alert logic.

Volatile Memory: Data is stored in RAM during runtime and resets when the program exits.

🔮 Roadmap & Future Enhancements

[ ] Persistent File Storage: Implement binary or CSV file I/O (fopen, fread, fwrite) to save and load inventory across sessions.

[ ] Real-Time System Clock: Integrate <time.h> (time() and localtime()) to automatically fetch the host machine's current date.

[ ] Prescription Dispensing: Add a dispenseDrug() feature to deduct stock when medications are issued to patients.

[ ] Dynamic Capacity: Replace the fixed MAX_DRUGS array with dynamic heap allocation (malloc / realloc).

[ ] Safe String Input: Switch to fgets() with input buffer clearing to allow spaces in medication names.
