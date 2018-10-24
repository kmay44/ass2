// graph.c ... Graph of strings (adjacency matrix)
// Written by John Shepherd, September 2015

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "graph.h"

#define strEQ(g,t) (strcmp((g),(t)) == 0)

Graph newGraph(int maxV)
{
	Graph new = malloc(sizeof(GraphRep));
	assert(new != NULL);
	int i, j;
	new->nV = maxV;
	
	new->edges = malloc(maxV*sizeof(int *));
	assert(new->edges != NULL);
	for (i = 0; i < maxV; i++) {
		new->edges[i] = malloc(maxV*sizeof(int));
		assert(new->edges[i] != NULL);
	}
	for(i=0; i < maxV; i++){
		for (j = 0; j < maxV; j++)
			new->edges[i][j] = 0;
	}
	return new;
}


void disposeGraph(Graph g)
{
	if (g == NULL) return;
	int i;
	for (i = 0; i < g->nV; i++) {
		free(g->edges[i]);
	}

	free(g->edges);
}


int findIndex(char *url_name, char url[MAX_URL][MAX_LENGTH]) {
	int i=0;
	for(i=0; i<MAX_URL; i++) {
		if(strcmp(url[i], url_name)==0) return i;
	}
	// this means there is no url called 'url_name' in the matrix.
	return -1;
}

void addEdge(Graph g, char *src, char *dest, char url[MAX_URL][MAX_LENGTH]) {
   // printf("%s\n", src);
	int srcIn = findIndex(src, url);
	//printf("fdsfds\n");
	int destIn = findIndex(dest, url);
	g->edges[destIn][srcIn] = 1;
}
	



// nVertices(Graph)
// - return # vertices currently in Graph
int nVertices(Graph g)
{
	assert(g != NULL);
	return (g->nV);
}

// showGraph(Graph)
// - display Graph
void showGraph(Graph g, int mode)
{
	assert(g != NULL);
	if (g->nV == 0)
		printf("Graph is empty\n");
	else {
		printf("Graph has %d vertices:\n",g->nV);
		int i, j;
		if (mode == 1) {
			for (i = 0; i < g->nV; i++) {
				for (j = 0; j < g->nV; j++)
					printf("%d",g->edges[i][j]);
				putchar('\n');
			}
		}
		else {
			for (i = 0; i < g->nV; i++) {
				printf("Vertex: %s\n", (char *)g->edges[i]);
				printf("connects to\n");
				for (j = 0; j < g->nV; j++) {
					if (g->edges[i][j])
						printf("   %s\n",(char *)g->edges[j]);
				}
			}
		}
	}
}

