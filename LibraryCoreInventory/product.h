// product.h
#ifndef PRODUCT_H
#define PRODUCT_H

#define NAME_LEN 50
#define CATEGORY_LEN 30

typedef struct Product {
    int id;
    char name[NAME_LEN];
    char category[CATEGORY_LEN];
    int quantity;
    float price;
    struct Product *next; // Linked list pointer
} Product;

// Function declarations
void product_Menu();
void addProduct();
void viewProducts();
void updateProduct();
void deleteProduct();
void displayProduct(const Product *p);

#endif
