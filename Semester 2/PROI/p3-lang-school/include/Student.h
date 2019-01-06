#ifndef STUDENT_H
#define STUDENT_H

#include "../include/StudentBase.h"

#include <string>
#include <iostream>
#include <iomanip>


template <typename T> class Student : public StudentBase
{
    T name; //either an int(index number) or a string(name and surname)
public:

    Student(int i, T x,int y, int gr, std::string lang):StudentBase(i, y, gr, lang), name(x) {};

    void print(std::ostream &str=std::cout) const //print data about the student
    {
        str << std::setw(3) << std::right << id << "|| " << std::setw(30) << std::left << name << " || " << std::setw(3) << age << " || ";
        str << std::setw(15) << std::left << language << " || " << group << std::endl;
    }

};

#endif // STUDENT_H
