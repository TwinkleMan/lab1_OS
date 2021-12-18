#ifndef OS_LAB1_PROG1_H
#define OS_LAB1_PROG1_H

#include "menu.h"

void getDiskList();
void getDiskInfoSpace();
//void createDirectory(LPCSTR path);
//void deleteDirectory(LPCSTR path);
void directoryOperations();
void createFile();
//void copyFile(char* existingFilePath, char* newFilePath);
//void moveFile(char* existingFilePath, char* newFilePath);
//void moveFileProtected(char* existingFilePath, char* newFilePath);
void copyMoveFile();
void fileAttributes();
void decodeAttributes(DWORD attributes);
void openFirstTask();


#endif //OS_LAB1_PROG1_H
