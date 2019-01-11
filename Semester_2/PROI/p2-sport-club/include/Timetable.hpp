//
// Author: Wojciech Sitek
// Date: 07/04/2018
// Tutor: Wiktor Kusmirek
// Subject: PROI
//

#ifndef PROJECT_TWO_TIMETABLE_HPP
#define PROJECT_TWO_TIMETABLE_HPP
#include <vector>
#include "Lesson.hpp"

class Timetable{
    std::vector<Lesson>courses;
public:
    Timetable();
    bool addLesson(Lesson &lesson);
    void deleteLesson(Lesson &lesson);
    std::vector<Lesson> *getCoursesPtr();
    void clearTimetable();
};

#endif //PROJECT_TWO_TIMETABLE_HPP
