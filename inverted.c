#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "readData.h"
#include "invertedIndex.h"
int main(void) {
    GetInvertedIndex();
    
    return 0;
}



void GetInvertedIndex(void) {

	char url[MAX_URL][MAX_LENGTH];
//	int numURLs;
	GetCollection("collection.txt", url);


    InvertedIndex invertedIdx = GetInvertedList(url);

    BSTreeInfixTxt(invertedIdx, fopen("invertedIndex.txt", "w"));    
}
