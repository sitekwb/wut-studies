/*
Imie i nazwisko:-------- Wojciech Sitek
Numer indeksu:---------- 2931480
Prowadzacy laboratorium: Wiktor Kusmirek
Numer projektu:--------- 0
*/

#include <iostream>

#include "main.hpp"
using namespace std;


Calculator::Calculator(double f, double s){
		first=f;
		second=s;
	}

double Calculator::getResult(){
		return (first+second);
	}


int main(){
	double in1,in2;
	char c;
	cout<<"---SIMPLE ADDING CALCULATOR---"<<endl;
	cin.clear();
	while(1){
		cout<<"Please enter first number of type double:  ";
		if(!(cin>>in1)){
			cin.clear();
			cin.ignore(1000, '\n');
			cout<<"-->Error! Try again. ";
			continue;
		}
		c=cin.get();
		if(c!='\n'){
			cin.clear();
			cin.ignore(1000, '\n');
			cout<<"-->Error! Try again. ";
			continue;
		}
		break;
	}
	while(1){
		cout<<"Please enter second number of type double:  ";
		if(!(cin>>in2)){
			cin.clear();
			cin.ignore(1000, '\n');
			cout<<"-->Error! Try again. ";
			continue;
		}
        c=cin.get();
		if(c!='\n'){
			cin.clear();
			cin.ignore(1000, '\n');
			cout<<"-->Error! Try again. ";
			continue;
		}
		break;
	}
	Calculator calc(in1,in2);

	cout<<"The result of addition is: "<<calc.getResult()<<"."<<endl;

	return 0;
}
