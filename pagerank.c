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
	}

	// new graph
	Graph g = newGraph(numURLs);


	// calculating the pagerank
	double damping = 0;
    int maxIterations = 0;
    double diffPR = 0.0;

    double diff = diffPR;

    if(argc == 1){
    	// these are the default values
        damping = 0.85;
        diffPR = 0.000001;
        maxIterations = 1000; 
        printf("DEFAULT VALUES USED\n");
    } else if(argc == 4){
    	// everything is given
        damping = atof(argv[1]);
        diffPR = atof(argv[2]);
        maxIterations = atoi(argv[3]);
    }else{
    	// not everything is given
        fprintf(stderr, "Incorrect number of arguments supplied\n");
        fprintf(stderr, "USAGE: ./pagerank [damping] [diffPR] [maxIterations]\n");
        exit(1);
    }


    int i, j, k = 0;
    double new;

    for(i = 0; i < maxIterations && diff >= diffPR; i++) {

    	for(j=0; j < numURLs; j++) {
    		char *currUrl = url[j];
    		double sum = 0.0;
    		for(k=0; k < g->nV; k++) {
    			if(g->edges[j][k]) {
    				if(i==0) {
    					/*initial case */
					    printf("Comparing %s & %s:\n", urls[j], urls[k]);
       					printf("\t weight in: %.7lf\n", w_in(urls[k], currUrl, g, url, pages));
        				printf("\t weight out: %.7lf\n", w_out(urls[k], currUrl, g, url, pages));

    				}
    				sum += pages[k].PR *w_in(urls[k], currUrl, g, url, pages)*w_out(urls[k], currUrl, g, url, pages);
    			}
    		}
    		pages[j].prevPR = pages[j].PR;
    		pages[j].PR = (double)(1-damping)/(double)numURLs + damping*sum;
    	}
    	diff = 0;
    	for(j=0; j < numURLs; j++) {
    		new = pages[j].PR - pages[j].prevPR;
    		if(diff < 0) {
    			diff = -diff;
    		} 
    		diff+= new;
    	}
    	if(diff < 0) {
    		diff = -diff;
    	}
    	printf("Iteration %d: %.7f\n", i+1, diff);


    }




	return 0;
}