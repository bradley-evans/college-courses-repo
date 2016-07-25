#ifndef VERTEX_H_
#define VERTEX_H_

#include <string>
#include <list>
#include <map>
#include <climits>
#include <utility>

using namespace std;

class Vertex {
public:
  list<pair<int, int> > neighbors;    // An STL list of STL pairs. For each 
                                      // int,int pair , the integer values are 
                                      // the neighboring vertex's position in 
                                      // the graph object's vector vertices and
                                      // the cost of the edge to that neighbor.
  string label; // Individual vertex's label.
  int distance; // The distance from source to the vertex. Initially distance 
                // should be INT_MAX for all vertices. Distance gets updated 
                // during BFS traversal.
  string color; 
  Vertex* prev; // The distance from source to the vertex. Initially distance 
                // should be INT_MAX for all vertices. Distance gets updated 
                // during BFS traversal.
  
  Vertex():label(""),distance(INT_MAX),color("WHITE"),prev(0){}
  ~Vertex(){}
};

#endif /* VERTEX_H_ */