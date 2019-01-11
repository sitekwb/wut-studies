#include <cstddef>
#include <cstdlib>
#include <string>

#include "Vector.h"
#include "LinkedList.h"

#include <initializer_list>
#include <iostream>
#include <fstream>


using namespace aisdi;


std::ofstream file;

template<typename Coll>
Coll *createCollection(size_t num=0){
    Coll *collection = new Coll;
    for(size_t i=0; i<num; i++){
        collection->append((const int)i);
    }
    return collection;
}

void prependTest(Vector<int> *vector, LinkedList<int> *linkedList){
    file<<vector->getSize()<<";";
    clock_t time = clock();
    vector->prepend(50);
    file<<float(clock() - time ) << ";";

    time = clock();
    linkedList->prepend(50);
    file<<float(clock() - time ) << ";";
}
void insertTest(Vector<int> *vector, LinkedList<int> *linkedList){
    auto vIt = vector->cbegin();
    clock_t time = clock();
    vector->insert(vIt, 50);
    file<<float(clock() - time ) << ";";

    auto lIt = linkedList->cbegin();
    time = clock();
    linkedList->insert(lIt, 50);
    file<<float(clock() - time ) << ";";
}
void eraseTest(Vector<int> *vector, LinkedList<int> *linkedList){
    auto vIt = vector->cbegin();
    clock_t time = clock();
    vector->erase(vIt);
    file<<float(clock() - time )<< ";";

    auto lIt = linkedList->cbegin();
    time = clock();
    linkedList->erase(lIt);
    file<<float(clock() - time )<< ";";

}
void indexTest(Vector<int> *vector, LinkedList<int> *linkedList){
    size_t index = vector->getSize()/2;
    clock_t time = clock();
    (*vector)[index];
    file<<float(clock() - time )<< ";";

    time = clock();
    (*linkedList)[index];
    file<<float(clock() - time )<< ";";

    file<<std::endl;
}
int main(int argc, char** argv)
{
    LinkedList<int> *linkedList = createCollection<LinkedList<int>>();
    Vector<int> *vector = createCollection<Vector<int>>();

    file.open(argc>2?argv[2] : "test.csv", std::fstream::out);
    file<<"ElementsNum;VectorPrependTime;LinkedListPrependTime;VectorInsertTime;LinkedListInsertTime;VectorEraseTime;LinkedListEraseTime;VectorIndexTime;LinkedListIndexTime"<<std::endl;

    const std::size_t repeatCount = argc > 1 ? std::atoi(argv[1]) : 10000;
    const std::size_t state = repeatCount/10;
    for (std::size_t i = 0; i < repeatCount; ++i) {
        prependTest(vector, linkedList);
        insertTest(vector, linkedList);
        eraseTest(vector, linkedList);
        indexTest(vector, linkedList);
        if (i % state == 0) {
            std::cout << '|';
        }
    }

    file.close();
    delete linkedList;
    delete vector;
    return 0;
}
