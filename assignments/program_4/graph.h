#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <map>
#include <string>

typedef std::map<std::string, int> strint;  // lookup and find duplicates
typedef std::map<int, int> intint;          // Not used for now

struct latlon {
    double lat;                             // latitude of location
    double lon;                             // longitude of location

    // Constructors
    latlon();                               // default constructor
    latlon(const double&, const double&);   // pass by reference lat and lon of location

    // Overload Operators
    latlon operator=(const latlon&);     // copy overload
    friend std::ostream & operator<<(std::ostream&, const latlon&);  // print overload
};

struct edge {
    int toID;                               // ID of vertex edge ends at
    double weight;                          // distance between vertices (weight of edge)
    bool visited;                           // was visited during traversal?

    // Constructors
    edge(const int&, const double&);        // pass by reference ending vertice index and weight
 
    // Overload Operators
    friend std::ostream & operator << (std::ostream&, const edge&);  // print overload
};

struct vertex {
    int ID;                                 // Unique ID for vertex (used for traversal and search)
    std::string city;                       // Name of city
    std::string state;                      // Name of state
    latlon location;                        // latitude and longitude (struct)
    std::vector<edge> E;                    // holds each edge leaving vertex
    bool visited;                           // was visited during traversal?

    // Constructors
    // Passing in an ID, city, state, and the latlon struct for location
    vertex(const int&, const std::string&, const std::string&, const latlon&);

    // Overload Operators
    friend std::ostream & operator << (std::ostream&, const vertex&); // print overload
};

class Graph {
public:
    // Constructors
    Graph();                                // Default constructor
    Graph(const Graph&);                    // Copy Constructor

    vertex *createVertex(const std::string&, const std::string&, const latlon&); // creates new vertex with unique id
    int addVertex(std::string, std:: string, double, double);   // adds a vertex to the graph
    void addEdge(int, int, double, bool);   // add edge between two vertices
    void addEdge(std::string, std::string, double, bool);   // add edge between two vertices
    void printGraph();                      // print the graph for debugging
    void printVids();                       // print the vertex ID's for debugging
    void printResults(std::ostream&);       // print edge/distance results
    std::string graphViz(bool);             // prints graphViz document format
    int maxID();                            // return highest ID assigned to a vertex
    int* graphSize();                       // returns the number of vertices and edges
    int getNumEdges();                      // returns the number of edges in complete graph
    int getTotDistance();                   // returns total distance between all edges on graph
    int getEdgePerV();                      // returns number of edges per vertice
    void set_maxEdges();                    // Sets numEdges equal to int passed in

    // Overload Operators
    Graph operator = (const Graph&);       // Copy overload

    // Variables
    std::vector<vertex*> vList;             // vector holding all vertices
    int edgePerV;                           // How many edges per vertex
    double totDistance;                     // Total Distance traveled between Vertices
    std::string startLoc;                    // Name of starting Location

private:
    int ID;                                 // id counter for new vertices
    int numEdges;                           // edge count (total)
    int maxEdges;                           // Max edges allowed
    strint cityLookup;                      // map used for searching
};