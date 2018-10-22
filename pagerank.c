#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "graph.h"
#include "set.h"
#include "readData.h"



double w_out(char *v, char* u, Graph g, char url[MAX_URL][MAX_LENGTH], Page *pages);
double w_in(char *v, char* u, Graph g, char url[MAX_URL][MAX_LENGTH], Page *pages);

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


    int j, k = 0;
    double new;

    for(i = 0; i < maxIterations && diff >= diffPR; i++) {

    	for(j=0; j < numURLs; j++) {
    		char *currUrl = url[j];
    		double sum = 0.0;
    		for(k=0; k < g->nV; k++) {
    			if(g->edges[j][k]) {
    				if(i==0) {
    					/*initial case */
					    printf("Comparing %s & %s:\n", url[j], url[k]);
       					printf("\t weight in: %.7lf\n", w_in(url[k], currUrl, g, url, pages));
        				printf("\t weight out: %.7lf\n", w_out(url[k], currUrl, g, url, pages));

    				}
    				sum += pages[k].PR *w_in(url[k], currUrl, g, url, pages)*w_out(url[k], currUrl, g, url, pages);
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

double w_in(char* v, char* u, Graph g, char url[MAX_URL][20], Page *pages)
{

    double win = 0;
    //url11 -> url31

    int source; // = getIndex(v, urls);
    int dest; // = getIndex(u, urls);
     int i;
    for(i=0; i < MAX_URL; i++) {
    	if(strcmp(url[i], v) == 0) {
    		source = i;
    		break;
    	}
    }

    for(i=0; i < MAX_URL; i++) {
    	if(strcmp(url[i], u) == 0) {
    		dest = i;
    		break;
    	}
    }

    int d_numIn = 0;
    for(int i = 0; i < g->nV; i ++){
        d_numIn += g->edges[dest][i];
    }

    double sumSource = 0; 
    for(int i = 0; i <  pages[source].num_out; i ++){
        int pageSource = getIndex(pages[source].out[i], url); 
        for(int j = 0; j < g.nvertices; j++){
            sumSource += g.edges[pageSource][j];
        }
    }

    win = (double) d_numIn/ (double) sumSource;
    return win;
}

double w_out(char *v, char *u, Graph g, char url[MAX_URL][20], Page *pages)
{ 
    double wout = 0.0;

    int source; // = getIndex(v, urls);
    int dest; // = getIndex(u, urls);
    int i;
    for(i=0; i < MAX_URL; i++) {
    	if(strcmp(url[i], v) == 0) {
    		source = i;
    		break;
    	}
    }

    for(i=0; i < MAX_URL; i++) {
    	if(strcmp(url[i], u) == 0) {
    		dest = i;
    		break;
    	}
    }

    double d_numOut = (pages[dest].num_out == 0) ? 0.5:pages[dest].num_out;

    double sumSource = 0; 
    int pageSource = 0;
    int j;
    for(int i = 0; i <  pages[source].num_out; i ++){

    	for(j=0; j < MAX_URL; j++) {
    		if(strcmp(url[j], pages[source].out[i]) == 0) {
	    		pageSource = j;
	    		break;
    		}
    	}

        //int pageThatSourcePointsTo = getIndex(pages[source].outlinks[i], urls); 
        sumSource += (pages[pageSource].out == 0) ? 0.5:pages[pageSource].num_out;
    }

    wout = (double)d_numOut/(double)sumSource;
    return wout;
}


