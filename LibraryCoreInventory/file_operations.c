#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_operations.h"


void fileOperationsMenu() {
    int choice;
    char filename[100] = "inventory.txt";

    do {
        printf("\n=== Advanced File Operations ===\n");
        printf("1. Add Record to File\n");
        printf("2. Read File\n");
        printf("3. Update Record by ID\n");
        printf("4. Delete Record by ID\n");
        printf("5. Exit to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // clear input buffer

        switch (choice) {
            case 1: {
                char data[256];
                printf("Enter new record (e.g., 101|Book Title|5):\n");
                fgets(data, sizeof(data), stdin);
                data[strcspn(data, "\n")] = '\0'; // remove newline
                if (addDataToFile(filename, data))
                    printf("Data added successfully.\n");
                else
                    printf("Failed to add data.\n");
                break;
            }

            case 2: {
                printf("\nContents of '%s':\n", filename);
                readDataFromFile(filename);
                break;
            }

            case 3: {
                char id[10], newData[256];
                printf("Enter ID to update: ");
                fgets(id, sizeof(id), stdin);
                id[strcspn(id, "\n")] = '\0'; // remove newline

                printf("Enter new full record (same format):\n");
                fgets(newData, sizeof(newData), stdin);
                newData[strcspn(newData, "\n")] = '\0';

                if (updateDataInFile(filename, id, newData))
                    printf("Record updated successfully.\n");
                else
                    printf("Record not found.\n");
                break;
            }

            case 4: {
                char id[10];
                printf("Enter ID to delete: ");
                fgets(id, sizeof(id), stdin);
                id[strcspn(id, "\n")] = '\0';

                if (deleteDataFromFile(filename, id))
                    printf("Record deleted successfully.\n");
                else
                    printf("Record not found.\n");
                break;
            }

            case 5:
                printf("Returning to Main Menu...\n");
                break;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 5);
}



int addDataToFile(const char *filename, const char *data) {
    FILE *fp = fopen(filename, "a");
    if (!fp) {
        perror("File open failed");
        return 0;
    }
    fprintf(fp, "%s\n", data);
    fclose(fp);
    return 1;
}

int readDataFromFile(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("File open failed");
        return 0;
    }

    char line[1024];
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }

    fclose(fp);
    return 1;
}

int updateDataInFile(const char *filename, const char *id, const char *newData) {
    FILE *fp = fopen(filename, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!fp || !temp) {
        perror("File open failed");
        if (fp) fclose(fp);
        if (temp) fclose(temp);
        return 0;
    }

    char line[1024];
    int found = 0;
    while (fgets(line, sizeof(line), fp)) {
        char tempLine[1024];
        strcpy(tempLine, line);
        char *token = strtok(tempLine, "|");
        if (token && strcmp(token, id) == 0) {
            fprintf(temp, "%s\n", newData);
            found = 1;
        } else {
            fputs(line, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    if (remove(filename) != 0 || rename("temp.txt", filename) != 0) {
        perror("File replace failed");
        return 0;
    }

    return found;
}

int deleteDataFromFile(const char *filename, const char *id) {
    FILE *fp = fopen(filename, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!fp || !temp) {
        perror("File open failed");
        if (fp) fclose(fp);
        if (temp) fclose(temp);
        return 0;
    }

    char line[1024];
    int found = 0;
    while (fgets(line, sizeof(line), fp)) {
        char tempLine[1024];
        strcpy(tempLine, line);
        char *token = strtok(tempLine, "|");
        if (token && strcmp(token, id) == 0) {
            found = 1;
        } else {
            fputs(line, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    if (remove(filename) != 0 || rename("temp.txt", filename) != 0) {
        perror("File replace failed");
        return 0;
    }

    return found;
}
