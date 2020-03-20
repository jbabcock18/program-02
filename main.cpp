// Jack Babcock

#include <iostream>
#include <vector>
#include <string>
#include "Graph.h"

using namespace std;


int main(int argc, const char * argv[]) {
    Graph<string> g;
    g.fillGraph("football.txt");
    g.setOutputFile("output.txt");
    g.depthFirstSearchStyling("SouthernMethodist");
    g.bredthFirstSearch("Hawaii");
    g.makeConnection("Texas", "Navy");
    g.findCommunities();

    return 0;

}

