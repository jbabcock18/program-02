// Jack Babcock

#include <iostream>
#include <vector>
#include <string>
#include "Graph.h"

using namespace std;


int main(int argc, const char * argv[]) {
    Graph<string> g;
    g.addVertex("Jack");
    g.addVertex("Christine");
    g.addVertex("Duke");
    g.addVertex("Mom");
    g.addVertex("Dad");
    g.addVertex("Pops");
    g.addEdge("Jack", "Christine");
    g.addEdge("Jack", "Duke");
    g.addEdge("Duke", "Dad");
    g.addEdge("Christine", "Dad");
    g.addEdge("Dad", "Mom");
    g.addEdge("Christine", "Mom");
    g.addEdge("Dad", "Pops");
    g.list();
    vector<string> dfs;
    vector<string> bfs;
    bfs = g.bredthFirstSearch("Jack");
    //g.depthFirstSearch("Duke", dfs);
    for (int i = 0; i < bfs.size(); i++) {
        cout << bfs[i] << ", ";
    }
    cout << endl;
    //g.reset();
    g.makeConnection("Jack", "Dad");
    //g.getNumberOfShortestPaths("Jack");
    g.findCommunities();
    return 0;

}

