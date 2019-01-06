//
// Created by wojtek on 15.04.18.
//

#include <iostream>
#include <iomanip>

#include "../include/MainAction.hpp"

#define NAME_LENGTH 128

using namespace std;

MainAction::MainAction(){

}

void MainAction::getMail(string &mail, bool &qFlag, bool &mailFlag){
    while(true){
        cout<<"Enter 'q' to proceed to main menu."<<endl;
        cout<<"Enter client's mail ('w' to omit mail): ";
        cin>>mail;
        if(!cin){
            cin.clear();
            cin.ignore(1000,'\n');
            mail.clear();
            cout<<errmessage<<endl;
            continue;
        }
        if(mail=="q"){
            qFlag=true;
            break;
        }
        if(mail=="w"){
            mailFlag=false;
            break;
        }

        break;
    }
}

void MainAction::getPhone(unsigned long &phone, bool &qFlag, bool &phoneFlag, bool const & mailFlag){
    while(true){
        cout<<"Enter '0' to proceed to main menu."<<endl;
        if(mailFlag) {//we doesn't need phone
            cout << "Enter client's phone, numbers only ('1' to omit phone): ";
        }
        else{//we need some contact
            cout<< "Enter client's phone (numbers only): ";
        }
        cin>>phone;
        if(!cin){
            cin.clear();
            cin.ignore(1000,'\n');
            cout<<errmessage<<endl;
            continue;
        }
        if(phone==0){//main menu
            qFlag=true;
            break;
        }
        if(phone==1&&mailFlag){//omit
            phoneFlag=false;
            break;
        }
        break;
    }
}

void MainAction::newClient() {
    bool qFlag=false;
    string name;
    int id=0;
    bool IDFlag;

    //get client's name from user
    while(true){
        IDFlag=true;
        cout<<"Enter 'q' to proceed to main menu."<<endl;
        cout<<"Enter client's name or ID (max. 5 numbers): ";
        cin>>name;
        if(name=="q"){
            cout<<"Aborted!"<<endl;
            return ;
        }
        for(string::iterator it=name.begin();it!=name.end();it++){
            if(!isdigit(*it)){
                IDFlag=false;
                break;
            }
        }

        if(!cin || name.size()>NAME_LENGTH ){
            cin.clear();
            cin.ignore(1000,'\n');
            name.clear();
            cout<<errmessage<<endl;
            continue;
        }
        if(IDFlag){
            id=stoi(name);
        }
        break;
    }

    //get client's mail
    bool mailFlag=true;
    string mail;
    getMail(mail,qFlag,mailFlag);
    if(qFlag){
        cout<<"Aborted!"<<endl;
        return ;
    }

    //get client's phone
    bool phoneFlag=true;
    unsigned long phone;
    getPhone(phone, qFlag, phoneFlag, mailFlag);
    if(qFlag){
        cout<<"Aborted!"<<endl;
        return ;
    }
    //add client
    if(IDFlag&&mailFlag&&phoneFlag) {
        clients.push_back(new Client<int>(id, mail, phone));
    }
    else if(IDFlag&&mailFlag) {
        clients.push_back(new Client<int>(id,mail));
    }
    else if(IDFlag&&phoneFlag){
        clients.push_back(new Client<int>(id,phone));
    }
    else if(mailFlag&&phoneFlag) {
        clients.push_back(new Client<string>(name, mail, phone));
    }
    else if(mailFlag) {
        clients.push_back(new Client<string>(name, mail));
    }
    else {
        clients.push_back(new Client<string>(name,phone));
    }
    cout<<"Client added with success."<<endl;
}

void MainAction::newTeacher(){
    string name;
    bool qFlag=false;
    //get teacher's name from user
    while(true){
        cout<<"Enter 'q' to proceed to main menu."<<endl;
        cout<<"Enter teacher's name: ";
        cin>>name;
        if(name=="q"){
            cout<<"Aborted!"<<endl;
            return ;
        }

        if(!cin || name.size()>NAME_LENGTH ){
            cin.clear();
            cin.ignore(1000,'\n');
            name.clear();
            cout<<errmessage<<endl;
            continue;
        }
        break;
    }
    //get client's mail
    bool mailFlag=true;
    string mail;
    getMail(mail,qFlag,mailFlag);
    if(qFlag){
        cout<<"Aborted!"<<endl;
        return ;
    }

    //get client's phone
    bool phoneFlag=true;
    unsigned long phone;
    getPhone(phone,qFlag,phoneFlag,mailFlag);
    if(qFlag){
        cout<<"Aborted!"<<endl;
        return ;
    }
    //add teacher
    teachers.push_back(new Teacher(name, mail, phone));
    cout<<"Teacher added with success."<<endl;
}

