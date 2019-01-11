//
// Created by Wojciech Sitek on 14/12/2018.
//

#include "Consumer.hpp"


using namespace std;

void Consumer::action(){
    //consume
    while(true){
        sleep(sleepTime);
        //enter to monitor Buffer
        monitor->enter();
        //if too low number of elements => wait on full
        for(int i=0; i < this->jump+MIN_LETTERS_TO_CONSUME; ++i) {
            if (buffer->getSize() == i) {
                std::cout<<functionName<<' '<<letterName<<' '<<i<<'/'<<jump+MIN_LETTERS_TO_CONSUME<<" WAIT"<<std::endl;
                i=0;
                monitor->wait(*full);
            }
        }
        //pick&inform user
        for(int i=1; i <= this->jump; ++i){
            char c = buffer->pick();
            std::cout<<functionName<<' '<<letterName<<' '<<i<<"/"<<jump<<' ';
            cout<<c<<' '<<buffer->getSize()<<' '<<buffer->getBuf()<<std::endl;
        }
        //signal(empty) = If no one was waiting, switch off light
        //cout<<functionName<<' '<<letterName;
        monitor->signal(*empty);
    }

}