#include "avlTree.h"
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>


AVLTREE* createTree()
{
    AVLTREE* tree = NULL;
    if((tree = (AVLTREE*)malloc(sizeof(AVLTREE))) == NULL)
    {
        return NULL;
    }
    tree->root = NULL;
    return tree;

}
AVLNODE* createNode(DATABASE* insert, char* key)
{
    AVLNODE* node = (AVLNODE*)malloc(sizeof(AVLNODE*));

	node->left = NULL;
	node->right = NULL;
	node->list = NULL;
    node->key = (char*)malloc(sizeof(char)*strlen(key));
    strncpy(node->key, key, strlen(key));

	return node;
}
AVLLIST* createList(AVLLIST* head,char* title)
{

    if((head) && (head->title) && strcasecmp(head->title, title) == 0)
    {
        return head;
    }
    AVLLIST* newHead = (AVLLIST*)malloc(sizeof(AVLLIST));
    newHead->title = (char*)malloc(sizeof(char)*(strlen(title)+1));
    strncpy(newHead->title, title, strlen(title));
    newHead->next = head;
    return newHead;
}
void printList(AVLLIST* head)
{
    AVLLIST* currNode = head;
    while(currNode != NULL)
    {
        printf("%s\n", currNode->title);
        currNode = currNode->next;
    }
}
int nodeHeight(AVLNODE* node)
{
    int leftHeight = 0;
	int rightHeight = 0;

	if(node->left) leftHeight = nodeHeight(node->left);
	if(node->right) rightHeight = nodeHeight(node->right);

    if(rightHeight > leftHeight)
    {
        return ++rightHeight;
    }
    return ++leftHeight;
}
int nodeBalance(AVLNODE* node)
{
    int nodeBalance = 0;
	if(node->left) nodeBalance += nodeHeight(node->left);
	if(node->right) nodeBalance -= nodeHeight(node->right);
	return nodeBalance;
}
AVLNODE* rotateLL(AVLNODE* node)
{
    AVLNODE* nodeA = node;
	AVLNODE* nodenodeB = nodeA->left;
	
	nodeA->left = nodenodeB->right;
	nodenodeB->right = nodeA;

	return nodenodeB;
}
AVLNODE* rotateLR(AVLNODE* node)
{
    AVLNODE* nodeA = node;
	AVLNODE* nodenodeB = nodeA->left;
	AVLNODE* nodeC = nodenodeB->right;
	
	nodeA->left = nodeC->right;
	nodenodeB->right = nodeC->left; 
	nodeC->left = nodenodeB;
	nodeC->right = nodeA;

	return nodeC;
}
AVLNODE* rotateRL(AVLNODE* node)
{
    AVLNODE* nodeA = node;
	AVLNODE* nodeB = nodeA->right;
	AVLNODE* nodeC = nodeB->left;
	
	nodeA->right = nodeC->left;
	nodeB->left = nodeC->right; 
	nodeC->right = nodeB;
	nodeC->left = nodeA;

	return nodeC;
}
AVLNODE* rotateRR(AVLNODE* node)
{
    AVLNODE* nodeA = node;
	AVLNODE* nodeB = nodeA->right;
	
	nodeA->right = nodeB->left;
	nodeB->left = nodeA; 

	return nodeB;
}
AVLNODE* balanceNode(AVLNODE* node)
{
    AVLNODE* newRoot = NULL;

	//Balances each node if they exist
	if(node->left) node->left = balanceNode(node->left);
	if(node->right) node->right = balanceNode(node->right);

	int balance = nodeBalance(node);

	if(balance >= 2) //Left heavy
    {
		if(nodeBalance(node->left) <= -1) 
        {
            newRoot = rotateLR(node);
        }
		else
        {
            newRoot = rotateLL(node);
        }
    }
    else if(balance <= -2) //Right heavy
    {
		if(nodeBalance(node->right) >= 1)
        {
            newRoot = rotateRL(node);
        }
		else 
        {
            newRoot = rotateRR(node);
        }
	}
    else //Already balanced
    {
		newRoot = node;
	}
	return newRoot;
}
void balanceTree(AVLTREE* tree)
{
	AVLNODE* newRoot = NULL;

	newRoot = balanceNode(tree->root);

	if(newRoot != tree->root )  {
		tree->root = newRoot; 
	}
}
void insertNode(AVLTREE* tree, DATABASE *newNode, char* key)
{
    AVLNODE* treeNode = NULL;
	AVLNODE* currNode = NULL;
	AVLNODE* prevNode = NULL;

	//Inserting into an empty list	
	if( tree->root == NULL ) {
		treeNode = createNode(newNode, key);
        treeNode->list = createList(treeNode->list, newNode->primaryTitle);
		tree->root = treeNode;
	} 
	//Inserting into a not empty tree
    else {
        
		currNode = tree->root;

		while(currNode != NULL) 
        {
			prevNode = currNode;
            //Key is less than the key of currNode node so move to the left
			if(strcasecmp(key,currNode->key) < 0) 
            {
				currNode = currNode->left;
			}
            //Key is greater than the key of currNode node so move to the right
            else if(strcasecmp(key,currNode->key) > 0) 
            {
				currNode = currNode->right;
			} 
            //Key is equal to the key of currNode node so add movie to this list
            else if(strcasecmp(key,currNode->key) == 0) 
            {
                currNode->list = createList(currNode->list, newNode->primaryTitle);
                currNode = NULL;
			}
		}
        if(strcasecmp(key,prevNode->key) != 0)
        {
            treeNode = createNode(newNode, key);
            treeNode->list = createList(treeNode->list, newNode->primaryTitle);

            if(strcasecmp(key,prevNode->key) < 0) prevNode->left = treeNode;
            else prevNode->right = treeNode;

        }
	}

	balanceTree(tree);
}
void insertNodeByName(AVLTREE* tree, DATABASE* node)
{
    char currString[50];
    int stringIterator = 0;
    for(int i = 0; i < strlen(node->primaryTitle); i++)
    {
        if(node->primaryTitle[i] == ' ')
        {
            if(strlen(currString) > 1)
            {
                insertNode(tree, node, currString);
            }
                stringIterator = 0;
                currString[0] = '\0';
        }
        else
        {
            currString[stringIterator] = node->primaryTitle[i];
            ++stringIterator;
            currString[stringIterator] = '\0';
        }
    }
    if(strlen(currString) > 1)
    {
        insertNode(tree, node, currString);
        stringIterator = 0;
        currString[0] = '\0';
    }
    
}
AVLNODE* search(AVLTREE* tree, char* key)
{
    AVLNODE* currNode = tree->root;
	while(currNode && strcasecmp(currNode->key,key) != 0) 
    {
		if(strcasecmp(key, currNode->key) > 0)
        {
			currNode = currNode->right;
        }
		else
        {
            currNode = currNode->left;
        }
        
	}
	return currNode;
}
void printTree(AVLNODE* head)
{
    if(head->left)
    {
        printTree(head->left);
    }

    printf("%s\n", head->key);
    if(head->right)
    {
        printTree(head->right);
    }
}
