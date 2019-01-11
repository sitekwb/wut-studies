//
// Created by wojtek on 22.05.18.
//

#ifndef PROJECT_TWO_WORKER_HPP
#define PROJECT_TWO_WORKER_HPP

#include <string>

class Worker{
protected:
    int id;
    std::string name;
    int salary;
public:
    virtual void print()=0;
    int getId();
    static void printHeader();
    virtual std::string getLang()=0;

};


#endif //PROJECT_TWO_WORKER_HPP
