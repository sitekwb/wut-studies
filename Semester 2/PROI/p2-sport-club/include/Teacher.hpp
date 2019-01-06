//
// Created by wojtek on 15.04.18.
//

#ifndef PROJECT_TWO_TEACHER_HPP
#define PROJECT_TWO_TEACHER_HPP

#include "Person.hpp"
#include "Timetable.hpp"

#include <string>

class Teacher: public Person{
    std::string name;
    Timetable timetable;
    void checkName (std::string &name)const;
public:
    Teacher(std::string tName, std::string tMail);
    Teacher(std::string tName, unsigned long tel);
    Teacher(std::string tName, std::string m, unsigned long tel);
    Timetable *getTimetablePtr();
    std::string getName();

};
#endif //PROJECT_TWO_TEACHER_HPP
