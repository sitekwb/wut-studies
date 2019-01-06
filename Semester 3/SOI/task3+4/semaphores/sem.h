#ifndef SEMAPHORE_H
#define SEMAPHORE_H


#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>

#include "queue.h"

#define MAX_JUMP        3


int consumer_sleep, producer_sleep;

sem_t mutex, empty, full, userMutex, consumeStart, consumeInitMutex;

Buffer buffer;

int notFinish = TRUE, notYetConsumed = TRUE;

char currentLetter;

void *consume(void *consumer) {//eat one letter
    person *p = (person *)consumer;
    char c[MAX_JUMP], elem[BUF_NUM_ELEMENTS];


    while(notFinish) {

        sleep(consumer_sleep);

        for(int i=0; i<p->jump; ++i) {
            sem_wait(&full);
        }
        sem_wait(&mutex);

        //remove item
        for(int i=0; i < p->jump; ++i) {
            c[i] = pickBuf(&buffer);
        }

        sem_wait(&userMutex);
        //eat item
	printBuf(&buffer, elem);
        for(int i=0; i < p->jump; ++i) {
            printf("%s: I ate letter: %c! Buffer: %s\n", p->name, c[i], elem);
        }
	fflush(stdout);
        sem_post(&userMutex);

        sem_post(&mutex);
        for(int i=0; i < p->jump; ++i) {
        	sem_post(&empty);
	}
    }
    return NULL;
}

void *produce(void *producer){
    person *p = (person *)producer;
    char c[MAX_JUMP], buf[3], elem[BUF_NUM_ELEMENTS];
    while(notFinish) {
        sleep(producer_sleep);

        //initialize produced item
        for(int i=0; i< p->jump; ++i){
            c[i] = currentLetter;
            if(currentLetter++ == 'z'){
                currentLetter = 'a';
            }
        }


        for(int i=0; i < p->jump; ++i) {
        	sem_wait(&empty);
	}
        sem_wait(&mutex);

        //enter item
        for(int i=0; i < p->jump; ++i) {
            addBuf(&buffer, c[i]);
        }

        //inform about produced item
        sem_wait(&userMutex);
	printBuf(&buffer, elem);
        for(int i=0; i < p->jump; ++i) {
            printf("%s: Produced letter: %c! Buffer: %s\n", p->name, c[i], elem);
        }
	fflush(stdout);
        sem_post(&userMutex);

        sem_post(&mutex);


        for(int i=0; i < p->jump; ++i) {
            if(notYetConsumed) {
                //stopping others who want to initialise full
                sem_wait(&consumeInitMutex);
            }
            if(notYetConsumed) {
                int semValue;
                sem_getvalue(&consumeInitMutex, &semValue);
                if (semValue <= 0) {
                    notYetConsumed = FALSE;
                    sem_post(&consumeInitMutex);
                }
            }
            else{
                sem_post(&full);
            }
        }
    }
    return NULL;
}




#endif //SEMAPHORE_H
