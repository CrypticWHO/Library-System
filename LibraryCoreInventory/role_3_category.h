#ifndef CATEGORY_H
#define CATEGORY_H

typedef struct {
    int catID;
    char catName[50];
} Category;

void addCategory();
void viewCategories();
void updateCategory();
void deleteCategory();

#endif
