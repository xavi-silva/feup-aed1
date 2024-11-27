//
// Created by duarte on 15-10-2023.
//

#include "LEIC.h"

#include <algorithm>
#include <iostream>

/**Constructor*/
LEIC::LEIC(const std::string& UCsPath, const std::string& studentsClassesPath, const std::string& classesPath) {
    parseUCs(UCsPath);
    parseStudentsClasses(studentsClassesPath);
    parseSchedules(classesPath);
}

/**LEIC management*/
void LEIC::addUC(const std::string& UCCode) {
    UCs_[UCCode] = UC(UCCode);
}

void LEIC::addClassToUc(const std::string& classCode, const std::string &UCCode) {
    getUC(UCCode).addClass(classCode);
}

void LEIC::addStudent(const std::string& name, const std::string& studentNr) {
    students_[studentNr] = Student(name, studentNr);
}

/**Check*/
bool LEIC::hasUC(const std::string& UCCode) {

    if(UCs_.find(UCCode) == UCs_.end()){
        std::cout << "There is no " << UCCode << " UC" << std::endl;
        return false;
    }
    return true;
}

bool LEIC::hasStudent(const std::string &studentNr) {
    return students_.find(studentNr) !=  students_.end();
}
bool LEIC::classHasStudent(const std::string& studentNr, const std::string& ucCode, const std::string& classCode){
    UC& uc = getUC(ucCode);
    Student student = getStudent(studentNr);
    for(auto& classPair: uc.getClasses()){
        if (classPair.second.getClassCode() == classCode){
            for (StudentData a : classPair.second.getClassStudents()){
                if (a.studentNr == studentNr) return true;
            }
        }
    }
    return false;
}

bool LEIC::ucHasStudent(std::string studentNr, std::string ucCode) {
    UC uc = getUC(ucCode);
    for (auto& classPair: uc.getClasses()) {
        if (classHasStudent(studentNr, ucCode, classPair.second.getClassCode())) return true;
    }
    return false;
}

/**Accessors*/
UC& LEIC::getUC(const std::string& UCcode){
    return UCs_[UCcode];
}


Student& LEIC::getStudent(const std::string& studentNr) {
    return students_[studentNr];
}



/**Parse*/

void LEIC::parseUCs(const std::string &UCsPath) {

    std::ifstream in(UCsPath);

    if (!in.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return;
    }

    std::string line, UCCode, classCode;
    std::getline(in, line);

    while (std::getline(in, line) )
    {

        std::istringstream ss(line);

      std::getline(ss, UCCode, ',');
      std::getline(ss, classCode, ',');


      if (!hasUC(UCCode)) {addUC(UCCode);}

      addClassToUc(classCode, UCCode);


    }




}

void LEIC::parseStudentsClasses(const std::string &studentsClassesPath) {

    std::ifstream in(studentsClassesPath);

    if (!in.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return;
    }

    std::string line, studentNr, studentName, UCCode, classCode;
    std::getline(in, line);
    while (std::getline(in, line) )
    {

        std::istringstream ss(line);

        std::getline(ss, studentNr, ',');
        std::getline(ss, studentName, ',');
        std::getline(ss, UCCode, ',');
        std::getline(ss, classCode, ',');

        if (!hasStudent(studentNr)) {
            addStudent(studentName, studentNr);
        };

        //applyStudentToUC(studentNr, UCCode, classCode);
        addStudentToUCParser(studentNr, UCCode, classCode);

    }




}
void LEIC::addStudentToUCParser(const std::string &studentNr, const std::string &UCCode, const std::string &classCode) {
    Student& student = getStudent(studentNr);
    student.addUC(UCCode, classCode);
    UC& uc= getUC(UCCode);
    uc.addStudentToClass(student.getData(), classCode);

}
void LEIC::parseSchedules(const std::string &schedulesPath) {

    std::ifstream in(schedulesPath);

    if (!in.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return;
    }

    /**ClassCode,UcCode,Weekday,StartHour,Duration,Type*/

    std::string line, classCode, UCcode, weekDay ,startHourStr, durationStr;
    float startHour = 0, duration = 0;
    std::string type;

    std::getline(in, line);
    while (std::getline(in, line) )
    {

        std::istringstream ss(line);

        std::getline(ss, classCode, ',');
        std::getline(ss, UCcode, ',');
        std::getline(ss, weekDay, ',');
        std::getline(ss, startHourStr, ',');
        std::getline(ss, durationStr, ',');
        std::getline(ss, type, ',');

        startHour = std::stof(startHourStr);
        duration = std::stof(durationStr);

        Class& c = getUC(UCcode).getClass(classCode);
        c.addEvent({type, weekDay, startHour, duration, UCcode});

    }



}




