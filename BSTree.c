// BSTree.c ... implementation of binary search tree ADT

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "BSTree.h"
#include "set.h"


typedef struct BSTNode *BSTLink;

typedef struct BSTNode {
	char *value;
	char **links;
	int nLinks;
	BSTLink left, right;
} BSTNode;

// make a new node containing a value
static
BSTLink newBSTNode(char *v, char *page)
{
 //   printf("TEST\n");
	BSTLink new = malloc(sizeof(BSTNode));
	new->links = malloc(sizeof(char *) * 100);
	assert(new != NULL);
	new->nLinks = 0;
	new->value = v;
	new->links[new->nLinks] = page;
	new->left = new->right = NULL;
	new->nLinks++;
	new->links[new->nLinks] = NULL;
	return new;
}

// create a new empty BSTree
BSTree newBSTree()
{
	return NULL;
}

// free memory associated with BSTree
void dropBSTree(BSTree t)
{
	if (t == NULL) return;
	dropBSTree(t->left);
	dropBSTree(t->right);
	free(t);
}

// display a BSTree
void showBSTree(BSTree t)
{
	void doShowBSTree(BSTree); // see later
 //   void showBSTreeNodeList(BSTree);
  //  showBSTreeNodeList(t);
	doShowBSTree(t);
}

// display BSTree root node
void showBSTreeNode(BSTree t)
{
	if (t == NULL) return;
	printf("%s ", t->value);
}

void showBSTreeNodeList(BSTree t)
{
    if (t == NULL) return;
    int i;
    printf("---------%s---------\n", t->value);
    for (i = 0; i < t->nLinks; i++) {
        printf("%s\n", t->links[i]);
	}
	showBSTreeNodeList(t->left);
	showBSTreeNodeList(t->right);
}

// print values in infix order
void BSTreeInfix(BSTree t)
{
	if (t == NULL) return;
	BSTreeInfix(t->left);
	showBSTreeNode(t);
	BSTreeInfix(t->right);
}

void BSTreeInfixTxt(BSTree t, FILE *stream)
{
	if (t == NULL) return;
	int i;
	BSTreeInfixTxt(t->left, stream);
	fprintf(stream, "%s", t->value);
    for (i = 0; i < t->nLinks; i++) {
        fprintf(stream, " %s", t->links[i]);
	}
	fprintf(stream, "\n");
	BSTreeInfixTxt(t->right, stream);
//	fclose(stream);
}

// print values in prefix order
void BSTreePrefix(BSTree t)
{
	if (t == NULL) return;
	showBSTreeNode(t);
	BSTreePrefix(t->left);
	BSTreePrefix(t->right);
}

// print values in postfix order
void BSTreePostfix(BSTree t)
{
	if (t == NULL) return;
	BSTreePostfix(t->left);
	BSTreePostfix(t->right);
	showBSTreeNode(t);
}



// count #nodes in BSTree
int BSTreeNumNodes(BSTree t)
{
	if (t == NULL)
		return 0;
	else
		return 1 + BSTreeNumNodes(t->left)
	             + BSTreeNumNodes(t->right);
}

// count #leaves in BSTree
int BSTreeNumLeaves(BSTree t)
{
    if (t == NULL) 
        return 0;
     else if (t->left == NULL && t->right == NULL)
	    return 1;
    else
        return BSTreeNumLeaves(t->left) + BSTreeNumLeaves(t->right);
}

// insert a new value into a BSTree
BSTree BSTreeInsert(BSTree t, char *v, char *page)
{
        
        
	if (t == NULL) {
	//    printf("TEST1\n");
//	printf("%s %s\n", v , page);
		return newBSTNode(v, page);
  //      printf("TEST\n");
           
	} else if (strcmp(v, t->value) < 0) { 
	//    printf("TEST2\n");
		t->left = BSTreeInsert(t->left, v, page);
		   
	}
	else if (strcmp(v, t->value) > 0) {
	//    printf("TEST3\n");
		t->right = BSTreeInsert(t->right, v, page);
		    
	}
	else {
	    int i;
	    int dup = 0;
	    for (i = 0; i < t->nLinks; i++) {
	        if (strcmp(t->links[i], page) == 0) {
	            dup = 1;
            }
        }
        if (!dup) {
            
            t->links[t->nLinks] = page;    // (v == t->value)
	        /* don't insert duplicates */
	     //   printf("%s %d %s\n",t->value,t->nLinks, t->links[t->nLinks]);
	        t->nLinks++;
	        t->links[t->nLinks] = NULL;
		}
	}
	return t;
}

