#include <stdio.h>
#include <stdlib.h>
 
typedef struct Node
{

	char *name;
	int links
	char** out;
    Page next;
    
}Node;

Page createPage(char);

typedef struct GraphRep {
{
    int nV;
    struct Page** adjLists;
} GraphRep;

struct Graph* createGraph(int vertices);
void addEdge(struct Graph* Graph, int src, int dest);
void printGraph(struct Graph* Graph);

int main()
{
    struct Graph* Graph = createGraph(6);
    addEdge(Graph, 0, 1);
    addEdge(Graph, 0, 2);
    addEdge(Graph, 1, 2);
    addEdge(Graph, 1, 4);
    addEdge(Graph, 1, 3);
    addEdge(Graph, 2, 4);
    addEdge(Graph, 3, 4);
    addEdge(Graph, 4, 6);
    addEdge(Graph, 5, 1);
    addEdge(Graph, 5, 6);
 
    printGraph(Graph);
 
    return 0;
}

 
 
Page createPage(char *v)
{
    Page p = malloc(sizeof(Page));
    p->name = v;
    p->next = NULL;
    return p;
}
 

Graph createGraph(int vertices)
{
    Graph new = malloc(sizeof(GraphRep));
    new->nV = vertices;
 
    new->adjLists = malloc(vertices * sizeof(Page));
 
    int i;
    for (i = 0; i < vertices; i++)
        new->adjLists[i] = NULL;
 
    return new;
}
 
void addEdge(Graph g, char *src, char *dest)
{
    // Add edge from src to dest
    Page p = createPage(dest);
    p->next = g->adjLists[src];
    g->adjLists[src] = p;
 
    // Add edge from dest to src
    p = createPage(src);
    p->next = g->adjLists[dest];
    g->adjLists[dest] = p;
}
 
void printGraph(Graph g)
{
    int v;
    for (v = 0; v < g->nV; v++)
    {
        Page temp = g->adjLists[v];
        printf("\n Adjacency list of vertex %d\n ", v);
        while (temp)
        {
            printf("%s -> ", temp->name);
            temp = temp->next;
        }
        printf("\n");
    }
}
