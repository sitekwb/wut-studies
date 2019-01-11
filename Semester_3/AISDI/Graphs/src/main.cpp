#include <cstddef>
#include <cstdlib>
#include <string>

#include <iostream>

#include "../include/Graph.h"

using namespace aisdi;

using namespace std;

int main()
{
    size_t size;
    cin>>size;

    Graph graph;
    for(size_t i = 0; i < size; ++i){
        size_t first, second;
        cin>>first>>second;
        graph.add(first, second);
    }

    graph.printGreatBridges();

    return 0;
}
