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
    g.addEdge("Jack", "Christine");
    g.addEdge("Jack", "Duke");
    g.addEdge("Duke", "Christine");
    g.addEdge("Jack", "Granny");
    g.addEdge("Pops", "Jack");
    g.list();
    vector<string> dfs;
    g.depthFirstSearch("Duke", dfs);
    for (int i = 0; i < dfs.size(); i++) {
        cout << dfs[i] << ", ";
    }
    cout << endl;
    return 0;

}

