//
// Created by wojtek on 22.05.18.
//

#include "Worker.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

int Worker::getId() {
    return id;
}

void Worker::printHeader(){
    cout<<"---|"<<setw(3)<<"ID"<<"|"<<setw(30)<<"NAME"<<"|"<<setw(6)<<"SALARY"<<"|";
    cout<<setw(15)<<"LANG/START YEAR"<<"|---"<<endl;
}