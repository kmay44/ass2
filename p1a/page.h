


#define MAX_LENGTH 50

#define MAX_URL 1000



typedef struct PageRep{
    char *name;
    int num_out;
    char** out;

    double PR;
    double prevPR;
}PageRep;


typedef struct PageGroupRepNode{
    struct PageRep *page;
    struct PageGroupRepNode *next;
}PageGroupRepNode;


typedef struct PageGroupRep{
    struct PageGroupRepNode *first;
    struct PageGroupRepNode *last;
}PageGroupRep;


void printPageDetails(PageRep page);


void insertedInOrder(PageGroupRep *L, PageRep *page);
PageRep newPage(char *url, int numUrls);
int getNumOutURLs(char *url, char **links);
void printPage(PageRep page);
int getLinks(char *name, char **url_list);



