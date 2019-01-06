//
// Created by Wojciech Sitek on 14/12/2018.
//

#ifndef MONITORS_CONSUMER_H
#define MONITORS_CONSUMER_H

#include "Person.hpp"

class Consumer : public Person{
public:
    Consumer(const int &&jump_, char &&letterName_, int sleepTime_)
            : Person(jump_, '-', letterName_, sleepTime_){}

    void action();
};



#endif //MONITORS_CONSUMER_H
