//
// Created by wojtek on 15.04.18.
//

#ifndef PROJECT_TWO_ACTION_HPP
#define PROJECT_TWO_ACTION_HPP

#include "Menu.hpp"
#include "Client.hpp"
#include "Teacher.hpp"
#include <vector>

static const std::string errmessage = "Error occured. Try again.";
enum fieldType{cl,te,le};
class MainAction{
    std::vector<ClientAbs *>clients;
    std::vector<Teacher *>teachers;
    std::vector<Lesson *>lessons;

    static void getMail(std::string &mail, bool &qFlag, bool &mailFlag);
    static void getPhone(unsigned long &phone, bool &qFlag, bool &phoneFlag, bool const & mailFlag);
    template <class T, fieldType A>static std::string getField(int n, T &object);
public:
    MainAction();
    void newClient();
    void newTeacher();
    void newLesson();
    std::vector<ClientAbs *> *getClientsPtr();
    std::vector<Teacher *> *getTeachersPtr();
    std::vector<Lesson *> *getLessonPtr();

    Teacher *findTeacher();
    Lesson *findLesson();
    ClientAbs *findClient();

    void loadTestData();
    ~MainAction();
};


#endif //PROJECT_TWO_ACTION_HPP
