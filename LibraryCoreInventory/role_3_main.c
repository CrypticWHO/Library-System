#include <stdio.h>
#include "role_3_category.h"
#include "role_3_supplier.h"

int main() {
    int choice;

    while (1) {
        printf("\n--- Menu ---\n");
        printf("1. Category\n");
        printf("2. Supplier\n");
        printf("3. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            int ch;
            while (1) {
                printf("\n--- Category ---\n");
                printf("1. Add\n2. View\n3. Update\n4. Delete\n5. Back\nChoice: ");
                scanf("%d", &ch);
                if (ch == 1) addCategory();
                else if (ch == 2) viewCategories();
                else if (ch == 3) updateCategory();
                else if (ch == 4) deleteCategory();
                else break;
            }
        }
        else if (choice == 2) {
            int ch;
            while (1) {
                printf("\n--- Supplier ---\n");
                printf("1. Add\n2. View\n3. Update\n4. Delete\n5. Back\nChoice: ");
                scanf("%d", &ch);
                if (ch == 1) addSupplier();
                else if (ch == 2) viewSuppliers();
                else if (ch == 3) updateSupplier();
                else if (ch == 4) deleteSupplier();
                else break;
            }
        }
        else {
            break;
        }
    }

    return 0;
}
