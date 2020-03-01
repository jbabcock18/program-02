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
    public:
        Vertex(T info): data(info) {}

        T getData() {
            return data;
        }

        void addEdge(Vertex<T>* edge) {
            Edge<T> e(edge);
            edges.push_back(e);
        }
};

template <class T>
class Edge {
    private:
        Vertex<T>* vtx;
    public:
        Edge(Vertex<T>* v): vtx(v) {}
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

        void listVerticies() {
            typename vector<Vertex<T>*>::iterator iter;

            for (iter = graph.begin(); iter != graph.end(); iter++) {
                cout << (*iter)->getData() << "\t";
            }
            cout << endl;
        }

        void addEdge() {
        }
        
};
