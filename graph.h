// graph.h ... Interface to Graph of strings
// Written by John Shepherd, September 2015

#ifndef GRAPH_H
#define GRAPH_H

#define MAX_URL 	1000
#define MAX_LENGTH	50

typedef struct GraphRep *Graph;

// Function signatures


Graph newGraph(int maxV);
void  disposeGraph(Graph g);

int   nVertices(Graph);
//int   isConnected(Graph, char *, char *);
void  showGraph(Graph,int);
int addVertex(char *, char **, int);
void addEdge(Graph g, char *src, char *dest, char url[MAX_URL][MAX_LENGTH]); 
int findIndex(char *url_name, char url[MAX_URL][MAX_LENGTH]);
//static int vertexID(char *str, char **names, int N);

typedef unsigned char Num;
typedef struct GraphRep {
	int   nV;
	int   nE;
	int   **edges;
} GraphRep;


//static int vertexID(char *, char **, int);
//int addVertex(char *, char **, int);

#endif
