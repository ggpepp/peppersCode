#include "avlTree.h"
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <assert.h>
#include <strings.h>
#include <stdlib.h>

void addToList(AVLLIST* head, DATABASE* node)
{
    if(head == NULL)
    {
        head = (AVLLIST*)malloc(sizeof(AVLLIST));
        head->title = malloc((strlen(node->primaryTitle)));
        strcpy(head->title, node->primaryTitle);
        head->next = NULL;
    }
    else
    {
        AVLLIST* currNode = head;
        while(currNode->next != NULL)
        {
            currNode = currNode->next;
        }
        currNode->next = (AVLLIST*)malloc(sizeof(AVLLIST*));
        currNode->next->title = (char*)malloc(sizeof(char)*strlen(node->primaryTitle));
        strcpy(currNode->next->title, node->primaryTitle);
        currNode->next->next = NULL;
    }
    
}
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
AVLNODE* createNode()
{
    AVLNODE* node = (AVLNODE*)malloc(sizeof(AVLNODE*));

	node->left = NULL;
	node->right = NULL;
	node->list = NULL;
    node->key = NULL;

	return node;
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
    AVLNODE* node = NULL;
	AVLNODE* next = NULL;
	AVLNODE* last = NULL;

	//Inserting into an empty list	
	if( tree->root == NULL ) {
		node = createNode();
		addToList(node->list,newNode);
        node->key = (char*)malloc(strlen(key));
        strcpy(node->key,key);
		tree->root = node;
	} 
	//Inserting into a not empty list
    else {
        
		next = tree->root;

		while(next != NULL) 
        {
			last = next;
            //Key is less than the key of current node so move to the left
			if(strcasecmp(key,next->key) < 0) 
            {
				next = next->left;
			}
            //Key is greater than the key of current node so move to the right
            else if(strcasecmp(key,next->key) > 0) 
            {
				next = next->right;
			} 
            //Key is equal to the key of current node so add movie to this list
            else if(strcasecmp(key,next->key) == 0) 
            {
                addToList(next->list, newNode);	
                next = NULL;
			}
		}
		node = createNode();
        node->key = malloc(sizeof(char)*strlen(key));
		strcpy(node->key,key);
        addToList(node->list, newNode);

		if(strcasecmp(key,last->key) < 0) last->left = node;
		if(strcasecmp(key,last->key) > 0) last->right = node;
	}

	balanceTree(tree);
}
void insertNodeByName(AVLTREE* tree, DATABASE* node)
{
    char currString[50];
    int stringIterator = 0;
    for(int i = 0; i < strlen(node->originalTitle); i++)
    {
        if(node->originalTitle[i] == ' ')
        {
            if(strlen(currString) > 0)
            {
                insertNode(tree, node, currString);
                stringIterator = 0;
                currString[0] = '\0';
            }
        }
        else
        {
            currString[stringIterator] = node->originalTitle[i];
            ++stringIterator;
            currString[stringIterator] = '\0';
        }
    }
    if(strlen(currString) != 0)
    {
        insertNode(tree, node, currString);
    }
    
}
AVLNODE* search(AVLTREE* tree, char* key)
{
    AVLNODE* current = tree->root;
	while(current && strcasecmp(current->key,key) != 0) 
    {
		if(strcasecmp(key, current->key) > 0)
        {
			current = current->right;
        }
		else
        {
            current = current->left;
        }
	}
	return current;
}

void printTree(AVLNODE* head)
{
    if(head->left)printTree(head->left);
    printf("%s\n", head->key);
    if(head->right)printTree(head->right);
}
