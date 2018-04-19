// A simple representation of graph using STL
#include "graph.h"

//////////////////////////////////////////////////////////////////////////////
//          Default constructor for struct latlon
// Params:  none
// Returns: none
// Desc:    Initializes the struct latlon and defaults values to 0
//////////////////////////////////////////////////////////////////////////////
latlon::latlon() {
    lat = 0.0;
    lon = 0.0;
}

//////////////////////////////////////////////////////////////////////////////
//          Secondary constructor for struct latlon
// Params:  const double& y (lat)
//          const double& x (lon)
// Returns: none
// Desc:    Initializes the struct latlon and assigns values to the same
//          ones that were passed in by reference.
//////////////////////////////////////////////////////////////////////////////
latlon::latlon(const double& y, const double& x) {
    lat = y;
    lon = x;
}

//////////////////////////////////////////////////////////////////////////////
//          Operator = overload assignment for latlon
// Params:  const latlon& ll (struct latlon passed by reference)
// Returns: *this (returns a struct in format latlon)
// Desc:    Overloads the = operator for easy way to copy values from 
//          one latlon to another latlon
//////////////////////////////////////////////////////////////////////////////
latlon latlon::operator=(const latlon& ll) {
    lat = ll.lat;
    lon = ll.lon;

    return *this;
}

//////////////////////////////////////////////////////////////////////////////
//          Operator << overload assignment for latlon
// Params:  std::ostream output (the output file you want to write too)
//          const latlon& ll (the struct you are getting lat and lon from)
// Returns: std::ostream (output declared in function)
// Desc:    Overloads the << operator to allow easy print of values from the
//          latlon struct (double lat and double lon)
//////////////////////////////////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& output, const latlon& ll) {
    output << "(" << ll.lat << ',' << ll.lon << ")";
    return output;
}

//////////////////////////////////////////////////////////////////////////////
//          Default constructor for struct edge
// Params:  const int& ID (ID of vertex edge ends at)
//          const double& W (the distance between vertices aka. weight)
// Returns: none
// Desc:    Initializes the struct edge and defaults values to whatever
//          was passed in by reference
//////////////////////////////////////////////////////////////////////////////
edge::edge(const int& ID, const double& W) {
    toID = ID;
    weight = W;
    visited = false;
}

//////////////////////////////////////////////////////////////////////////////
//          Operator << overload assignment for edge
// Params:  std::ostream output (the output file you want to write too)
//          const edge& e (the edge getting ID, weight, and visited from)
// Returns: std::ostream output
// Desc:    Overloads the << oeprator to allow easy print of values from the
//          edge struct (ID, weight and visited)
//////////////////////////////////////////////////////////////////////////////
std::ostream & operator << (std::ostream& output, const edge& e) {
    output << "(To:" << e.toID << " W: " << e.weight << " V: " << e.visited << ")";
    return output;
}

//////////////////////////////////////////////////////////////////////////////
//          Constructor for struct vertex
// Params:  const int& id (unique id for searching)
//          const std::string& c (city)
//          const std::string& s (state)
//          const latlon& ll (struct for location defaulting to 0,0)
// Returns: none
// Desc:    Initializes the struct vertex and defaults values to whatever
//          was passed in by reference
//////////////////////////////////////////////////////////////////////////////
vertex::vertex(const int& id,
               const std::string& c, 
               const std::string& s, 
               const latlon& ll) {
    ID = id;
    city = c;
    state = s;
    location = ll;
    visited = false;
}

//////////////////////////////////////////////////////////////////////////////
//          Operator << overload assignment for vertex
// Params:  std::ostream output (the output file you want to write too)
//          const vertex& v (the vertex getting data from from)
// Returns: std::ostream output
// Desc:    Overloads the << oeprator to allow easy print of values from the
//          vertex struct (ID, City, State, Location, and number of edges)
//////////////////////////////////////////////////////////////////////////////
std::ostream & operator << (std::ostream& output, const vertex& v) {
    output << "(ID: " << v.ID << " C: " << v.city << " S: " 
            << v.state << " L: " << v.location << " Edges: " 
            << v.E.size() << ")";
    return output;
}

//////////////////////////////////////////////////////////////////////////////
//          Default Constructor for class Graph
// Params:  none
// Returns: none
// Desc:    Initializes the class with default values of 0
//////////////////////////////////////////////////////////////////////////////
Graph::Graph() {
    ID = 0;
    numEdges = 0;
}