// check whether a value is in a BSTree
int BSTreeFind(BSTree t, char *v)
{
	if (t == NULL)
		return 0;
	else if (strcmp(v, t->value) < 0)
		return BSTreeFind(t->left, v);
	else if (strcmp(v, t->value) > 0)
		return BSTreeFind(t->right, v);
	else // (v == t->value)
		return 1;
}

// delete root of tree
static
BSTree deleteRoot(BSTree t)
{
	// if no subtrees, tree empty after delete
	if (t->left == NULL && t->right == NULL) {
		free(t);
		return NULL;
	}
	// if only right subtree, make it the new root
	else if (t->left == NULL && t->right != NULL) {
		BSTree hold = t->right;
        free(t);
		return hold;
	}
	// if only left subtree, make it the new root
	else if (t->left != NULL && t->right == NULL) {
        BSTree hold = t->left;
		free(t);
		return hold;
	}
	// else (t->left != NULL && t->right != NULL)
	// so has two subtrees
	// - find inorder successor
	// - move its value to root
	// - delete inorder successor node
	BSTLink parent = t;
	BSTLink succ = t->right; // not null!
	while (succ->left != NULL) {
		parent = succ;
		succ = succ->left;
	}
	t->value = succ->value;
	free(succ);
	if (parent == t)
		parent->right = succ->right;
	else
		parent->left = succ->right;
	return t;
}

// delete a value from a BSTree
BSTree BSTreeDelete(BSTree t, char *v)
{
	if (t == NULL)
		return NULL;
	else if (strcmp(v, t->value) < 0)
		t->left = BSTreeDelete(t->left, v);
	else if (strcmp(v, t->value) > 0)
		t->right = BSTreeDelete(t->right, v);
	else // (v == t->value)
		t = deleteRoot(t);
	return t;
}

// ASCII tree printer
// Courtesy: ponnada
// Via: http://www.openasthra.com/c-tidbits/printing-binary-trees-in-ascii/

// data structures
typedef struct asciinode_struct asciinode;
struct asciinode_struct
{
	asciinode * left, * right;
	//length of the edge from this node to its children
	int edge_length;
	int height;
	int lablen;
	//-1=I am left, 0=I am root, 1=I am right
	int parent_dir;
	//max supported unit32 in dec, 10 digits max
	char label[11];
};

// functions
void print_level(asciinode *node, int x, int level);
void compute_edge_lengths(asciinode *node);
void compute_lprofile(asciinode *node, int x, int y);
void compute_rprofile(asciinode *node, int x, int y);
asciinode *build_ascii_tree(BSTree t);
void free_ascii_tree(asciinode *node);

#define MAX_HEIGHT 1000
int lprofile[MAX_HEIGHT];
int rprofile[MAX_HEIGHT];
#define INFINITY (1<<20)

#define MIN(X,Y)  (((X) < (Y)) ? (X) : (Y))
#define MAX(X,Y)  (((X) > (Y)) ? (X) : (Y))

int gap = 3;  // gap between left and right nodes

//used for printing next node in the same level, 
//this is the x coordinate of the next char printed
int print_next;    

//prints ascii tree for given Tree structure
void doShowBSTree(BSTree t)
{
	asciinode *proot;
	int xmin, i;
	if (t == NULL) return;
	proot = build_ascii_tree(t);
	compute_edge_lengths(proot);
	for (i = 0; i < proot->height && i < MAX_HEIGHT; i++)
		lprofile[i] = INFINITY;
	compute_lprofile(proot, 0, 0);
	xmin = 0;
	for (i = 0; i < proot->height && i < MAX_HEIGHT; i++)
		xmin = MIN(xmin, lprofile[i]);
	for (i = 0; i < proot->height; i++) {
		print_next = 0;
		print_level(proot, -xmin, i);
		printf("\n");
	}
	if (proot->height >= MAX_HEIGHT) {
		printf("(Tree is taller than %d; may be drawn incorrectly.)\n",
			MAX_HEIGHT);
	}
	free_ascii_tree(proot);
}

//This function prints the given level of the given tree, assuming
//that the node has the given x cordinate.
void print_level(asciinode *node, int x, int level)
{
	int i, isleft;
	if (node == NULL) return;
	isleft = (node->parent_dir == -1);
	if (level == 0)
	{
		for (i=0; i<(x-print_next-((node->lablen-isleft)/2)); i++)
			printf(" ");
		print_next += i;
		printf("%s", node->label);
		print_next += node->lablen;
	}
	else if (node->edge_length >= level)
	{
		if (node->left != NULL)
		{
		  for (i=0; i<(x-print_next-(level)); i++)
		  {
		    printf(" ");
		  }
		  print_next += i;
		  printf("/");
		  print_next++;
		}
		if (node->right != NULL)
		{
		  for (i=0; i<(x-print_next+(level)); i++)
		  {
		    printf(" ");
		  }
		  print_next += i;
		  printf("\\");
		  print_next++;
		}
	}
	else
	{
		print_level(node->left,
			    x-node->edge_length-1,
			    level-node->edge_length-1);
		print_level(node->right,
			    x+node->edge_length+1,
			    level-node->edge_length-1);
	}
}


