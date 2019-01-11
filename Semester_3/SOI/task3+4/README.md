# SEMAPHORE/MONITOR SOI PROJECTS

Project "Semaphores" implements consumer-producer problem in C language using threads from <pthread.h> and semaphors from <semaphore.h>.
Project "Monitors" implements consumer-producer problem in C++ language using processes by Linux function fork(), shared memory and semaphores from Boost library.
1. Parameters:
	- producers/consumers are operating on characters buffer with capacity of 9
	- there are two producers and two consumers (consuming/producing one or more letters at once)
	- after each consumption there should be at least 3 letters in buffer.
2. Solutions for "Semaphores":
	- structure Buffer implemented as a cycled queue with 'methods' to get front, pick element or add element 
	- different semaphors used:
		- binary semaphore *mutex*
		- binary semaphore *userMutex*
		- counting semaphore *consumeInitMutex* - when producer produces third letter, they enter in their critical section and raises binary flag *notYetConsumed* to false, allowing next producers to raise *full* semaphore 
		- counting semaphore *empty* (indicating how many places are left empty in buffer)
		- counting semaphore *full* (indicating how many places are full and ready to be consumed)
	- four additional threads imitating four people - 2 consumers and 2 producers and one main thread which finishes program running after time indicated by user in program arguments.
3. Solutions for "Monitors":
    - not shared between processes class *Buffer* with public methods pick, add and getters and with shared:
        - pointer to array with elements,
        - reference to tabsize
    - shared class Monitor (inspired by Ph.D. Tomasz Kruk implementation) which is an implementation on idea of monitors, including classes:
        - class Condition (condition variables)
        - class Semaphore (using boost semaphores).
    - virtual class Person with method action overriden in derivative classes
    - class Producer inheriting from Person with constructor and method action, servicing producer process action:
        - enter to monitor
        - if can't write (empty queue) => wait (having leaved monitor)
        - add to queue given number of letters
        - signal that queue is more *full* (leaving monitor)
    - class Consumer inheriting from Person with constructor and method action, servicing consumer process action:
        - enter to monitor
        - if can't read => wait (having leaved monitor)
        - pick from queue given number of letters
        - signal that queue is more *empty* (leaving monitor)
    - class *Letter* keeping letter:
        - letter can be incremented with operator++ by Producer:
        - used to simulate "producing items by Producer"
    - function main(), which includes:
        - declaration of local and shared between processes variables.
        - fork producers and consumers
        - as each person child process find shared objects and map them
        - perform action()
        - as parent process, sleep for given number of seconds and then kill all child processes and finish.

## SEMAPHORES

4. How to compile:
```
$ cd semaphores
$ make
```
5. How to execute program:
```
$ ./sem [time-of-work] [producer-sleep-time] [consumer-sleep-time] [>output/file/path]
```
## MONITORS

6. How to compile:
```
$ cd monitors
$ cmake .
$ make
```
4. How to execute program:
```
$ ./monitor [time-of-work] [producer-sleep-time] [consumer-sleep-time] [>output/file/path]
```

### FOR BOTH PROJECTS:
If *time-of-work* is not specified, program will work for 30 seconds. But if sleep-times are not be specified, producer and consumer will work instantly.