void MainAction::newLesson(){
    string name;
    //get lesson's name from user
    while(true){
        cout<<"Enter 'q' to proceed to main menu."<<endl;
        cout<<"Enter lesson's name: ";
        cin>>name;
        if(name=="q"){
            cout<<"Aborted!"<<endl;
            return ;
        }

        if(!cin || name.size()>NAME_LENGTH ){
            cin.clear();
            cin.ignore(1000,'\n');
            name.clear();
            cout<<errmessage<<endl;
            continue;
        }
        break;
    }
    //get day
    Menu dayMenu("Day of the week", "When is the lesson?");
    dayMenu.addOption("Monday");
    dayMenu.addOption("Tuesday");
    dayMenu.addOption("Wednesday");
    dayMenu.addOption("Thursday");
    dayMenu.addOption("Friday");
    dayMenu.addOption("Saturday");
    dayMenu.addOption("Sunday");
    dayMenu.addOption("Exit to main menu.");
    int a = dayMenu.show();
    if(a==7){
        return ;
    }
    weekDay d = static_cast<weekDay>(a);
    //get start hour
    short startHHMM;
    while(true){
        cout<<"Enter '0' to proceed to main menu."<<endl;
        cout<<"Enter start hour of lesson (format HHMM): ";
        cin>>startHHMM;
        if(startHHMM==0){
            cout<<"Aborted!"<<endl;
            return ;
        }

        if(!cin || startHHMM/100 >23 || startHHMM%100 > 59 || startHHMM>=2359){
            cin.clear();
            cin.ignore(1000,'\n');
            name.clear();
            cout<<errmessage<<endl;
            continue;
        }
        break;
    }
    //get finish hour
    short finishHHMM;
    while(true){
        cout<<"Enter '0' to proceed to main menu."<<endl;
        cout<<"Enter finish hour of lesson (format HHMM): ";
        cin>>finishHHMM;
        if(finishHHMM==0){
            cout<<"Aborted!"<<endl;
            return ;
        }

        if(!cin || finishHHMM/100 >23 || finishHHMM%100 > 59 || finishHHMM <= startHHMM){
            cin.clear();
            cin.ignore(1000,'\n');
            name.clear();
            cout<<errmessage<<endl;
            continue;
        }
        break;
    }

    lessons.push_back(new Lesson(name,d, startHHMM,finishHHMM));
    cout<<"Lesson added with success."<<endl;

}

template <class T, fieldType A> string MainAction::getField(int n, T &object){
    switch(A) {
        case cl:
            switch (n) {
                case 0: case 1:
                    return object.getName();
                case 2:
                    return object.getMail();
                case 3: default:
                    return ""+object.getPhone();
            }
        case te:
            switch (n) {
                case 0:
                    return object.getName();
                case 1:
                    return object.getMail();
                case 2: default:
                    return object.getPhone();
            }
        case le:
            return object.getName();
    }
}

Teacher *MainAction::findTeacher() {
    Teacher *found = nullptr;
    Menu fieldMenu("Type of field to search with", "Which field do you want to search with?");
    fieldMenu.addOption("Name");//0
    fieldMenu.addOption("Mail");//1
    fieldMenu.addOption("Phone");//2
    fieldMenu.addOption("Exit to main menu");//3
    auto it= teachers.begin();
    while (true) {
        int a = fieldMenu.show();
        if (a == 3) {
            cout << "Aborted!" << endl;
            return nullptr;
        }

        string field;

        //get field from user
        cout << "Enter 'q' to proceed to main menu." << endl;
        cout << "Enter field sentence: ";
        cin >> field;
        if (field == "q") {
            cout << "Aborted!" << endl;
            return nullptr;
        }

        if (!cin || field.size() > NAME_LENGTH) {
            cin.clear();
            cin.ignore(1000, '\n');
            field.clear();
            cout << errmessage << endl;
            continue;
        }
        bool flag = false;

        for (; it != teachers.end(); it++) {
            if (field.compare(getField<Teacher, te>(a, **it)) == 0) {
                if (flag) {//he was before
                    flag = false;//if he was before or it wasn't at all, then flag will be false
                    break;
                }
                flag = true;
                found = *it;
            }
        }
        if (!flag && it == teachers.end()) {//there wasn't such person
            cout << "There wasn't such person in sports club database. Try again." << endl;
            found = nullptr;
            continue;
        }
        if (!flag) {//there are more people like that
            cout << "Choice isn't unique. Try again with other field." << endl;
            found = nullptr;
            continue;
        }
        break;
    }
    return found;
}