/**Consulting functions*/

/**Consult in LEIC*/
void LEIC::ConsultDataInLEICMenu() {
    std::string leicMessage = R"(
1-Students by Name
2-Students by Enrollment
qo-Quit Operation
Enter:)";
    std::string command;
    std::string dummy;

    while (true) {
        std::cout << leicMessage;
        std::cin >> command;

        if (command == "qo") {
            break;
        }
        else if (command == "1") {
            consultCourseStudentsByName();


        }
        else if (command == "2") {
            consultCourseStudentsByEnrollment();
        }
        else {
            std::cout << "Invalid Command" << std::endl;
            continue;
        }
        std::cout << "(Enter Anything to Continue)" << std::endl;
        std::cin >> dummy;
    }
}

void LEIC::consultCourseStudentsByEnrollment() {
    for(auto& p : students_){
        Student& student = p.second;
        std::cout<<"Name: "<< student.getName()<<"\nNumber: "<< student.getStudentNr()<< "\n===========" << std::endl;}
}

void LEIC::consultCourseStudentsByName() {
    std::set<StudentData> studentDataSet;
    for(auto& p : students_){
        Student& student = p.second;
        studentDataSet.insert(student.getData());
    }
    for(auto& sd : studentDataSet){
        sd.print();
    }

}

/**Consult in Year*/
void LEIC::consultDataInYearMenu() {

    std::string leicMessage = R"(
1-Year Occupation
2-Students in a Year
qo-Quit Operation
Enter:)";

    std::string command;
    char year;
    std::string dummy;

    while (true) {
        std::cout << leicMessage;
        std::cin >> command;

        if (command == "qo") {
            break;
        }
        else if (command == "1") {
            std::cout << "Year:";
            std::cin >> year;
            Consult_yearOccupation(year);


        }
        else if (command == "2") {
            std::cout << "Year:";
            std::cin >> year;
            Consult_yearStudents(year);
        }
        else {
            std::cout << "Invalid Command" << std::endl;
            continue;
        }
        std::cout << "(Enter Anything to Continue)" << std::endl;
        std::cin >> dummy;
    }

}
void LEIC::Consult_yearStudents(char year) {
    if (year < '1' or year > '3') {
        std::cout << "Invalid Year" << std::endl;
        return;
    }

    std::set<StudentData> yearStudentData;
    for(auto& ucPair : UCs_){
        UC& uc = ucPair.second;
        for(auto& classPair : uc.getClasses()){
            Class& c = classPair.second;
            if(c.getClassYear()==year){
                yearStudentData.insert(c.getClassStudents().begin(), c.getClassStudents().end());
            }
        }
    }

    for(auto& sd : yearStudentData){
        std::cout<<"Name: "<< sd.name <<"\nNumber: "<< sd.studentNr << "\n===========" << std::endl;
    }
}

void LEIC::Consult_yearOccupation(char year){
    if (year < '1' or year > '3') {
        std::cout << "Invalid Year" << std::endl;
        return;
    }
    std::set<StudentData> yearStudentData;

    for(auto& ucPair : UCs_){
        UC& uc = ucPair.second;
        for(auto& classPair : uc.getClasses()){
            Class& c = classPair.second;
            if(c.getClassYear()==year){
                yearStudentData.insert(c.getClassStudents().begin(), c.getClassStudents().end());
            }
        }
    }


    if(year=='1'){std::cout<<"The " << year << "st year has "<< yearStudentData.size() <<" students enrolled." << std::endl;}
    else if(year=='2'){std::cout<<"The " << year << "nd year has "<< yearStudentData.size() <<" students enrolled." << std::endl;}
    else if(year=='3'){std::cout<<"The " << year << "rd year has "<< yearStudentData.size() <<" students enrolled." << std::endl;}


}

