#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>



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

int notInList(char str[][1024], char *s);
void permute(int *array,int i,int length);


int main(int argc, char *argv[])
{
 
 
    while (argv[i] != NULL) {
    
    FILE *abcd = fopen("collection.txt", "r");
    int nUrls = 0;
    char url[1024][1024];
    while(fscanf(abcd, "%s", url[nUrls]) != -1) {
        nUrls++;
    }
    url[nUrls][0] = '\0';
    
    
    
    
    
    


    

 recursive(5);*/
 int array[5] = {1,2,3,4,5};
 
    permute(array, 0, 5);
    
}




void permute(int *array,int i,int length) { 
  if (length == i){
     printArray(array,length);
     return;
  }
  int j = i;
  for (j = i; j < length; j++) { 
     swap(array+i,array+j);
     permute(array,i+1,length);
     swap(array+i,array+j);
  }
  return;
}








int notInList(char str[][1024], char *s)
{
    int i;
    for (i = 0; str[i][0] != 0; i++) {
        if (!strcmp(str[i], s)) {
            return 0;
        }
    }
    return 1;
}




