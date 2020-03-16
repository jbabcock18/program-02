// Jack Babcock

#include <iostream>
#include <vector>
#include <string>
#include "Graph.h"

using namespace std;


int main(int argc, const char * argv[]) {
    Graph<string> g;
    g.fillGraph("football.txt");
    g.list();

    g.bredthFirstSearch("Hawaii");
    cout << endl;

    g.depthFirstSearch("Hawaii");
    cout << endl << endl;

    g.makeConnection("Hawaii", "Texas");

    g.calculateBetweenness();
    g.removeBetweeniest();
    //g.list();
    return 0;

}

