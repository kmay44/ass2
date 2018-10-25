#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>



// finding the urls with the given search word
int findMatchedUrls(char **argv, int argc, char urls[][1024]);

// checking if 's' is in the list of strings
int notInList(char str[][1024], char *s);

// using the previous calculated pageranks to find the url
void findPagerank(char str[][1024], int len);