/**Consult in UC*/
void LEIC::consultDataInUCsMenu(){
    std::string ucMessage = R"(
1-List UCs
2-Students in UC
3-UC Occupation
4-UC Availability
5-How Many Students are Registered in at Least n UCs:
qo-Quit Operation
Enter:)";

    std::string command;
    std::string UCCode;
    int n;
    std::string dummy;

    while (true) {
        std::cout << ucMessage;
        std::cin >> command;

        if (command == "qo") {
            break;
        }
        else if (command == "1") {
            listUCs();
        }
        else if (command == "2") {
            std::cout << "UC Code:";
            std::cin >> UCCode;
            Consult_UCStudents(UCCode);
        }
        else if (command == "3") {
            std::cout << "UC Code:";
            std::cin >> UCCode;
            Consult_UCoccupation(UCCode);
        }
        else if (command == "4") {
            std::cout << "UC Code:";
            std::cin >> UCCode;
            Consult_UCAvailability(UCCode);
        }
        else if (command == "5") {
            std::cout << "n:";
            std::cin >> n;
            Consult_StudentsInNuc(n);
        }
        else {
            std::cout << "Invalid Command" << std::endl;
            continue;
        }
        std::cout << "(Enter Anything to Continue)" << std::endl;
        std::cin >> dummy;
    }

}
void LEIC::listUCs() {
    for (auto& ucPair : UCs_) {
        std::cout << ucPair.first << std::endl;/**Prints UCCode*/
    }
}
void LEIC::Consult_UCStudents(const std::string &UCcode) {
    if (!hasUC(UCcode)) {return;}

    UC& uc = getUC(UCcode);
    std::set<StudentData> studentDataSet;
    for(auto& classPair : uc.getClasses()){
        Class c = classPair.second;
        for(auto& sd : c.getClassStudents()){
            studentDataSet.insert(sd);}
    }

    for(auto& sd : studentDataSet){
        sd.print();
    }
}

void LEIC::Consult_StudentsInNuc(int n){
    if (n < 1 or n > 7) {
        std::cout << "Invalid Number of UCs" << std::endl;
        return;
    }
    int count=0;
    for(auto& studentPair : students_){
        Student& student = studentPair.second;
        if(student.getStudentUCs().size() >= n){count++;}
    }
    std::cout<<"There are "<< count <<" students registered in at least "<< n <<" UCs" << std::endl;
}

void LEIC::Consult_UCoccupation(const std::string& UCcode) {
    if (!hasUC(UCcode)) {return;}

    unsigned int count = 0;
    UC &uc = getUC(UCcode);
    for (auto& classPair: uc.getClasses()) {
        Class& c = classPair.second;
        count += c.getClassStudents().size();

    }

    std::cout << "The UC " << UCcode << " has " << count << " students." << std::endl;

}

void LEIC::Consult_UCAvailability(const std::string& ucCode){
    if (!hasUC(ucCode)) {return;}

    auto& classes = getUC(ucCode).getClasses();

    for (auto& classPair : classes) {
        Class& c = classPair.second;

        std:: cout << c.getClassCode() << ": " << c.getClassStudents().size() << "/" << ClassConstants::maxStudents << std::endl;

    }

}


/**Consult Class*/

void LEIC::consultDataInClassesMenu(){
    std::string classMessage = R"(
1-Class Schedule
2-Class Occupation
3-Class Students
qo-Quit Operation
Enter:)";

    std::string command;
    std::string UCCode;
    std::string classCode;
    std::string dummy;

    while (true) {
        std::cout << classMessage;
        std::cin >> command;

        if (command == "qo") {
            break;
        }
        else if (command == "1") {
            std::cout << "UC Code:";
            std::cin >> UCCode;
            std::cout << "Class Code:";
            std::cin >> classCode;

            Consult_classSchedule(UCCode, classCode);
        }
        else if (command == "2") {
            std::cout << "UC Code:";
            std::cin >> UCCode;
            std::cout << "Class Code:";
            std::cin >> classCode;

            Consult_classOccupation(UCCode, classCode);

        }
        else if (command == "3") {
            std::cout << "UC Code:";
            std::cin >> UCCode;
            std::cout << "Class Code:";
            std::cin >> classCode;

            Consult_classStudents(UCCode, classCode);

        }
        else {
            std::cout << "Invalid Command" << std::endl;
            continue;
        }
        std::cout << "(Enter Anything to Continue)" << std::endl;
        std::cin >> dummy;
    }

}

