//
// Created by duarte on 10-10-2023.
//

#ifndef AED_PROJECT_STUDENT_H
#define AED_PROJECT_STUDENT_H

#include <string>
#include <list>
#include <iostream>

namespace Schedule {

};
namespace StudentConstants{
    const unsigned int maxUCs = 7; /**@param maxUCs represents the maximum number of UCs a student can be into*/
}

struct StudentData {
    std::string name;/**student name*/
    std::string studentNr;/**student number*/

    /**@brief Function that prints the informations of a Student*/
    void print() const {
        std::cout<<"Name: "<< name <<"\nNumber: "<< studentNr << "\n===========" << std::endl;
    }
    bool operator<(const StudentData& other) const {
        if (name == other.name) {
            return studentNr < other.studentNr;
        }
        return name < other.name;
    }
    bool operator==(const StudentData& other) const {
        return (name == other.name) && (studentNr == other.studentNr);
    }
};

/**@brief Struct that defines the class of a Student inside of an UC*/
struct enrolment {
    std::string UCcode;
    std::string classCode;

    /**@brief Function that prints the UC and respective class that a student is enrolled in*/
    void print() const {
        std::cout << UCcode << " : " << classCode << std::endl;
    }
};

class Student {
private:
    StudentData data_; /**@param data_ represents the name and number of a student*/
    std::list<enrolment> studentUCs_; /**@param studentUCs_ represents the classes (of each UC) that a student is enrolled in*/

public:
    Student() = default;
    Student(const std::string& name, const std::string& studentNr);

    /**Accessors*/
    const StudentData& getData() const;
    const std::string& getName() const;
    const std::string& getStudentNr() const;
    const std::list<enrolment>& getStudentUCs() const;
    //const ClassSchedule::Schedule getSchedule() const;


    void addUC(const std::string& UCCode, const std::string& classCode);
    void removeUC(const std::string& UCCode);
    bool canApplyToUC(const std::string& UCCode);

    /**Compare operator*/
    bool operator<(Student& student){return data_ < student.data_;}
    /** Copy assignment operator*/
    Student& operator=(const Student& other) {
        if (this != &other) {
            data_.studentNr = other.data_.studentNr;
            data_.name = other.data_.name;
            studentUCs_ = other.studentUCs_;

        }
        return *this;
    }

};



#endif //AED_PROJECT_STUDENT_H

