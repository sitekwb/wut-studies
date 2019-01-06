//
// Created by wojtek on 22.05.18.
//

#include <AdmWorker.hpp>

#include <iostream>
#include <iomanip>

using namespace std;

void AdmWorker::print() {
    cout<<"---|"<<setw(3)<<id<<"|"<<setw(30)<<name<<"|"<<setw(6)<<salary<<"|"<<setw(15)<<startYear<<"|---"<<endl;
}
AdmWorker::AdmWorker(int admId, std::string admName, int admSalary, int admStartYear) {
    id = admId;
    name = admName;
    salary = admSalary;
    startYear = admStartYear;
}
string AdmWorker::getLang(){
    return "";
}