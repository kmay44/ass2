#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include "searchPagerank.h"

int notInList(char str[][1024], char *s);
int main(int argc, char *argv[]) {


    char urls[1024][1024];
    int len = findMatchedUrls(argv, argc, urls);
    findPagerank(urls, len);
    return 0;
}



int findMatchedUrls(char **argv, int argc, char urls[][1024])
{

    int i;

    char strn[1024];
    int j =0;
    char *t;
    int abc = 0;
    FILE *stream = fopen("invertedIndex.txt", "r");


    while (fgets(strn, 1024, stream) != NULL) {

           char *p = index(strn, '\n');
           p[0] = 0;
           p = strn;

        for (i = 0; i < argc; i++) {
            abc = 0;

            if (strncmp(strn, argv[i], strlen(argv[i])) == 0 && !abc) {
                t = strtok(p, " ");
                while ((t=strtok(NULL, " ")) != NULL) { 
                    if (notInList(urls, t)) {
                        strcpy(urls[j], t);
                        j++;
                    }
                        
  
                }
                abc = 1;

            }
            
        }
    }



    fclose(stream);

    return j;


}


int notInList(char str[][1024], char *s){
    int i;
    for (i = 0; str[i][0] != 0; i++) {
        if (!strcmp(str[i], s)) {
            return 0;
        }
    }
    return 1;
}

    
void findPagerank(char str[][1024], int len)
{

    int i;
    char strn[1024];
    char *t;
    int abc = 0;
    FILE *stream = fopen("pagerankList.txt", "r");


    while (fgets(strn, 1024, stream) != NULL) {

        char *p = index(strn, '\n');
        p[0] = 0;
        p = strn;

        for (i = 0; i < len; i++) {
            abc = 0;

            if (strncmp(strn, str[i], strlen(str[i])) == 0 && !abc) {
                t = strtok(p, ",");
                printf("%s\n", t);
                abc = 1;
            }
        }
    }

    fclose(stream);

}








