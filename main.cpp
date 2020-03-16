// Jack Babcock

#include <iostream>
#include <vector>
#include <string>
#include "Graph.h"

using namespace std;


int main(int argc, const char * argv[]) {
    Graph<string> g;
    g.fillGraph("karate.txt");
    g.list();

    //g.bredthFirstSearch("9");
    //cout << endl;

    //g.depthFirstSearch("8");
    //cout << endl << endl;

    g.makeConnection("8", "27");

    g.calculateBetweenness();
    g.removeBetweeniest();
    g.calculateBetweenness();
    g.removeBetweeniest();
    //g.list();
    return 0;

}

