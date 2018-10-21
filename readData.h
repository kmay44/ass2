//#ifndef MAX_LENGTH 50
#define MAX_LENGTH 50
//#ifndef MAX_URL 1000
#define MAX_URL 1000

typedef struct structpages {
	char *name;
	int num_out;
	char** out;

	double PR;
	double prevPR
}Page;

int getCollection(char *filename, char url[MAX_URL][MAX_LENGTH]);
Page newPage(char *url, int numUrls);
int getNumOutURLs(char *url, char **links);
