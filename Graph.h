// Jack Babcock

#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;


// Basic layout:
// Graph is a vector of vertex pointers
// Vertex holds data, as well as a vector of Edges
// Edge is a pointer to a vertex
// Inspired by Miguel Gazela : https://gist.github.com/miguelgazela/4428700

// Declared so that they are recognized
template <class T> class Vertex;
template <class T> class Edge;

template <class T>
class Vertex {
    private:
        vector<Edge<T>* > edges;
        T data;
        bool visited;
    public:
        Vertex(T info) {
            data = info;
            visited = false;
        }

        T getData() {
            return data;
        }

        void addEdge(Vertex<T>* edge) {
            Edge<T>* e = new Edge<T>(edge);
            edges.push_back(e);
        }

        vector<Edge<T>* > getEdges() {
            return edges;
        }

        bool isVisited() {
            return visited;
        }

        void visit() {
            visited = true;
        }

        void unvisit() {
            visited = false;
        }
        
        Vertex<T>* cameFrom;
        int equalPaths = 1; // number of equally shortest paths
        int layer = 1;
};

template <class T>
class Edge {
    private:
        Vertex<T>* vtx;
        double betweennesss;
    public:
        Edge(Vertex<T>* v): vtx(v) {
            betweennesss = 1;
        }
        Vertex<T>* getVertex() {
            return vtx;
        }
        void addBetweennesss(double num) {
            betweennesss += num;
        }
        double getBetweenness() {
            return betweennesss;
        }
        void resetBetweenness() {
            betweennesss = 1;
        }
};


template <class T>
class Graph {
    private:
        vector<Vertex<T>* > graph;

    public:
        Graph() {}

        void addVertex(T data) {
            Vertex<T>* node = new Vertex<T>(data);
            graph.push_back(node);
        }

        void reset() {
            typename vector<Vertex<T>*>::iterator iter;
            for (iter = graph.begin(); iter != graph.end(); iter++) {
                (*iter)->unvisit();
                (*iter)->layer = 1;
                (*iter)->equalPaths = 1;
            }
        }

        void list() {
            typename vector<Vertex<T>*>::iterator iter;

            for (iter = graph.begin(); iter != graph.end(); iter++) {
                cout << (*iter)->getData() << ": ";
                vector<Edge<T>* > edges = (*iter)->getEdges();
                for (int i = 0; i < edges.size(); i++) {
                    cout << edges[i]->getVertex()->getData() << ", ";
                }
                cout << endl;
                
            }
            cout << endl;
        }

        void addEdge(T const &source, T const &dest) {
            bool sourceFound = false;
            bool destFound = false;
            Vertex<T>* sourceEdge;
            Vertex<T>* destEdge;

            typename vector<Vertex<T>*>::iterator iter;
            for (iter = graph.begin(); iter != graph.end(); iter++) {
                if ((*iter)->getData() == source) {
                    sourceFound = true;
                    sourceEdge = *iter;
                }

                if ((*iter)->getData() == dest) {
                    destEdge = *iter;
                    destFound = true;
                }
            }
            if (sourceFound && destFound) {
                sourceEdge->addEdge(destEdge);
                destEdge->addEdge(sourceEdge); // undirected so you add both ways
            }
            else {
                cout << "Error adding edge" << endl;
            }

        }

        void depthFirstSearch(T startNode, vector<T> &output) {
            typename vector<Vertex<T>*>::iterator iter;
            for (iter = graph.begin(); iter != graph.end(); iter++) {
                if ((*iter)->getData() == startNode && (*iter)->isVisited() == false) {
                    output.push_back(startNode);
                    (*iter)->visit(); // set visited to true
                    for (int i = 0; i < (*iter)->getEdges().size(); i++) {
                       depthFirstSearch((*iter)->getEdges()[i]->getVertex()->getData() , output);
                    }
                }
            }
        }

