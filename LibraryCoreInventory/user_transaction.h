#ifndef USER_TRANSACTION_H
#define USER_TRANSACTION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Symbolic constants
#define MAX_NAME 50
#define MAX_EMAIL 100
#define MAX_TYPE 20
#define MAX_STATUS 20
#define MAX_LINE 256
#define USERS_FILE "users.txt"
#define TRANSACTIONS_FILE "transactions.txt"

// User structure
typedef struct User {
    int userID;
    char username[MAX_NAME];
    char userEmail[MAX_EMAIL];
    char userType[MAX_TYPE];
    struct User* next;
} User;

// Transaction structure
typedef struct Transaction {
    int transactionID;
    int userID;
    int itemID;
    char itemType[MAX_TYPE];
    char status[MAX_STATUS];
    struct Transaction* next;
} Transaction;

// Function prototypes
void user_transaction_menu();
void load_users(User** head);
void save_users(User* head);
void load_transactions(Transaction** head);
void save_transactions(Transaction* head);
void add_user(User** head);
void view_users(User* head);
void update_user(User* head);
void delete_user(User** head);
void add_transaction(Transaction** head);
void view_transactions(Transaction* head);
void update_transaction(Transaction* head);
void delete_transaction(Transaction** head);
void free_users(User* head);
void free_transactions(Transaction* head);

#endif // USER_TRANSACTION_H
