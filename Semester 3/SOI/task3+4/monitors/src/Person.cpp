
//
// Created by Wojciech Sitek on 11/12/2018.
//

#include "Person.hpp"


Buffer *buffer;
Condition *full, *empty;
Monitor *monitor;
char *tab;
int *tabsize;

using namespace std;

int Person::getJump(){
    return jump;
}
char Person::getFunction(){
    return functionName;
}
char Person::getLetterName(){
    return letterName;
}

