#include <iostream>

#include "LEIC.h"


//Set This Directory as The Working Directory
int main() {
    LEIC leic("classes_per_uc.csv", "students_classes.csv", "classes.csv");

    std::string mainInput;
    std::string dummy;
    std::string mainMenuMessage = R"(
1-Consult General Data in LEIC
2-Consult Data of a Year
3-Consult Data of an UC
4-Consult Data of a Class
5-Consult Data of a Student
6-Manage Students
7-Process Requests
8-Undo Changes
q-Quit

Enter:)";



    while (true) {
        std::cout << mainMenuMessage;
        std::cin >> mainInput;
        if (mainInput == "q"){
            break;
        }
        else if (mainInput == "1") {
            leic.ConsultDataInLEICMenu();
        }
        else if (mainInput == "2") {
            leic.consultDataInYearMenu();
        }
        else if (mainInput == "3") {
            leic.consultDataInUCsMenu();
        }
        else if (mainInput == "4") {
            leic.consultDataInClassesMenu();
        }
        else if (mainInput == "5") {
            leic.consultDataInStudentMenu();
        }
        else if (mainInput == "6") {
            leic.manageStudentsMenu();
        }
        else if (mainInput == "7") {
            leic.processRequestMenu();
        }
        else if (mainInput == "8") {
            leic.undoMenu();
        }
        else {
            std::cout << "Invalid Command" << std::endl;
        }


        std::cout << "(Enter Anything to Continue)" << std::endl;
        std::cin >> dummy;
    }

    //201920727
    return 0;
}
