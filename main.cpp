#include <windows.h>
#include "prog1.h"
#include "prog2.h"
using namespace std;

menuItem mainMenu[] {
        {1,"Task 1",openFirstTask},
        {2,"Task 2",openSecondTask},
        {0,"Exit"}
};
static const unsigned int mainMenuSize = sizeof(mainMenu) / sizeof(mainMenu[0]);

int main() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    system("CLS");
    MenuEngine(&mainMenu[0], mainMenuSize);
    return 0;
}
