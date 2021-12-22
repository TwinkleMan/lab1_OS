#include <iostream>
#include <fileapi.h>
#include <windows.h>
#include "menu.h"

using namespace std;

int callback = 0;

OVERLAPPED* over1;
OVERLAPPED* over2;

VOID CALLBACK FileIOCompletionRoutine(DWORD dwErrorCode, DWORD dwNumberOfBytesTransfered, LPOVERLAPPED lpOverlapped) {

    callback++;

}

void copyFileOverlap() {
    system("CLS");

    int fileLength;
    char filePath[MAX_PATH];
    char destination[MAX_PATH];
    HANDLE fileHandle, destinationHandle;
    int key = 1;

    int completedOperations = 0;
    int startSize = 0;

    int sizeOfBlock = 4;
    int numberOfOperations = 2;
    cout << "Enter size of the copied block (will be multiplied by 4096)"<< endl;
    cin >> sizeOfBlock;
    sizeOfBlock *= 4096;
    cout << "Enter number of operations\n1  2  4  8  12  16"<< endl;
    cin >> numberOfOperations;

    OVERLAPPED* over1 = new OVERLAPPED[numberOfOperations];
    OVERLAPPED* over2 = new OVERLAPPED[numberOfOperations];

    DWORD startTime,endTime = 0;

    for (int i = 0; i < numberOfOperations; i++)
    {

        over1[i].Offset = 0;
        over1[i].OffsetHigh = 0;
        over1[i].hEvent = NULL;

        over2[i].Offset = 0;
        over2[i].OffsetHigh = 0;
        over2[i].hEvent = NULL;

    }

    cout << "Enter path to the file, including the file name, "
            "extension & using backslashes\n(Example: C:\\Users\\test.txt):"<< endl;
    cin >> filePath;
    fileHandle = CreateFile(filePath,GENERIC_READ,0,NULL,OPEN_EXISTING, FILE_FLAG_NO_BUFFERING | FILE_FLAG_OVERLAPPED,NULL);
    if (fileHandle != INVALID_HANDLE_VALUE) {

        cout << "Enter destination path, including the file name, "
                "extension & using backslashes\n(Example: C:\\Users\\test.txt):" << endl;
        cin >> destination;
        destinationHandle = CreateFile(destination, GENERIC_READ | GENERIC_WRITE, 0, NULL,CREATE_ALWAYS, FILE_FLAG_NO_BUFFERING | FILE_FLAG_OVERLAPPED, NULL);
        if (destinationHandle != INVALID_HANDLE_VALUE) {

            cout << "Looks fine, starting copy..." << endl;

            //time measure
            startTime = GetTickCount();

            fileLength = GetFileSize(fileHandle,NULL);
            startSize = fileLength;

            CHAR* buff1 = new CHAR[fileLength + (fileLength % sizeOfBlock > 0 ? 1 : 0) * sizeOfBlock];
            CHAR* buff2 = new CHAR[fileLength + (fileLength % sizeOfBlock > 0 ? 1 : 0) * sizeOfBlock];
            buff2 = buff1;

            int readFlag = 0, writeFlag = 0;

            do {

                callback = 0;
                completedOperations = 0;

                for (int i = 0; i < numberOfOperations; i++)
                {
                    if (fileLength > 0)
                    {
                        completedOperations++;
                        if (i || readFlag)
                        {
                            for (int j = 0; j < numberOfOperations; j++) over1[j].Offset += sizeOfBlock;
                            buff1 += sizeOfBlock;
                        }
                        readFlag = 1;
                        ReadFileEx(fileHandle, buff1, sizeOfBlock, &over1[i], (LPOVERLAPPED_COMPLETION_ROUTINE)FileIOCompletionRoutine);
                        fileLength -= sizeOfBlock;
                    }

                }

                while (callback < completedOperations)
                    SleepEx(-1, TRUE);

                callback = 0;

                for (int i = 0; i < completedOperations; i++)
                {
                    if (i || writeFlag)
                    {
                        for (int j = 0; j < numberOfOperations; j++)
                            over2[j].Offset += sizeOfBlock;

                        buff2 += sizeOfBlock;
                    }
                    writeFlag = 1;
                    WriteFileEx(destinationHandle, buff2, sizeOfBlock, &over2[i], (LPOVERLAPPED_COMPLETION_ROUTINE)FileIOCompletionRoutine);
                }

                while (callback < completedOperations)
                    SleepEx(-1, TRUE);

            } while (fileLength > 0);

            //time measure
            endTime = GetTickCount();

        } else cout << "Something went wrong at destination file opening! Error: " << GetLastError();
    } else cout << "Something went wrong at base file opening! Error: " << GetLastError();

    SetFilePointer(destinationHandle, startSize, NULL, FILE_BEGIN);
    SetEndOfFile(destinationHandle);

    if (endTime != 0) cout << "\n\nCopy time: " << endTime - startTime << endl;

    cout << "\n0)Exit" << endl;
    cin >> key;
    if (fileHandle != INVALID_HANDLE_VALUE) CloseHandle(fileHandle);
    if (destinationHandle != INVALID_HANDLE_VALUE) CloseHandle(destinationHandle);

    delete[] over1, over2;

    system("CLS");
}

menuItem taskTwoMenu[] {
        {1,"Copy file with overlapping", copyFileOverlap},
        {0,"Exit"}
};
static const unsigned int taskTwoMenuSize = sizeof(taskTwoMenu) / sizeof(taskTwoMenu[0]);

void openSecondTask() {
    system("CLS");
    MenuEngine(&taskTwoMenu[0],taskTwoMenuSize);
    system("CLS");
}
