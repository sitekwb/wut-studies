//
// Created by Wojciech Sitek on 30/11/2018.
//
#include "sem.h"
#include <pthread.h>
#include <string.h>

#define PSSHARED                    0
#define MIN_LETTERS_TO_CONSUME      3

person *caPerson, *cbPerson, *paPerson, *pbPerson;


int main(int argc, char **argv){
    setbuf(stdout, 0);
    initBuf(&buffer);
    pthread_t caThread, cbThread, paThread, pbThread;

    currentLetter = 'a';

    //INITIALIZE VAR VALUES
    caPerson = (person *)malloc(sizeof(person));
    caPerson->jump = 1;
    strcpy(caPerson->name, "ConsumerA");

    cbPerson = (person *)malloc(sizeof(person));
    cbPerson->jump = 2;
    strcpy(cbPerson->name, "ConsumerB");

    paPerson = (person *)malloc(sizeof(person));
    paPerson->jump = 1;
    strcpy(paPerson->name, "ProducerA");

    pbPerson = (person *)malloc(sizeof(person));
    pbPerson->jump = 3;
    strcpy(pbPerson->name, "ProducerB");

    if(argc >= 4 ){
	producer_sleep = atoi(argv[2]);
	consumer_sleep = atoi(argv[3]);
    } 	
    //INIT OF SEMAPHORS
    sem_init(&mutex, PSSHARED, 1);
    sem_init(&userMutex, PSSHARED, 1);
    sem_init(&empty, PSSHARED, BUF_NUM_ELEMENTS-1);
    sem_init(&consumeInitMutex, PSSHARED, MIN_LETTERS_TO_CONSUME);
    sem_init(&full, PSSHARED, 0);

    //RUN THREADS
    int retCA = pthread_create( &caThread, NULL, consume, (void *)(caPerson));
    if(retCA){
        fprintf(stderr,"Error - pthread_create() return code: %d\n",retCA);
        exit(EXIT_FAILURE);
    }

    int retCB = pthread_create( &cbThread, NULL, consume, (void *)(cbPerson));
    if(retCB){
        fprintf(stderr,"Error - pthread_create() return code: %d\n",retCB);
        exit(EXIT_FAILURE);
    }

    int retPA = pthread_create( &paThread, NULL, produce, (void *)(paPerson));
    if(retPA){
        fprintf(stderr,"Error - pthread_create() return code: %d\n",retPA);
        exit(EXIT_FAILURE);
    }

    int retPB = pthread_create( &pbThread, NULL, produce, (void *)(pbPerson));
    if(retPB){
        fprintf(stderr,"Error - pthread_create() return code: %d\n",retPB);
        exit(EXIT_FAILURE);
    }

    unsigned int runtime = (argc>1)?atoi(argv[1]):30;

    sleep(runtime);

    notFinish = FALSE;

    free(caPerson);
    free(cbPerson);
    free(paPerson);
    free(pbPerson);

    sem_destroy(&mutex);
    sem_destroy(&userMutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    exit(EXIT_SUCCESS);
    pthread_join( caThread, NULL);
    pthread_join( cbThread, NULL);
    pthread_join( paThread, NULL);
    pthread_join( pbThread, NULL);

}
