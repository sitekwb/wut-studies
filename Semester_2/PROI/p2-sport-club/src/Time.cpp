//
// Author: Wojciech Sitek
// Date: 09/04/2018
// Tutor: Wiktor Kusmirek
// Subject: PROI
//
#include <iostream>
#include <string>
#include "../include/Time.hpp"

using namespace std;

void Time::checkHour(short startH, short startM,short finishH, short finishM){
    if(startH<0 || startH>23 || finishH<0 || finishH>23 ||
       startM>59 || finishM>59 ||
       !(startH<finishH || (startH==finishH&&startM<finishM)) ){
        startHour=800;
        finishHour=900;
    }
    else{
        startHour=startH*100+startM;
        finishHour=finishH*100+finishM;
    }
}
void Time::checkHour(short startHHMM, short finishHHMM){
    short startH = startHHMM/100;
    short finishH = finishHHMM/100;

    short startM = startHHMM%100;
    short finishM = finishHHMM%100;
    checkHour(startH,startM,finishH,finishM);
}
weekDay Time::convertStringDay(string dayOfWeek){

    if(dayOfWeek.compare("tuesday")==0 ||dayOfWeek=="Tuesday" || dayOfWeek.compare("tu")==0){
        return tuesday;
    }
    else if(dayOfWeek.compare("wednesday")==0 ||dayOfWeek.compare("Wednesday")==0|| dayOfWeek.compare("w")==0){
        return wednesday;
    }
    else if(dayOfWeek.compare("thursday")==0 ||dayOfWeek.compare("Thursday")==0 || dayOfWeek.compare("th")==0){
        return thursday;
    }
    else if(dayOfWeek.compare("friday")==0 ||dayOfWeek.compare("Friday")==0|| dayOfWeek.compare("f")==0){
        return friday;
    }
    else if(dayOfWeek.compare("saturday")==0 ||dayOfWeek.compare("Saturday")==0 || dayOfWeek.compare("sa")==0){
        return saturday;
    }
    else if(dayOfWeek.compare("sunday")==0 ||dayOfWeek.compare("Sunday")==0 || dayOfWeek.compare("su")==0){
        return sunday;
    }
    return monday;

}

Time::Time() :day(monday),startHour(800), finishHour(900){ }

Time::Time(weekDay dayOfWeek, short startHHMM, short finishHHMM)
        :day(dayOfWeek){
    short startH = startHHMM/100;
    short finishH = finishHHMM/100;

    short startM = startHHMM%100;
    short finishM = finishHHMM%100;
    checkHour(startH,startM,finishH,finishM);

}
Time::Time(weekDay dayOfWeek, short startH, short startM, short finishH, short finishM)
        :day(dayOfWeek){
    this->checkHour(startH,startM,finishH,finishM);
}

Time::Time(std::string dayOfWeek, short startHHMM, short finishHHMM){
   	Time a(convertStringDay(dayOfWeek),startHHMM,finishHHMM);
	*this = a;
}
Time::Time(std::string dayOfWeek, short startH, short startM, short finishH, short finishM){
	Time a(convertStringDay(dayOfWeek),startH,startM,finishH,finishM);
	*this = a;
}


weekDay Time::getDay(){
    return this->day;
};
short Time::getStartHour(){
    return this->startHour;
}
short Time::getFinishHour(){
    return this->finishHour;
}

void Time::setDay(weekDay d){
    day=d;
}
void Time::setHour(short startHHMM, short finishHHMM){
    startHour=startHHMM;
    finishHour=finishHHMM;
    checkHour(startHHMM,finishHHMM);
}

std::string Time::convertEnumDay(weekDay d){
    switch(d){
        case monday: return "Monday";
        case tuesday: return "Tuesday";
        case wednesday: return "Wednesday";
        case thursday: return "Thursday";
        case friday: return "Firday";
        case saturday: return "Saturday";
        case sunday: default: return "Sunday";
    }
}

std::string Time::toString(){
	int hour = startHour/100;
	int minute = startHour%100;
    string startH = to_string(hour)+":"+to_string(minute);
    hour = finishHour/100;
	minute = finishHour%100;
    string finishH = to_string(hour)+":"+to_string(minute);
    return convertEnumDay(day)+", "+startH+" - "+finishH;
}


bool Time::operator==(Time & t){
    short s1 = t.getStartHour();
    short f1 = t.getFinishHour();
    return ( this->day==t.getDay() ) &&
           ( (this->startHour >= s1 && this->startHour <= f1 ) || (s1 >= this->startHour && s1 <= this->finishHour) );
}

bool Time::operator<(Time & t){
    return (this->day < t.getDay() ) || ( this->day == t.getDay() && this->finishHour<t.getStartHour() );
}

bool Time::operator>(Time & t){
    return (this->day > t.getDay() ) || ( this->day == t.getDay() && this->startHour > t.getFinishHour() );
}


Time::~Time(){

}
