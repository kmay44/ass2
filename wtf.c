#include <stdio.h>




int main(int argc, char *argv[]) {




    FILE *stream = fopen("invertedIndex.txt", "r");
    char str[1024];
    while (fgets(str, 1024, stream) != NULL) {
        printf("%s\n", str);
    }
}


 
