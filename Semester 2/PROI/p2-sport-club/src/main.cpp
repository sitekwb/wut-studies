#include <iostream>
#include "../include/Client.hpp"
#include "../include/Menu.hpp"
#include "../include/Teacher.hpp"
#include "../include/MainAction.hpp"
#include "../spike/Presentation.hpp"

#include <string>
#include <vector>
#include <iomanip>

using namespace std;


int main() {

	Menu mainMenu("SPORTS CLUB DATABASE","What action do you want to perform?");

	mainMenu.addOption("New client.");//0
	mainMenu.addOption("Find client.");//1
	mainMenu.addOption("Show clients.");//2
	mainMenu.addOption("New teacher.");//3
	mainMenu.addOption("Find teacher.");//4
	mainMenu.addOption("Show teachers.");//5
	mainMenu.addOption("New lesson.");//6
    mainMenu.addOption("Load test data.");//7
	mainMenu.addOption("Exit program.");//8

    Menu personMenu("Client actions", "What do you want to find or change?");
    personMenu.addOption("Show data.");//0
    personMenu.addOption("Add to lesson.");//1
    personMenu.addOption("Exit to main menu.");//2

    MainAction mainAction;
	bool exitFlag=false;
	while (true) {
        switch (mainMenu.show()) {
            case 0:
                mainAction.newClient();
                break;
            case 1: {
                //find client
                ClientAbs *client = mainAction.findClient();
                if(client!=nullptr) {
                    bool flag=true;
                    while(flag) {
                        switch (personMenu.show()) {
                            case 0: {
                                //show found client
                                cout << "CLIENT" << endl;
                                cout << "Name: " << client->getName() << endl;
                                cout << "Email: " << client->getMail() << endl;
                                cout << "Phone: " << client->getPhone() << endl;
                                cout << "Timetable: " << endl;


                                vector<Lesson> *courses = client->getTimetablePtr()->getCoursesPtr();
                                cout << "---";
                                cout << "|" << setw(20) << "NAME" << "||" << setw(20) << "TIME" << "|---" << endl;
                                //outputing rows
                                for (auto i: *courses) {
                                    cout << "---|" << setw(20) << i.getName() << "||" << setw(20)
                                         << i.getTime()->toString()
                                         << "|---" << endl;
                                }
                            }
                                break;
                            case 1:
                            {
                                Lesson *lesson = mainAction.findLesson();
                                if(lesson!= nullptr) {
                                    client->getTimetablePtr()->addLesson(*lesson);
                                    lesson->addPerson(*client);
                                }
                            }
                                break;
                            case 2:
                            default:
                                flag=false;
                                break;
                        }
                    }
                }
            }
                break;
            case 2: {
                //show all clients basic data
                vector<ClientAbs *>*clients = mainAction.getClientsPtr();
                cout<< "CLIENTS IN THE DATABASE"<<endl;
                cout<< "---|" << setw(20) << "NAME" << "||" <<setw(30) <<"MAIL"<<"||"<<setw(20) <<"PHONE"<< "|---" <<endl;
                //outputing rows
                for (auto i: *clients) {
                    cout << "---|" << setw(20) << i->getName() << "||" << setw(30)<<i->getMail() << "||" << setw(20)<<i->getPhone()<<"|---"<<endl;
                }

            }
                break;
            case 3:
                mainAction.newTeacher();
                break;
            case 4: {
                //find teacher
                Teacher *teacher = mainAction.findTeacher();
                if(teacher!= nullptr) {
                    bool flag=true;
                    while(flag) {
                        switch(personMenu.show()) {
                            case 0: {
                                //show found teacher
                                cout << "TEACHER" << endl;
                                cout << "Name: " << teacher->getName() << endl;
                                cout << "Email: " << teacher->getMail() << endl;
                                cout << "Phone: " << teacher->getPhone() << endl;
                                cout << "Timetable: " << endl;


                                vector<Lesson> *courses = teacher->getTimetablePtr()->getCoursesPtr();
                                cout << "---";
                                cout << "|" << setw(20) << "NAME" << "||" << setw(20) << "TIME" << "|---" << endl;
                                //outputing rows
                                for (auto i: *courses) {
                                    cout << "---|" << setw(20) << i.getName() << "||" << setw(20)
                                         << i.getTime()->toString()
                                         << "|---" << endl;
                                }
                            }
                            break;
                            case 1:{
                                //add lesson to teacher
                                Lesson *lesson = mainAction.findLesson();
                                if(lesson!= nullptr) {
                                    teacher->getTimetablePtr()->addLesson(*lesson);
                                    lesson->addPerson(*teacher);
                                }
                            }
                            case 2:
                            default:
                                flag=false;
                                break;
                        }
                    }
                }
            }
            break;
            case 5:
            {
                //show all teachers basic data
                vector<Teacher *>*teachers = mainAction.getTeachersPtr();

                cout<< "TEACHERS IN THE DATABASE"<<endl;
                cout<< "---|" << setw(20) << "NAME" << "||" <<setw(30) <<"MAIL"<<"||"<<setw(20) <<"PHONE"<< "|---" <<endl;
                //outputing rows
                for (auto i: *teachers) {
                    cout << "---|" << setw(20) << i->getName() << "||" << setw(30)<<i->getMail() << "||" << setw(20)<<i->getPhone()<<"|---"<<endl;
                }

            }
                break;
            case 6:
                mainAction.newLesson();
                break;
            case 7: //load test data
                mainAction.loadTestData();
                break;
            case 8: default://exit program
                exitFlag=true;
                break;
        }
        if(exitFlag){
            break;
        }
    }
    return 0;
}

