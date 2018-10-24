#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "readData.h"

// getting the inverted index
// functions used are from readData.c and BSTree.c
void GetInvertedIndex(void) {

	char url[MAX_URL][MAX_LENGTH];
	GetCollection("collection.txt", url);
    InvertedIndex invertedIdx = GetInvertedList(url);
    BSTreeInfixTxt(invertedIdx, fopen("invertedIndex.txt", "w"));    

}


int main(void) {

    GetInvertedIndex();
    
    return 0;
}




