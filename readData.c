#define MAX_URL 1000
#define MAX_LENGTH 50
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "graph.h"
#include "set.h"
#include "readData.h"


/*
Set GetCollection(void) {

    FILE *stream = fopen("collection.txt", "r");
    Set list = newSet()
    char str[1024] = {0};


    while (fscanf(stream, "%s", &str) != EOF) {
        insertInto(list, &str);
    }
}
*/
// this could be an alternative to getcollection
// filename is the thing being read, 'url' is the an array of urls that is inside the file
// return the number of urls in the .txt file
int getCollection(char *filename, char url[MAX_URL][MAX_LENGTH]) {
    FILE *stream = fopen(filename, "r");
    int i = 0;
    while(fscanf(stream, "%s", url[i]) != -1) {
        i++;
    }
    return i;
}


/*
Graph GetGraph(Set list) {

    Graph web = newGraph(100);
    FILE *stream;
    Link curr = list->elems;
    char str[1024] = {0};


    while (curr != NULL) {
        stream = fopen(curr->val, "r");
        while (fscanf(stream, "%s", &str) != EOF) {
            addEdge(web, curr->val, &str);
        }
        
    }
}*/

Page newPage(char *url, int numUrls) {
    Page new;
    new.name = malloc(sizeof(char)*MAX_LENGTH);
    strcpy(new.name, url);
    new.out = malloc(sizeof(char *)*numUrls);

    int i;
    for(i=0; i<numUrls; i++) {
        new.out[i] = malloc(sizeof(char)*MAX_LENGTH);
    }
    new.num_out = getNumOutURLs(url, new.out);
    return new;
}

int getNumOutURLs(char *url, char **links) {
    char filename[MAX_LENGTH];
    //strcpy(filename, "Sample1/");
    strcat(filename, url);
    strcat(filename, ".txt");

    FILE *fin = fopen(filename, "r");

    char buffer[1000];
    int n_outlinks = 0;
    char outlink[20];
    fgets(buffer, 1000, fin);
    
    assert(strcmp(buffer, "#start Section-1\n")==0);    
    while(fscanf(fin, "%s", outlink) != -1){
        if(strcmp(outlink, "#end") == 0) break;
        if(strcmp(outlink, url) == 0) continue;
        strcpy(links[n_outlinks], outlink);
        n_outlinks++;
    } 
 
    return n_outlinks;
}

/*
BST GetInvertedList(Set list) {

    FILE *stream;
    Link curr = list->elems;
    
    while (curr != NULL) {
        stream = fopen(curr->val, "r");
        
        while (fscanf(stream, "%s", &str) != EOF) {

        }
        
    }   
}*/

