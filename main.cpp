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
    g.addVertex("Granny");
    g.addVertex("Pops");
    g.addVertex("Mom");
    g.addVertex("Dad");
    g.addVertex("Alex");
    g.addVertex("Zurlo");
    g.addEdge("Jack", "Christine");
    g.addEdge("Jack", "Duke");
    g.addEdge("Duke", "Christine");
    g.addEdge("Jack", "Granny");
    g.addEdge("Pops", "Jack");
    g.addEdge("Alex", "Zurlo");
    g.addEdge("Christine", "Mom");
    g.addEdge("Alex", "Dad");
    g.addEdge("Pops", "Dad");
    g.list();
    vector<string> dfs;
    vector<string> bfs;
    bfs = g.bredthFirstSearch("Duke");
    //g.depthFirstSearch("Duke", dfs);
    for (int i = 0; i < bfs.size(); i++) {
        cout << bfs[i] << ", ";
    }
    cout << endl;
    return 0;

}

