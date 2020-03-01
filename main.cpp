// Jack Babcock

#include <iostream>
#include <vector>
#include <string>
#include "Graph.h"

using namespace std;


int main(int argc, const char * argv[]) {
    cout << "Hello, World" << endl;
    Graph<string> g;
    g.addVertex("Jack");
    g.addVertex("Christine");
    g.listVerticies();
    return 0;
}

