//
// Created by Wojciech Sitek on 14/12/2018.
//

#include "Producer.hpp"



using namespace std;



Producer::Producer(const int jump_, char letterName_, int sleepTime_)
: Person(jump_, '+', letterName_, sleepTime_),
    currentLetter((letterName == 'A') ? 'a' : 'A') {}

void Producer::action(){
    //produce
    while(true){
        sleep(sleepTime);
        //enter to monitor Buffer
        monitor->enter();
        //if too much elements => wait till is more EMPTY
        for(int i=0; i < this->jump; ++i) {
            if (buffer->getSize() == buffer->getCapacity() - i) {
                // I'll be waiting <= inform user
                std::cout<<functionName<<' '<<letterName<<' '<<i<<'/'<<jump<<" WAIT"<<std::endl;
                //wait
                i=0;
                monitor->wait(*empty);
            }
        }
        //add&inform user
        for(int i=1; i <= this->jump; ++i){
            buffer->add(currentLetter++);
            std::cout<<functionName<<' '<<letterName<<' '<<i<<'/'<<jump<<' '  \
                <<buffer->getBack()<<' '<<buffer->getSize()<<' '<<buffer->getBuf()<<std::endl;
        }

        monitor->signal(*full);

    }
}