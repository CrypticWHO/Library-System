#include "user_transaction.h"
#include "file_operations.h"  // Role 5

// Auto-create file if missing
void ensure_file_exists(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        file = fopen(filename, "w");
        if (file) {
            printf("Created missing file: %s\n", filename);
            fclose(file);
        } else {
            printf("Failed to create file: %s\n", filename);
        }
    } else {
        fclose(file);
    }
}

// Load users
void load_users(User** head) {
    ensure_file_exists(USERS_FILE);

    FILE* file = fopen(USERS_FILE, "r");
    if (!file) return;

    User* tail = NULL;
    char line[MAX_LINE];

    while (fgets(line, sizeof(line), file)) {
        User new_user;
        int matches = sscanf(line, "User ID: %d\nUsername: %s\nEmail: %s\nType: %s\n\n",
                             &new_user.userID,
                             new_user.username,
                             new_user.userEmail,
                             new_user.userType);

        if (matches == 4) {
            User* node = (User*)malloc(sizeof(User));
            *node = new_user;
            node->next = NULL;

            if (!*head) {
                *head = node;
                tail = node;
            } else {
                tail->next = node;
                tail = node;
            }
        }
    }
    fclose(file);
}

// Save users (Role 5)
void save_users(User* head) {
    FILE* file = fopen(USERS_FILE, "w");
    if (!file) return;
    fclose(file);

    User* current = head;
    while (current) {
        char buffer[256];
        snprintf(buffer, sizeof(buffer),
                 "User ID: %d\nUsername: %s\nEmail: %s\nType: %s\n",
                 current->userID, current->username, current->userEmail, current->userType);
        addDataToFile(USERS_FILE, buffer);
        addDataToFile(USERS_FILE, "");
        current = current->next;
    }
}

// Load transactions
void load_transactions(Transaction** head) {
    ensure_file_exists(TRANSACTIONS_FILE);

    FILE* file = fopen(TRANSACTIONS_FILE, "r");
    if (!file) return;

    Transaction* tail = NULL;
    char line[MAX_LINE];

    while (fgets(line, sizeof(line), file)) {
        Transaction new_trans;
        int matches = sscanf(line, "Transaction ID: %d\nUser ID: %d\nItem ID: %d\nItem Type: %s\nStatus: %s\n\n",
                             &new_trans.transactionID,
                             &new_trans.userID,
                             &new_trans.itemID,
                             new_trans.itemType,
                             new_trans.status);

        if (matches == 5) {
            Transaction* node = (Transaction*)malloc(sizeof(Transaction));
            *node = new_trans;
            node->next = NULL;

            if (!*head) {
                *head = node;
                tail = node;
            } else {
                tail->next = node;
                tail = node;
            }
        }
    }
    fclose(file);
}

// Save transactions (Role 5)
void save_transactions(Transaction* head) {
    FILE* file = fopen(TRANSACTIONS_FILE, "w");
    if (!file) return;
    fclose(file);

    Transaction* current = head;
    while (current) {
        char buffer[256];
        snprintf(buffer, sizeof(buffer),
                 "Transaction ID: %d\nUser ID: %d\nItem ID: %d\nItem Type: %s\nStatus: %s\n",
                 current->transactionID, current->userID, current->itemID,
                 current->itemType, current->status);
        addDataToFile(TRANSACTIONS_FILE, buffer);
        addDataToFile(TRANSACTIONS_FILE, "");
        current = current->next;
    }
}

// Remaining user/transaction functions unchanged:
void add_user(User** head) {
    User* new_user = (User*)malloc(sizeof(User));
    printf("Enter user ID: ");
    scanf("%d", &new_user->userID);

    User* current = *head;
    while (current) {
        if (current->userID == new_user->userID) {
            printf("User ID exists!\n");
            free(new_user);
            return;
        }
        current = current->next;
    }

    printf("Enter username: ");
    scanf("%s", new_user->username);
    printf("Enter email: ");
    scanf("%s", new_user->userEmail);
    printf("Enter user type: ");
    scanf("%s", new_user->userType);

    if (strcmp(new_user->userType, "admin") && strcmp(new_user->userType, "staff") && strcmp(new_user->userType, "customer")) {
        strcpy(new_user->userType, "customer");
    }

    new_user->next = *head;
    *head = new_user;
    save_users(*head);
    printf("User added.\n");
}

void view_users(User* head) {
    if (!head) {
        printf("No users.\n");
        return;
    }
    while (head) {
        printf("ID: %d\nName: %s\nEmail: %s\nType: %s\n\n",
               head->userID, head->username, head->userEmail, head->userType);
        head = head->next;
    }
}

void delete_user(User** head) {
    int id;
    printf("Enter user ID to delete: ");
    scanf("%d", &id);

    User *prev = NULL, *curr = *head;
    while (curr && curr->userID != id) {
        prev = curr;
        curr = curr->next;
    }

    if (!curr) {
        printf("User not found.\n");
        return;
    }

    if (!prev) *head = curr->next;
    else prev->next = curr->next;

    free(curr);
    char idStr[10]; sprintf(idStr, "%d", id);
    deleteDataFromFile(USERS_FILE, idStr);
    save_users(*head);
    printf("User deleted.\n");
}

