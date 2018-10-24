#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>

#include "readData.h"
#include "BSTree.h"


int GetCollection(char *filename, char url[MAX_URL][MAX_LENGTH]) {
    FILE *stream = fopen(filename, "r");
    int i = 0;
    
    while(fscanf(stream, "%s", url[i]) != -1)i++;
    url[i][0] = '\0';
    return i;
}


BSTree GetInvertedList(char url[MAX_URL][MAX_LENGTH]) {




    BSTree tree = newBSTree();
    FILE *stream;
    char str[1024];

    char tmp1[1024] = {0};
    int i = 0;
    int start = 0;

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
                tree = BSTreeInsert(tree, str, url[i]);


            }
        }

        
        start = 0;

        i++;

    }
    return tree;


}

