#ifndef UI_H
#define UI_H
#include "School.h"


class UI
{
    int id = 1; //every students gets an unique id number
    int worker_id = 1;
    int index = 290000; // nameless students get index number instead
    School language_school;

    public:
    void addWorker();
    void printWorkers();
    void printMenu();
    void printStudents();
    void addStudent();
    void deleteStudent();
    void changeLanguage(); //every student with an old language gets a new one
    void increaseAge(); //increases age of everyone by 1
    void changeGroup(); //changes group of a chosen student


};

#endif // UI_H
