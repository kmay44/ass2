#define MAX_URL 1000
#define MAX_LENGTH 50
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "graph.h"
#include "set.h"
#include "readData.h"
#include "BSTree.h"

//////////////

/*
Set GetCollection(void) {

    FILE *stream = fopen("collection.txt", "r");
    Set list = newSet()
    char str[1024] = {0};


    while (fscanf(stream, "%s", &str) != EOF) {
        insertInto(list, &str);
    }
=======
*/

/*
int GetCollection(char *filename, char url[MAX_URL][MAX_LENGTH]) {
    FILE *stream = fopen(filename, "r");
    int i = 0;
    
    while(fscanf(stream, "%s", url[i++]) != -1);
    url[i][0] = '\0';
    return i;
>>>>>>> test2
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
=======
Graph GetGraph(char url[MAX_URL][MAX_LENGTH]) {
>>>>>>> test2

    Graph web = newGraph(100);
    FILE *stream;
    char str[1024] = {0};
    char tmp[1024] = {0};
    char tmp1[1024] = {0};
    int i = 0;
    int start = 0;
    int end = 0;

    while (url[i][0] != '\0') {

        strcpy(tmp1, url[i]);
        strcat(tmp1, ".txt");
        stream = fopen(tmp1, "r");

        
        
        while (fscanf(stream, "%s", str) != EOF) {

            if (strcmp(str, "Section-1") == 0) start = 1;
            if (strcmp(str, "#end") == 0) end = 1;
            if (start == 1 && end == 0 && strcmp(str, "Section-1")) {
                addEdge(web, url[i], str);
            }
            
        }
        
        start = 0;
        end = 0;
        i++;

    }
<<<<<<< HEAD
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


//>>>>>>> eef0b898e4f1c24224bab392cd67e7aa0cbf289d
/*BST GetInvertedList(Set list) {


    
    //return web;
}*/
/*
BSTree GetInvertedList(char url[MAX_URL][MAX_LENGTH]) {





    BSTree tree = newBSTree();
    FILE *stream;
    char str[1024];
    char tmp[1024] = {0};
    char tmp1[1024] = {0};
    int i = 0;
    int start = 0;
    int end = 0;
    char *t;
    while (url[i][0] != '\0') {

        strcpy(tmp1, url[i]);
        strcat(tmp1, ".txt");
        stream = fopen(tmp1, "r");

        
        



        while (fscanf(stream, " %1023s", str) != EOF) {
            char *p = &str[0];
            if (strcmp(str, "Section-2") == 0) start = 1;
            else if (start == 1 && strcmp(str, "#end")) {
                if ((t = index(str, '.')) != NULL) t[0] = 0;
                if ((t = index(str, ',')) != NULL) t[0] = 0;
                if ((t = index(str, ';')) != NULL) t[0] = 0;
                if ((t = index(str, '?')) != NULL) t[0] = 0; 
                for (; *p; p++) *p = tolower(*p);
             //   printf("READ DATA %s %s\n", str, url[i]);
                tree = BSTreeInsert(tree, strdup(str), strdup(url[i]));


            }
        }

        

   // }   
//}

        start = 0;
        end = 0;
        i++;

    }
    return tree;


}

*/
