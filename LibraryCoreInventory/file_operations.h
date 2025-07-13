#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

void fileOperationsMenu();
int addDataToFile(const char *filename, const char *data);
int readDataFromFile(const char *filename);
int updateDataInFile(const char *filename, const char *id, const char *newData);
int deleteDataFromFile(const char *filename, const char *id);

#endif
