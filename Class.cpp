//
// Created by Migas on 10/10/2023.
//

#include "Class.h"

/**Constructor*/
Class::Class(const std::string& classCode)
        : classCode(classCode){}


/** Accessor definitions*/

const std::string& Class::getClassCode() const {
    return classCode;
}

const std::set<StudentData>& Class::getClassStudents() const{
    return studentSet;
}

const char Class::getClassYear() {
    return classCode[0];
}

const ClassSchedule::Schedule Class::getClassSchedule() {
    ClassSchedule::Schedule s;
    s.addEvent(classEvents);
    return s;
}

const std::vector<ClassSchedule::event> &Class::getClassEvents() const {
    return classEvents;
}




/**Event management*/

void Class::addEvent(const ClassSchedule::event& event) {
    classEvents.push_back(event);
}

/**Student management*/
void Class::addStudent(const StudentData& studentData) {
    studentSet.insert(studentData);
}

void Class::removeStudent(StudentData studentData) {
    auto it = studentSet.find(studentData);
    if (it != studentSet.end()) {
        studentSet.erase(it);
    }
}

bool Class::isFull() {

    if(studentSet.size() >= ClassConstants::maxStudents) {
        std::cout << classCode << " is Full!" << std::endl;
        return true;
    };
    return false;
}

bool Class::hasStudent(const std::string& studentNr){

    for (StudentData student : studentSet){
        if (student.studentNr == studentNr) return true;
    }
    return false;
}








