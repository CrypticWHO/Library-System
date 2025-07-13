#ifndef SUPPLIER_H
#define SUPPLIER_H

typedef struct {
    int supID;
    char supName[50];
    char phone[20];
    char email[50];
} Supplier;

void addSupplier();
void viewSuppliers();
void updateSupplier();
void deleteSupplier();

#endif
