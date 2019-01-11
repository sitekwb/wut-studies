#include <cstddef>
#include <cstdlib>
#include <string>

#include "HashMap.h"
#include "TreeMap.h"

#include <initializer_list>
#include <iostream>
#include <fstream>


using namespace aisdi;


std::ofstream file;

template<typename Coll>
Coll *createCollection(){
    return new Coll;
}

void addTest(HashMap<int, std::string> *hashMap, TreeMap<int, std::string> *treeMap){
    int size = hashMap->getSize();
    file<<size<<";";
    clock_t time = clock();
    (*hashMap)[size] = "Value";
    file<<float(clock() - time ) << ";";

    time = clock();
    (*treeMap)[size] = "Value";
    file<<float(clock() - time ) << ";";
}

void findTest(HashMap<int, std::string> *hashMap, TreeMap<int, std::string> *treeMap){
    int i = hashMap->getSize()/2;
    clock_t time = clock();
    hashMap->find(i);
    file<<float(clock() - time ) << ";";

    time = clock();
    treeMap->find(i);
    file<<float(clock() - time ) << ";";
}
void iterateTest(HashMap<int, std::string> *hashMap, TreeMap<int, std::string> *treeMap){
    clock_t time = clock();
    for(auto it1 = hashMap->begin(); it1 != hashMap->end(); ++it1){}
    file<<float(clock() - time ) << ";";

    time = clock();
    for(auto it1 = treeMap->begin(); it1 != treeMap->end(); ++it1){}
    file<<float(clock() - time ) << ";";
}

int main(int argc, char** argv)
{
    HashMap<int, std::string> *hashMap = createCollection<HashMap<int, std::string>>();
    TreeMap<int, std::string> *treeMap = createCollection<TreeMap<int, std::string>>();

    file.open(argc>2?argv[2] : "test.csv", std::fstream::out);
    file<<"ElementsNum;HashAddTime;TreeAddTime;HashFindTime;TreeFindTime;HashIterateTime;TreeIterateTime"<<std::endl;

    const std::size_t repeatCount = argc > 1 ? std::atoi(argv[1]) : 100000;
    for (std::size_t i = 0; i < repeatCount; ++i) {
        addTest(hashMap, treeMap);
        findTest(hashMap, treeMap);
        iterateTest(hashMap, treeMap);
        //eraseTest(hashMap, treeMap);
        file<<std::endl;
    }

    file.close();
    delete hashMap;
    delete treeMap;
    return 0;
}