        vector<T> bredthFirstSearch(T startNode) {
            typename vector<Vertex<T>*>::iterator iter;
            queue<Vertex<T>*> q;
            vector<T> output;
            for (iter = graph.begin(); iter != graph.end(); iter++) {
                if ((*iter)->getData() == startNode) {
                    q.push(*iter);
                    (*iter)->visit();
                }
            }
            while (!q.empty()) {
                output.push_back(q.front()->getData());
                vector<Edge<T>* > nextEdges = q.front()->getEdges();
                for (int i = 0; i < nextEdges.size(); i++) {
                    if (!nextEdges[i]->getVertex()->isVisited()) { // Visiting a new node
                        q.push(nextEdges[i]->getVertex());
                        nextEdges[i]->getVertex()->visit();
                    }
                }
                q.pop();
            }
            return output;
            
        }

        void makeConnection(T src, T dest) {
            reset();
            typename vector<Vertex<T>*>::iterator iter;
            queue<Vertex<T>*> q;
            bool found = false;
            Vertex<T>* vtx; 
            for (iter = graph.begin(); iter != graph.end(); iter++) {
                if ((*iter)->getData() == src) {
                    q.push(*iter);
                    (*iter)->visit();
                }
            }
            // same as BFS.
            while (!q.empty() && !found) {
                vector<Edge<T>* > nextEdges = q.front()->getEdges();
                for (int i = 0; i < nextEdges.size(); i++) {
                    if (!nextEdges[i]->getVertex()->isVisited()) { // Visiting a new node
                        q.push(nextEdges[i]->getVertex());
                        nextEdges[i]->getVertex()->visit();
                        nextEdges[i]->getVertex()->cameFrom = q.front();
                        if (nextEdges[i]->getVertex()->getData() == dest) {

                            found = true;
                            vtx = nextEdges[i]->getVertex();
                        }
                    }
                }
                q.pop();
            }
            stack<T> path;
            while (vtx) { // while vtx is not undefined
                path.push(vtx->getData());
                vtx = vtx->cameFrom;
            }
            while (!path.empty()) {
                cout << path.top() << " -> ";
                path.pop();
            }
            cout << endl;
        }

        void getNumberOfShortestPaths(T startNode) {
            reset();
            typename vector<Vertex<T>*>::iterator iter;
            queue<Vertex<T>*> q;
            Vertex<T>* curr;
            for (iter = graph.begin(); iter != graph.end(); iter++) {
                if ((*iter)->getData() == startNode) {
                    q.push(*iter);
                    (*iter)->visit();
                }
            }
            while (!q.empty()) {
                curr = q.front();
                vector<Edge<T>* > nextEdges = curr->getEdges();
                for (int i = 0; i < nextEdges.size(); i++) {
                    if (!nextEdges[i]->getVertex()->isVisited()) { // Visiting a new node
                        //nextEdges[i].getVertex()->equalPaths = curr->equalPaths;
                        q.push(nextEdges[i]->getVertex());
                        nextEdges[i]->getVertex()->visit();
                        nextEdges[i]->getVertex()->layer = curr->layer + 1;
                    }
                    else {
                        if (nextEdges[i]->getVertex()->layer == curr->layer + 1) {
                            nextEdges[i]->getVertex()->equalPaths += curr->equalPaths;
                        }
                    }
                }
                q.pop();
            }
        }

        double findBetweenness(Vertex<T>* v, Edge<T>* e) {
            cout << v->getData() << "->" <<  e->getVertex()->getData() << endl;
            typename vector<Vertex<T>*>::iterator iter;
            Vertex<T>* vtx = e->getVertex();
            vector<Edge<T>* > edges = vtx->getEdges();
            for (int i = 0; i < edges.size(); i++) {
                if (edges[i]->getVertex()->layer == vtx->layer + 1) { 
                    // gets only the edges below it
                    double btw = (findBetweenness(vtx, edges[i]) /
                                  edges[i]->getVertex()->equalPaths);
                    e->addBetweennesss(btw);
                }
            }
            cout << vtx->getData() << ": " <<  e->getBetweenness() << endl;
            return e->getBetweenness();

        }

        void findCommunities() {
            typename vector<Vertex<T>*>::iterator iter;
            for (iter = graph.begin(); iter != graph.end(); iter++) {
                getNumberOfShortestPaths((*iter)->getData());
                cout << endl << "START: " << (*iter)->getData() << endl;
                vector<Edge<T>* > edges = (*iter)->getEdges();
                for (int i = 0; i < edges.size(); i++) {
                    findBetweenness((*iter), edges[i]);
                }
            }
        }
};

