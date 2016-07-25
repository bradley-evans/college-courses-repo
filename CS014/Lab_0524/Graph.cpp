#include "Graph.h"

// Private Member Functions

int Graph::labelsearch(string string) {
    // returns the int vector position of a particular label.
    int i = 0;
    while (i < numVerticies) {
        if (this->vertices.at(i).label == string) {
            return i;
        }
        i++;
    }
    return 0;
}

void Graph::addneighbor(int curr, int newneighbor_loc) {
    pair <int,int> pair(newneighbor_loc,1);
    this->vertices.at(curr).neighbors.push_back(pair);
}


// Public Functions
Graph::Graph() {
// Default constructor.
    
}
Graph::Graph(ifstream& file) { 
// Reads the graph input file and instantiates a graph object.
// N is at most MaxN = 50 M is at most maxM = 200
    
    // First number is number of nodes.
    // Second number is number of edges. 
    file >> this->numVerticies >> this->numEdges;
    
    // Create vector of verticies.
    int i = 0;
    string nodestring;
    for ( i=0 ; i<numVerticies ; ++i ) {
        file >> nodestring;
        Vertex vertex;
        vertex.label = nodestring;
        this->vertices.push_back(vertex);
    }
    
    // Now populate the rest of the adjacent list.
    
    while (!file.eof()) {
        string currstring, newneighbor;
        int currstring_loc, newneighbor_loc;
        file >> currstring >> newneighbor; //  set to the vertex label
        // TODO: Search function
        currstring_loc = labelsearch(currstring);
        newneighbor_loc = labelsearch(newneighbor);
        addneighbor(currstring_loc,newneighbor_loc);
    }
}

Graph::~Graph() {
// Default destructor.

}
void Graph::output_graph(const string &) {
// Outputs graph object to a .dot file, then makes a system call that calls 
// dotty on this file. In the dotty file, each node should include vertex label 
// and its distance value.

    
}
void Graph::bfs() {
// Breadth First Search. Via a BFS traversal, this function should assign each 
// individual vertex's distance to the number of hops that the vertex is from 
// the start vertex. You can find the pseudo code for BFS on graphs.pdf
    list<pair<int,int> >::iterator it;
    vertices.at(0).color = "GRAY";
    vertices.at(0).distance = 0;
    queue<Vertex> q;
    Vertex tempFront, v;
    q.push(vertices.at(0));
    while (!q.empty()) {
        tempFront = q.front();
        q.pop();
        cout << "Visiting " << tempFront.label << endl;
        for(it = tempFront.neighbors.begin(); it != tempFront.neighbors.end(); it++) {
            v = vertices.at(it->first);
            if(v.color == "WHITE") {
                v.color = "GRAY";
                v.distance = tempFront.distance + 1;
                v.prev = &tempFront;
                q.push(v);
            }
        }
        tempFront.color = "BLACK";
    }
}


/*

void functionname(int) {
// start at vertices[0]
currpos = 0

verticies[currpos];






*/