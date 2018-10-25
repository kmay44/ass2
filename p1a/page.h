#define MAX_LENGTH 50
#define MAX_URL 1000


// A Page is a webpage that contains the following information: 
// - url name, number of out going links from that url,
// - what these urls are, and it's pagerank
typedef struct PageRep{
    char *name;
    int num_out;
    char** out;

    double PR;
    double prevPR;
}PageRep;

// A PageGroup Node is a list of Pages
typedef struct PageGroupRepNode{
    struct PageRep *page;
    struct PageGroupRepNode *next;
}PageGroupRepNode;

// A list of Pages
typedef struct PageGroupRep{
    struct PageGroupRepNode *first;
    struct PageGroupRepNode *last;
}PageGroupRep;

// printing the contents of the pagerep struct
void printPageDetails(PageRep page);
// inserts the pages into a list based off their page rank value
void insertedInOrder(PageGroupRep *L, PageRep *page);
// creating a new page
PageRep newPage(char *url, int numUrls);
//  get the links connected to the given url 'name'
int getLinks(char *name, char **url_list);



