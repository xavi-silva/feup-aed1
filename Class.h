//
// Created by Migas on 10/10/2023.
//




#ifndef AED_PROJECT_CLASS_H
#define AED_PROJECT_CLASS_H

#include <string>
#include <map>
#include <unordered_map>
#include <set>
#include <iostream>
#include <queue>
#include "Student.h"

/**
 * @brief struct that represents an event in the schedule
 */
namespace ClassSchedule {
    struct event {
        std::string type;/**Type of the event*/
        std::string weekDay;/**Weekday of the event*/
        float sTime;/**Starting time of the event*/
        float duration;/**Duration of the event*/
        std::string UCCode;/**Code of the UC which has the event*/

        float getETime() const {return sTime + duration;}/**@return End time of the event*/

        bool operator<(const event& other) const {
            return sTime < other.sTime;
        }

        bool conflictsWith(const event& other) const{
            /** Check if this event ends before the other event starts or
             if this event starts after the other event ends, they don't conflict.*/
            if (weekDay != other.weekDay or getETime() <= other.sTime or sTime >= other.getETime()) {
                return false;
            }
            /** Otherwise, they conflict.*/
            return true;
        }
    };

    /**@brief vector with the days of the week*/
    const std::vector<std::string> daysOfWeek = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

    /**@brief struct that represents the schedule*/
    struct Schedule{
    std::unordered_map<std::string, std::set<event>> schedule{
            {"Monday", std::set<event>()},
            {"Tuesday", std::set<event>()},
            {"Wednesday", std::set<event>()},
            {"Thursday", std::set<event>()},
            {"Friday", std::set<event>()},
            {"Saturday", std::set<event>()},
            {"Sunday", std::set<event>()}

    };


    void addEvent(const std::vector<event>& events) {
        for (const event& e : events) {
            schedule[e.weekDay].insert(e);
        }
    }

        /**@brief Function that prints the schedule*/
    void print() const {

        for (const auto& day : daysOfWeek) {

            std::cout << day << ":\n" << "=======\n";
            for (const auto& e : schedule.at(day)) {
                std::cout << "  " << e.UCCode << ": " << e.type << "\n";
                std::cout << "  Start Time: " << e.sTime << " - End Time: " << e.getETime() << "\n";
                std::cout << "  Duration: " << e.duration << "\n";
                std::cout << "=======\n";
            }
        }
    }

        /**@brief Checks if any of the events in the vector conflict with each-other*/
        bool conflictsWith(const std::vector<event>& events) {
            for (const event& newEvent : events) {
                const std::string& day = newEvent.weekDay;
                const std::set<event>& eventsOnDay = schedule[day];
                if (newEvent.type == "T"){
                    continue;
                }

                for (const event& existingEvent : eventsOnDay) {
                    if (existingEvent.type == "T" or existingEvent.UCCode == newEvent.UCCode){
                        continue;
                    }
                    if (existingEvent.conflictsWith(newEvent)) {
                        std::cout << "The New Class Schedule Conflicts With Your Current Schedule (" << existingEvent.UCCode << ")" << std::endl;
                        return true;  /**@brief Found a conflict with an existing event on the same day.*/
                    }
                }
            }

            return false;  /** No conflicts were found.*/
        }
};

}
/**@param maxStudents represents the maximum number of students per class */
namespace ClassConstants {
    const unsigned int maxStudents = 26;
}
class Class {
private:

    const std::string classCode;
    std::set<StudentData> studentSet;/**@param studentSet represents the students in a class*/
    std::queue<StudentData> waitingQueue;
    std::vector<ClassSchedule::event> classEvents;


public:
    Class() = default;
    Class(const std::string& classCode);

    /**Accessors*/
    const std::string& getClassCode() const;
    const std::set<StudentData>& getClassStudents() const;
    const char getClassYear();
    const std::vector<ClassSchedule::event>& getClassEvents() const;
    const ClassSchedule::Schedule getClassSchedule();



    /**Event management*/
    void addEvent(const ClassSchedule::event& event);

    /**Student management*/
    void addStudentToQueue(const StudentData& studentData);
    void addStudent(const StudentData& studentData);
    void removeStudent(StudentData studentData);
    bool hasStudent(const std::string& studentNr);
    bool isFull();
};


#endif //AED_PROJECT_CLASS_H



