#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "readData.h"
#include "invertedIndex.h"
#include "searchPagerank.h"
#include "BSTree.h"


int main(int argc, char *argv[])
{
	// initialising all the urls
	char url[MAX_URL][MAX_LENGTH];
	int numURLs;
	printf("Number of pages: %d\n", numURLs=GetCollection("collection.txt", url));
	int i;
	printf("These are the urls in collection.txt:");

	for(i=0; i < numURLs - 1; i++) {

		printf("%s\n", url[i]);

	}
 /*   int input = 0;
    while (scanf("%d", &input) == 1) {
        printf("1 - Generate Graph\n2- Generate invertedIndex.txt\n");
        if (input == 1) {
    	    Graph web = GetGraph(url);
	        showGraph(web, 0);
        }
        if (input == 2) {
            */
        

	// making the graph
	Graph web = GetGraph(url);
	showGraph(web, 0);
	
	
    InvertedIndex invertedIdx = GetInvertedList(url);
  //  if (argv[1] != NULL) 
    
    showBSTree(invertedIdx);
    showBSTreeNodeList(invertedIdx);
    FILE *stream = fopen("invertedIndex.txt", "w");
    BSTreeInfixTxt(invertedIdx, stream);
    fclose(stream); 

    
     
  //  printf("%s\n", argv[1]);
 //   findMatchedUrls(argv, argc);






	return 0;
}
