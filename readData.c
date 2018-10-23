#define MAX_URL 1000
#define MAX_LENGTH 50
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
//#include "graph.h"
//#include "set.h"
#include "readData.h"

//////////////

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

PageRep newPage(char *url, int numUrls) {
    PageRep new; //= malloc(sizeof(PageRep));
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


int getLinks(char *name, char **url_list){
    char filename[MAX_LENGTH];
    strcpy(filename, name);
    strcat(filename, ".txt");

    FILE *file = fopen(filename, "r");
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

void printPageDetails(PageRep page)
{
    printf("------ Page Name:\t %s\n", page.name);
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

PageGroupRepNode *newNodeOutput(PageRep *page){
    PageGroupRepNode *new = malloc(sizeof(PageGroupRepNode *));
    new->page = page;
    new->next = NULL;
    return new;
}

void insertedInOrder(PageGroupRep *L, PageRep *page)
{
    PageGroupRepNode *n = newNodeOutput(page);
    //printf("%p\n", L);
    PageGroupRepNode *curr = L->first;
    PageGroupRepNode *prev = NULL;

    if(curr == NULL){
        //printf("HI\n");
        L->first = L->last = n;
        return;
    }

    while(curr!=NULL && page->PR < curr->page->PR){
        prev = curr;
        curr = curr->next;
    }

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

/*
<<<<<<< HEAD
// INCOMPLETE
=======

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
}*/

/*
>>>>>>> eef0b898e4f1c24224bab392cd67e7aa0cbf289d
BST GetInvertedList(Set list) {

    FILE *stream;
    Link curr = list->elems;
    
    while (curr != NULL) {
        stream = fopen(curr->val, "r");
        
        while (fscanf(stream, "%s", &str) != EOF) {

        }
        
    }   
}*/

