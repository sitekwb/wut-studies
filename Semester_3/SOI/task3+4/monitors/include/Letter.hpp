//
// Created by Wojciech Sitek on 14/12/2018.
//

#ifndef MONITORS_LETTER_H
#define MONITORS_LETTER_H



struct Letter{
    char c;
    Letter(char e) : c(e) {}
    char operator++();
    char operator++(int);
    char operator*();
};



#endif //MONITORS_LETTER_H
