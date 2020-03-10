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
        vector<Edge<T> > edges;
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
            Edge<T> e(edge);
            edges.push_back(e);
        }

        vector<Edge<T> > getEdges() {
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
};

template <class T>
class Edge {
    private:
        Vertex<T>* vtx;
        double betweennesss;
    public:
        Edge(Vertex<T>* v): vtx(v) {
            betweennesss = 0;
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
            }
        }

        void list() {
            typename vector<Vertex<T>*>::iterator iter;

            for (iter = graph.begin(); iter != graph.end(); iter++) {
                cout << (*iter)->getData() << ": ";
                vector<Edge<T> > edges = (*iter)->getEdges();
                for (int i = 0; i < edges.size(); i++) {
                    cout << edges[i].getVertex()->getData() << ", ";
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
                       depthFirstSearch((*iter)->getEdges()[i].getVertex()->getData() , output);
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
                vector<Edge<T> > nextEdges = q.front()->getEdges();
                for (int i = 0; i < nextEdges.size(); i++) {
                    if (!nextEdges[i].getVertex()->isVisited()) { // Visiting a new node
                        q.push(nextEdges[i].getVertex());
                        nextEdges[i].getVertex()->visit();
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
                vector<Edge<T> > nextEdges = q.front()->getEdges();
                for (int i = 0; i < nextEdges.size(); i++) {
                    if (!nextEdges[i].getVertex()->isVisited()) { // Visiting a new node
                        q.push(nextEdges[i].getVertex());
                        nextEdges[i].getVertex()->visit();
                        nextEdges[i].getVertex()->cameFrom = q.front();
                        if (nextEdges[i].getVertex()->getData() == dest) {
                            found = true;
                            vtx = nextEdges[i].getVertex();
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


        void getBetweenness() {
            typename vector<Vertex<T>*>::iterator iter;
            for (iter = graph.begin(); iter != graph.end(); iter++) {
                bredthFirstSearch(iter->getData);
            }
        }
};

