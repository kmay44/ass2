#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <math.h>

    typedef struct page {   
	    double tf;
	    double idf;
	    double count;
	    double total;
	    double nd;
	    double td;
	    double tfidf;
	    char val[];
    } page;

void countWords(char **q, char *str, page *p);

int notInList(char str[][1024], char *s);


int main(int argc, char *argv[]) 
{

    FILE *abcd = fopen("collection.txt", "r");
    int nUrls = 0;
    char url[1024][1024];
    while(fscanf(abcd, "%s", url[nUrls]) != -1) {
        nUrls++;
    }
    url[nUrls][0] = '\0';

    
    int tmp, k;
    page pages[50];
    int i;
    char strn[1024];
    char list[1024][1024];
    char *t;
    int j =0;
    int matches = 0;
    FILE *stream = fopen("invertedIndex.txt", "r");


    while (fgets(strn, 1024, stream) != NULL) {
        char *p = index(strn, '\n');
        p[0] = 0;
        p = strn;
        for (i = 0; i < argc; i++) {
            if (strncmp(strn, argv[i], strlen(argv[i])) == 0 ) {
                t = strsep(&p, " ");
                while ((t=strsep(&p, " ")) != NULL) {
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
    while (list[i][0] != 0) {
        countWords(argv, list[i], &pages[i]);        
        pages[i].tf = pages[i].count / pages[i].total;        
        pages[i].nd = matches;
        pages[i].td = nUrls;
        pages[i].idf = log10(pages[i].td/pages[i].nd);
        pages[i].tfidf = pages[i].tf * pages[i].idf;
     //   printf("%s %lf %lf %lf %lf %lf %lf\n",list[i], pages[i].count, pages[i].total, pages[i].tf, pages[i].nd, pages[i].td,pages[i].tf * pages[i].idf);
        i++;
    }
    
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
        printf("%s %lf\n", list[i], pages[i].tfidf);
    return 0;
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

void countWords(char **q, char *url, page *p) {     
   char tmp1[1024];
   char str[1024];
        strcpy(tmp1, url);
        strcat(tmp1, ".txt");
        FILE *stream = fopen(tmp1, "r");
        int count = 0;
        int total = 0;
        int start = 0;
        int end = 0;
        char *t;
        int k =0; 
        while (fscanf(stream, " %1023s", str) != EOF) {
            char *p = &str[0];
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
        p->total = total;
        p->count = count;
}


