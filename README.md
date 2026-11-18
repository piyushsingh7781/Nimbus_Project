# 🏥 Hospital Pharmacy Stock System (HPSS) — Technical Reference Manual

A robust, enterprise-grade, console-based inventory management system written in standard **C (C99)**. Engineered specifically for hospital pharmacies, this application provides precision tracking of medication batches, real-time stock mutations using pointer arithmetic, automated chronological expiration screening, and strict boundary validation.

---

## 📋 Table of Contents

1. [System Architecture & Memory Layout](https://www.google.com/search?q=%23-system-architecture--memory-layout)
2. [Data Structure Specifications](https://www.google.com/search?q=%23-data-structure-specifications)
3. [Function-by-Function Technical Reference](https://www.google.com/search?q=%23-function-by-function-technical-reference)
4. [Algorithmic Deep Dives](https://www.google.com/search?q=%23-algorithmic-deep-dives)
5. [Core C Concepts Demonstrated](https://www.google.com/search?q=%23-core-c-concepts-demonstrated)
6. [Compilation, Linking, & Debugging Guide](https://www.google.com/search?q=%23-compilation-linking--debugging-guide)
7. [Comprehensive Interactive Session Walkthrough](https://www.google.com/search?q=%23-comprehensive-interactive-session-walkthrough)
8. [Edge Cases, Error Handling, & Limitations](https://www.google.com/search?q=%23-edge-cases-error-handling--limitations)
9. [Future Roadmap & Modular Expansion Plan](https://www.google.com/search?q=%23-future-roadmap--modular-expansion-plan)

---

## 🏗️ System Architecture & Memory Layout

The application follows a **monolithic procedural architecture** with strict separation of concerns across single-responsibility functions. Memory management relies on a statically allocated array on the stack (`inventory[MAX_DRUGS]`), manipulated efficiently via pointers and pass-by-reference mechanics.

```text
               +----------------------------------------+
               |              main()                    |
               |  - stack allocation: inventory[100]    |
               |  - tracking variable: drugCount        |
               |  - reference date: 2026-10-27          |
               +----------------------------------------+
                                   |
         +-------------------------+-------------------------+
         |                         |                         |
         v                         v                         v
+-----------------+       +-------------------+     +------------------+
|   addDrug()     |       | displayInventory()|     |   checkExpiry()  |
| - modifies count|       | - read-only (const)|    | - date evaluation|
| - pointer offset|       | - pointer traversal|    | - structural scan|
+-----------------+       +-------------------+     +------------------+
                                   |
                                   v
                          +-------------------+
                          |   restockDrug()   |
                          | - ID lookup match |
                          | - live qty update |
                          +-------------------+

```

---

## 🗂️ Data Structure Specifications

The core entity of the system is `struct Drug`, designed to pack heterogeneous data fields efficiently while keeping memory footprint minimal.

```c
struct Drug {
    int id;          // Unique numeric identifier (Primary Key simulation)
    char name[50];   // Null-terminated string for medication name (Max 49 chars + '\0')
    int expYear;     // Four-digit expiration year (e.g., 2027)
    int expMonth;    // Expiration month (1-12)
    int expDay;      // Expiration day (1-31)
    float price;     // Floating-point unit price in USD ($)
    int stock;       // Current numerical quantity available on shelves
};

```

---

## ⚙️ Function-by-Function Technical Reference

### 1. `int main()`

* **Purpose:** Entry point of the program. Manages the primary execution loop (`do-while`), user menu dispatch via `switch-case`, and holds system state variables (`inventory` array, `drugCount`, and simulated current date constants).
* **Parameters:** None (`void`).
* **Return Value:** `int` (`0` on successful termination).

### 2. `void addDrug(struct Drug *drugs, int *count)`

* **Purpose:** Registers a new medication record into the next available array index.
* **Parameters:**
* `struct Drug *drugs`: Pointer to the base address of the inventory array.
* `int *count`: Pointer to the integer tracking current total items (enables in-place incrementing).


* **Execution Logic:**
1. Checks if `*count >= MAX_DRUGS` (Overflow protection).
2. Computes target insertion address using pointer arithmetic: `struct Drug *newDrug = &drugs[*count];`.
3. Prompts user for input fields (`id`, `name`, `expYear`, `expMonth`, `expDay`, `price`, `stock`).
4. Increments `*count` dereference (`(*count)++`).



### 3. `void displayInventory(const struct Drug *drugs, int count)`

* **Purpose:** Renders a clean, formatted ASCII table of all active inventory records.
* **Parameters:**
* `const struct Drug *drugs`: Read-only pointer to the inventory array (`const` ensures data integrity).
* `int count`: Total number of active records to iterate through.


* **Execution Logic:**
1. Validates if `count == 0` (Early exit for empty inventory).
2. Prints formatted table headers using width specifiers (`%-5s`, `%-20s`, etc.).
3. Iterates through records using pointer offset notation: `(drugs + i)->member` instead of traditional array indexing `drugs[i].member`.



### 4. `void checkExpiry(const struct Drug *drugs, int count, int curYear, int curMonth, int curDay)`

* **Purpose:** Evaluates every medication's expiration date against a reference current date.
* **Parameters:**
* `const struct Drug *drugs`: Read-only inventory pointer.
* `int count`: Number of items to check.
* `int curYear`, `int curMonth`, `int curDay`: Reference date components.


* **Execution Logic:**
* Performs hierarchical chronological evaluation:
* If `expYear < curYear` $\rightarrow$ Expired.
* Else if `expYear == curYear` and `expMonth < curMonth` $\rightarrow$ Expired.
* Else if `expYear == curYear` and `expMonth == curMonth` and `expDay < curDay` $\rightarrow$ Expired.


* Emits formatted `[ALERT]` warning strings for non-compliant batches.



### 5. `void restockDrug(struct Drug *drugs, int count)`

* **Purpose:** Facilitates real-time inventory quantity adjustments for specific medications.
* **Parameters:**
* `struct Drug *drugs`: Mutable pointer to the inventory array.
* `int count`: Total records to search.


* **Execution Logic:**
* Prompts for `targetId`.
* Scans array linearly (`O(n)` search time complexity).
* Upon matching `d->id == targetId`, prompts for `addQty`, validates positivity (`addQty > 0`), and updates stock in-place: `d->stock += addQty;`.



---

## 🧠 Algorithmic Deep Dives

### Chronological Expiry Evaluation Algorithm

The expiration checker avoids complex calendar epoch conversions by breaking dates down into discrete scalar integers (`YYYY`, `MM`, `DD`) and comparing them lexicographically:

$$\text{IsExpired} = \begin{cases} 1, & \text{if } \text{Year}_{\text{exp}} < \text{Year}_{\text{cur}} \\ 1, & \text{if } \text{Year}_{\text{exp}} = \text{Year}_{\text{cur}} \land \text{Month}_{\text{exp}} < \text{Month}_{\text{cur}} \\ 1, & \text{if } \text{Year}_{\text{exp}} = \text{Year}_{\text{cur}} \land \text{Month}_{\text{exp}} = \text{Month}_{\text{cur}} \land \text{Day}_{\text{exp}} < \text{Day}_{\text{cur}} \\ 0, & \text{otherwise} \end{cases}$$

---

## 🔬 Core C Concepts Demonstrated

| Concept | Technical Implementation | Why It Matters |
| --- | --- | --- |
| **Structures (`struct`)** | `struct Drug { ... }` | Groups heterogeneous variables into a unified semantic type. |
| **Pointer Arithmetic** | `(drugs + i)->id` | Direct memory address manipulation for high-performance array navigation. |
| **Pass-by-Reference** | `addDrug(struct Drug *drugs, int *count)` | Allows functions to modify caller-scope variables directly without global state pollution. |
| **`const` Correctness** | `const struct Drug *drugs` | Guarantees read-only safety for display and audit routines, preventing accidental mutations. |
| **Buffer Management** | Fixed-size array bounds checks | Prevents stack overflows by enforcing `MAX_DRUGS` limits. |

---

## 🛠️ Compilation, Linking, & Debugging Guide

To compile the program with maximum compiler warnings enabled for robust code quality verification:

### 1. GCC (GNU Compiler Collection)

```bash
gcc -Wall -Wextra -std=c99 -O2 pharmacy_system.c -o pharmacy_system

```

### 2. Clang (LLVM)

```bash
clang -Wall -Wextra -std=c99 pharmacy_system.c -o pharmacy_system

```

### 3. MSVC (Microsoft Visual C++ / Developer Command Prompt)

```cmd
cl /W4 /O2 pharmacy_system.c /Fe:pharmacy_system.exe

```

---

## 💻 Comprehensive Interactive Session Walkthrough

```text
=========================================
    HOSPITAL PHARMACY STOCK SYSTEM       
=========================================
1. Add New Drug
2. Display All Inventory
3. Check for Expired Products
4. Restock Drug (Dynamic Update)
5. Exit
Enter your choice: 1

Enter Drug ID: 101
Enter Drug Name: Paracetamol
Enter Expiry Date (YYYY MM DD): 2027 08 15
Enter Price ($): 4.50
Enter Initial Stock Quantity: 200

[Success] Drug added successfully!

=========================================
    HOSPITAL PHARMACY STOCK SYSTEM       
=========================================
1. Add New Drug
2. Display All Inventory
3. Check for Expired Products
4. Restock Drug (Dynamic Update)
5. Exit
Enter your choice: 1

Enter Drug ID: 102
Enter Drug Name: Amoxicillin
Enter Expiry Date (YYYY MM DD): 2026 05 10
Enter Price ($): 12.75
Enter Initial Stock Quantity: 75

[Success] Drug added successfully!

=========================================
    HOSPITAL PHARMACY STOCK SYSTEM       
=========================================
1. Add New Drug
2. Display All Inventory
3. Check for Expired Products
4. Restock Drug (Dynamic Update)
5. Exit
Enter your choice: 2

-----------------------------------------------------------------
ID    | Name                 | Expiry Date  | Price    | Stock 
-----------------------------------------------------------------
101   | Paracetamol          | 2027-08-15   | $4.50    | 200   
102   | Amoxicillin          | 2026-05-10   | $12.75   | 75    
-----------------------------------------------------------------

=========================================
    HOSPITAL PHARMACY STOCK SYSTEM       
=========================================
1. Add New Drug
2. Display All Inventory
3. Check for Expired Products
4. Restock Drug (Dynamic Update)
5. Exit
Enter your choice: 3

--- EXPIRY ALERTS ---
[ALERT] Drug ID: 102 (Amoxicillin) expired on 2026-05-10! Remove from shelf.

=========================================
    HOSPITAL PHARMACY STOCK SYSTEM       
=========================================
1. Add New Drug
2. Display All Inventory
3. Check for Expired Products
4. Restock Drug (Dynamic Update)
5. Exit
Enter your choice: 4

Enter Drug ID to restock: 101
Current Stock for Paracetamol: 200
Enter quantity to add: 100

[Success] Stock updated! New stock for Paracetamol is 300.

=========================================
    HOSPITAL PHARMACY STOCK SYSTEM       
=========================================
1. Add New Drug
2. Display All Inventory
3. Check for Expired Products
4. Restock Drug (Dynamic Update)
5. Exit
Enter your choice: 5

Exiting system. Stay safe!

```

---

## ⚠️ Edge Cases, Error Handling, & Limitations

| Condition | Failure Mode Risk | System Mitigation Strategy |
| --- | --- | --- |
| **Inventory Full (`count >= MAX_DRUGS`)** | Stack memory corruption / segmentation fault | Handled in `addDrug()` with an early bounds check and error message. |
| **Negative / Zero Restock Input** | Logical stock corruption | Validated via `if (addQty > 0)` check before applying addition. |
| **Drug ID Not Found** | Silent failures or incorrect memory mutations | `found` flag mechanism prints explicit error message if ID lookup fails. |
| **Whitespace in Medication Names** | Truncated strings using standard `scanf("%s")` | Limitation acknowledged; input requires continuous strings or underscores (e.g., `Ibuprofen_400mg`). |
| **Volatile RAM Storage** | Data loss upon application termination | Program operates entirely in-memory; restart clears records. |

---

## 🔮 Future Roadmap & Modular Expansion Plan

* **[ ] Persistent Database Storage (File I/O):** Integrate `<stdio.h>` binary/CSV serialization (`fopen`, `fwrite`, `fread`) to save state across sessions.
* **[ ] System Clock Integration:** Replace hardcoded reference dates with real-time system calls via `<time.h>` (`time()` and `localtime()`).
* **[ ] Prescription Dispensing Engine:** Implement a `dispenseDrug()` function to decrement inventory when prescriptions are fulfilled.
* **[ ] Dynamic Heap Allocation:** Replace the rigid `MAX_DRUGS 100` macro with dynamic memory allocation (`malloc`, `realloc`, `free`) for scalable inventory tracking.
* **[ ] Safe String Buffers:** Transition from unsafe `scanf("%s")` calls to buffer-bounded `fgets()` with whitespace handling.