void LEIC::Consult_classSchedule(const std::string& ucCode, const std::string& classCode) {
    if (!hasUC(ucCode)){return;}
    UC& uc = getUC(ucCode);
    if (!uc.hasClass(classCode)) { return;}
    Class& c = uc.getClass(classCode);
    auto& schedule = c.getClassSchedule();
    schedule.print();

}

void LEIC::Consult_classOccupation(const std::string& ucCode, const std::string& classCode){
    if (!hasUC(ucCode)) {return;}
    UC& uc= getUC(ucCode);
    if (!uc.hasClass(classCode)) { return;}
    Class& turma = uc.getClass(classCode);
    std::cout<<"The Class " << classCode<<" of the "<<ucCode<<" has "<<turma.getClassStudents().size()<<" students." << std::endl;

}



void LEIC::Consult_classStudents(const std::string &UCCode, const std::string &classCode) {
    if (!hasUC(UCCode)) {return;}
    UC& uc = getUC(UCCode);
    if (!uc.hasClass(classCode)) { return;}
    Class& c = uc.getClass(classCode);
    std::set<StudentData> students = c.getClassStudents();

    for(auto& sd : students){
        sd.print();
    }

}

/**Consult Student*/
void LEIC::consultDataInStudentMenu() {
    std::string studentMessage = R"(
1-Student's UCs
2-Schedule
qo-Quit Operation
Enter:)";

    std::string command;
    std::string studentNr;
    std::string dummy;

    while (true) {
        std::cout << studentMessage;
        std::cin >> command;

        if (command == "qo") {
            break;
        }
        else if (command == "1") {
            std::cout << "Student Number:";
            std::cin >> studentNr;

            Consult_studentUCs(studentNr);
        }
        else if (command == "2") {
            std::cout << "Student Number:";
            std::cin >> studentNr;

            Consult_studentSchedule(studentNr);

        }
        else {
            std::cout << "Invalid Command" << std::endl;
            continue;
        }
        std::cout << "(Enter Anything to Continue)" << std::endl;
        std::cin >> dummy;
    }


}

void LEIC::Consult_studentUCs(const std::string &studentNumber) {
    if (!hasStudent(studentNumber)){ return;}
    Student& student = getStudent(studentNumber);
    for (const enrolment& enr : student.getStudentUCs()) {
        enr.print();
    }
}

void LEIC::Consult_studentSchedule(std::string &studentNumber) {
    ClassSchedule::Schedule schedule = getStudentSchedule(studentNumber);
    schedule.print();
}




