#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "readData.h"
#include "set.h"







void findMatchedUrls(char *str, char **argv, int argc)
{
 /*   int i;
    Set urls = newSet();
    char strn[1024];
    char *tok;
    FILE *stream = fopen("invertedIndex.txt", "r");
    if (stream == NULL) {
        printf("%d\n", argc);
    }

printf("%d\n", argc);
    while (fgets(strn, 1024, stream) != NULL) {
    printf("tttt");
      //  for (tok = strtok(query, ";"); tok && *tok; tok = strtok(NULL, ";")) {  
   //         if (strncmp(strn, tok, strlen(tok)) == 0) {
            printf("%d\n", argc);
        for (i = 0; i < argc; i++) {
            printf("%s %s\n", strn, argv[i]);
            if (strncmp(strn, argv[i], strlen(argv[i])) == 0) {
                insertInto(urls, strn);
                printf("%s", strn);
            }
        }
    }
 //   }

    showSet(urls);

*/
    FILE *fp = fopen("invertedIndex.txt", "r");
    char string[100];
    while(fgets(string, 100, fp)) {
        printf("%s\n", string);
    }



}
    
void findPagerank(char *str, char *list)
{










}








