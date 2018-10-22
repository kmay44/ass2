CC=gcc
CFLAGS=-Wall -lm -std=c11 -g -pg
HELPER=readData.c graph.c set.c
all: pagerank
pagerank: $(HELPER) pagerank.c
	$(CC) $(CFLAGS) pagerank.c $(HELPER) -o pagerank