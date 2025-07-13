#include "product.h"
#include "library_inventory.h"
#include "category_and_supplier.h"
#include "user_transaction.h"
#include "file_operations.h"

int main()
{
    int choice;

    do {
        printf("\n===== Library Inventory System =====\n");
        printf("1. Product Management (Role 1)\n");
        printf("2. Inventory & Stock (Role 2)\n");
        printf("3. Category & Suppliers (Role 3)\n");
        printf("4. Users & Transactions (Role 4)\n");
        printf("5. File Operations & Reports (Role 5)\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Call your submenu or product management options
                product_Menu();
                break;
            case 2:
                printf("Inventory Module (Role 2)");
                inventoryMenu();
                break;
            case 3:
                printf("Category/Supplier Module (Role 3)\n");
                categorySupplierMenu();
                break;
            case 4:
                printf("User/Transaction Module (Role 4)\n");
                user_transaction_menu();
                break;
            case 5:
                printf("File & Reports Module (Role 5)\n");
                fileOperationsMenu();
                break;
            case 6:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}
