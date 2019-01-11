//
// Author: Wojciech Sitek
// Date: 09/04/2018
// Tutor: Wiktor Kusmirek
// Subject: PROI
//
#include "../include/Lesson.hpp"
#include <vector>
using namespace std;
Lesson::Lesson(string n,weekDay d, short startHHMM, short finishHHMM){
    name=n;
    time = new Time(d,startHHMM, finishHHMM);
}
Lesson::Lesson(string n, string d, short startHHMM, short finishHHMM){
    name = n;
    time= new Time(d, startHHMM, finishHHMM);
}

Person *Lesson::getTeacher(unsigned which) {
    vector<Person *>::iterator it;
    int i;
    bool isFound=false;
    for (it=people.begin(), i=0; it!=people.end();it++){
        if((*it)->getIsTeacher()){
            if(i!=which){
                i++;
            }
            else{
                isFound=true;
                break;
            }
        }
    }
    if(isFound){
        return *it;
    }
    return nullptr;

}

void Lesson::addPerson(Person &person){
    people.push_back(&person);
}
void Lesson::deletePerson(Person &person){
    vector<Person *>::iterator it;
    for (it=people.begin();it!=people.end()&& **it!=person;it++){}
    if(it!=people.end()){
        people.erase(it);
    }

}

Time *Lesson::getTime(){
    return this->time;
}

void Lesson::changeTime(weekDay dayOfWeek, short startHHMM, short finishHHMM){
    time->setDay(dayOfWeek);
    time->setHour(startHHMM,finishHHMM);
}
void Lesson::setIndividual(bool &isIndividual){

}
string Lesson::getName(){
    return name;
}

bool Lesson::operator==(Lesson & x) {
    return this->time == x.getTime();
}

Lesson::~Lesson(){
    delete time;
}