Lesson *MainAction::findLesson() {
	
	cout << "---";
    cout << "|" << setw(4)<<"NUM"<<"||"<<setw(20) << "NAME" << "||" << setw(20) << "TIME" << "|---" << endl;
    //outputing rows
    int j=1;
    for (auto i: lessons) {
		cout << "---|" << setw(4)<<j++<<"||"<< setw(20) << i->getName() << "||" << setw(20)<< i->getTime()->toString()<< "|---" << endl;
    }
	int k;
    while(true){
        cout<<"Enter appropriate number:";
        cin>>k;
        if(!cin || k<1 || k>lessons.size() ){
            cin.clear();
            cin.ignore(1000,'\n');
            cout<<"Error! Try again!"<<endl;
            continue;
        }
        break;
    }
    return lessons[--k];
    /*
    Lesson *found= nullptr;
    Menu fieldMenu("FIND LESSON", "Which field do you want to search with?");
    fieldMenu.addOption("Name");//0
    fieldMenu.addOption("Exit to previous menu");//1
    auto it = lessons.begin();
    while (true) {
        int a = fieldMenu.show();
        if (a == 1) {
			//return to previous menu
            cout << "Aborted!" << endl;
            return nullptr;
        }

        string field;

        cout << "Enter 'q' to proceed to main menu." << endl;
        cout << "Enter field sentence: ";
        cin >> field;
        if (field == "q") {
            cout << "Aborted!" << endl;
            return nullptr;
        }

        if (!cin || field.size() > NAME_LENGTH) {
            cin.clear();
            cin.ignore(1000, '\n');
            field.clear();
            cout << errmessage << endl;
            continue;
        }
        bool flag = false;

        for (; it != lessons.end(); it++) {
            if (field.compare(getField<Lesson, le>(a, **it)) == 0) {
                if (flag) {//he was before
                    flag = false;//if he was before or it wasn't at all, then flag will be false
                    break;
                }
                flag = true;
                found = *it;
            }
        }
        if (!flag && it == lessons.end()) {//there wasn't such person
            cout << "There wasn't such person in sports club database. Try again." << endl;
            found= nullptr;
            continue;
        }
        if (!flag) {//there are more people like that
            cout << "Choice isn't unique. Try again with other field." << endl;
            found= nullptr;
            continue;
        }
        break;
    }
    return found;
    */
}

ClientAbs *MainAction::findClient() {
    ClientAbs *found = nullptr;
    Menu fieldMenu("Type of field to search with", "Which field do you want to search with?");
    fieldMenu.addOption("Name");//0
    fieldMenu.addOption("ID");//1
    fieldMenu.addOption("Mail");//2
    fieldMenu.addOption("Phone");//3
    fieldMenu.addOption("Exit to main menu");//4
    auto it = clients.begin();
    while (true) {
        int a = fieldMenu.show();
        if (a == 4) {
            cout << "Aborted!" << endl;
            return nullptr;
        }

        string field;

        //get field from user
        cout << "Enter 'q' to proceed to main menu." << endl;
        cout << "Enter field sentence: ";
        cin >> field;
        if (field == "q") {
            cout << "Aborted!" << endl;
            return nullptr;
        }

        if (!cin || field.size() > NAME_LENGTH) {
            cin.clear();
            cin.ignore(1000, '\n');
            field.clear();
            cout << errmessage << endl;
            continue;
        }
        bool flag = false;

        for (; it != clients.end(); it++) {
            if (field.compare(getField<ClientAbs, cl>(a, **it)) == 0) {
                if (flag) {//he was before
                    flag = false;//if he was before or it wasn't at all, then flag will be false
                    break;
                }
                flag = true;
                found= *it;
            }
        }
        if (!flag && it == clients.end()) {//there wasn't such person
            cout << "There wasn't such person in sports club database. Try again." << endl;
            found=nullptr;
            continue;
        }
        if (!flag) {//there are more people like that
            cout << "Choice isn't unique. Try again with other field." << endl;
            found = nullptr;
            continue;
        }
        break;
    }
    return found;
}

std::vector<ClientAbs *> *MainAction::getClientsPtr(){
    return &clients;
}
std::vector<Teacher *> *MainAction::getTeachersPtr(){
    return &teachers;
}
std::vector<Lesson *> *MainAction::getLessonPtr(){
    return &lessons;
}


void MainAction::loadTestData(){
    clients.push_back(new Client<string>("Kunegunda", 501138492));
    clients.push_back(new Client<string>("Jakub", "jakub@gmail.com", 123523476));
    clients.push_back(new Client<string>("Wiktor", "wiktorXD@wp.pl"));
    clients.push_back(new Client<string>("Zawisza", "czarny@onet.pl", 15071410));

    teachers.push_back(new Teacher("Aleksandra","a.smith@elka.pw.edu.pl", 102938475));
    teachers.push_back(new Teacher("Barbara","baska@elka.pw.edu.pl", 920394857));

    lessons.push_back(new Lesson("PROZ", "Monday", 1215, 1400));
    lessons.push_back(new Lesson("PROI", "Thursday", 815, 1000));

    cout<<"Test data loaded."<<endl;

}

MainAction::~MainAction(){
    for(auto i : clients){
        delete i;
    }
    for(auto i : teachers){
        delete i;
    }
    for(auto i : lessons){
        delete i;
    }
    clients.clear();
    teachers.clear();
    lessons.clear();
}
