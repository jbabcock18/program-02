// Jack Babcock

#include <iostream>
#include <vector>

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
};

template <class T>
class Edge {
    private:
        Vertex<T>* vtx;
    public:
        Edge(Vertex<T>* v): vtx(v) {}
        Vertex<T>* getVertex() {
            return vtx;
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
            
        }


        
};
