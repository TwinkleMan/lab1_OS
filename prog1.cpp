#include <iostream>
#include <windows.h>
#include <cstdio>
#include <fileapi.h>
#include <tchar.h>

#include "prog1.h"
using namespace std;

void getDiskList() {

    TCHAR myDrives[] = _T(" A:");
    DWORD myLogicalDrives;

    DWORD dwResult;
    DWORD dwSize = MAX_PATH;
    char szLogicalDrives[MAX_PATH] = {0};

    int key;

    do {
        system("CLS");
        myLogicalDrives = GetLogicalDrives();

        cout << "In bit: ";
        for (int i = sizeof(myLogicalDrives); i >= 0; --i) {
            printf("%d", myLogicalDrives & (1 << i) ? 1 : 0);
        }
        cout << endl;

        if (myLogicalDrives == 0) {
            cout << "Error getting drives!";
        } else {
            wprintf(L"This machine has the following logical drives:\n");
            while (myLogicalDrives) {
                if (myLogicalDrives & 1) {
                    // Printing out the available drives
                    wprintf(L"drive %s\n", myDrives);
                }
                // increment counter for the next available drive.
                myDrives[1]++;
                // shift the bitmask binary right
                myLogicalDrives >>= 1;
            }
        }

        cout << "\n------GetLogicalDriveStrings------\n";
        dwResult = GetLogicalDriveStrings(dwSize, szLogicalDrives);
        if (dwResult > 0 && dwResult <= MAX_PATH) {
            char *szSingleDrive = szLogicalDrives;
            printf("GetLogicalDriveStrings() return value: %d, Error (if any): %d \n", dwResult, GetLastError());
            printf("The logical drives of this machine are:\n");
            while (*szSingleDrive) {
                printf("Drive: %s\n", szSingleDrive);

                // get the next drive
                szSingleDrive += strlen(szSingleDrive) + 1;
            }
        } else
            printf("GetLogicalDriveStrings() is failed lor!!! Error code: %d\n", GetLastError());

        cout << "\n0)Exit" << endl;
        cin >> key;
    } while (key != 0);
    system("CLS");
}

