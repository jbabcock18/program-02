// Jack Babcock

#include <iostream>
#include <fstream>
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
        void removeEdge(T dest) {
            for (int i = 0; i < edges.size(); i++) {
                if (edges[i]->getVertex()->getData() == dest) {
                    delete edges[i];
                    edges.erase(edges.begin() + i);
                }
            }
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
        double total;
    public:
        Edge(Vertex<T>* v): vtx(v) {
            betweennesss = 1;
            total = 0;
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
        void updateBetweenness() {
            total += betweennesss;
            betweennesss = 1;
        }
        double getTotalBetweenness() {
            return total;
        }
        void resetBetweenness() {
            total = 0;
            betweennesss = 1;
        }
};


template <class T>
class Graph {
    private:
        vector<Vertex<T>* > graph;

    public:
        Graph() {}
        ofstream ofile;

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
                vector<Edge<T>*> edges = (*iter)->getEdges();
                for (int i = 0; i < edges.size(); i++) {
                    edges[i]->updateBetweenness();
                }
            }
        }

        void hardReset() {
            reset();
            typename vector<Vertex<T>*>::iterator iter;
            for (iter = graph.begin(); iter != graph.end(); iter++) {
                vector<Edge<T>*> edges = (*iter)->getEdges();
                for (int i = 0; i < edges.size(); i++) {
                    edges[i]->resetBetweenness();
                }
            }
        }

        void list() {
            typename vector<Vertex<T>*>::iterator iter;

            for (iter = graph.begin(); iter != graph.end(); iter++) {
                ofile << (*iter)->getData() << ": ";
                vector<Edge<T>* > edges = (*iter)->getEdges();
                for (int i = 0; i < edges.size(); i++) {
                    ofile << edges[i]->getVertex()->getData() << ", ";
                }
                ofile << endl;
                
            }
            ofile << endl;
        }

        void addEdge(T source, T dest) {
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
                ofile << "Error adding edge" << endl;
            }

        }

        void removeEdge(T src, T edge) {
            typename vector<Vertex<T>*>::iterator iter;
            for (iter = graph.begin(); iter != graph.end(); iter++) {
                if ((*iter)->getData() == src) {
                    (*iter)->removeEdge(edge);
                }
            }
            // remove both cuz undirected
            for (iter = graph.begin(); iter != graph.end(); iter++) {
                if ((*iter)->getData() == edge) {
                    (*iter)->removeEdge(src);
                }
            }
        }

        void setOutputFile(string filename) {
            ofile.open(filename);
        }

        void fillGraph(string filename) {
            ifstream inFile;
            inFile.open(filename);
            if (inFile.is_open()) {
                string firstLine;
                string vertex;
                inFile >> firstLine;
                while (!inFile.eof()) {
                    inFile >> vertex;
                    if (vertex != "[undirected]") {
                        addVertex(vertex);
                    }
                    else {
                        break;
                    }
                }
                string src = "";
                string dash = "-";
                string dest = "";
                while (!inFile.eof()) {
                    inFile >> src >> dash >> dest;
                    addEdge(src, dest);
                }
            }
            inFile.close();
        }

        void depthFirstSearchStyling(T startNode) {
            ofile << "{";
            depthFirstSearch(startNode);
            ofile << "}" << endl;
        }

        void depthFirstSearch(T startNode) {
            typename vector<Vertex<T>*>::iterator iter;
            for (iter = graph.begin(); iter != graph.end(); iter++) {
                if ((*iter)->getData() == startNode && (*iter)->isVisited() == false) {
                    (*iter)->visit(); // set visited to true
                    vector<Edge<T>*> edges = (*iter)->getEdges();
                    for (int i = 0; i < edges.size(); i++) {
                        if (edges[i]->getVertex()->isVisited() == false) {
                            ofile << "(" << startNode
                                 << ","
                                 << edges[i]->getVertex()->getData() << "), ";
                        }
                        depthFirstSearch(edges[i]->getVertex()->getData());
                    }
                }
            }
        }

        void bredthFirstSearch(T startNode) {
            reset();
            typename vector<Vertex<T>*>::iterator iter;
            queue<Vertex<T>*> q;
            for (iter = graph.begin(); iter != graph.end(); iter++) {
                if ((*iter)->getData() == startNode) {
                    q.push(*iter);
                    (*iter)->visit();
                }
            }
            ofile << "{";
            while (!q.empty()) {
                vector<Edge<T>* > nextEdges = q.front()->getEdges();
                for (int i = 0; i < nextEdges.size(); i++) {
                    if (!nextEdges[i]->getVertex()->isVisited()) {
                        ofile << "(" << q.front()->getData() 
                             << "," 
                             << nextEdges[i]->getVertex()->getData()
                             << "), ";
                        q.push(nextEdges[i]->getVertex());
                        nextEdges[i]->getVertex()->visit();
                    }
                }
                q.pop();
            }
            ofile << "}" << endl << endl;
            reset();
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
            ofile << "{";
            while (path.size() != 1) {
                ofile << "(" << path.top() << ",";
                path.pop();
                ofile << path.top() << "), ";
            }
            ofile << "}" << endl;
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
            return e->getBetweenness();

        }

        void removeBetweeniest() {
            typename vector<Vertex<T>*>::iterator iter;
            Vertex<T>* maxVtx;
            Edge<T>* maxEdge;
            for (iter = graph.begin(); iter != graph.end(); iter++) {
                vector<Edge<T>*> edges = (*iter)->getEdges();
                for (int i = 0; i < edges.size(); i++) {
                    if (edges[i]->getTotalBetweenness() > maxEdge->getTotalBetweenness()) {
                        maxVtx = (*iter);
                        maxEdge = edges[i];
                    }
                }
            }
            ofile << maxVtx->getData() << "->"
                 << maxEdge->getVertex()->getData()
                 << "= "
                 << maxEdge->getTotalBetweenness() << endl;
            removeEdge(maxVtx->getData(), maxEdge->getVertex()->getData());

        }

        void calculateBetweenness() {
            hardReset();
            typename vector<Vertex<T>*>::iterator iter;
            for (iter = graph.begin(); iter != graph.end(); iter++) {
                getNumberOfShortestPaths((*iter)->getData());
                vector<Edge<T>* > edges = (*iter)->getEdges();
                for (int i = 0; i < edges.size(); i++) {
                    findBetweenness((*iter), edges[i]);
                }
            }
        }

        double getAverageBetweenness() {
            double sum = 0;
            int numOfEdges = 0;
            typename vector<Vertex<T>*>::iterator iter;
            for (iter = graph.begin(); iter != graph.end(); iter++) {
                vector<Edge<T>*> edges = (*iter)->getEdges();
                for (int i = 0; i < edges.size(); i++) {
                    sum += edges[i]->getTotalBetweenness();
                    numOfEdges++;
                }
            }
            double average = sum / numOfEdges;
            return average;
        }

        void removeAboveAverageEdges(double average) {
            typename vector<Vertex<T>*>::iterator iter;
            for (iter = graph.begin(); iter != graph.end(); iter++) {
                vector<Edge<T>*> edges = (*iter)->getEdges();
                for (int i = 0; i < edges.size(); i++) {
                    if (edges[i]->getTotalBetweenness() > average) {
                        removeEdge((*iter)->getData(), edges[i]->getVertex()->getData());
                    }
                }
            }
        }

        void dfs(T startNode, vector<T>& output) {
            typename vector<Vertex<T>*>::iterator iter;
            for (iter = graph.begin(); iter != graph.end(); iter++) {
                if ((*iter)->getData() == startNode && (*iter)->isVisited() == false) {
                    (*iter)->visit(); // set visited to true
                    output.push_back(startNode);
                    vector<Edge<T>*> edges = (*iter)->getEdges();
                    for (int i = 0; i < edges.size(); i++) {
                        dfs(edges[i]->getVertex()->getData(), output);
                    }
                }
            }
        }

        void findCommunities() {
            calculateBetweenness();
            double avg = getAverageBetweenness();
            removeAboveAverageEdges(avg);
            // recalculate
            calculateBetweenness();
            avg = getAverageBetweenness();
            removeAboveAverageEdges(avg);
            reset();
            int commCounter = 0;
            typename vector<Vertex<T>*>::iterator iter;
            for (iter = graph.begin(); iter != graph.end(); iter++) {
                if ((*iter)->isVisited() == false) {
                    vector<T> community;
                    dfs((*iter)->getData(), community);
                    ofile << "Community " << ++commCounter << ": ";
                    for (int i = 0; i < community.size(); i++) {
                        ofile << community[i];
                        if (i != community.size() -1) {
                            ofile << ", ";
                        }
                    }
                    ofile << endl << endl;
                }
            }
        }

        void followDirections(string filename) {
            ifstream inFile;
            inFile.open(filename);
            if (inFile.is_open()) {
                string command = "";
                string arg1 = "";
                string arg2 = "";
                while (!inFile.eof()) {
                    inFile >> command;
                    if (command == "or") {
                        inFile >> arg1;
                        fillGraph(arg1);
                    }
                    else if (command == "ow") {
                        inFile >> arg1;
                        setOutputFile(arg1);
                    }
                    else if (command == "dfs") {
                        inFile >> arg1;
                        depthFirstSearchStyling(arg1);
                    }
                    else if (command == "bfs") {
                        inFile >> arg1;
                        bredthFirstSearch(arg1);
                    }
                    else if (command == "mc" ) {
                        inFile >> arg1 >> arg2;
                        makeConnection(arg1, arg2);
                    }
                    else if (command == "dc") {
                        findCommunities();
                    }
                    else {
                        cout << "Error with command file" << endl;
                    }
                }
            }
        }
};

