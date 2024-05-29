#include "libs/data/func/func.h"
#include "generate.h"
#include "windows.h"


int main() {
    SetConsoleOutputCP(CP_UTF8);

    generateMatrixFile1();
    generateMatrixFile2();


    Task1();
    Task2();
    Task3();
    Task4();
    Task5("inputStr.txt");
    Task6(3, "xDigit.txt");
    Task7("7task.txt", 3);
    Task8("8task.txt",9);
    Task9("task9",22);
    Task10("first_10","second_10");

}