//////////////////////////////////////////////////////////////////////////////
//          Copy Constructor for class Graph
// Params:  const Graph& G
// Returns: none
// Desc:    Copies Graph G into new Graph
//////////////////////////////////////////////////////////////////////////////
Graph::Graph(const Graph& G) {
    ID = G.ID;
    numEdges = G.numEdges;
    vList = G.vList;
    cityLookup = G.cityLookup;
}

//////////////////////////////////////////////////////////////////////////////
//          createVertex
// Params:  const std::string& c (city)
//          const std::string& s (state)
//          const latlon&ll (struct holding location)
// Returns: vertex*
// Desc:    Creates new vertex with passed in data and returns it
//////////////////////////////////////////////////////////////////////////////
vertex* Graph::createVertex(const std::string& c, const std::string& s, const latlon& ll) {
    return new vertex(ID++, c, s, ll);
}

//////////////////////////////////////////////////////////////////////////////
//          addVertex
// Params:  std::string& c (city)
//          std::string& s (state)
//          double lat (latitude for struct - initialized to 0)
//          double lon (longitude for struct - initialized to 0)
// Returns: int ID - unique ID of newly added vertex
// Desc:    Adds a vertex to both the map for search later and to the
//          vector holding all vertices, then returns the unique ID associated
//          with the particular vertex added
//////////////////////////////////////////////////////////////////////////////
int Graph::addVertex(std::string c, std::string s, double lat = 0, double lon = 0) {
    if(cityLookup.find(c + s) == cityLookup.end())
        cityLookup[c] = 0;          // add city as a key to the map
    else
        return -1;

    // add new vertex to the adj list
    vertex *temp = createVertex(c, s, latlon(lat, lon));
    vList.push_back(temp);

    // Update value that city points too
    cityLookup[c] = temp->ID;
    return temp->ID;
}

//////////////////////////////////////////////////////////////////////////////
//          addEdge
// Params:  int fromID (ID of beggining vertex)
//          int toID (ID of ending vertex)
//          double weight (distance between 2 vertices aka weight - init 0)
//          bool directed (does edge go both ways?)
// Returns: none
// Desc:    Creates new edge between two given vertices and increments the
//          total numEdges counter
//////////////////////////////////////////////////////////////////////////////
void Graph::addEdge(int fromID, int toID, double weight = 0, bool directed = false) {
    edge e1(toID, weight);
    vList[fromID]->E.push_back(e1);

    if(!directed) {
        edge e2(fromID, weight);
        vList[toID]->E.push_back(e2);
    }
    numEdges++;
}

//////////////////////////////////////////////////////////////////////////////
//          addEdge - overloaded to accept strings
// Params:  std::string fromC (city name of beginning vertex)
//          std::string toC (city name of ending vertex)
//          double weight (distance between 2 vertices aka weight - init 0)
//          bool directed (does edge go both ways?)
// Returns: none
// Desc:    Creates new edge between two given vertices and increments the
//          total numEdges counter
//////////////////////////////////////////////////////////////////////////////
void Graph::addEdge(std::string fromC, std::string toC, double weight = 0, bool directed = false) {

}

//////////////////////////////////////////////////////////////////////////////
//          printGraph
// Params:  none
// Returns: none
// Desc:    Prints out visual representation of graph for debugging
//////////////////////////////////////////////////////////////////////////////
void Graph::printGraph() {
    std::vector<vertex *>::iterator vit;
    std::vector<edge>::iterator eit;

    for (vit = vList.begin(); vit != vList.end(); vit++) {
        std::cout << *(*vit) << std::endl;

        if ((*vit)->E.size() > 0) {
            for (eit = (*vit)->E.begin(); eit != (*vit)->E.end(); eit++) {
                std::cout << "\t" << (*eit) << std::endl;
            }
        }
    }
}

//////////////////////////////////////////////////////////////////////////////
//          printVids
// Params:  none
// Returns: none
// Desc:    Prints out vertex ID's for debugging
//////////////////////////////////////////////////////////////////////////////
void Graph::printVids(){
    std::vector<vertex *>::iterator vit;
    std::vector<edge>::iterator eit;

    for (vit = vList.begin(); vit != vList.end(); vit++)
        std::cout << (*vit)->ID << std::endl;
}

