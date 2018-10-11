#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "graph.h"
#include "set.h"
#include "readData.h"


int GetCollection(char *filename, char url[MAX_URL][MAX_LENGTH]) {
    FILE *stream = fopen(filename, "r");
    int i = 0;
    
    while(fscanf(stream, "%s", url[i++]) != -1);
    url[i][0] = '\0';
    return i;
}


Graph GetGraph(char url[MAX_URL][MAX_LENGTH]) {

    Graph web = newGraph(100);
    FILE *stream;
    char str[1024] = {0};
    char tmp[1024] = {0};
    char tmp1[1024] = {0};
    int i = 0;
    int start = 0;
    int end = 0;
   // printf("%d\n", i);
    while (url[i][0] != '\0') {
  //       printf("%d\n", i);
        strcpy(tmp1, url[i]);
        strcat(tmp1, ".txt");
        stream = fopen(tmp1, "r");
 //        printf("%s\n", url[i]);
        
        
        while (fscanf(stream, "%s", str) != EOF) {
   //          printf("%d\n", i);
            if (strcmp(str, "Section-1") == 0) start = 1;
            if (strcmp(str, "#end") == 0) end = 1;
            if (start == 1 && end == 0 && strcmp(str, "Section-1")) {
                addEdge(web, url[i], str);
            }
            
        }
        
        start = 0;
        end = 0;
        i++;
   //     printf("%d\n", i);
    }
  //  showGraph(web, 0);
    
    return web;
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

