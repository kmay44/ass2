#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "readData.h"




int main(int argc, char *argv[])
{
	// initialising all the urls
	char url[MAX_URL][MAX_LENGTH];
	int numURLs;
	printf("Number of pages: %d\n", numURLs=GetCollection("collection.txt", url));
	int i;
	printf("These are the urls in collection.txt:");
//	Page *pages = malloc(sizeof(Page)*numURLs);
	for(i=0; i < numURLs - 1; i++) {
//	    strcat(url[i], ".txt");
		printf("%s\n", url[i]);
	//	pages[i] = newPage(url[i], numURLs);
	}
    

	// making the graph
	Graph web = GetGraph(url);
	showGraph(web, 0);
	
	
	
    BSTree tree = GetInvertedList(url);
    showBSTree(tree);
    showBSTreeNodeList(tree);

	return 0;
}
