//
// Created by Wojciech Sitek on 14/12/2018.
//

#ifndef MONITORS_PRODUCER_H
#define MONITORS_PRODUCER_H

#include "Person.hpp"

class Producer : public Person{
public:
    Producer(const int jump_, char letterName_, int sleepTime_);

    void action();
private:
    Letter currentLetter;
};


#endif //MONITORS_PRODUCER_H
