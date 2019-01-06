//
// Author: Wojciech Sitek
// Date: 07/04/2018
// Tutor: Wiktor Kusmirek
// Subject: PROI
//

#include "../include/Timetable.hpp"

using namespace std;
Timetable::Timetable(){

}

bool Timetable::addLesson(Lesson &lesson){
    bool flag=true;
    vector<Lesson>::iterator it;
    for(it=courses.begin(); !((*it).getTime() > lesson.getTime() || it==courses.end() );it++ ){
        if((*it).getTime() == lesson.getTime() ){
            flag=false;
            break;//someone is just busy
        }
    }
    if(flag) {
        courses.insert(it, lesson);
        return false;
    }
    return true;
}

void Timetable::deleteLesson(Lesson &lesson) {
    vector<Lesson>::iterator it;
    for(it=courses.begin(); it!=courses.end();it++){
        if(*it==lesson){
            courses.erase(it);
            break;
        }
    }
}
void Timetable::clearTimetable() {
    courses.clear();
}


std::vector<Lesson> *Timetable::getCoursesPtr(){
    return &courses;
}