void getDiskInfoSpace() {

    DWORD dwResult;
    DWORD dwSize = MAX_PATH;
    char szLogicalDrives[MAX_PATH] = {0};

    int key = 1;

    char* szSingleDrive = szLogicalDrives;

    do {
        system("CLS");
        dwResult = GetLogicalDriveStrings(dwSize, szLogicalDrives);
        if (dwResult > 0 && dwResult <= MAX_PATH) {
            char *szSingleDrive = szLogicalDrives;
            printf("GetLogicalDriveStrings() return value: %d, Error (if any): %d \n", dwResult, GetLastError());
            printf("The logical drives of this machine are:\n");
            int count = 0;
            while (*szSingleDrive) {
                printf("Drive %d: %s\n", count++, szSingleDrive);

                // get the next drive
                szSingleDrive += strlen(szSingleDrive) + 1;
            }
        } else
            printf("GetLogicalDriveStrings() is failed lor!!! Error code: %d\n", GetLastError());

        cout << "Choose drive: ";
        int key2;
        cin >> key2;
        cout << endl;

        szSingleDrive = szLogicalDrives;
        for (int i = 0; i < key2; i++) {
            szSingleDrive += strlen(szSingleDrive) + 1;
        }
        printf("Drive: %s\n", szSingleDrive);
        cout << "-------GetDriveType-------" << endl;
        switch ((int) GetDriveType(szSingleDrive)) {
            case 0:
                cout << "DRIVE_UNKNOWN; The drive type cannot be determined." << endl;
                break;
            case 1:
                cout << "DRIVE_NO_ROOT_DIR; The root path is invalid; for example, "
                        "there is no volume mounted at the specified path." << endl;
                break;
            case 2:
                cout << "DRIVE_REMOVABLE; The drive has removable media; for example, a floppy drive, "
                        "thumb drive, or flash card reader." << endl;
                break;
            case 3:
                cout << "DRIVE_FIXED; The drive has fixed media; for example, a hard disk drive or flash drive."
                     << endl;
                break;
            case 4:
                cout << "DRIVE_REMOTE; The drive is a remote (network) drive." << endl;
                break;
            case 5:
                cout << "DRIVE_CDROM; The drive is a CD-ROM drive." << endl;
                break;
            case 6:
                cout << "DRIVE_RAMDISK; The drive is a RAM disk." << endl;
                break;
        }

        char Name[MAX_PATH];
        char NameFileSystem[MAX_PATH];
        DWORD SerialNumber;
        DWORD TypeFileSystem;
        DWORD SizeTom;

        if (GetVolumeInformation(szSingleDrive, (LPSTR) Name, sizeof(Name), &SerialNumber, &SizeTom, &TypeFileSystem,
                                 (LPSTR) NameFileSystem, sizeof(NameFileSystem))) {
            cout << "-------GetVolumeInformation-------" << endl;
            cout << "Name: " << Name << endl;
            cout << "Serial number: " << SerialNumber << endl;
            printf("File system flags: 0x%p\n", TypeFileSystem);
            cout << "File system: " << NameFileSystem << endl;
        } else cout << "Something got wrong and volume information aren't received!" << endl;

        DWORD lpSectorsPerCluster, lpBytesPerSector, lpNumberOfFreeClusters, lpTotalNumberOfClusters;
        if (GetDiskFreeSpace(szSingleDrive, &lpSectorsPerCluster, &lpBytesPerSector, &lpNumberOfFreeClusters,
                             &lpTotalNumberOfClusters)) {
            cout << "-------GetDiskFreeSpace-------" << endl;
            cout << "Sectors per cluster: " << lpSectorsPerCluster << endl;
            cout << "Bytes per cluster: " << lpBytesPerSector << endl;
            cout << "Number of free clusters: " << lpNumberOfFreeClusters << endl;
            cout << "Total number of clusters: " << lpTotalNumberOfClusters << endl;
        } else cout << "Something got wrong and disk space information aren't recieved!" << endl;

        cout << "\n0)Exit" << endl;
        cin >> key;
    } while (key != 0);
    system("CLS");
}

void createDirectory() {

    char path[MAX_PATH];

    system("CLS");
    cout
            << "Enter path to the file, including the file name, extension & using backslashes\n(Example: C:\\Users\\test.txt):"
            << endl;
    cin >> path;

    if (CreateDirectory(path, nullptr)) {
        cout << "Directory created" << endl;
    } else cout << "Error creating directory, " << GetLastError() << endl;

}

void deleteDirectory() {

    char path[MAX_PATH];

    system("CLS");
    cout
            << "Enter path to the file, including the file name, extension & using backslashes\n(Example: C:\\Users\\test.txt):"
            << endl;
    cin >> path;

    if (RemoveDirectory(path)) {
        cout << "Directory deleted" << endl;
    } else cout << "Error deleting directory, " << GetLastError() << endl;
}

void directoryOperations() {

    menuItem directoryMenu[] {
            {1,"Create folder",createDirectory},
            {2,"Delete folder",deleteDirectory},
            {0,"Exit"}
    };
    static const unsigned int directoryMenuSize = sizeof(directoryMenu) / sizeof(directoryMenu[0]);

    system("CLS");
    MenuEngine(&directoryMenu[0],directoryMenuSize);
    system("CLS");
}

