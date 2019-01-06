#include <iostream>
#include <sstream>
#include "Calculator.hpp"
#include "Buffer.hpp"
using namespace std;

int main(){
	cout<<"---HEXADECIMAL CALCULATOR---"<<endl<<endl;
	Buffer buff;
	Calculator *calc;
	while(true){
		buff.askForExpression();
		if(!buff.getContFlag()) break;
		calc = new Calculator();
		if(buff.extractExpression(*calc)){//gets from user and extracts string to reverse Polish notation in calc
			cout<<"Syntax error. Please try again"<<endl;
			delete calc;
			continue;
		}
		int result = calc->getResult();//calculates and returns result
		if(calc->getErrorFlag()) {
            cout << "-->Error! Possibly dividing by zero! Try again." << endl;
            delete calc;
            continue;
        }
		cout<<"The hexadecimal result is: "<<((result<0)?"-":"")<<hex<<((result<0)?(-1):1)*result<<endl;
        cout<<"The decimal result is: "<<dec<<result<<endl<<endl;
		delete calc;
	}
	cout<<"Thank you for using my calculator. See you in next programs. :)"<<endl;
	return 0;
	
	
}
