//#ifndef MAX_LENGTH 50
#define MAX_LENGTH 50
//#ifndef MAX_URL 1000
#define MAX_URL 1000
#include "graph.h"
#include "BSTree.h"
// getting the collection of urls from the file
int GetCollection(char *filename, char url[MAX_URL][MAX_LENGTH]);
// getting a list of pages for every word in a group of pages
BSTree GetInvertedList(char url[MAX_URL][MAX_LENGTH]);
