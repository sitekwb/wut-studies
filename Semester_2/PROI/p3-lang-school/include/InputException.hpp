//
// Created by wojtek on 17.05.18.
//

#ifndef PROJECT_TWO_INPUTEXCEPTION_HPP
#define PROJECT_TWO_INPUTEXCEPTION_HPP

#include <string>
enum ExceptionType{integer, longish, vectorSize, notFound, emptyVector, existing};
static std::string errorMsgArray[]={"Error! Enter right int value.", "Error! Too long value.", \
"Error! Max 99 workers and 99 students in program.", "Error! Value not found in database.", \
"Empty set of students.", "Error! Value is just existing!"};

class InputException : public std::exception{
private:

    ExceptionType exceptionType;
public:
    InputException(ExceptionType type){
        exceptionType = type;
    }
    ExceptionType getType(){
        return exceptionType;
    }
    std::string printMsg(){
        return errorMsgArray[(int)exceptionType];
    }
};

#endif //PROJECT_TWO_INPUTEXCEPTION_HPP
