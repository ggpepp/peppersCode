#include "database.h"

struct avlList {
	char* title;
	struct avlList* next;
};
typedef struct avlList AVLLIST;

struct avlNode {
	struct avlNode *left;
	struct avlNode *right;
	AVLLIST* list;
	char* key;
};

typedef struct avlNode AVLNODE;

struct avlTree {
	AVLNODE *root;
};

typedef struct avlTree AVLTREE;



void addToList(AVLLIST* head, DATABASE* node);
AVLTREE *createTree();
AVLNODE *createNode();
int nodeHeight(AVLNODE *node);
int nodeBalance(AVLNODE *node);
AVLNODE* rotateLL(AVLNODE *node);
AVLNODE* rotateLR(AVLNODE *node);
AVLNODE* rotateRR(AVLNODE *node);
AVLNODE* rotateRL(AVLNODE *node);
AVLNODE* balanceNode(AVLNODE *node);
void balanceTree(AVLTREE *tree);
void insertNode(AVLTREE *root, DATABASE *node, char* key);
void insertNodeByName(AVLTREE* tree, DATABASE* node);
AVLNODE* search(AVLTREE *root, char* key);
void printTree(AVLNODE* head);