/**Student Management*/
void LEIC::manageStudentsMenu() {
    std::string studentMessage = R"(
Request:
1-Enroll Student in a UC
2-Remove a Student from an UC
3-Switch a Student UC
4-Switch a Student Class
qo-Quit Operation
Enter:)";

    std::string command;
    std::string studentNr;
    std::string newUCCode;
    std::string prevUCCode;
    std::string newClassCode;

    std::string dummy;

    while (true) {
        std::cout << studentMessage;
        std::cin >> command;

        if (command == "qo") {
            break;
        }
        else if (command == "1") {
            std::cout << "Student Number:";
            std::cin >> studentNr;
            listUCs();
            std::cout << "UC Code:";
            std::cin >> newUCCode;

            std::cout << "These Are The Available Classes:" << std::endl;
            Consult_UCAvailability(newUCCode);
            std::cout << "Class Code:";
            std::cin >> newClassCode;

            std::vector<std::string> vector = {"Add Student", studentNr, newUCCode, newClassCode};
            requestsQueue.push(vector);


        }
        else if (command == "2") {
            std::cout << "Student Number:";
            std::cin >> studentNr;
            Consult_studentUCs(studentNr);
            std::cout << "UC Code:";
            std::cin >> prevUCCode;

            std::vector<std::string> vector = {"Remove Student", studentNr, prevUCCode};
            requestsQueue.push(vector);


        }
        else if (command == "3") {
            std::cout << "Student Number:";
            std::cin >> studentNr;


            Consult_studentUCs(studentNr);
            std::cout << "UC Code to Abandon:";
            std::cin >> prevUCCode;

            listUCs();
            std::cout << "UC Code to Join:";
            std::cin >> newUCCode;

            Consult_UCAvailability(newUCCode);
            std::cout << "Class Code:";
            std::cin >> newClassCode;

            std::vector<std::string> vector = {"Switch Student UC", studentNr, prevUCCode, newUCCode, newClassCode};
            requestsQueue.push(vector);


        }
        else if (command == "4") {
            std::cout << "Student Number:";
            std::cin >> studentNr;

            Consult_studentUCs(studentNr);
            std::cout << "UC Code to Switch Class:";
            std::cin >> prevUCCode;

            Consult_UCAvailability(prevUCCode);
            std::cout << "Class Code:";
            std::cin >> newClassCode;
            std::vector<std::string> vector = {"Switch Student Class", studentNr, prevUCCode, newClassCode};
            requestsQueue.push(vector);


        }
        else {
            std::cout << "Invalid Command" << std::endl;
            continue;
        }
        std::cout << "(Enter Anything to Continue)" << std::endl;
        std::cin >> dummy;
    }


}
void LEIC::applyStudentToUC(const std::string &studentNr, const std::string& UCcode, const std::string& classCode) {
    if (!hasStudent(studentNr)) {
        return;
    }
    if (!canStudentApplyToUC(UCcode, studentNr)) {
        return;
    }
    if (!canStudentApplyToClass(studentNr, classCode, UCcode)) {
        return;
    }
    addStudentToUC(studentNr, UCcode, classCode);
}
void LEIC::addStudentToUC(const std::string &studentNr, const std::string &UCCode, const std::string &classCode) {
    Student& student = getStudent(studentNr);
    student.addUC(UCCode, classCode);
    UC& uc= getUC(UCCode);
    uc.addStudentToClass(student.getData(), classCode);

    std::vector<std::string> vector = {"Added Student", studentNr, UCCode, classCode};
    undoStack.push(vector);
    std::cout << studentNr << " Successfully Joined "<< UCCode << " " << classCode << std::endl;

}

bool LEIC::canStudentApplyToUC(const std::string& UCCode, const std::string& studentNr) { // request switch/add
    /**Check if UC exists*/
    if (!hasUC(UCCode)){return false;}
    /**Check if the student is in the UC already*/
    for (const enrolment& enr : getStudent(studentNr).getStudentUCs()){
        if (enr.UCcode == UCCode) {
            std::cout << "Already in UC " + UCCode << std::endl;
            return false;
        }
    }

    /**Check if the student cannot enroll in more UCs*/
    if (getStudent(studentNr).getStudentUCs().size() == StudentConstants::maxUCs){
        std::cout << "Can't join more UC's" << std::endl;
        /**display student current uc's maybe*/
        return false;
    }

    /**Check if the UC is full*/
    if (!getUC(UCCode).hasVacancy()){
        std::cout << "UC " + UCCode + " is full" << std::endl;
        return false;
    }

    return true;
}

bool LEIC::canStudentApplyToClass(const std::string& studentNr, const std::string &classCode, const std::string &UCCode) {
    ClassSchedule::Schedule schedule = getStudentSchedule(studentNr);
    UC& uc = getUC(UCCode);

    /**Check if class exists*/
    if (!uc.hasClass(classCode)) {
        return false;
    }
    Class& c = getUC(UCCode).getClass(classCode);

    /**Check for schedule conflicts*/
    if (schedule.conflictsWith(c.getClassEvents())){
        return false;
    }

    /**Check for schedule conflicts*/
    if (c.isFull()) {
        return false;
    }

    if (uc.currentBalance() >= UCConstants::MAX_BALANCE){
        unsigned max = 0;
        for (auto classPair : uc.getClasses()){
            if (classPair.second.getClassStudents().size() > max){
                max = classPair.second.getClassStudents().size();
            }
        }
        if (max - c.getClassStudents().size() < UCConstants::MAX_BALANCE) {
            std::cout << "Joining Class will unbalance student distribution" << "(" << studentNr << " " << UCCode << " " << classCode << ")" << std::endl;
            return false;
        }
    }

    return true;
}

