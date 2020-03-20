// Jack Babcock

#include <iostream>
#include <vector>
#include <string>
#include "Graph.h"

using namespace std;


int main(int argc, const char * argv[]) {
    Graph<string> g;
    g.followDirections(argv[1]);

    return 0;

}

