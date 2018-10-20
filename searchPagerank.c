#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "readData.h"
#include "set.h"
#include "searchPagerank.h"


int main(int argc, char *argv[]) {
/*

	// initialising all the urls
	char url[MAX_URL][MAX_LENGTH];
	int numURLs;
	printf("Number of pages: %d\n", numURLs=GetCollection("collection.txt", url));
	int i;
	printf("These are the urls in collection.txt:");

	for(i=0; i < numURLs - 1; i++) {

		printf("%s\n", url[i]);

	}

        

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

*/


    findMatchedUrls(argv, argc);
    return 0;
}



void findMatchedUrls(char **argv, int argc)
{



    int i;
    Set urls = newSet();
    char strn[1024];
    
    char *t;
    int abc = 0;
    FILE *stream = fopen("invertedIndex.txt", "r");


    while (fgets(strn, 1024, stream) != NULL) {

           char *p = index(strn, '\n');
           p[0] = 0;
           p = strn;

        for (i = 0; i < argc; i++) {
            abc = 0;

            if (strncmp(strn, argv[i], strlen(argv[i])) == 0 && !abc) {
                t = strsep(&p, " ");
                while ((t=strsep(&p, " ")) != NULL) { 
                    insertInto(urls, t);
  
                }
                abc = 1;

            }
            
        }
    }


    showSet(urls);

    fclose(stream);




}
    
void findPagerank(char *str, char *list)
{










}








