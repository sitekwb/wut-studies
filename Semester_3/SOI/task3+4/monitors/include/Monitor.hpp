#ifndef __monitor_h
#define __monitor_h

#include <stdio.h> 
#include <stdlib.h> 

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/types.h> 
#include <sys/stat.h> 
#include <string.h> 
#include <errno.h> 
#include <fcntl.h> 
#include <pthread.h> 
#include <unistd.h>
#include <semaphore.h>

#include <boost/interprocess/sync/interprocess_semaphore.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>
#include <boost/interprocess/sync/sharable_lock.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>

#endif

class Semaphore
{
public:

  	Semaphore( unsigned int value );
  	~Semaphore();

  	void p();
  	void v();


private:

	boost::interprocess::interprocess_semaphore sem;

};

class Condition
{

public:
	Condition() : sem(0), waitingCount(0){}

	void wait();

	bool signal();

private:
	Semaphore sem;
	int waitingCount;

};


class Monitor
{
public:
	Monitor() : s( 1 ) {}

	void enter();

	void leave();

	void wait( Condition & cond );

	void signal( Condition & cond );


	Semaphore s;
};

#endif

