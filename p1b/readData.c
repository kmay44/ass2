#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>
#define _POSIX_C_SOURCE 200809L

#include "readData.h"
#include "BSTree.h"

// getting the collection of urls from the file
int GetCollection(char *filename, char url[MAX_URL][MAX_LENGTH]) {

    if(filename==NULL){
        fprintf(stderr, "Ensure filename is exists\n");
        exit(1);
    }
    FILE *stream = fopen(filename, "r");
    int i = 0;
    
    while(fscanf(stream, "%s", url[i]) != -1)i++;
    url[i][0] = '\0';
    return i;
}

// getting a list of pages for every word in a group of pages
BSTree GetInvertedList(char url[MAX_URL][MAX_LENGTH]) {

    BSTree tree = newBSTree();
    FILE *stream;
    char str[1024];

    char tmp1[1024] = {0};
    int i = 0;
    int start = 0;

    char *t;
    // going through each letter in the url
    while (url[i][0] != '\0') {

        strcpy(tmp1, url[i]);
        strcat(tmp1, ".txt");
        stream = fopen(tmp1, "r");

        // normalising the words and inserting the words into the tree
        while (fscanf(stream, " %1023s", str) != EOF) {
            char *p = &str[0];
            if (strcmp(str, "Section-2") == 0) start = 1;
            else if (start == 1 && strcmp(str, "#end")) {
                if ((t = index(str, '.')) != NULL) t[0] = 0;
                if ((t = index(str, ',')) != NULL) t[0] = 0;
                if ((t = index(str, ';')) != NULL) t[0] = 0;
                if ((t = index(str, '?')) != NULL) t[0] = 0; 
                for (; *p; p++) *p = tolower(*p);
                tree = BSTreeInsert(tree, str, url[i]);
            }
        }

        
        start = 0;
        i++;

    }
    return tree;

}

