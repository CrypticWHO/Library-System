#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library_inventory.h"
#include "file_operations.h" // Role 5 header

void inventoryMenu() {
    int choice;
    do {
        printf("\nLibrary Inventory Management\n");
        printf("1. Add Book\n");
        printf("2. Update Stock\n");
        printf("3. Remove Book\n");
        printf("4. View Inventory\n");
        printf("5. Low Stock Alerts\n");
        printf("6. Inventory Report\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addBook(); break;
            case 2: updateStock(); break;
            case 3: removeBook(); break;
            case 4: viewInventory(); break;
            case 5: lowStockAlert(); break;
            case 6: inventoryReport(); break;
            case 7: printf("Exiting...\n"); break;
            default: printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 7);
}

void addBook() {
    Book b;
    char data[256];

    printf("Enter Book ID: ");
    while (scanf("%d", &b.id) != 1) {
        printf("Invalid input. Please enter a valid ID: ");
        while(getchar() != '\n');
    }

    getchar(); // Clear newline
    printf("Enter Title: ");
    fgets(b.title, sizeof(b.title), stdin);
    b.title[strcspn(b.title, "\n")] = '\0';

    printf("Enter Quantity: ");
    while (scanf("%d", &b.quantity) != 1 || b.quantity < 0) {
        printf("Invalid input. Enter a non-negative quantity: ");
        while(getchar() != '\n');
    }

    snprintf(data, sizeof(data), "%d|%s|%d", b.id, b.title, b.quantity);

    if (addDataToFile(FILENAME, data))
        printf("Book added successfully.\n");
    else
        printf("Failed to add book.\n");
}

void updateStock() {
    Book b;
    int id, change;
    char idStr[10], newData[256];
    int found = 0;

    printf("Enter Book ID to update: ");
    scanf("%d", &id);
    sprintf(idStr, "%d", id);

    printf("Enter stock change (+/-): ");
    scanf("%d", &change);

    FILE *fp = fopen(FILENAME, "r");
    if (!fp) {
        perror("File open failed");
        return;
    }

    while (fscanf(fp, "%d|%[^|]|%d\n", &b.id, b.title, &b.quantity) == 3) {
        if (b.id == id) {
            b.quantity += change;
            if (b.quantity < 0) b.quantity = 0;
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (found) {
        snprintf(newData, sizeof(newData), "%d|%s|%d", id, b.title, b.quantity);
        if (updateDataInFile(FILENAME, idStr, newData))
            printf("Stock updated successfully.\n");
        else
            printf("Failed to update file.\n");
    } else {
        printf("Book ID not found.\n");
    }
}

void removeBook() {
    int id;
    char idStr[10];

    printf("Enter Book ID to remove: ");
    scanf("%d", &id);
    sprintf(idStr, "%d", id);

    if (deleteDataFromFile(FILENAME, idStr))
        printf("Book removed successfully.\n");
    else
        printf("Book ID not found.\n");
}

void viewInventory() {
    Book b;
    FILE *fp = fopen(FILENAME, "r");

    if (!fp) {
        printf("No inventory found.\n");
        return;
    }

    printf("\n%-5s %-30s %-10s\n", "ID", "Title", "Quantity");
    printf("--------------------------------------------------\n");

    while (fscanf(fp, "%d|%[^|]|%d\n", &b.id, b.title, &b.quantity) == 3) {
        printf("%-5d %-30s %-10d\n", b.id, b.title, b.quantity);
    }

    fclose(fp);
}


void lowStockAlert() {
    Book b;
    FILE *fp = fopen(FILENAME, "r");
    int alert = 0;

    if (!fp) {
        printf("No inventory found.\n");
        return;
    }

    printf("\nLow Stock Alert (Less than %d)\n", LOW_STOCK_THRESHOLD);
    printf("%-5s %-30s %-10s\n", "ID", "Title", "Quantity");

    while (fscanf(fp, "%d|%[^|]|%d\n", &b.id, b.title, &b.quantity) == 3) {
        if (b.quantity < LOW_STOCK_THRESHOLD) {
            printf("%-5d %-30s %-10d\n", b.id, b.title, b.quantity);
            alert = 1;
        }
    }

    if (!alert)
        printf("No low stock alerts.\n");

    fclose(fp);
}

void inventoryReport() {
    Book b;
    FILE *fp = fopen(FILENAME, "r");
    int total = 0;

    if (!fp) {
        printf("No inventory data.\n");
        return;
    }

    printf("\nInventory Report:\n");
    printf("%-5s %-30s %-10s\n", "ID", "Title", "Quantity");

    while (fscanf(fp, "%d|%[^|]|%d\n", &b.id, b.title, &b.quantity) == 3) {
        printf("%-5d %-30s %-10d\n", b.id, b.title, b.quantity);
        total += b.quantity;
    }

    printf("--------------------------------------------------\n");
    printf("Total Books in Inventory: %d\n", total);
    fclose(fp);
}


