//
// Created by Wojciech Sitek on 30/11/2018.
//

#ifndef T3_QUEUE_H
#define T3_QUEUE_H

#include <stdio.h>
#include <stdlib.h>

#define PERSON_NUMBER           4
#define BUF_NUM_ELEMENTS        9

#define TRUE                    1
#define FALSE                   0

typedef struct person{
    int jump;
    char name[10];
}person;

typedef person* Person;

typedef struct Buffer{
    int capacity;
    int size;
    int front;
    int rear;
    char elements[BUF_NUM_ELEMENTS];
}Buffer;
void initBuf(Buffer *Q){
    Q->size = 0;
    Q->capacity = BUF_NUM_ELEMENTS;
    Q->front = 0;
    Q->rear = -1;
    Q->elements[0] = 0;
}
char pickBuf(Buffer *Q) {
    if(Q->size==0){
        return NULL;
    }
    --Q->size;
    char p = Q->elements[Q->front++];
    if(Q->front==Q->capacity){
        Q->front=0;
    }
    return p;
}
void addBuf(Buffer *Q,char element){
    if(Q->size == Q->capacity){
        printf("Critical error!");
        return;
    }
    ++Q->size;
    ++Q->rear;
    if(Q->rear == Q->capacity){
        Q->rear = 0;
    }
    Q->elements[Q->rear] = element;
}
void printBuf(Buffer *Q, char *str){
	int b=Q->front;
	int i;
	for(i=0;i<Q->size; ++i){
		str[i] = Q->elements[b];
		++b;
		if(b == Q->capacity){
			b=0;
		}
	}
	str[i] = '\0';
}

#endif //T3_QUEUE_H
