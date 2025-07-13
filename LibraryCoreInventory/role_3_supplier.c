#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "role_3_category.h"

#define SUP_FILE "suppliers.txt"

void addSupplier() {
    FILE *f = fopen(SUP_FILE, "a");
    if (f == NULL) {
        printf("File error.\n");
        return;
    }

    Supplier s;
    printf("Supplier ID: ");
    scanf("%d", &s.supID);
    getchar();
    printf("Name: ");
    fgets(s.supName, sizeof(s.supName), stdin);
    s.supName[strcspn(s.supName, "\n")] = '\0';

    printf("Phone: ");
    fgets(s.phone, sizeof(s.phone), stdin);
    s.phone[strcspn(s.phone, "\n")] = '\0';

    printf("Email: ");
    fgets(s.email, sizeof(s.email), stdin);
    s.email[strcspn(s.email, "\n")] = '\0';

    fprintf(f, "%d|%s|%s|%s\n", s.supID, s.supName, s.phone, s.email);
    fclose(f);
    printf("Added.\n");
}

void viewSuppliers() {
    FILE *f = fopen(SUP_FILE, "r");
    if (f == NULL) {
        printf("No data.\n");
        return;
    }

    Supplier s;
    printf("\n--- Suppliers ---\n");
    while (fscanf(f, "%d|%[^|]|%[^|]|%[^\n]\n", &s.supID, s.supName, s.phone, s.email) == 4) {
        printf("ID: %d | Name: %s | Phone: %s | Email: %s\n", s.supID, s.supName, s.phone, s.email);
    }

    fclose(f);
}

void updateSupplier() {
    int id, found = 0;
    Supplier s;
    FILE *f = fopen(SUP_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (f == NULL || temp == NULL) return;

    printf("Supplier ID to update: ");
    scanf("%d", &id);
    getchar();

    while (fscanf(f, "%d|%[^|]|%[^|]|%[^\n]\n", &s.supID, s.supName, s.phone, s.email) == 4) {
        if (s.supID == id) {
            found = 1;
            printf("New Name: ");
            fgets(s.supName, sizeof(s.supName), stdin);
            s.supName[strcspn(s.supName, "\n")] = '\0';

            printf("New Phone: ");
            fgets(s.phone, sizeof(s.phone), stdin);
            s.phone[strcspn(s.phone, "\n")] = '\0';

            printf("New Email: ");
            fgets(s.email, sizeof(s.email), stdin);
            s.email[strcspn(s.email, "\n")] = '\0';
        }
        fprintf(temp, "%d|%s|%s|%s\n", s.supID, s.supName, s.phone, s.email);
    }

    fclose(f);
    fclose(temp);
    remove(SUP_FILE);
    rename("temp.txt", SUP_FILE);

    if (found) printf("Updated.\n");
    else printf("ID not found.\n");
}

void deleteSupplier() {
    int id, found = 0;
    Supplier s;
    FILE *f = fopen(SUP_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (f == NULL || temp == NULL) return;

    printf("Supplier ID to delete: ");
    scanf("%d", &id);

    while (fscanf(f, "%d|%[^|]|%[^|]|%[^\n]\n", &s.supID, s.supName, s.phone, s.email) == 4) {
        if (s.supID != id)
            fprintf(temp, "%d|%s|%s|%s\n", s.supID, s.supName, s.phone, s.email);
        else
            found = 1;
    }

    fclose(f);
    fclose(temp);
    remove(SUP_FILE);
    rename("temp.txt", SUP_FILE);

    if (found) printf("Deleted.\n");
    else printf("ID not found.\n");
}
