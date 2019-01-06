//
// Author: Wojciech Sitek
// Date: 07/04/2018
// Tutor: Wiktor Kusmirek
// Subject: PROI
//

#ifndef PROJECT_TWO_CLIENTABS_HPP
#define PROJECT_TWO_CLIENTABS_HPP
#include "Timetable.hpp"


class ClientAbs: public Person{
protected:
    Timetable timetable;
public:
    Timetable *getTimetablePtr();
    virtual void checkName(std::string &name)const=0;
    virtual std::string getName()=0;
};

#endif //PROJECT_TWO_CLIENTABS_HPP
