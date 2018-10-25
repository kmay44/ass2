#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <math.h>

// page struct containing all the tf and idf values
typedef struct page {   
    double tf;
    double idf;
    double count;
    double total;
    double nd;
    double td;
    double tfidf;
    char val[1024];
} page;


void countWords(char **q, char *str, page *p);
int notInList(char str[][1024], char *s);


int main(int argc, char *argv[]) 
{
    // reading through the urls to count the number of them
    int nUrls = 0;
    char url[1024][1024];
    FILE *stream = fopen("collection.txt", "r");

    
    if (stream == NULL) {
        printf("Failed to open collection.txt\n");
        exit(1);
    }
    // finding the number of urls 
    while(fscanf(stream, "%s", url[nUrls]) != -1) {
        nUrls++;
    }
    url[nUrls][0] = '\0';
    fclose(stream);
    
    // opening up the invertedindex text file
    int  k;
    page pages[50];
    int i;
    char strn[1024];
    char list[1024][1024];
    char *t;
    int j =0;
    int matches = 0;
    stream = fopen("invertedIndex.txt", "r");

    // filling up the list of urls
    while (fgets(strn, 1024, stream) != NULL) {
        char *p = index(strn, '\n');
        p[0] = 0;
        p = strn;
        for (i = 0; i < argc; i++) {
            if (strncmp(strn, argv[i], strlen(argv[i])) == 0 ) {
                t = strtok(p, " ");
                while ((t=strtok(NULL, " ")) != NULL) {
                    if (notInList(list, t)) {
                        strcpy(list[j], t);
                        j++;
                    }
                }
                list[j][0] = 0;
            }           
        }
    }
    matches = j;
    i = 0;
    // calculating the total and number of given words in the list
    while (list[i][0] != 0) {
        countWords(argv, list[i], &pages[i]);      
        strcpy(pages[i].val, list[i]);  
        pages[i].tf = pages[i].count / pages[i].total;        
        pages[i].nd = matches;
        pages[i].td = nUrls;
        pages[i].idf = log10(pages[i].td/pages[i].nd);
        pages[i].tfidf = pages[i].tf * pages[i].idf;
        i++;
    }
    
    // sorting in order
    for (i = 0; i<matches; i++) {
        for (k = 0; k < matches - i; k++) {
            if (pages[k].tfidf < pages[k + 1].tfidf) {
                page temp = pages[k];
                pages[k] = pages[k + 1];
                pages[k + 1] = temp;
            }
        }
    }
    for (i = 0; i < matches; i++) 
        printf("%s %lf\n", pages[i].val, pages[i].tfidf);
    return 0;
}

// returns 0 if s is not in the list, returns 1 if it is in the list
int notInList(char str[][1024], char *s){
    int i;
    for (i = 0; str[i][0] != 0; i++) {
        if (!strcmp(str[i], s)) {
            return 0;
        }
    }
    return 1;
}

// calculating the total number of words and the number of instances of a given word
void countWords(char **q, char *url, page *p) {     
    char tmp1[1024];
    char str[1024];
    // opening up the url text file
    strcpy(tmp1, url);
    strcat(tmp1, ".txt");
    FILE *stream = fopen(tmp1, "r");
    if (stream != NULL) {
        int count = 0;
        int total = 0;
        int start = 0;
        char *t;
        int k =0; 
        // beginning process of counting words
        while (fscanf(stream, " %1023s", str) != EOF) {
            char *p = &str[0];
            // dont start until the string surpasses 'section 2'
            if (strcmp(str, "Section-2") == 0) start = 1;
            else if (start == 1 && strcmp(str, "#end")) {
                if ((t = index(str, '.')) != NULL) t[0] = 0;
                if ((t = index(str, ',')) != NULL) t[0] = 0;
                if ((t = index(str, ';')) != NULL) t[0] = 0;
                if ((t = index(str, '?')) != NULL) t[0] = 0; 
                for (; *p; p++) *p = tolower(*p);
                for (k=0; q[k] != NULL; k++) {
                    if (strncmp(str, q[k], strlen(str)) == 0) {
                        count++;
                        break;
                    }
                }
                total++;            
            }
        }
        // total and count found and stored
        p->total = total;
        p->count = count;
    } 
    // error in opening the file
    else {
        fprintf(stderr, "Could not read file\n");
        exit(1);
    }
}



