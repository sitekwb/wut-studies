#ifndef SCHOOL_H
#define SCHOOL_H

#include "../include/StudentBase.h"
#include "Student.h"
#include "InputException.hpp"
#include "Worker.hpp"
#include "Teacher.hpp"

#include <vector>
#include <iostream>
#include <string>
#include <typeinfo>

class School
{
    std::vector<StudentBase*> studentsVector; //vector containing pointers to Student<int> and Student<std::string>
    std::vector<Worker *> workers;
    public:

    void printStudents(std::ostream &str=std::cout);
    void printWorkers();
    template<typename T> void addStudent(int id, T name, int age, int gr, std::string language) //template function, students can be added with name or index number
    {
        if(id < ((studentsVector.empty())?0:(studentsVector.back()->getID())) || age>999 || age<0
                || gr<0 || gr>99 || language.length()>15){
            throw InputException(longish);
        }
        if(studentsVector.size()==99){
            throw InputException(vectorSize);
        }
        Student<T>* new_student = new Student<T>(id, name, age, gr, language);
        studentsVector.push_back(new_student);
    }
    static bool checklength(std::string str){
        return str.length()<=30;
    }
    void deleteStudent(int id);
    void changeData(int id, int gr);
    void changeData(std::string lang, std::string newlang);

    Teacher *addTeacher(int id, std::string name, int salary, std::string language);
    void addAdmWorker(int id, std::string name, int salary, int startYear);

    virtual ~School();
    School& operator++(); //operator overload - increases age of everyone by 1

};

#endif // SCHOOL_H
