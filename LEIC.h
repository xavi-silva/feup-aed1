//
// Created by duarte on 15-10-2023.
//

#ifndef AED_PROJECT_LEIC_H
#define AED_PROJECT_LEIC_H

#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>

#include "UC.h"
#include "Class.h"
#include "Student.h"
/**
 * @class LEIC
 * @brief This class represents the LEIC system.
 */
class LEIC {

private:

    std::map<std::string , Student> students_;/**< Map of students */
    std::map<std::string, UC> UCs_;/**< Map of UCs */
    std::stack<std::vector<std::string>> undoStack;/**< Undo stack for actions */
    std::queue<std::vector<std::string>> requestsQueue;

public:
    /**
 * @brief Constructor for LEIC class.
 * @param UCsPath Path for UCs data.
 * @param studentsClassesPath Path for students' classes data.
 * @param classesPath Path for classes data.
 */
    LEIC(const std::string& UCsPath, const std::string& studentsClassesPath, const std::string& classesPath);


private:
    /**Accessors*/
    Student& getStudent(const std::string& studentNumber);
    UC& getUC(const std::string& UCcode);

    /**Parse*/
    /**@brief Functions that parse all the information contained in the text files*/
    void parseUCs(const std::string& UCsPath);
    void parseStudentsClasses(const std::string& studentsClassesPath);
    void parseSchedules(const std::string& schedulesPath);
    void addStudentToUCParser(const std::string &studentNr, const std::string &UCCode, const std::string &classCode);

    /**LEIC management*/
    void addStudent(const std::string& name, const std::string& studentNr);
    void addUC(const std::string& UCCode);
    void addClassToUc(const std::string& classCode, const std::string& UCCode);
    void addStudentToUC(const std::string &studentNr, const std::string& UCCode, const std::string& classCode);

    /**Check*/
    bool hasUC(const std::string& UCCode);
    bool hasStudent(const std::string& studentNr);




public:
    /**Consult Functions*/

    void ConsultDataInLEICMenu();
    void consultCourseStudentsByEnrollment();
    void consultCourseStudentsByName();
    void consultDataInYearMenu();
    void Consult_yearStudents(char year);/**@return All the students within a given year*/
    void Consult_yearOccupation(char year);/**@return The occupation by students of a given year*/
    void consultDataInUCsMenu();
    void listUCs();
    void Consult_UCStudents(const std::string& UCcode);/**@return All the students within a given UC*/
    void Consult_StudentsInNuc(int n);/**@return The number of students enrolled in at least a given number*/
    void Consult_UCoccupation(const std::string& UCcode);/**@return The occupation by students of a given UC*/
    void Consult_maxStudentUC(char year);/**@return The UCs that have the most number of enrolled students within a given year*/
    void Consult_UCAvailability(const std::string& ucCode);
    void consultDataInClassesMenu();
    void Consult_classSchedule(const std::string& ucCode, const std::string& classCode);/**@return The schedule of a given class*/
    void Consult_classOccupation(const std::string& ucCode, const std::string& classCode);/**@return The occupation by students of a given class*/
    void Consult_classStudents(const std::string& UCCode, const std::string& classCode);/**@return All the students within a given class*/
    void consultDataInStudentMenu();
    void Consult_studentUCs(const std::string& studentNumber);/**@return All the UCs that a given student is enrolled in*/
    void Consult_studentSchedule( std::string& studentNumber);/**@return The schedule of a given student*/


    void manageStudentsMenu();
    void applyStudentToUC(const std::string &studentNr, const std::string& UCCode, const std::string& classCode);
    void removeStudentFromUC(const std::string& studentNr, const std::string& UCCode);
    void switchStudentUC(const std::string& studentNr, const std::string& previousUC, const std::string& newUC, const std::string& newClass);
    void switchStudentClass(const std::string& studentNr, const std::string& UCCode, const std::string& newClass);
    bool canStudentApplyToUC(const std::string& UCCode, const std::string& studentNr);
    bool canStudentApplyToClass(const std::string& studentNr, const std::string& classCode, const std::string& UCCode);
    Class& findStudentClass(const std::string& studentNr, const std::string& ucCode);
    bool classHasStudent(const std::string& studentNr, const std::string& ucCode, const std::string& classCode);
    bool ucHasStudent(std::string studentNr, std::string ucCode);
    ClassSchedule::Schedule getStudentSchedule(const std::string& studentNr);

    void undoMenu();
    void undo();
    void revertAll();
    void clearStack();

    void processRequestMenu();
    void checkRequest();
    void Consult_requests();

};



#endif //AED_PROJECT_LEIC_H
