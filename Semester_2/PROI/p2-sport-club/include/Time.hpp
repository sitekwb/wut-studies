//
// Author: Wojciech Sitek
// Date: 09/04/2018
// Tutor: Wiktor Kusmirek
// Subject: PROI
//

#ifndef PROJECT_TWO_TIME_HPP
#define PROJECT_TWO_TIME_HPP


#include <string>
enum weekDay{monday, tuesday, wednesday, thursday, friday, saturday, sunday};

class Time {
    weekDay day;
    short startHour; //12:56 = 1256
    short finishHour;
    //startHour<finishHour
    //hour between 0000 and 2359
    void checkHour(short startHHMM, short finishHHMM);
    void checkHour(short startH, short startM,short finishH, short finishM);
    static weekDay convertStringDay(std::string dayOfWeek);
    static std::string convertEnumDay(weekDay day);
public:
    Time();
    Time(weekDay dayOfWeek, short startHHMM, short finishHHMM);
    Time(weekDay dayOfWeek, short startH, short startM, short finishH, short finishM);
    Time(std::string dayOfWeek, short startHHMM, short finishHHMM);
    Time(std::string dayOfWeek, short startH, short startM, short finishH, short finishM);
    ~Time();
    weekDay getDay();
    short getStartHour();
    short getFinishHour();

    std::string toString();
    void setDay(weekDay d);
    void setHour(short startHHMM, short finishHHMM);

    bool operator==(Time & t);//if they have even one minute in common
    bool operator<(Time & t);
    bool operator>(Time & t);
};


#endif //PROJECT_TWO_TIME_HPP