//This function fills in the edge_length and
//height fields of the specified tree
void compute_edge_lengths(asciinode *node)
{
	int h, hmin, i, delta;
	if (node == NULL) return;
	compute_edge_lengths(node->left);
	compute_edge_lengths(node->right);

	/* first fill in the edge_length of node */
	if (node->right == NULL && node->left == NULL)
		node->edge_length = 0;
	else
	{
		if (node->left == NULL)
			hmin = 0;
		else {
			for (i = 0; i < node->left->height && i < MAX_HEIGHT; i++)
				rprofile[i] = -INFINITY;
			compute_rprofile(node->left, 0, 0);
			hmin = node->left->height;
		}
		if (node->right == NULL)
			hmin = 0;
		else {
			for (i=0; i<node->right->height && i < MAX_HEIGHT; i++)
		    		lprofile[i] = INFINITY;
			compute_lprofile(node->right, 0, 0);
			hmin = MIN(node->right->height, hmin);
		}
		delta = 4;
		for (i=0; i<hmin; i++) {
			int w = gap+1+rprofile[i]-lprofile[i];
			delta = (delta > w) ? delta : w;
		}

		//If the node has two children of height 1, then we allow the
		//two leaves to be within 1, instead of 2
		if (((node->left != NULL && node->left->height == 1) ||
		      (node->right != NULL && node->right->height == 1))
				&& delta > 4)
			delta--;
		node->edge_length = ((delta+1)/2) - 1;
	}

	//now fill in the height of node
	h = 1;
	if (node->left != NULL)
		h = MAX(node->left->height + node->edge_length + 1, h);
	if (node->right != NULL)
		h = MAX(node->right->height + node->edge_length + 1, h);
	node->height = h;
}

asciinode *build_ascii_tree_recursive(BSTree t)
{
	asciinode * node;

	if (t == NULL) return NULL;
	node = malloc(sizeof(asciinode));
	node->left = build_ascii_tree_recursive(t->left);
	node->right = build_ascii_tree_recursive(t->right);
	if (node->left != NULL) node->left->parent_dir = -1;
	if (node->right != NULL) node->right->parent_dir = 1;
	sprintf(node->label, "%s", t->value);
	node->lablen = strlen(node->label);;
	return node;
}


//Copy the tree into the ascii node structre
asciinode *build_ascii_tree(BSTree t)
{
	asciinode *node;
	if (t == NULL) return NULL;
	node = build_ascii_tree_recursive(t);
	node->parent_dir = 0;
	return node;
}

//Free all the nodes of the given tree
void free_ascii_tree(asciinode *node)
{
	if (node == NULL) return;
	free_ascii_tree(node->left);
	free_ascii_tree(node->right);
	free(node);
}

//The following function fills in the lprofile array for the given tree.
//It assumes that the center of the label of the root of this tree
//is located at a position (x,y).  It assumes that the edge_length
//fields have been computed for this tree.
void compute_lprofile(asciinode *node, int x, int y)
{
	int i, isleft;
	if (node == NULL) return;
	isleft = (node->parent_dir == -1);
	lprofile[y] = MIN(lprofile[y], x-((node->lablen-isleft)/2));
	if (node->left != NULL) {
		for (i=1; i <= node->edge_length && y+i < MAX_HEIGHT; i++)
			lprofile[y+i] = MIN(lprofile[y+i], x-i);
	}
	compute_lprofile(node->left, x-node->edge_length-1, y+node->edge_length+1);
	compute_lprofile(node->right, x+node->edge_length+1, y+node->edge_length+1);
}

void compute_rprofile(asciinode *node, int x, int y)
{
	int i, notleft;
	if (node == NULL) return;
	notleft = (node->parent_dir != -1);
	rprofile[y] = MAX(rprofile[y], x+((node->lablen-notleft)/2));
	if (node->right != NULL) {
		for (i=1; i <= node->edge_length && y+i < MAX_HEIGHT; i++)
	  		rprofile[y+i] = MAX(rprofile[y+i], x+i);
	}
	compute_rprofile(node->left, x-node->edge_length-1, y+node->edge_length+1);
	compute_rprofile(node->right, x+node->edge_length+1, y+node->edge_length+1);
}