//////////////////////////////////////////////////////////////////////////////
//          printResults
// Params:  None
// Returns: None
// Desc:    Outputs the total number of edges created and the total distance
//          traveled between all edges.
//////////////////////////////////////////////////////////////////////////////
void Graph::printResults(std::ostream &outfile) {
    std::cout << getNumEdges() << " edges were created traveling in total "
              << std::fixed << std::setprecision(4) << getTotDistance()
              << " miles." << std::endl;
    outfile << " - " << startLoc << std::endl;
    outfile << "\t" << std::fixed << std::setprecision(4) << getTotDistance() 
            << " miles " << getNumEdges() << " edges" << std::endl;
}

//////////////////////////////////////////////////////////////////////////////
//          graphViz
// Params:  bool directed (graph defaults to directed = true)
// Returns: string viz
// Desc:    Prints out in a format compatible with GraphViz -
//          Graphviz is used to automatically generate graphs
//          http://www.webgraphviz.com/
//////////////////////////////////////////////////////////////////////////////
std::string Graph::graphViz(bool directed = true) {
    std::vector<vertex *>::iterator vit;
    std::vector<edge>::iterator eit;

    // [label="hi", weight=100];

    std::string viz = "";
    std::string labels = "";
    std::string conns = "";
    int weight = 0;
    std::string arrow = "";

    if(directed){
        viz = "digraph G {\n";
        arrow = "->";

    }
    else {
        viz = "graph G {\n";
        arrow = "--";
    }

    for (vit = vList.begin(); vit != vList.end(); vit++) {
        if ((*vit)->E.size() > 0) {
            labels += "\t" + std::to_string((*vit)->ID) + " [label=\"" + (*vit)->city + ", " + (*vit)->state +  "\"]\n";

            for (eit = (*vit)->E.begin(); eit != (*vit)->E.end(); eit++) {
                labels += "\t" + std::to_string(eit->toID) + " [label=\"" +  
                vList[eit->toID]->city + ", " + vList[eit->toID]->state +  "\"]\n";

                weight = eit->weight;
                conns += "\t" + std::to_string((*vit)->ID) + arrow 
                    + std::to_string(eit->toID) + " [weight="+ std::to_string(weight) 
                    + ", label="+ std::to_string(weight) +"]\n";
            }
        }
    }

    viz += labels;
    viz += conns;
    viz += "}\n";

    return viz;
}

//////////////////////////////////////////////////////////////////////////////
//          maxID
// Params:  none
// Returns: int id (id of a vertex)
// Desc:    gets and returns the max id assigned to any vertex
//////////////////////////////////////////////////////////////////////////////
int Graph::maxID() {
    return ID;
}

//////////////////////////////////////////////////////////////////////////////
//          graphSize
// Params:  none
// Returns: int* vals (pointer of int vals)
// Desc:    returns the values of vList.size and numEdges
//////////////////////////////////////////////////////////////////////////////
int* Graph::graphSize() {
    int* vals = new int[2];
    vals[0] = vList.size();
    vals[1] = numEdges;
    return vals;
}

//////////////////////////////////////////////////////////////////////////////
//          getNumEdges
// Params:  none
// Returns: int (the number of edges total in graph)
// Desc:    returns the exact number of edges created during the construction
//          of the graph
//////////////////////////////////////////////////////////////////////////////
int Graph::getNumEdges() {
    return numEdges;
}

//////////////////////////////////////////////////////////////////////////////
//          getTotDistance
// Params:  none
// Returns: int (the number of edges total in graph)
// Desc:    returns the exact number of edges created during the construction
//          of the graph
//////////////////////////////////////////////////////////////////////////////
int Graph::getTotDistance() {
    return totDistance;
}

//////////////////////////////////////////////////////////////////////////////
//          getEdgePerV
// Params:  none
// Returns: int (the number of edges per vertex)
// Desc:    returns the exact number of edges allowed per vertex
//////////////////////////////////////////////////////////////////////////////
int Graph::getEdgePerV() {
    return edgePerV;
}

//////////////////////////////////////////////////////////////////////////////
//          set_numEdges
// Params:  int size (number of edges to be set)
// Returns: void
// Desc:    returns the values of vList.size and numEdges
//////////////////////////////////////////////////////////////////////////////
void Graph::set_maxEdges() {
    int edges;
    std::cout << "Edges: ";
    std::cin >> edges;

    maxEdges = numEdges * edges;
}

//////////////////////////////////////////////////////////////////////////////
//          &operator =    -  Copy constructor
// Params:  const Graph& G (graph to copy from)
// Returns: Graph (*this - copied graph)
// Desc:    Copies one Graph into another using the = operator
//////////////////////////////////////////////////////////////////////////////
Graph Graph::operator = (const Graph& G) {
    vList = G.vList;
    ID = G.ID;

    return *this;
}