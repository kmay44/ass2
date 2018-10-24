#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>

typedef struct rank {   
    char str[128][128];
    int size;
} rank ;


void swap(int *a, int *b);
void printArray(int *array, int length);
int notInList(rank r, char *s);
double permute(int *array,int i,int length, rank ranks[], int files, double total, int *optarray);
void permutation(int *array, int len);

double scaledFootrule(int *array, rank ranks[], int files);
int main(int argc, char *argv[])
{
    if (argc == 1) {
        printf("Usage : ./scaledFootrule ?.txt\n");
        exit(0);
    }
    rank ranks[50];
    int array[1024] = {0};
    int optarray[1024] = {0};
    int i;
    int j = 1;
    int nUrls =0 ;
    int nUrls1=0;
    char line[1024];
    int files =1;
    
    for (i = 1; i < argc; i++) {
        nUrls1=0;
        FILE *stream = fopen(argv[i], "r");
        if (stream != NULL) {
            while(fscanf(stream, "%s", line) != EOF) {
  
                strcpy(ranks[j].str[nUrls1],line);
                nUrls1++;
                ranks[j].size = nUrls1;
                if (notInList(ranks[0], line)) {          
                    strcpy(ranks[0].str[nUrls],line);
                    nUrls++;             
                    ranks[0].size = nUrls;   
                }
            }
            
            j++;
            fclose(stream);
        }
    }
    files = j;
    


    permutation(array, nUrls);


    double total = 100;
    total = permute(array, 0, nUrls, ranks, files, total, optarray);
    printf("%lf\n", total);
    int o = 0;
    for (o = 0; o < nUrls; o++) {
        printf("%s\n", ranks[0].str[optarray[o] - 1]);
    }
    
}

double scaledFootrule(int *array, rank ranks[], int files) {
    int i;
    int j;
    int k;
    double pos = 0;
    double total = 0;
    double n;
    double fn;
    double a;
    int found = 0;
    for (i = 0; i < ranks[0].size; i++) {
        for (j = 1; j < files; j++) {
            found = 0;
            for (k = 0; k < ranks[j].size; k++) {
                if (!strcmp(ranks[j].str[k], ranks[0].str[i])) {
          //          printf("%s %s %d   ", ranks[j].str[k], ranks[0].str[i], k+1);
                    pos = k+1;
                    found = 1;
                    break;
                }

            }
            fn = ranks[j].size;
            a = array[i];
            n = ranks[0].size;
            if (found) {
            total+=fabs(pos/fn - a/n);

            }
            
        }

    }

    return total;
}
        


double permute(int *array,int i,int length, rank ranks[], int files, double total, int *optarray) { 
    if (length == i){
        double dist = scaledFootrule(array, ranks, files);
        if (dist < total){

            int k;
            for (k = 0; k < length; k++) {
                optarray[k] = array[k];
            } 
 
            return dist;
        }
        else return total;
    }
    int j = i;
    for (j = i; j < length; j++) { 
        swap(array+i,array+j);
        total = permute(array,i+1,length, ranks, files, total, optarray);
        swap(array+i,array+j);
    }
    return total;
}



void permutation(int *array, int len)
{
    int i;
    for (i = 0; i < len; i++) {

        array[i] = i + 1;
    }
}




int notInList(rank r, char *s)
{
    int i;
    for (i = 0; i < r.size; i++) {
        if (!strcmp(r.str[i], s)) {
            return 0;
        }
    }
    return 1;
}



void swap(int *a, int *b) {
    int temp = *b;
    *b = *a;
    *a = temp;
}
void printArray(int *array, int length) {
    int i;
    for (i = 0; i < length; i++) {
        printf("%d", array[i]);
    }
    printf("\n");
}