void createFile() {

    char fileName[MAX_PATH];
    HANDLE fHandle;
    int key = 1;

    do {
        system("CLS");
        cout
                << "Enter path to the file, including the file name, extension & using backslashes\n(Example: C:\\Users\\test.txt):"
                << endl;
        cin >> fileName;

        fHandle = CreateFile(fileName, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
        if (INVALID_HANDLE_VALUE == fHandle) {
            cout << "Something went wrong and file wasn't created! Error:\n" << GetLastError() << endl;
        } else cout << "File created successfully!" << endl;

        cout << "\n0)Exit" << endl;
        cin >> key;
    } while (key != 0);
    system("CLS");

}

void copyFile() {

    char existingFilePath[MAX_PATH], newFilePath[MAX_PATH];

    bool failIfExists;
    int key;

    cout << "-------copyFile-------" << endl;
    cout
            << "Enter path to the file, including the file name, extension & using backslashes\n(Example: C:\\Users\\test.txt):"
            << endl;
    cin >> existingFilePath;
    cout << "Enter new path to the file:" << endl;
    cin >> newFilePath;

    cout << "Do you want to overwrite if new file already exists? (1 - yes, 2 - no):" << endl;
    cin >> key;

    if (key == 1) {
        failIfExists = false;
    } else if (key == 2) {
        failIfExists = true;
    } else {
        cout << "There's no such option!\nFile overwrite is disabled" << endl;
        failIfExists = true;
    }

    if (CopyFile(existingFilePath, newFilePath, failIfExists)) {
        cout << "File successfully copied!" << endl;
    } else cout << "Something went wrong and file wasn't copied! Error:\n" << GetLastError() << endl;

}

void moveFile() {

    char existingFilePath[MAX_PATH], newFilePath[MAX_PATH];

    cout << "-------moveFile-------" << endl;
    cout
            << "Enter path to the file, including the file name, extension & using backslashes\n(Example: C:\\Users\\test.txt):"
            << endl;
    cin >> existingFilePath;
    cout << "Enter new path to the file:" << endl;
    cin >> newFilePath;

    //simple file move, the file cannot be overwritten here
    if (MoveFile(existingFilePath,newFilePath)) {
        cout << "File/folder has been moved" << endl;
    } else cout << "Something went wrong and file wasn't moved! Error:\n" << GetLastError() << endl;

}

void moveFileProtected() {

    //you can overwrite a file
    char existingFilePath[MAX_PATH], newFilePath[MAX_PATH];

    bool result;
    int key;

    cout << "-------moveFileEx-------" << endl;
    cout
            << "Enter path to the file, including the file name, extension & using backslashes\n(Example: C:\\Users\\test.txt):"
            << endl;
    cin >> existingFilePath;
    cout << "Enter new path to the file:" << endl;
    cin >> newFilePath;

    cout << "Do you want to overwrite file if new already exists? (1 - yes, 2 - no):" << endl;
    cin >> key;

    if (key == 1) {
        result = MoveFileEx(existingFilePath,newFilePath,MOVEFILE_REPLACE_EXISTING);
    } else if (key == 2) {
        result = MoveFileEx(existingFilePath,newFilePath,MOVEFILE_WRITE_THROUGH);
    } else {
        cout << "There's no such option!\nFile overwrite is disabled" << endl;
        result = MoveFileEx(existingFilePath,newFilePath,MOVEFILE_WRITE_THROUGH);
    }

    if (result) {
        cout << "File/folder has been moved" << endl;
    } else cout << "Something went wrong and file wasn't moved! Error:\n" << GetLastError() << endl;

}

void copyMoveFile() {

    menuItem copyFileMenu[] {
            {1,"Copy file",copyFile},
            {2,"Move file (moveFile, no overwrite check)",moveFile},
            {3,"Protected move file (moveFileEx, files can be overwritten)",moveFileProtected},
            {0,"Exit"}
    };
    static const unsigned int taskOneMenuSize = sizeof(copyFileMenu) / sizeof(copyFileMenu[0]);

    system("CLS");
    MenuEngine(&copyFileMenu[0],taskOneMenuSize);
    system("CLS");
}

void decodeAttributes(DWORD attributes) {

    if (attributes & FILE_ATTRIBUTE_DIRECTORY) cout << "Directory;\n";
    if (attributes & FILE_ATTRIBUTE_ARCHIVE) cout << "File or directory is an archive;\n";
    if (attributes & FILE_ATTRIBUTE_COMPRESSED) cout << "File or directory is compressed;\n";
    if (attributes & FILE_ATTRIBUTE_ENCRYPTED) cout << "File or directory is encrypted;\n";
    if (attributes & FILE_ATTRIBUTE_HIDDEN) cout << "File or directory is hidden;\n";
    if (attributes & FILE_ATTRIBUTE_NORMAL) cout << "File does not have other attributes set;\n";
    if (attributes & FILE_ATTRIBUTE_NOT_CONTENT_INDEXED) cout << "File or directory is not indexed by the content indexing service;\n";
    if (attributes & FILE_ATTRIBUTE_OFFLINE) cout << "File data is physically moved to offline storage;\n";
    if (attributes & FILE_ATTRIBUTE_READONLY) cout << "File is read-only;\n";
    if (attributes & FILE_ATTRIBUTE_REPARSE_POINT) cout << "File or directory has an associated reparse point, or a file that is a symbolic link;\n";
    if (attributes & FILE_ATTRIBUTE_SPARSE_FILE) cout << "File is a sparse file;\n";
    if (attributes & FILE_ATTRIBUTE_SYSTEM) cout << "File or directory that the operating system uses a part of, or uses exclusively;\n";
    if (attributes & FILE_ATTRIBUTE_TEMPORARY) cout << "File is being used for temporary storage;\n";

}

void fileAttributes() {

    CHAR* filePath;
    string buff;
    int key;

    DWORD fileAttributes = 0;

    settingsMenuItem attributesMenu[] {
            {"directory",FILE_ATTRIBUTE_DIRECTORY},
            {"archive",FILE_ATTRIBUTE_ARCHIVE},
            {"compressed",FILE_ATTRIBUTE_COMPRESSED},
            {"encrypted",FILE_ATTRIBUTE_ENCRYPTED},
            {"hidden",FILE_ATTRIBUTE_HIDDEN},
            {"normal",FILE_ATTRIBUTE_NORMAL},
            {"not content indexed",FILE_ATTRIBUTE_NOT_CONTENT_INDEXED},
            {"offline",FILE_ATTRIBUTE_OFFLINE},
            {"readonly",FILE_ATTRIBUTE_READONLY},
            {"reparse point",FILE_ATTRIBUTE_REPARSE_POINT},
            {"sparse",FILE_ATTRIBUTE_SPARSE_FILE},
            {"system",FILE_ATTRIBUTE_SYSTEM},
            {"temporary",FILE_ATTRIBUTE_TEMPORARY},
            {"exit",FILE_ATTRIBUTE_TEMPORARY}
    };
    static const unsigned int attributesMenuSize = sizeof(attributesMenu) / sizeof(attributesMenu[0]);

    do {
        system("CLS");

        cout
                << "Enter path to the file, including the file name, extension & using backslashes\n(Example: C:\\Users\\test.txt):"
                << endl;
        cin >> buff;
        filePath = buff.data();
        cout << "-------GetFileAttributes-------" << endl;
        fileAttributes = GetFileAttributes(filePath);
        if (fileAttributes != INVALID_FILE_ATTRIBUTES) {
            cout << "Success!" << endl;
            printf("File attributes: 0x%p\n", fileAttributes);
            decodeAttributes(fileAttributes);
        } else cout << "Something went wrong, couldn't get the file attributes! Error:\n" << GetLastError() << endl;
        cout << "1)Set custom file attributes to current file\n2)Skip" << endl;
        cin >> key;
        if (key == 1) {
            //set attributes, no check
            DWORD customAttributes = 128;
            cout << "Choose file attributes:" << endl;
            SettingsEngine(&attributesMenu[0],attributesMenuSize,&customAttributes);
            cout << "-------SetFileAttributes-------" << endl;
            SetFileAttributes(filePath, customAttributes);
            //show result
            fileAttributes = GetFileAttributes(filePath);
            if (fileAttributes != INVALID_FILE_ATTRIBUTES) {
                printf("Current file attributes : 0x%p\n", fileAttributes);
            } else cout << "Something went wrong, couldn't get the file attributes! Error:\n" << GetLastError() << endl;
        }
        //next  C:\Users\Artem\Desktop\output.txt
        cout << "-------GetFileInformationByHandle-------" << endl;
        HANDLE myFile = NULL;
        BY_HANDLE_FILE_INFORMATION handleFileInfo;
        SYSTEMTIME sysTimeTemp, localTimeTemp;
        FILETIME create, access, write;

        //receiving a handle
        myFile = CreateFile(filePath, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

        if (myFile != INVALID_HANDLE_VALUE) {
            if (GetFileInformationByHandle(myFile, &handleFileInfo)) {
                printf("File attributes: 0x%p\n", handleFileInfo.dwFileAttributes);
                //converting file time to printable format
                TIME_ZONE_INFORMATION timeZone;
                char buffer[256];

                FileTimeToSystemTime(&handleFileInfo.ftCreationTime,
                                     &sysTimeTemp);  //converting file time to system time
                GetTimeZoneInformation(&timeZone);  //get time zone info
                SystemTimeToTzSpecificLocalTime(&timeZone, &sysTimeTemp,
                                                &localTimeTemp);     //converting system time to local time
                sprintf(buffer, "%d-%02d-%02d %02d:%02d:%02d.%03d",
                        localTimeTemp.wYear, localTimeTemp.wMonth, localTimeTemp.wDay, localTimeTemp.wHour,
                        localTimeTemp.wMinute,
                        localTimeTemp.wSecond, localTimeTemp.wMilliseconds);
                cout << "File creation time: " << buffer << endl;

                //ftLastAccessTime
                FileTimeToSystemTime(&handleFileInfo.ftLastAccessTime, &sysTimeTemp);
                SystemTimeToTzSpecificLocalTime(&timeZone, &sysTimeTemp, &localTimeTemp);
                sprintf(buffer, "%d-%02d-%02d %02d:%02d:%02d.%03d",
                        localTimeTemp.wYear, localTimeTemp.wMonth, localTimeTemp.wDay, localTimeTemp.wHour,
                        localTimeTemp.wMinute,
                        localTimeTemp.wSecond, localTimeTemp.wMilliseconds);
                cout << "File last access time: " << buffer << endl;

                //ftLastWriteTime
                FileTimeToSystemTime(&handleFileInfo.ftLastWriteTime, &sysTimeTemp);
                SystemTimeToTzSpecificLocalTime(&timeZone, &sysTimeTemp, &localTimeTemp);
                sprintf(buffer, "%d-%02d-%02d %02d:%02d:%02d.%03d",
                        localTimeTemp.wYear, localTimeTemp.wMonth, localTimeTemp.wDay, localTimeTemp.wHour,
                        localTimeTemp.wMinute,
                        localTimeTemp.wSecond, localTimeTemp.wMilliseconds);
                cout << "File last write time: " << buffer << endl;

                //VolumeSerialNumber
                printf("Volume serial number: 0x%p\n", handleFileInfo.dwVolumeSerialNumber);
                //fileSizeHigh
                printf("Volume high-order size part: 0x%p\n", handleFileInfo.nFileSizeHigh);
                //fileSizeLow
                printf("Volume low-order size part: 0x%p\n", handleFileInfo.nFileSizeLow);
                //numberOfLinks
                printf("Volume number of links: %d\n", handleFileInfo.nNumberOfLinks);
                //fileIndexHigh
                printf("Volume high-order part of a unique identifier: 0x%p\n", handleFileInfo.nFileIndexHigh);
                //fileIndexLow
                printf("Volume low-order part of a unique identifier: 0x%p\n", handleFileInfo.nFileSizeLow);
                cout << "-------GetFileTime-------" << endl;
                //myFile = NULL;
                //myFile = CreateFile(filePath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
                if (myFile != INVALID_HANDLE_VALUE) {
                    if (GetFileTime(myFile, &create, &access, &write)) {
                        FileTimeToSystemTime(&create, &sysTimeTemp);  //converting file time to system time
                        SystemTimeToTzSpecificLocalTime(&timeZone, &sysTimeTemp,
                                                        &localTimeTemp);     //converting system time to local time
                        sprintf(buffer, "%d-%02d-%02d %02d:%02d:%02d.%03d",
                                localTimeTemp.wYear, localTimeTemp.wMonth, localTimeTemp.wDay, localTimeTemp.wHour,
                                localTimeTemp.wMinute,
                                localTimeTemp.wSecond, localTimeTemp.wMilliseconds);
                        cout << "File creation time: " << buffer << endl;

                        FileTimeToSystemTime(&access, &sysTimeTemp);  //converting file time to system time
                        SystemTimeToTzSpecificLocalTime(&timeZone, &sysTimeTemp,
                                                        &localTimeTemp);     //converting system time to local time
                        sprintf(buffer, "%d-%02d-%02d %02d:%02d:%02d.%03d",
                                localTimeTemp.wYear, localTimeTemp.wMonth, localTimeTemp.wDay, localTimeTemp.wHour,
                                localTimeTemp.wMinute,
                                localTimeTemp.wSecond, localTimeTemp.wMilliseconds);
                        cout << "File last access time: " << buffer << endl;

                        FileTimeToSystemTime(&write, &sysTimeTemp);  //converting file time to system time
                        SystemTimeToTzSpecificLocalTime(&timeZone, &sysTimeTemp,
                                                        &localTimeTemp);     //converting system time to local time
                        sprintf(buffer, "%d-%02d-%02d %02d:%02d:%02d.%03d",
                                localTimeTemp.wYear, localTimeTemp.wMonth, localTimeTemp.wDay, localTimeTemp.wHour,
                                localTimeTemp.wMinute,
                                localTimeTemp.wSecond, localTimeTemp.wMilliseconds);
                        cout << "File last write time: " << buffer << endl;
                    } else cout << "Something went wrong! Error: " << GetLastError() << endl;
                }

                cout << "Do you want to change file time co current system time? (1 - yes,2 - no)" << endl;
                cin >> key;
                if (key == 1) {
                    cout << "-------SetFileTime-------" << endl;
                    //GetSystemTimeAsFileTime(&access);
                    GetSystemTime(&sysTimeTemp);
                    SystemTimeToFileTime(&sysTimeTemp,&access);
                    if (SetFileTime(myFile,&access,&access,&access)) {
                        cout << "Time set successfully!" << endl;
                    } else cout << "Something went wrong! Error: " << GetLastError() << endl;
                }
            } else cout << GetLastError() << endl;
            CloseHandle(myFile);
        } else cout << "Couldn't get the file hande, please check file path! Error: " << GetLastError() << endl;

        cout << "\n0)Exit" << endl;
        cin >> key;
    } while (key != 0);
    system("CLS");
}

menuItem taskOneMenu[] {
        {1,"Get drives list",getDiskList},
        {2,"Get drive info",getDiskInfoSpace},
        {3,"Create/delete folder",directoryOperations},
        {4,"Create file",createFile},
        {5,"Copy/move file",copyMoveFile},
        {6,"Get/Set file attributes",fileAttributes},
        {0,"Exit"}
};
static const unsigned int taskOneMenuSize = sizeof(taskOneMenu) / sizeof(taskOneMenu[0]);
void openFirstTask() {
    system("CLS");
    MenuEngine(&taskOneMenu[0],taskOneMenuSize);
    system("CLS");
}
