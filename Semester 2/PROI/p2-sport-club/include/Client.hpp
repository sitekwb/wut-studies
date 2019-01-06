//
// Author: Wojciech Sitek
// Date: 03/04/2018
// Tutor: Wiktor Kusmirek
// Subject: PROI

#ifndef PROJECT_TWO_CLIENT_HPP
#define PROJECT_TWO_CLIENT_HPP


#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
#include "Timetable.hpp"
#include "ClientAbs.hpp"

#define NAME_LENGTH 128




template <typename Type>
class Client: public ClientAbs {

    Type name;

    void checkName(std::string &name)const{
        if (name.length() > NAME_LENGTH) {
            name.erase(NAME_LENGTH);
        }
    }

    void checkName(int &name)const{

    }

public:
    Client(Type clientName, std::string m){
        name = clientName;
        mail=m;
        phone=0;
        checkMail(mail);
        checkName(name);
        isTeacher=false;
    }
    Client(Type clientName, unsigned long tel) {
        name = clientName;
        phone=tel;
        mail="";
        checkName(name);
        checkPhone(phone);
        checkMail(mail);
        isTeacher=false;
    }
    Client(Type clientName, std::string m, unsigned long tel){
		name = clientName;
        phone=tel;
        mail=m;
        checkName(name);
        checkMail(mail);
        isTeacher=false;
    }

    virtual std::string getName(){
        return ""+this->name;
    }


    bool operator==(Client const &client){
        return this->name==client.name && this->mail==client.mail && this->phone==client.phone;
    }
    bool operator!=(Client &client){
        return !(this->name==client.name &&
                this->mail==client.mail && this->phone==client.phone);
    }

};


#endif //PROJECT_TWO_CLIENT_HPP