void update_user(User* head) {
    int id;
    printf("Enter user ID to update: ");
    scanf("%d", &id);

    while (head && head->userID != id) head = head->next;

    if (!head) {
        printf("User not found.\n");
        return;
    }

    char name[MAX_NAME], email[MAX_EMAIL], type[MAX_TYPE];
    printf("New username (- to skip): ");
    scanf("%s", name);
    if (strcmp(name, "-")) strcpy(head->username, name);

    printf("New email (- to skip): ");
    scanf("%s", email);
    if (strcmp(email, "-")) strcpy(head->userEmail, email);

    printf("New type (- to skip): ");
    scanf("%s", type);
    if (strcmp(type, "-") == 0 || (strcmp(type, "admin") && strcmp(type, "staff") && strcmp(type, "customer"))) {
        printf("Invalid. Keeping old.\n");
    } else {
        strcpy(head->userType, type);
    }

    save_users(head);
    printf("User updated.\n");
}

void add_transaction(Transaction** head) {
    Transaction* new_trans = (Transaction*)malloc(sizeof(Transaction));
    printf("Enter transaction ID: ");
    scanf("%d", &new_trans->transactionID);

    Transaction* current = *head;
    while (current) {
        if (current->transactionID == new_trans->transactionID) {
            printf("ID exists!\n");
            free(new_trans);
            return;
        }
        current = current->next;
    }

    printf("User ID: ");
    scanf("%d", &new_trans->userID);
    printf("Item ID: ");
    scanf("%d", &new_trans->itemID);
    printf("Item Type: ");
    scanf("%s", new_trans->itemType);
    strcpy(new_trans->status, "pending");

    new_trans->next = *head;
    *head = new_trans;
    save_transactions(*head);
    printf("Transaction added.\n");
}

void view_transactions(Transaction* head) {
    if (!head) {
        printf("No transactions.\n");
        return;
    }
    while (head) {
        printf("Trans ID: %d\nUser ID: %d\nItem ID: %d\nItem Type: %s\nStatus: %s\n\n",
               head->transactionID, head->userID, head->itemID,
               head->itemType, head->status);
        head = head->next;
    }
}

void update_transaction(Transaction* head) {
    int id;
    printf("Enter transaction ID: ");
    scanf("%d", &id);

    while (head && head->transactionID != id) head = head->next;
    if (!head) {
        printf("Not found.\n");
        return;
    }

    printf("New status (completed/pending/cancelled): ");
    scanf("%s", head->status);
    save_transactions(head);
    printf("Transaction updated.\n");
}

void delete_transaction(Transaction** head) {
    int id;
    printf("Enter transaction ID to delete: ");
    scanf("%d", &id);

    Transaction *prev = NULL, *curr = *head;
    while (curr && curr->transactionID != id) {
        prev = curr;
        curr = curr->next;
    }

    if (!curr) {
        printf("Not found.\n");
        return;
    }

    if (!prev) *head = curr->next;
    else prev->next = curr->next;

    free(curr);
    char idStr[10]; sprintf(idStr, "%d", id);
    deleteDataFromFile(TRANSACTIONS_FILE, idStr);
    save_transactions(*head);
    printf("Deleted.\n");
}

void free_users(User* head) {
    while (head) {
        User* temp = head;
        head = head->next;
        free(temp);
    }
}

void free_transactions(Transaction* head) {
    while (head) {
        Transaction* temp = head;
        head = head->next;
        free(temp);
    }
}

void user_transaction_menu() {
    User* users = NULL;
    Transaction* transactions = NULL;

    load_users(&users);
    load_transactions(&transactions);

    int choice;
    do {
        printf("\n=== User & Transaction Management ===\n");
        printf("1. User Management\n");
        printf("2. Transaction Management\n");
        printf("3. Exit\nYour choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            int ch;
            do {
                printf("\n--- User ---\n1. Add\n2. View\n3. Update\n4. Delete\n5. Back\nChoice: ");
                scanf("%d", &ch);
                switch (ch) {
                    case 1: add_user(&users); break;
                    case 2: view_users(users); break;
                    case 3: update_user(users); break;
                    case 4: delete_user(&users); break;
                }
            } while (ch != 5);
        } else if (choice == 2) {
            int ch;
            do {
                printf("\n--- Transaction ---\n1. Add\n2. View\n3. Update\n4. Delete\n5. Back\nChoice: ");
                scanf("%d", &ch);
                switch (ch) {
                    case 1: add_transaction(&transactions); break;
                    case 2: view_transactions(transactions); break;
                    case 3: update_transaction(transactions); break;
                    case 4: delete_transaction(&transactions); break;
                }
            } while (ch != 5);
        }
    } while (choice != 3);

    save_users(users);
    save_transactions(transactions);
    free_users(users);
    free_transactions(transactions);
}
