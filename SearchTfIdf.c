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

void stuff(char **q, char *str, page *p);

int no(char str[][1024], char *s);


int main(int argc, char *argv[]) 
{

    FILE *abcd = fopen("collection.txt", "r");
    int nUrls = 0;
    char url[1024][1024];
    while(fscanf(abcd, "%s", url[nUrls]) != -1) {
        nUrls++;
    }
    url[nUrls][0] = '\0';

    
    
    
    
    
    page pages[50];
    int i;

    char strn[1024];
    char list[1024][1024];
    char *t;
  //  int abc = 0;
    int j =0;
    FILE *stream = fopen("invertedIndex.txt", "r");


    while (fgets(strn, 1024, stream) != NULL) {

        char *p = index(strn, '\n');
        p[0] = 0;
        p = strn;

        for (i = 0; i < argc; i++) {
//            abc = 0;

            if (strncmp(strn, argv[i], strlen(argv[i])) == 0 ) {
                t = strsep(&p, " ");
                while ((t=strsep(&p, " ")) != NULL) {
          //          printf("%s\n", t);
                    if (no(list, t)) {
                    strcpy(list[j], t);
                    j++;
                    }
                }
    //            abc = 1;
                list[j][0] = 0;
            }
            
        }
    }
    
    

    i = 0;
    while (list[i][0] != 0) {
      //  printf("PAGE %d ---------------\n", i);
        stuff(argv, list[i], &pages[i]);
        
        pages[i].tf = pages[i].count / pages[i].total;
        
        pages[i].nd = j;
        pages[i].td = nUrls;
        pages[i].idf = log10(pages[i].td/pages[i].nd);
        pages[i].tfidf = pages[i].tf * pages[i].idf;
     //   printf("%s %lf %lf %lf %lf %lf %lf\n",list[i], pages[i].count, pages[i].total, pages[i].tf, pages[i].nd, pages[i].td,pages[i].tf * pages[i].idf);
   //   printf("t %s %lf\n", list[i], pages[i].tfidf);
       // printf("%s\n", list[i]);
        i++;
    }
    int tmp, k;
  //  page temp;
  
    for (i = 0; i<j; i++) {
        for (k = 0; k < j - i; k++) {
            if (pages[k].tfidf < pages[k + 1].tfidf) {
                page temp = pages[k];
                pages[k] = pages[k + 1];
                pages[k + 1] = temp;
            }
        }
    }
   // i =0;
  /*  
    double min = 0;
    int o;
    for (i = 0; list[i][0] != 0; i++) {
        min = 0;
        for (j = 0; list[j][0] != 0; j++) {
            if (pages[j].tfidf > min) {
                min = pages[j].tfidf;
                o = j;
            }
        }
        
        printf("%s %lf\n", list[o], pages[o].tfidf);
    }
 
      

     //   i++;
    */
    for (i = 0; i < j; i++) 
        printf("%s %lf\n", list[i], pages[i].tfidf);
    return 0;

}

int no(char str[][1024], char *s)
{
    int i;
    for (i = 0; str[i][0] != 0; i++) {
        if (!strcmp(str[i], s)) {
            return 0;
        }
    }
    return 1;


}

void stuff(char **q, char *url, page *p) {
        
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
             //           printf("match %s\n", str);
                        count++;
                        break;
                    }
                //    printf("%s\n", str);
              //      printf("%s\n", q[k]);
 
                }
                total++;
                


            }
        }
    //    printf("%d %d\n", count, total);
        p->total = total;
        p->count = count;

}



