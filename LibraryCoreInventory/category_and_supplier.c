
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "category_and_supplier.h"

// Include Role 5 functions
extern int addDataToFile(const char *filename, const char *data);
extern int readDataFromFile(const char *filename);
extern int updateDataInFile(const char *filename, const char *id, const char *newData);
extern int deleteDataFromFile(const char *filename, const char *id);

#define CAT_FILE "categories.txt"
#define SUP_FILE "suppliers.txt"

// CATEGORY FUNCTIONS

void categorySupplierMenu() {
    int choice;

    do {
        printf("\n=== Category & Supplier Management Menu ===\n");
        printf("1. Add Category\n");
        printf("2. View Categories\n");
        printf("3. Update Category\n");
        printf("4. Delete Category\n");
        printf("5. Add Supplier\n");
        printf("6. View Suppliers\n");
        printf("7. Update Supplier\n");
        printf("8. Delete Supplier\n");
        printf("9. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addCategory();
                break;
            case 2:
                viewCategories();
                break;
            case 3:
                updateCategory();
                break;
            case 4:
                deleteCategory();
                break;
            case 5:
                addSupplier();
                break;
            case 6:
                viewSuppliers();
                break;
            case 7:
                updateSupplier();
                break;
            case 8:
                deleteSupplier();
                break;
            case 9:
                printf("Returning to Main Menu...\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 9.\n");
        }
    } while (choice != 9);
}


void addCategory() {
    Category c;
    printf("Category ID: ");
    scanf("%d", &c.catID); getchar();
    printf("Category Name: ");
    fgets(c.catName, sizeof(c.catName), stdin);
    c.catName[strcspn(c.catName, "\n")] = 0;

    char buffer[100];
    sprintf(buffer, "%d|%s", c.catID, c.catName);
    addDataToFile(CAT_FILE, buffer);
}

void viewCategories() {
    printf("\n--- Categories ---\n");
    readDataFromFile(CAT_FILE);
}

void updateCategory() {
    char id[10];
    printf("Category ID to update: ");
    scanf("%s", id); getchar();

    char name[50];
    printf("New Category Name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;

    char updatedLine[100];
    sprintf(updatedLine, "%s|%s", id, name);

    if (updateDataInFile(CAT_FILE, id, updatedLine))
        printf("Updated.\n");
    else
        printf("ID not found.\n");
}

void deleteCategory() {
    char id[10];
    printf("Category ID to delete: ");
    scanf("%s", id);

    if (deleteDataFromFile(CAT_FILE, id))
        printf("Deleted.\n");
    else
        printf("ID not found.\n");
}

// SUPPLIER FUNCTIONS
void addSupplier() {
    Supplier s;
    printf("Supplier ID: ");
    scanf("%d", &s.supID); getchar();
    printf("Name: ");
    fgets(s.supName, sizeof(s.supName), stdin);
    s.supName[strcspn(s.supName, "\n")] = 0;

    printf("Phone: ");
    fgets(s.phone, sizeof(s.phone), stdin);
    s.phone[strcspn(s.phone, "\n")] = 0;

    printf("Email: ");
    fgets(s.email, sizeof(s.email), stdin);
    s.email[strcspn(s.email, "\n")] = 0;

    char buffer[200];
    sprintf(buffer, "%d|%s|%s|%s", s.supID, s.supName, s.phone, s.email);
    addDataToFile(SUP_FILE, buffer);
}

void viewSuppliers() {
    printf("\n--- Suppliers ---\n");
    readDataFromFile(SUP_FILE);
}

void updateSupplier() {
    char id[10];
    printf("Supplier ID to update: ");
    scanf("%s", id); getchar();

    Supplier s;
    printf("New Name: ");
    fgets(s.supName, sizeof(s.supName), stdin);
    s.supName[strcspn(s.supName, "\n")] = 0;

    printf("New Phone: ");
    fgets(s.phone, sizeof(s.phone), stdin);
    s.phone[strcspn(s.phone, "\n")] = 0;

    printf("New Email: ");
    fgets(s.email, sizeof(s.email), stdin);
    s.email[strcspn(s.email, "\n")] = 0;

    char buffer[200];
    sprintf(buffer, "%s|%s|%s|%s", id, s.supName, s.phone, s.email);

    if (updateDataInFile(SUP_FILE, id, buffer))
        printf("Updated.\n");
    else
        printf("ID not found.\n");
}

void deleteSupplier() {
    char id[10];
    printf("Supplier ID to delete: ");
    scanf("%s", id);

    if (deleteDataFromFile(SUP_FILE, id))
        printf("Deleted.\n");
    else
        printf("ID not found.\n");
}
