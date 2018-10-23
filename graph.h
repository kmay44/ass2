// graph.h ... Interface to Graph of strings
// Written by John Shepherd, September 2015

#ifndef GRAPH_H
#define GRAPH_H

typedef struct GraphRep *Graph;

// Function signatures


Graph newGraph(int);
void  disposeGraph(Graph);
int   addEdge(Graph,char *,char *); //, char**);
int   nVertices(Graph);
int   isConnected(Graph, char *, char *);
void  showGraph(Graph,int);
int addVertex(char *, char **, int);

typedef unsigned char Num;
typedef struct GraphRep {
	int   nV;
	int   nE;
	int   **edges;
} GraphRep;


//static int vertexID(char *, char **, int);
//int addVertex(char *, char **, int);

#endif
