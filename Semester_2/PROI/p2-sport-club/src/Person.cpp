//
// Created by wojtek on 15.04.18.
//
#include "../include/Person.hpp"
#include <string>

using namespace std;
bool Person::isPhone(unsigned long &phone){
    if(phone<100000000 || phone>999999999) {
        return false;
    }
    return true;
}

void Person::checkPhone(unsigned long &phone){
    if(!isPhone(phone)){
        phone = 0;
    }
}
bool Person::isMailCharacter(char & c) {
    return (c>='0'||c<='9') || (c>='A'&&c<='Z') || (c>='a'&&c<='z') || c=='.';
}

bool Person::isMail(string &mail){
    bool isAt=false;
    for (string::iterator it = mail.begin(); it!=mail.end();it++ ){
        if(*it=='@'){
            if(it==mail.begin()){//no characters before

            }
            if(isAt){//there was @ before
                return false;
            }
            isAt=true;
        }
        if(!isMailCharacter(*it)){
            return false;
        }
    }
    return true;
}

void Person::checkMail(string &mail ) {
    if(!isMail(mail)){
        mail.clear();
        mail="";
        return ;
    }

}


string Person::getMail(){
    return mail;
}
string Person::getPhone(){
    return to_string(phone);
}
bool Person::getIsTeacher(){
    return isTeacher;
}

bool Person::operator==(Person &person){
    return this->mail==person.getMail() && this->getPhone()==person.getPhone();
}
bool Person::operator!=(Person &person){
    return !( this->mail==person.getMail() && this->getPhone()==person.getPhone() );
}