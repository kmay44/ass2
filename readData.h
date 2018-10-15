//#ifndef MAX_LENGTH 50
#define MAX_LENGTH 50
//#ifndef MAX_URL 1000
#define MAX_URL 1000
#include "graph.h"
#include "BSTree.h"
int GetCollection(char *filename, char url[MAX_URL][MAX_LENGTH]);
Graph GetGraph(char url[MAX_URL][MAX_LENGTH]);
BSTree GetInvertedList(char url[MAX_URL][MAX_LENGTH]);
