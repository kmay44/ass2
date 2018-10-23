#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "readData.h"
#include "set.h"








void findMatchedUrls(char *str, char **argv, int argc)

#include "searchPagerank.h"


int main(int argc, char *argv[]) {


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

           // printf("tttt");
           char *p = index(strn, '\n');
           p[0] = 0;
           p = strn;
      //  for (tok = strtok(query, ";"); tok && *tok; tok = strtok(NULL, ";")) {  
   //         if (strncmp(strn, tok, strlen(tok)) == 0) {
   //         printf("%d\n", argc);
        for (i = 0; i < argc; i++) {
            abc = 0;
    //        printf("%s %s\n", strn, argv[i]);


           char *p = index(strn, '\n');
           p[0] = 0;
           p = strn;

        for (i = 0; i < argc; i++) {
            abc = 0;


            if (strncmp(strn, argv[i], strlen(argv[i])) == 0 && !abc) {
                t = strsep(&p, " ");
                while ((t=strsep(&p, " ")) != NULL) { 
                    insertInto(urls, t);

      //              printf("%s", t);
                }
                abc = 1;
               // break;

  
                }
                abc = 1;

            }
            
        }
    }

 //   }

    showSet(urls);




    showSet(urls);

    fclose(stream);



}
    
void findPagerank(char *str, char *list)
{










}



/*
    double damping = 0;
    int maxIterations = 0;
    double diffPR = 0;

    if(argc == 1){
        damping = 0.85;
        diffPR = 0.000001;
        maxIterations = 1000; 
        printf("DEFAULT VALUES USED\n");
    } else if(argc == 4){
        damping = atof(argv[1]);
        diffPR = atof(argv[2]);
        maxIterations = atoi(argv[3]);
    }else{
        fprintf(stderr, "Incorrect number of arguments supplied\n");
        fprintf(stderr, "USAGE: ./pagerank [damping] [diffPR] [maxIterations]\n");
        exit(1);
    }

    double diff = diffPR;

    int timesRan = 0;

    for(int i = 0; i < maxIterations && diff >= diffPR; i++){

        for(int j = 0; j < nurls; j++){

            char *currentUrl = urls[j];
            double sum_right = 0.0;
            for(int k = 0; k < linkMatrix.nvertices; k++){
                if(linkMatrix.edges[j][k]){
            if(i == 0){
            printf("Comparison between %s & %s:\n", urls[j], urls[k]);
            printf("\t win: %.7lf\n", w_in(urls[k], currentUrl, linkMatrix, urls, pages));
            printf("\t wout: %.7lf\n", w_out(urls[k], currentUrl, linkMatrix, urls, pages));
            }
                    sum_right += pages[k].pageRank * w_in(urls[k], currentUrl, linkMatrix, urls, pages) * w_out(urls[k], currentUrl, linkMatrix, urls, pages);   
                }
            }
            pages[j].p_pageRank = pages[j].pageRank;
            pages[j].pageRank = (double)(1-damping)/(double)nurls + damping*sum_right;
        }

        diff = 0;
        for(int j = 0; j < nurls; j ++){
            double new = pages[j].pageRank - pages[j].p_pageRank;
            diff = (diff < 0) ? -diff:diff;
            diff += new;
        }

        diff = (diff < 0) ? -diff:diff;
        printf("iteration %d: %.7f\n", i+1, diff);

        timesRan = i;
    }

double w_in(char* v, char* u, Graph linkMatrix, char urls[MAX_URLS][20], Webpage *pages)
{

    double win = 0;
    //url11 -> url31

    int source = getIndex(v, urls);
    int dest = getIndex(u, urls);

    int destIncoming = 0;
    for(int i = 0; i < linkMatrix.nvertices; i ++){
        destIncoming += linkMatrix.edges[dest][i];
    }

    double sumOfInlinksOfPagesThatSourcePointsTo = 0; 
    for(int i = 0; i <  pages[source].n_outlinks; i ++){
        int pageThatSourcePointsTo = getIndex(pages[source].outlinks[i], urls); 
        for(int j = 0; j < linkMatrix.nvertices; j++){
            sumOfInlinksOfPagesThatSourcePointsTo += linkMatrix.edges[pageThatSourcePointsTo][j];
        }
    }

    win = (double) destIncoming/ (double) sumOfInlinksOfPagesThatSourcePointsTo;
    return win;
}

double w_out(char *v, char *u, Graph linkMatrix, char urls[MAX_URLS][20], Webpage *pages)
{ 
    double wout = 0.0;

    int source = getIndex(v, urls);
    int dest = getIndex(u, urls);

    double destOutgoing = (pages[dest].n_outlinks == 0) ? 0.5:pages[dest].n_outlinks;

    double sumOfOutlinksOfPagesThatSourcePointsTo = 0; 
    for(int i = 0; i <  pages[source].n_outlinks; i ++){
        int pageThatSourcePointsTo = getIndex(pages[source].outlinks[i], urls); 
        sumOfOutlinksOfPagesThatSourcePointsTo += (pages[pageThatSourcePointsTo].n_outlinks == 0) ? 0.5:pages[pageThatSourcePointsTo].n_outlinks;
    }

    wout = (double)destOutgoing/(double)sumOfOutlinksOfPagesThatSourcePointsTo;
    return wout;
}*/


