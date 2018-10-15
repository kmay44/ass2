#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "readData.h"
#include "set.h"







void findMatchedUrls(char *str, char **argv, int argc)
{



    int i;
    Set urls = newSet();
    char strn[1024];
    
    char *t;
    int abc = 0;
    FILE *stream = fopen("invertedIndex.txt", "r");


    while (fgets(strn, 1024, stream) != NULL) {
           // printf("tttt");
           char *p = index(strn, '\n');
           p[0] = 0;
           p = strn;
      //  for (tok = strtok(query, ";"); tok && *tok; tok = strtok(NULL, ";")) {  
   //         if (strncmp(strn, tok, strlen(tok)) == 0) {
   //         printf("%d\n", argc);
        for (i = 0; i < argc; i++) {
            abc = 0;
    //        printf("%s %s\n", strn, argv[i]);
            if (strncmp(strn, argv[i], strlen(argv[i])) == 0 && !abc) {
                t = strsep(&p, " ");
                while ((t=strsep(&p, " ")) != NULL) { 
                    insertInto(urls, t);
      //              printf("%s", t);
                }
                abc = 1;
               // break;
            }
            
        }
    }
 //   }

    showSet(urls);






}
    
void findPagerank(char *str, char *list)
{










}








