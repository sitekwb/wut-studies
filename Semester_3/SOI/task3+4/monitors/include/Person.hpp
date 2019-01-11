
//
// Created by Wojciech Sitek on 11/12/2018.
//

#ifndef MONITORS_PERSON_H
#define MONITORS_PERSON_H

#include <string>

#include "Buffer.hpp"
#include "Letter.hpp"

#define BUFFERS_NUM             1
#define CONDITIONS_NUM          2
#define MIN_LETTERS_TO_CONSUME  3


extern Condition *full, *empty;
extern Buffer *buffer;
extern Monitor *monitor;
extern char *tab;
extern int *tabsize;




class Person{
public:
    Person(const int &jump_, char functionName_, char letterName_, int sleepTime_)
    : jump(jump_), functionName(functionName_), letterName(letterName_), sleepTime(sleepTime_){}

    int getJump();
    char getFunction();
    char getLetterName();
    virtual void action() = 0;


protected:
    int sleepTime;
    int jump;
    char functionName, letterName;
};

#endif //MONITORS_PERSON_H
