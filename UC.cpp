//
// Created by duarte on 18-10-2023.
//

#include "UC.h"

UC::UC(const std::string& UCCode) : UCCode_(UCCode){}

void UC::addClass(const std::string& classCode) {
    classes_.emplace(classCode, Class(classCode));
}

void UC::addStudentToClass(const StudentData& studentData, const std::string& classCode) {
    Class& c = getClass(classCode);

    c.addStudent(studentData);
}

Class &UC::getClass(const std::string &classCode) {
    return classes_[classCode];
}

bool UC::hasClass(const std::string &classCode) {
    if (classes_.find(classCode) == classes_.end()) {
        std::cout << "There is no \"" << classCode << "\" in this UC.";
        return false;
    }
    return true;
}

bool UC::hasVacancy(){
    for(auto& classPair : classes_){
        if (classPair.second.getClassStudents().size() < ClassConstants::maxStudents) return true;
    }
    return false;
}

int UC::currentBalance() {
    auto first = *classes_.begin();
    unsigned max = first.second.getClassStudents().size();
    unsigned min = first.second.getClassStudents().size();
    //for (sizet i = 1; i < classes.size(); i++) {
    for (auto classPair : classes_){
        if (classPair.second.getClassStudents().size() > max) {
            max = classPair.second.getClassStudents().size();
        }
        else if (classPair.second.getClassStudents().size() < min) {
            min = classPair.second.getClassStudents().size();
        }
    }

    return (int)(max - min);
}



