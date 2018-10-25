// graph.h ... Interface to Graph of strings
// Written by John Shepherd, September 2015
// Functions taken from labs

#ifndef GRAPH_H
#define GRAPH_H

#define MAX_URL 	1000
#define MAX_LENGTH	50

typedef struct GraphRep *Graph;

// Function signatures

// making a new graph with maxV nodes
Graph newGraph(int maxV);
// freeing the graph
void  disposeGraph(Graph g);

// finding the number of vertices
int   nVertices(Graph);
// displaying graph
void  showGraph(Graph,int);
// adding an edge between two indexes in a graph
void addEdge(Graph g, char *src, char *dest, char url[MAX_URL][MAX_LENGTH]); 
// finding the index of a given url_name
int findIndex(char *url_name, char url[MAX_URL][MAX_LENGTH]);

// graph struct 
typedef unsigned char Num;
typedef struct GraphRep {
	int   nV;
	int   nE;
	int   **edges;
} GraphRep;

#endif
