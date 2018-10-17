#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "readData.h"
#include "set.h"
#include "searchPagerank.h"


int main(int argc, char *argv[]) {
    findMatchedUrls(argv, argc);
    return 0;
}



void findMatchedUrls(char **argv, int argc)
{



    int i;
    Set urls = newSet();
    char strn[1024];
    
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
                t = strsep(&p, " ");
                while ((t=strsep(&p, " ")) != NULL) { 
                    insertInto(urls, t);
  
                }
                abc = 1;

            }
            
        }
    }


    showSet(urls);






}
    
void findPagerank(char *str, char *list)
{










}








