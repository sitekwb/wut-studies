#include "School.h"
#include "UI.h"
#include "InputException.hpp"
#include "Worker.hpp"
#include <iostream>
#include <string>
#include <Teacher.hpp>

using namespace std;

void UI::printMenu() {
    bool finishFlag=false;
    while (1) {
        cout << endl;
        cout << "0. Finish program." << endl;
        cout << "1. Add a student." << endl;
        cout << "2. Print students." << endl;
        cout << "3. Delete a student." << endl;
        cout << "4. Make everyone 1 year older." << endl;
        cout << "5. Change group of a student." << endl;
        cout << "6. Replace a language with another one." << endl;
        cout << "7. Add worker." <<endl;
        cout << "8. Print workers."<<endl;
        try {
            cout << "Select an option: ";
            int choice;
            cin >> choice;
            if(!cin){
                throw InputException(integer);
            }
            if (choice > 8 || choice < 0) {
                throw InputException(longish);
            }
            switch (choice) {
                case 0:
                    cout<<"Thank you!";
                    finishFlag=true;
                    break;
                case 1:
                    addStudent();
                    break;
                case 2:
                    language_school.printStudents();
                    break;
                case 3:
                    deleteStudent();
                    break;
                case 4:
                    increaseAge();
                    break;
                case 5:
                    changeGroup();
                    break;
                case 6:
                    changeLanguage();
                    break;
                case 7:
                    addWorker();
                    break;
                case 8:
                    printWorkers();
                    break;
            }
            if(finishFlag){
                break;
            }
        }
        catch (InputException &e) {
            cin.clear();
            cin.ignore(1000,'\n');
            cout<<endl<<e.printMsg()<<endl;
        }
        catch (std::exception &e){
            cout<<"Unknown error. Try again."<<endl<<e.what()<<endl;
        }
    }
}

void UI::addWorker(){
    string name, surname, language;
    cout << "Name: (max. 30 characters together) ";
    cin>>name;
    cout << "Surname: (max. 30 characters with name) ";
    cin>>surname;
    name = name+" "+surname;
    if(name.length() >30){
        throw InputException(longish);
    }
    int salary,group;
    cout << "Salary: (max. 100000)";
    cin >>salary;
    if(!cin){
        throw InputException(integer);
    }
    if(salary<0 || salary> 100000){
        throw InputException(longish);
    }
    bool isTeacher;
    cout << "Is this worker a teacher? (1/0)";
    cin >> isTeacher;
    if(!cin){
        throw InputException(integer);
    }
    if(isTeacher) {
        cout << "Language (max. 15 characters):";
        cin >> language;
        if (language.length() > 15) {
            throw InputException(longish);
        }
        Teacher *teacher = language_school.addTeacher(worker_id,name,salary,language);
        while(1){
            cout << "Group (max. 2 digit integer, '-1' to finish): ";
            cin >> group;
            if (!cin) {
                throw InputException(integer);
            }
            if(group==-1){
                break;
            }
            teacher->addGroup(group);
        }
    }
    else{
        int startYear;
        cout << "Year of start of work:";
        cin >>startYear;
        if(!cin){
            throw InputException(integer);
        }
        language_school.addAdmWorker(worker_id, name, salary, startYear);
    }

    worker_id++;
}

void UI::printWorkers() {

    language_school.printWorkers();
}

void UI::increaseAge()
{
    cout << "\nHappy new year!" << endl;
    ++language_school;
}

void UI::changeGroup() {
    int id, gr;
    cout << "Choose a student by id: ";
    cin >> id;
    if (!cin) {
        throw InputException(integer);
    }
    cout << "Choose a group: ";
    cin >> gr;
    if (!cin) {
        throw InputException(integer);
    }
    language_school.changeData(id, gr);

}

void UI::addStudent()
{
    string name, surname, language;
    int nameChoice;
    cout << "Do you want to add student's name(1) or assign him with the album number(0)? 0/1 ";
    cin >> nameChoice;
    if(!cin){
        throw InputException(integer);
    }
    if(nameChoice!=1 && nameChoice!=0){
        throw InputException(integer);
    }
    if(nameChoice)
    {
        cout << "Name: (max. 30 characters together) ";
        cin>>name;
        cout << "Surname: (max. 30 characters with name) ";
        cin>>surname;
        name = name+" "+surname;
        if(name.length() >30){
            throw InputException(longish);
        }
    }

    int age, group;
    cout << "Age: ";
    cin >> age;
    if(!cin){
        throw InputException(integer);
    }

    cout << "Language: (max. 15 signs)";
    cin >> language;

    cout << "Group (max. 2 digit integer): ";
    cin >> group;
    if(!cin){
        throw InputException(integer);
    }
    if(group<0 || group>99){
        throw InputException(longish);
    }
    if(nameChoice)
        language_school.addStudent(id, name, age, group, language); //adding by name
    else
        language_school.addStudent(id, index, age, group, language); //adding by index number

    index++;
    id++;
}

void UI::deleteStudent() {
    int chosenID;
    cout << "Type ID of the student: ";
    cin >> chosenID;
    if(!cin){
        throw InputException(integer);
    }

    language_school.deleteStudent(chosenID);
    cout << "Successfully deleted.\n";

}

void UI::changeLanguage() //deletes students of a chosen language
{
    std::string oldL, newL;
    cout << "Old language: ";
    cin >> oldL;
    if(!cin){
        throw InputException(integer);
    }
    cout << "New language: ";
    cin >> newL;
    if(!cin){
        throw InputException(integer);
    }
    language_school.changeData(oldL, newL);
}
