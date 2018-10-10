#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "graph.h"
#include "set.h"
#include "readData.h"

int main(int argc, char *argv[])
{
	// initialising all the urls
	char url[MAX_URL][MAX_LENGTH];
	int numURLs;
	printf("Number of pages: %d\n", numURLs=getCollection("collection.txt", url));
	int i;
	printf("These are the urls in collection.txt:\n");
	Page *pages = malloc(sizeof(Page)*numURLs);
	for(i=0; i < numURLs; i++) {
		printf("%s\n", url[i]);
		pages[i] = newPage(url[i], numURLs);
	}


	// making the graph
	//Graph web = newGraph(numURLs);




	return 0;
}