// Add a new product// product.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product.h"
#include "file_operations.h"  // Role 5 functions


void product_Menu()
{
 int choice;

    do {
        printf("\n===== Inventory Management System =====\n");
        printf("1. Add Product\n");
        printf("2. View Products\n");
        printf("3. Update Product\n");
        printf("4. Delete Product\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addProduct();
                break;
            case 2:
                viewProducts();
                break;
            case 3:
                updateProduct();
                break;
            case 4:
                deleteProduct();
                break;
            case 5:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 5.\n");
        }
    } while (choice != 5);
}

// Add a new product (uses pointer + dynamic memory)
void addProduct() {
    Product *p = (Product *)malloc(sizeof(Product)); // Using pointer

    if (!p) {
        printf("Memory allocation failed.\n");
        return;
    }

    char data[200];

    printf("Enter Product ID: ");
    while (scanf("%d", &p->id) != 1 || p->id <= 0) {
        printf("Invalid ID. Enter a positive integer: ");
        while (getchar() != '\n');
    }

    printf("Enter Product Name: ");
    getchar();
    fgets(p->name, NAME_LEN, stdin);
    strtok(p->name, "\n");
    while (strlen(p->name) == 0) {
        printf("Name cannot be empty. Enter again: ");
        fgets(p->name, NAME_LEN, stdin);
        strtok(p->name, "\n");
    }

    printf("Enter Category: ");
    fgets(p->category, CATEGORY_LEN, stdin);
    strtok(p->category, "\n");
    while (strlen(p->category) == 0) {
        printf("Category cannot be empty. Enter again: ");
        fgets(p->category, CATEGORY_LEN, stdin);
        strtok(p->category, "\n");
    }

    printf("Enter Quantity: ");
    while (scanf("%d", &p->quantity) != 1 || p->quantity < 0) {
        printf("Invalid quantity. Enter non-negative integer: ");
        while (getchar() != '\n');
    }

    printf("Enter Price: ");
    while (scanf("%f", &p->price) != 1 || p->price < 0) {
        printf("Invalid price. Enter non-negative value: ");
        while (getchar() != '\n');
    }

    snprintf(data, sizeof(data), "%d|%s|%s|%d|%.2f", p->id, p->name, p->category, p->quantity, p->price);

    if (addDataToFile("products.txt", data)) {
        printf("Product added successfully!\n");
    } else {
        printf("Failed to add product.\n");
    }

    free(p); // Clean up memory
}

// View all products using linked list
void viewProducts() {
    FILE *fp = fopen("products.txt", "r");
    if (!fp) {
        printf("No products found.\n");
        return;
    }

    Product *head = NULL, *tail = NULL;

    while (!feof(fp)) {
        Product *newNode = (Product *)malloc(sizeof(Product));
        if (fscanf(fp, "%d|%[^|]|%[^|]|%d|%f\n", &newNode->id, newNode->name, newNode->category, &newNode->quantity, &newNode->price) == 5) {
            newNode->next = NULL;
            if (!head)
                head = tail = newNode;
            else {
                tail->next = newNode;
                tail = newNode;
            }
        } else {
            free(newNode); // Skip incomplete
        }
    }
    fclose(fp);

    if (!head) {
        printf("No products to display.\n");
        return;
    }

    printf("\n--- Product List ---\n");
    Product *current = head;
    while (current) {
        displayProduct(current);
        current = current->next;
    }

    // Free memory
    current = head;
    while (current) {
        Product *temp = current;
        current = current->next;
        free(temp);
    }
}

// Update a product by ID
void updateProduct() {
    Product p;
    int id;
    char idStr[10], updatedData[200];

    printf("Enter Product ID to update: ");
    scanf("%d", &id);
    sprintf(idStr, "%d", id);

    printf("Enter new name: ");
    getchar(); fgets(p.name, NAME_LEN, stdin); strtok(p.name, "\n");

    printf("Enter new category: ");
    fgets(p.category, CATEGORY_LEN, stdin); strtok(p.category, "\n");

    printf("Enter new quantity: ");
    scanf("%d", &p.quantity);

    printf("Enter new price: ");
    scanf("%f", &p.price);

    snprintf(updatedData, sizeof(updatedData), "%d|%s|%s|%d|%.2f", id, p.name, p.category, p.quantity, p.price);

    if (updateDataInFile("products.txt", idStr, updatedData)) {
        printf("Product updated successfully.\n");
    } else {
        printf("Product not found.\n");
    }
}

// Delete a product by ID
void deleteProduct() {
    int id;
    char idStr[10];

    printf("Enter Product ID to delete: ");
    scanf("%d", &id);
    sprintf(idStr, "%d", id);

    if (deleteDataFromFile("products.txt", idStr)) {
        printf("Product deleted successfully.\n");
    } else {
        printf("Product not found.\n");
    }
}

// Display a single product
void displayProduct(const Product *p) {
    printf("ID: %d\nName: %s\nCategory: %s\nQuantity: %d\nPrice: RM%.2f\n\n",
           p->id, p->name, p->category, p->quantity, p->price);
}


//int main()
//{
//    void product_Menu();


//    return 0;
//}

