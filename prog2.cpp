#include <iostream>
#include <fileapi.h>
#include <windows.h>
#include "menu.h"

using namespace std;

void copyFileSecond() {
    system("CLS");

    DWORD readCounter, writeCounter,fileLength;
    char filePath[MAX_PATH];
    char destination[MAX_PATH];
    HANDLE fileHandle, destinationHandle;
    int key = 1;

    cout << "Enter path to the file, including the file name, "
            "extension & using backslashes\n(Example: C:\\Users\\test.txt):"<< endl;
    cin >> filePath;
    fileHandle = CreateFile(filePath,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
    if (fileHandle != INVALID_HANDLE_VALUE) {

        cout << "Enter destination path, including the file name, "
                "extension & using backslashes\n(Example: C:\\Users\\test.txt):" << endl;
        cin >> destination;
        destinationHandle = CreateFile(destination, GENERIC_READ | GENERIC_WRITE, 0, NULL,CREATE_NEW,FILE_ATTRIBUTE_NORMAL, NULL);
        if (destinationHandle != INVALID_HANDLE_VALUE) {
            fileLength = GetFileSize(fileHandle,NULL);
            char lpBuffer[fileLength];
            if (ReadFile(fileHandle, &lpBuffer, fileLength, &readCounter, NULL)) {
                cout << "Data read!" << endl;
                if (WriteFile(destinationHandle, &lpBuffer, readCounter,&writeCounter,NULL)) {
                    cout << "Success!" << endl;
                } else cout << "Something went wrong at data copying! Error: " << GetLastError();
            } else cout << "Something went wrong at data reading! Error: " << GetLastError();
        } else cout << "Something went wrong at destination file opening! Error: " << GetLastError();
    } else cout << "Something went wrong at base file opening! Error: " << GetLastError();

    cout << "\n0)Exit" << endl;
    cin >> key;
    if (fileHandle != INVALID_HANDLE_VALUE) CloseHandle(fileHandle);
    if (destinationHandle != INVALID_HANDLE_VALUE) CloseHandle(destinationHandle);

    system("CLS");
}

void copyFileOverlap() {
    system("CLS");

    DWORD readCounter, writeCounter,fileLength;
    char filePath[MAX_PATH];
    char destination[MAX_PATH];
    HANDLE fileHandle, destinationHandle;
    int key = 1;

    int sizeOfBlock = 4;
    int numberOfOperations = 2;
    cout << "Enter size of the copied block"<< endl;
    cin >> sizeOfBlock;
    cout << "Enter number of operations\n1  2  4  8  12  16"<< endl;
    cin >> numberOfOperations;

    cout << "Enter path to the file, including the file name, "
            "extension & using backslashes\n(Example: C:\\Users\\test.txt):"<< endl;
    cin >> filePath;
    fileHandle = CreateFile(filePath,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL | FILE_FLAG_NO_BUFFERING | FILE_FLAG_OVERLAPPED,NULL);
    if (fileHandle != INVALID_HANDLE_VALUE) {

        cout << "Enter destination path, including the file name, "
                "extension & using backslashes\n(Example: C:\\Users\\test.txt):" << endl;
        cin >> destination;
        destinationHandle = CreateFile(destination, GENERIC_READ | GENERIC_WRITE, 0, NULL,CREATE_NEW,
                                       FILE_ATTRIBUTE_NORMAL | FILE_FLAG_NO_BUFFERING | FILE_FLAG_OVERLAPPED, NULL);
        if (destinationHandle != INVALID_HANDLE_VALUE) {
            fileLength = GetFileSize(fileHandle,NULL);
            char lpBuffer[fileLength];
            if (ReadFile(fileHandle, &lpBuffer, fileLength, &readCounter, NULL)) {
                cout << "Data read!" << endl;
                if (WriteFile(destinationHandle, &lpBuffer, readCounter,&writeCounter,NULL)) {
                    cout << "Success!" << endl;
                } else cout << "Something went wrong at data copying! Error: " << GetLastError();
            } else cout << "Something went wrong at data reading! Error: " << GetLastError();
        } else cout << "Something went wrong at destination file opening! Error: " << GetLastError();
    } else cout << "Something went wrong at base file opening! Error: " << GetLastError();

    cout << "\n0)Exit" << endl;
    cin >> key;
    if (fileHandle != INVALID_HANDLE_VALUE) CloseHandle(fileHandle);
    if (destinationHandle != INVALID_HANDLE_VALUE) CloseHandle(destinationHandle);

    system("CLS");
}

void moveFileSecond() {
    system("CLS");
    //code
    system("CLS");
}

menuItem taskTwoMenu[] {
        {1,"Copy file", copyFileSecond},
        {2,"Copy file with overlapping", copyFileOverlap},
        {3,"Move file", moveFileSecond},
        {0,"Exit"}
};
static const unsigned int taskTwoMenuSize = sizeof(taskTwoMenu) / sizeof(taskTwoMenu[0]);

void openSecondTask() {
    system("CLS");
    MenuEngine(&taskTwoMenu[0],taskTwoMenuSize);
    system("CLS");
}
