
#ifndef INVENTORY_H
#define INVENTORY_H

typedef struct {
    int catID;
    char catName[50];
} Category;

typedef struct {
    int supID;
    char supName[50];
    char phone[20];
    char email[50];
} Supplier;

void categorySupplierMenu();
void addCategory();
void viewCategories();
void updateCategory();
void deleteCategory();
void addSupplier();
void viewSuppliers();
void updateSupplier();
void deleteSupplier();

#endif
