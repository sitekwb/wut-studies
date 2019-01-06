//
// Created by Wojciech Sitek on 11/12/2018.
//

//boost shared memory
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/shared_memory_object.hpp>

//fork
#include <sys/types.h>

//kill
#include <signal.h>

//classes
#include "Producer.hpp"
#include "Consumer.hpp"


using namespace boost::interprocess;

int main (int argc, char **argv)
{

    int pid[4];
    Person *person[4];
    person[0] = new Consumer(1, 'A', (argc==4)?atoi(argv[3]):0);
    person[1] = new Producer(1, 'A', (argc==4)?atoi(argv[2]):0);
    person[2] = new Consumer(2, 'B', (argc==4)?atoi(argv[3]):0);
    person[3] = new Producer(3, 'B', (argc==4)?atoi(argv[2]):0);


    shared_memory_object::remove("Memory");
    try{
        //allocate memory and buffer and monitors objects
        //shared_memory_object segment(create_only, "Memory", read_write);

        managed_shared_memory segment(create_only, "Memory", 100*(sizeof(Monitor) + BUFFERS_NUM*sizeof(Buffer) + CONDITIONS_NUM*sizeof(Condition)));

        tabsize = segment.construct<int>("tabsize")();
        tab = segment.construct<char>("tab")[9]();
        empty = segment.construct<Condition>("empty")();
        full = segment.construct<Condition>("full")();
        monitor = segment.construct<Monitor>("Monitor")();

        *tabsize = 0;
        //for(char i='a'; i<'a'+4; ++i){
          //  buffer->add(i);
        //}
        //create child processes performing their actions
        for(int i=0; i<4; ++i){
            pid[i] = fork();
            if(pid[i] == 0){//I am child
                managed_shared_memory memory(open_only, "Memory");

                tabsize = memory.find<int>("tabsize").first;
                tab = memory.find<char>("tab").first;
                empty = memory.find<Condition>("empty").first;
                full = memory.find<Condition>("full").first;
                monitor = memory.find<Monitor>("Monitor").first;

                if(!(tabsize && tab && empty && full && monitor)){
                    throw std::runtime_error("Pointer not found");
                }

                buffer = new Buffer(tab, *tabsize);//buffer is local, but uses shared queue

                person[i]->action();
            }
        }
        //sleep waiting for result of people work
        sleep((argc>1)?atoi(argv[1]):10);
    }
    catch(const std::runtime_error& re)
    {
        std::cout << "Runtime error: " << re.what() << std::endl;
    }
    catch(const interprocess_exception& ie){
        std::cout << "Interprocess exception: " << ie.what() << std::endl;
    }
    catch(...){
        std::cout << "Unknown error! Exiting." << std::endl;
    }
    //kill processes and exit
    for(int i=0; i<4; ++i){
        kill(pid[i], SIGKILL);
    }
    shared_memory_object::remove("MySharedMemory");
    return 0;
}