ClassSchedule::Schedule LEIC::getStudentSchedule(const std::string& studentNr) {
    ClassSchedule::Schedule schedule;
    if (!hasStudent(studentNr)) {return schedule;}

    Student& student = getStudent(studentNr);

    for (const enrolment& enr : student.getStudentUCs()) {
        UC& uc = getUC(enr.UCcode);
        Class& c = uc.getClass(enr.classCode);
        schedule.addEvent(c.getClassEvents());
    }
    return schedule;
}


void LEIC::switchStudentUC(const std::string& studentNr, const std::string& previousUC, const std::string& newUC, const std::string& newClass){
    if (!ucHasStudent(studentNr, previousUC)) {
        std::cout << "Student is not currently registered in UC " + previousUC << std::endl;
        return;
    }

    std::string previousClass = findStudentClass(studentNr, previousUC).getClassCode();
    removeStudentFromUC(studentNr, previousUC);

    if (canStudentApplyToUC(newUC, studentNr) and canStudentApplyToClass(studentNr, newClass, newUC)) {
        addStudentToUC(studentNr, newUC, newClass);
        undoStack.pop();
        undoStack.pop();
        std::vector<std::string> vector = {"Switched Student UC", studentNr, previousUC, newUC, previousClass, newClass};
        undoStack.push(vector);
        std::cout << studentNr << " Successfully Switched From " << previousUC << " to " << newUC << std::endl;

    }
    else {
        std::cout << studentNr << " Failed to Switch From " << previousUC << " to " << newUC << std::endl;
        undo();
    }
}

void LEIC::switchStudentClass(const std::string& studentNr, const std::string& UCCode, const std::string& newClass){

    if (!ucHasStudent(studentNr, UCCode)){
        std::cout << "Student is not currently registered in UC " + UCCode << std::endl;
        return;
    }

    std::string previousClass = findStudentClass(studentNr, UCCode).getClassCode();
    removeStudentFromUC(studentNr, UCCode);
    if(canStudentApplyToClass(studentNr, newClass, UCCode)) {
        addStudentToUC(studentNr, UCCode, newClass);
        undoStack.pop();
        undoStack.pop();

        std::vector<std::string> vector = {"Switched Student Class", studentNr, UCCode, previousClass, newClass};
        undoStack.push(vector);
        std::cout << studentNr << " Successfully Switched From " << previousClass << " to " << newClass << " in " << UCCode << std::endl;
    }
    else {
        undo();
        std::cout << studentNr << " Failed to Switch From " << previousClass << " to " << newClass << " in " << UCCode << std::endl;
    }
}

void LEIC::removeStudentFromUC(const std::string& studentNr, const std::string& UCCode){
    if (!ucHasStudent(studentNr, UCCode)) {
        std::cout << "Student is not currently registered in UC " + UCCode << std::endl;
        return;
    }
    Student& student = getStudent(studentNr);
    Class& class_ = findStudentClass(studentNr, UCCode);
    class_.removeStudent(student.getData());
    student.removeUC(UCCode);

    std::vector<std::string> vector = {"Removed Student", studentNr, UCCode, class_.getClassCode()};
    undoStack.push(vector);
    std::cout << studentNr << " Was Removed From " << UCCode << std::endl;

}

Class& LEIC::findStudentClass(const std::string& studentNr, const std::string& ucCode){
    Student& student = getStudent(studentNr);
    UC& uc = getUC(ucCode);
    for(auto& classPair : uc.getClasses()){
        if (classPair.second.hasStudent(studentNr))  return classPair.second;
    }
}

/**Undo*/

