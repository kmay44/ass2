#define MAX_URL 1000
#define MAX_LENGTH 50
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "graph.h"
#include "page.h"


// A Page is a webpage that contains the following information: 
// - url name, number of out going links from that url,
// - what these urls are, and it's pagerank

// creating a new page
PageRep newPage(char *url, int numUrls) {
    PageRep new; 
    new.name = malloc(sizeof(char)*MAX_LENGTH);
    strcpy(new.name, url);
    new.out = malloc(sizeof(char *)*numUrls);
    new.num_out = 0;
    int i;
    for(i=0; i<numUrls; i++) {
        new.out[i] = malloc(sizeof(char)*MAX_LENGTH);
    }
    new.num_out = getLinks(url, new.out);
    new.PR = 1.0/numUrls;
    return new;
}

//  get the links connected to the given url 'name'
// - returns the number of links available
int getLinks(char *name, char **url_list){
    char filename[MAX_LENGTH];
    strcpy(filename, name);
    strcat(filename, ".txt");

    FILE *file = fopen(filename, "r");
    if(file==NULL) {
        fprintf(stderr, "Can't open and read %s\n", filename);
        exit(1);
    }
    
    char buff[MAX_URL];
    int n_outlinks = 0;
    char out[MAX_LENGTH];
    fgets(buff, MAX_LENGTH, file);

    while(fscanf(file, "%s", out)!= -1) {
        if(strcmp(out, "#end")==0) break;
        if(strcmp(out, name)==0) continue;
        strcpy(url_list[n_outlinks], out);
        n_outlinks++;
    }

    return n_outlinks;
}

// printing page details
void printPageDetails(PageRep page)
{
    printf("Page details:\n\n");
    printf("Page Name:\t %s\n", page.name);
    printf("Out Degrees:\t %d\n", page.num_out);
    printf("PageRank:\t %.7f\n", page.PR);      
    if(page.num_out > 0){
        printf("Outgoing Links: \n");
        int i = 0;
        for(i = 0; i < page.num_out; i ++){
            printf("\t%s\n", page.out[i]);
        }
    }
    printf("\n");
}

// PageNode for a group of Pages
PageGroupRepNode *newNodeOutput(PageRep *page){
    PageGroupRepNode *new = malloc(sizeof(PageGroupRepNode *));
    new->page = page;
    new->next = NULL;
    return new;
}

// inserts the pages into a list based off their page rank value
void insertedInOrder(PageGroupRep *L, PageRep *page)
{
    PageGroupRepNode *n = newNodeOutput(page);
    PageGroupRepNode *curr = L->first;
    PageGroupRepNode *prev = NULL;

    // nothing inside
    if(curr == NULL){
        L->first = L->last = n;
        return;
    }
    // inserting it into its proper spot
    while(curr!=NULL && page->PR < curr->page->PR){
        prev = curr;
        curr = curr->next;
    }
    // at the head and the tail
    if(prev == NULL){
        L->first = n;
        n->next = curr;
    }else{
        prev->next = n;
        n->next = curr;
        if(n->next == NULL){
            L->last = n;
        }
    }
}

