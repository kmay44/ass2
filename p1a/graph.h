// graph.h ... Interface to Graph of strings
// Written by John Shepherd, September 2015
// Functions taken from labs

#ifndef GRAPH_H
#define GRAPH_H

#define MAX_URL 	1000
#define MAX_LENGTH	50

typedef struct GraphRep *Graph;

// Function signatures


Graph newGraph(int maxV);
void  disposeGraph(Graph g);

int   nVertices(Graph);

void  showGraph(Graph,int);

void addEdge(Graph g, char *src, char *dest, char url[MAX_URL][MAX_LENGTH]); 
int findIndex(char *url_name, char url[MAX_URL][MAX_LENGTH]);


typedef unsigned char Num;
typedef struct GraphRep {
	int   nV;
	int   nE;
	int   **edges;
} GraphRep;

#endif
