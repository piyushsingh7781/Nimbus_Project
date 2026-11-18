#include <stdio.h>
#include <string.h>

#define MAX_DRUGS 100

// Structure to store Drug Details
struct Drug {
    int id;
    char name[50];
    int expYear;
    int expMonth;
    int expDay;
    float price;
    int stock;
};

// Function prototypes
void addDrug(struct Drug *drugs, int *count);
void displayInventory(const struct Drug *drugs, int count);
void checkExpiry(const struct Drug *drugs, int count, int curYear, int curMonth, int curDay);
void restockDrug(struct Drug *drugs, int count);

int main() {
    struct Drug inventory[MAX_DRUGS];
    int drugCount = 0;
    int choice;

    // Simulated Current Date for Expiry Check (e.g., October 27, 2026)
    int currentYear = 2026;
    int currentMonth = 10;
    int currentDay = 27;

    do {
        printf("\n=========================================\n");
        printf("    HOSPITAL PHARMACY STOCK SYSTEM       \n");
        printf("=========================================\n");
        printf("1. Add New Drug\n");
        printf("2. Display All Inventory\n");
        printf("3. Check for Expired Products\n");
        printf("4. Restock Drug (Dynamic Update)\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addDrug(inventory, &drugCount);
                break;
            case 2:
                displayInventory(inventory, drugCount);
                break;
            case 3:
                checkExpiry(inventory, drugCount, currentYear, currentMonth, currentDay);
                break;
            case 4:
                restockDrug(inventory, drugCount);
                break;
            case 5:
                printf("\nExiting system. Stay safe!\n");
                break;
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}

// Function to add a new drug using pointers
void addDrug(struct Drug *drugs, int *count) {
    if (*count >= MAX_DRUGS) {
        printf("\n[Error] Inventory is full!\n");
        return;
    }

    struct Drug *newDrug = &drugs[*count];

    printf("\nEnter Drug ID: ");
    scanf("%d", &newDrug->id);
    printf("Enter Drug Name: ");
    scanf("%s", newDrug->name);
    printf("Enter Expiry Date (YYYY MM DD): ");
    scanf("%d %d %d", &newDrug->expYear, &newDrug->expMonth, &newDrug->expDay);
    printf("Enter Price ($): ");
    scanf("%f", &newDrug->price);
    printf("Enter Initial Stock Quantity: ");
    scanf("%d", &newDrug->stock);

    (*count)++;
    printf("\n[Success] Drug added successfully!\n");
}

// Function to display inventory using pointer traversal
void displayInventory(const struct Drug *drugs, int count) {
    if (count == 0) {
        printf("\n[Info] Inventory is empty.\n");
        return;
    }

    printf("\n-----------------------------------------------------------------\n");
    printf("%-5s | %-20s | %-12s | %-8s | %-6s\n", "ID", "Name", "Expiry Date", "Price", "Stock");
    printf("-----------------------------------------------------------------\n");
    
    for (int i = 0; i < count; i++) {
        printf("%-5d | %-20s | %04d-%02d-%02d   | $%-7.2f | %-6d\n", 
               (drugs + i)->id, 
               (drugs + i)->name, 
               (drugs + i)->expYear, 
               (drugs + i)->expMonth, 
               (drugs + i)->expDay, 
               (drugs + i)->price, 
               (drugs + i)->stock);
    }
    printf("-----------------------------------------------------------------\n");
}

// Function to check and alert expired products
void checkExpiry(const struct Drug *drugs, int count, int curYear, int curMonth, int curDay) {
    if (count == 0) {
        printf("\n[Info] No drugs in inventory to check.\n");
        return;
    }

    int expiredCount = 0;
    printf("\n--- EXPIRY ALERTS ---\n");
    
    for (int i = 0; i < count; i++) {
        const struct Drug *d = drugs + i;
        int isExpired = 0;

        if (d->expYear < curYear) {
            isExpired = 1;
        } else if (d->expYear == curYear && d->expMonth < curMonth) {
            isExpired = 1;
        } else if (d->expYear == curYear && d->expMonth == curMonth && d->expDay < curDay) {
            isExpired = 1;
        }

        if (isExpired) {
            printf("[ALERT] Drug ID: %d (%s) expired on %04d-%02d-%02d! Remove from shelf.\n",
                   d->id, d->name, d->expYear, d->expMonth, d->expDay);
            expiredCount++;
        }
    }

    if (expiredCount == 0) {
        printf("[Info] All drugs are within their valid shelf life.\n");
    }
}

// Function to dynamically restock a drug using pointers for real-time updates
void restockDrug(struct Drug *drugs, int count) {
    if (count == 0) {
        printf("\n[Info] Inventory is empty.\n");
        return;
    }

    int targetId, addQty, found = 0;
    printf("\nEnter Drug ID to restock: ");
    scanf("%d", &targetId);

    for (int i = 0; i < count; i++) {
        struct Drug *d = (drugs + i);
        if (d->id == targetId) {
            printf("Current Stock for %s: %d\n", d->name, d->stock);
            printf("Enter quantity to add: ");
            scanf("%d", &addQty);

            if (addQty > 0) {
                d->stock += addQty; // Real-time pointer update
                printf("\n[Success] Stock updated! New stock for %s is %d.\n", d->name, d->stock);
            } else {
                printf("\n[Error] Invalid quantity.\n");
            }
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\n[Error] Drug with ID %d not found in inventory.\n", targetId);
    }
}
