#ifndef LIBRARY_INVENTORY_H
#define LIBRARY_INVENTORY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // For strcasestr()

// Constants
#define FILENAME "inventory.txt"
#define LOW_STOCK_THRESHOLD 3

// Struct for inventory books
typedef struct {
    int id;
    char title[100];
    int quantity;
} Book;

// Function prototypes
void inventoryMenu();
void addBook();
void updateStock();
void removeBook();
void viewInventory();
void lowStockAlert();
void inventoryReport();

#endif // LIBRARY_INVENTORY_H
