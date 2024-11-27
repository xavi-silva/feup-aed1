//
// Created by duarte on 10-10-2023.
//

#include "Student.h"
//Constructor
Student::Student(const std::string &name, const std::string &studentNr) {
    data_.name = name;
    data_.studentNr = studentNr;

}

/**Accessors*/
const StudentData &Student::getData() const {
    return data_;
}
const std::string &Student::getName() const {
    return data_.name;
}

const std::string& Student::getStudentNr() const {
    return data_.studentNr;
}
const std::list<enrolment>& Student::getStudentUCs() const {
    return studentUCs_;
}



/**UC management*/
void Student::addUC(const std::string &UCCode, const std::string& classCode) {

    studentUCs_.push_back({UCCode, classCode});

}
void Student::removeUC(const std::string& UCCode){
    auto it = studentUCs_.begin();

    while (it != studentUCs_.end()) {
        if (it->UCcode == UCCode) {
            it = studentUCs_.erase(it); /** Erase the element and advance the iterator*/
        } else {
            ++it;
        }
    }
}
bool Student::canApplyToUC(const std::string &UCCode) {
    return studentUCs_.size() < StudentConstants::maxUCs;
}


