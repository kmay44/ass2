#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "graph.h"
#include "set.h"



Set GetCollection(void) {

    FILE *stream = fopen("collection.txt", "r");
    Set list = newSet()
    char str[1024] = {0};


    while (fscanf(stream, "%s", &str) != EOF) {
        insertInto(list, &str);
    }
}

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
}
// INCOMPLETE
BST GetInvertedList(Set list) {

    FILE *stream;
    Link curr = list->elems;
    
    while (curr != NULL) {
        stream = fopen(curr->val, "r");
        
        while (fscanf(stream, "%s", &str) != EOF) {

        }
        
    }   
}

