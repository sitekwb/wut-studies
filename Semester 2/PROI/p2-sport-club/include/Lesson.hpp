//
// Author: Wojciech Sitek
// Date: 07/04/2018
// Tutor: Wiktor Kusmirek
// Subject: PROI
//

#ifndef PROJECT_TWO_LESSON_HPP
#define PROJECT_TWO_LESSON_HPP

#include <iostream>
#include <vector>
#include "Time.hpp"
#include "Person.hpp"

//class Lesson: Time(weekDay, startH, finH) Teacher, array of Client
class Lesson{
    std::string name;
    Time *time;
    std::vector<Person *> people;
public:
    Lesson(std::string name, weekDay day, short startHHMM, short finishHHMM);
    Lesson(std::string name, std::string day, short startHHMM, short finishHHMM);
    Person *getTeacher(unsigned which=0);
    void addPerson(Person &person);
    void deletePerson(Person &person);
    Time *getTime();
    void changeTime(weekDay dayOfWeek, short startHHMM, short finishHHMM);
    std::string getName();
    void setIndividual(bool &isIndividual);
    std::string getMail();
    std::string getPhone();
    bool operator==(Lesson & x);
    ~Lesson();
};

#endif //PROJECT_TWO_LESSON_HPP
