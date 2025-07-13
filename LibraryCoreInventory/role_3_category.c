#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "role_3_category.h"

#define CAT_FILE "categories.txt"

void addCategory() {
    FILE *f = fopen(CAT_FILE, "a");
    if (f == NULL) {
        printf("File error.\n");
        return;
    }

    Category c;
    printf("Category ID: ");
    scanf("%d", &c.catID);
    getchar();
    printf("Category Name: ");
    fgets(c.catName, sizeof(c.catName), stdin);
    c.catName[strcspn(c.catName, "\n")] = '\0';

    fprintf(f, "%d|%s\n", c.catID, c.catName);
    fclose(f);
    printf("Added.\n");
}

void viewCategories() {
    FILE *f = fopen(CAT_FILE, "r");
    if (f == NULL) {
        printf("No data.\n");
        return;
    }

    Category c;
    printf("\n--- Categories ---\n");
    while (fscanf(f, "%d|%[^\n]\n", &c.catID, c.catName) == 2) {
        printf("ID: %d | Name: %s\n", c.catID, c.catName);
    }

    fclose(f);
}

void updateCategory() {
    int id, found = 0;
    Category c;
    FILE *f = fopen(CAT_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (f == NULL || temp == NULL) return;

    printf("Category ID to update: ");
    scanf("%d", &id);
    getchar();

    while (fscanf(f, "%d|%[^\n]\n", &c.catID, c.catName) == 2) {
        if (c.catID == id) {
            found = 1;
            printf("New Name: ");
            fgets(c.catName, sizeof(c.catName), stdin);
            c.catName[strcspn(c.catName, "\n")] = '\0';
        }
        fprintf(temp, "%d|%s\n", c.catID, c.catName);
    }

    fclose(f);
    fclose(temp);
    remove(CAT_FILE);
    rename("temp.txt", CAT_FILE);

    if (found) printf("Updated.\n");
    else printf("ID not found.\n");
}

void deleteCategory() {
    int id, found = 0;
    Category c;
    FILE *f = fopen(CAT_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (f == NULL || temp == NULL) return;

    printf("Category ID to delete: ");
    scanf("%d", &id);

    while (fscanf(f, "%d|%[^\n]\n", &c.catID, c.catName) == 2) {
        if (c.catID != id)
            fprintf(temp, "%d|%s\n", c.catID, c.catName);
        else
            found = 1;
    }

    fclose(f);
    fclose(temp);
    remove(CAT_FILE);
    rename("temp.txt", CAT_FILE);

    if (found) printf("Deleted.\n");
    else printf("ID not found.\n");
}