void LEIC::undoMenu() {

        std::string studentMessage = R"(
1-Undo
2-Undo All
qo-Quit Operation
Enter:)";
        std::string command;
        std::string dummy;
        while (true) {
            std::cout << studentMessage;
            std::cin >> command;
            if (command == "qo") {
                break;
            }
            else if (command == "1") {
                undo();
            }
            else if (command == "2") {
                revertAll();
            }
            else {
                std::cout << "Invalid Command" << std::endl;
                continue;
            }
            std::cout << "(Enter Anything to Continue)" << std::endl;
            std::cin >> dummy;
        }

}

void LEIC::undo(){
    if (!undoStack.empty()){
        auto action = undoStack.top();
        if (action[0] == "Added Student") {
            removeStudentFromUC(action[1], action[2]);
            undoStack.pop();

        }
        //{"Removed Student", studentNr, UCCode, class_.getClassCode()}
        else if (action[0] == "Removed Student"){
            addStudentToUC(action[1],action[2],action[3]);
            undoStack.pop();
        }
        //{"Switched Student UC", studentNr, previousUC, newUC, previousClass, newClass};
        else if (action[0] == "Switched Student UC"){
            removeStudentFromUC(action[1],action[3]);
            addStudentToUC(action[1],action[2],action[4]);
            undoStack.pop();
            undoStack.pop();


        }
        //{"Switched Student Class", studentNr, UCCode, previousClass, newClass};
        else if (action[0] == "Switched Student Class"){
            removeStudentFromUC(action[1],action[2]);
            addStudentToUC(action[1],action[2],action[3]);
            undoStack.pop();
            undoStack.pop();

        }

        undoStack.pop();
        return;

    }
    std::cout<< "Nothing to undo" << std::endl;
}


void LEIC::revertAll(){
    while(!undoStack.empty()){
        undo();

    }
}

void LEIC::clearStack(){
    while(!undoStack.empty()){
        undoStack.pop();
    }
}



/**Process Requests*/

void LEIC::processRequestMenu() {

    std::string studentMessage = R"(
1-Process Next
2-Process All
3-Consult Requests
qo-Quit Operation
Enter:)";
    std::string command;
    std::string dummy;
    while (true) {
        std::cout << studentMessage;
        std::cin >> command;
        if (command == "qo") {
            break;
        }
        else if (command == "1") {
            checkRequest();
        }
        else if (command == "2") {
            while(!requestsQueue.empty()) checkRequest();
        }
        else if (command == "3") {
            Consult_requests();
        }
        else {
            std::cout << "Invalid Command" << std::endl;
            continue;
        }
        std::cout << "(Enter Anything to Continue)" << std::endl;
        std::cin >> dummy;
    }

}

void LEIC::checkRequest() {
    auto action = requestsQueue.front();
    if (action[0] == "Add Student") {     //{"Add Student", studentNr, newUCCode, newClassCode}
        applyStudentToUC(action[1], action[2], action[3]);
    }
    else if (action[0] == "Remove Student") {
        removeStudentFromUC(action[1], action[2]);
    }
    else if (action[0] == "Switch Student UC") {//{"Switch Student UC", studentNr, prevUCCode, newUCCode, newClassCode}

        switchStudentUC(action[1],action[2],action[3],action[4]);
        //{"Switch Student Class", studentNr, newUCCode, newClassCode}
    }
    else if (action[0] == "Switch Student Class") {

        switchStudentClass(action[1],action[2],action[3]);

    }
    requestsQueue.pop();
}

void LEIC::Consult_requests() {
   auto copyQueue = requestsQueue;

    while (!copyQueue.empty()){
        for (auto a : copyQueue.front()) {
            std::cout << a << " " ;
        }
        copyQueue.pop();
        std::cout << std::endl;
    }
}

/*
 * To keep the changes made along the utilization of this program we would:
 * 1-Store all pending requests in a PendingRequests.txt
 * 2-Store all executed requests in a ExecutedRequests.txt
 * 3-Fill the requests queue with the data in PendingRequests.txt at run
 * 4-Execute all the data present in ExecutedRequests.txt at run
 *
 * This way the application would keep the data between runs.
 *
 * With our apologies, unfortunately this was not possible to achieve in time.*/

