//
// Created by duarte on 18-10-2023.
//
#include <string>
#include <map>
#include <vector>
#include "Class.h"
#ifndef AED_PROJECT_UC_H
#define AED_PROJECT_UC_H

namespace UCConstants {
    const unsigned int MAX_BALANCE = 4;
}

class UC {

private:
    std::string UCCode_; /**@param UCCode_ represents the code of an UC */

    std::map<std::string , Class> classes_; /**@param classes_ represents all the classes that belong to the UC*/

public:
    UC() = default;
    UC(const std::string& UCCode);

    /**Accessors*/
    std::string& getUCcode(){return UCCode_;}
    Class& getClass(const std::string& classCode);
    auto& getClasses(){return classes_;}

    /**Check*/
    bool hasClass(const std::string& classCode);

    /**UC management*/
    void addStudentToClass( const StudentData& studentData, const std::string& classCode);
    void addClass(const std::string& classCode);

    bool hasVacancy();
    int currentBalance();
};


#endif //AED_PROJECT_UC_H
