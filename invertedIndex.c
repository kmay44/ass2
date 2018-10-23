#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "readData.h"




void GetInvertedIndex(void) {

	char url[MAX_URL][MAX_LENGTH];
	int numURLs;
	numURLs = GetCollection("collection.txt", url);


    InvertedIndex invertedIdx = GetInvertedList(url);

    BSTreeInfixTxt(invertedIdx, fopen("invertedIndex.txt", "w"));    

}
