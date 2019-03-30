#include "database.h"

struct avlNode {
	struct avlNode *left;
	struct avlNode *right;
	DATABASE *list;
};

typedef struct avlNode AVLNODE;

struct avlTree {
	struct avlTree *root;
};

typedef struct avlTree AVLTREE;

AVLTREE *createRoot();
AVLNODE *createNode();
int nodeHeight(AVLNODE *node);
int nodeBalance(AVLNODE *node);
AVLNODE rotateLL(AVLNODE *node);
AVLNODE rotateLR(AVLNODE *node);
AVLNODE rotateRR(AVLNODE *node);
AVLNODE rotateRL(AVLNODE *node);
AVLNODE balanceNode(AVLNODE *node);
void balanceTree(AVLTREE *root);
void insertNode(AVLTREE *root, DATABASE *node)
