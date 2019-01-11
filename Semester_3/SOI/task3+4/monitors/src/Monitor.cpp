#include "Monitor.hpp"


#include <iostream>//for a while TODO
using namespace boost::interprocess;

Semaphore::Semaphore( unsigned int value ) : sem(value){}
Semaphore::~Semaphore() {}

void Semaphore::p()
{
	sem.wait();
}

void Semaphore::v()
{
	sem.post();
}



void Condition::wait()
{
	++waitingCount;
	sem.p();
}

bool Condition::signal()
{
	if(waitingCount) {
		//std::cout << "[N]" << std::endl;
		--waitingCount;
		sem.v();
		return false;
	}
	return true;

}



void Monitor::enter()
{
	s.p();
}

void Monitor::leave()
{
	s.v();
}

void Monitor::wait( Condition & cond )
{
	leave();
	cond.wait();
}

void Monitor::signal( Condition & cond )
{
    if(cond.signal()){
    	leave();
    }
}


