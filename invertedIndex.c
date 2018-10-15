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
	printf("These are the urls in collection.txt:\n");

	for(i=0; i < numURLs - 1; i++) {

		printf("%s\n", url[i]);

	}
 

	// making the graph
	//Graph web = GetGraph(url);
	//showGraph(web, 0);
	
	
	
    InvertedIndex invertedIdx = GetInvertedList(url);

    BSTreeInfixTxt(invertedIdx, fopen("invertedIndex.txt", "w"));    
  //  showBSTree(tree);
 //  showBSTreeNodeList(tree);

    

    
	return 0;
}
