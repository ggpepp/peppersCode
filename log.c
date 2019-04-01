#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "log.h"

void printToFile(LOG* info, char* fileName)
{   
    remove(fileName);
    FILE* f = fopen(fileName, "w");
    fprintf(f, "%s\n", info->username);
    if(info->recentAdded != NULL)
    {
        TITLELIST* currNode = info->recentAdded->next;
        while(currNode != NULL)
        {
            fprintf(f, "%s\n", currNode->title);
            currNode = currNode->next;
        }
    }
    fclose(f);
}
LOG* readFile(char* fileName)
{
    LOG* info = (LOG*)malloc(sizeof(LOG));
    FILE* f = fopen(fileName, "r");
    if(f == NULL)
    {
        return NULL;
    }
    char username[50];
    char titleBuffer[250];
    char c = fgetc(f);
    int stringIterator = 0;
    while(c!='\n')
    {
        username[stringIterator] = c;
        stringIterator++;
        username[stringIterator] = '\0';
        c = fgetc(f);
    }
    info->username = (char*)malloc((stringIterator + 1) * sizeof(char));
    info->recentAdded = malloc(sizeof(TITLELIST));
    strncpy(info->username, username, stringIterator);
    stringIterator = 0;
    c = fgetc(f);
    TITLELIST* currNode = info->recentAdded;
    while(!feof(f))
    {
        while(c!='\n')
        {
            titleBuffer[stringIterator] = c;
            stringIterator++;
            titleBuffer[stringIterator] = '\0';
            c = fgetc(f);
        }
        currNode->next = addToLog(currNode->next,titleBuffer);
        currNode = currNode->next;
        stringIterator = 0;
        titleBuffer[0] = '\0';
        c = fgetc(f);
    }
    fclose(f);
    return info;
}
TITLELIST* addToLog(TITLELIST* inputLog,char* add)
{
    TITLELIST* newTitle = malloc(sizeof(TITLELIST));
    newTitle->title = malloc(sizeof(char) * (strlen(add)+1));
    strncpy(newTitle->title, add, strlen(add));
    if(inputLog == NULL)
    {
        newTitle->next = NULL;
    }
    else
    {
        newTitle->next = inputLog;
    }
    return newTitle;
}
void deleteFromLog(LOG* userLog, char* search)
{
    TITLELIST* currNode = userLog->recentAdded->next;
    TITLELIST* prevNode = NULL;
    while((strcasecmp(currNode->title, search) != 0) && (currNode->next!=NULL))
    {
        prevNode = currNode;
        currNode = currNode->next;
    }
    if(strcasecmp(currNode->title, search) == 0)
    {
        prevNode->next = currNode->next;
        free(currNode->title);
        free(currNode);    
    }
    else
    {
        printf("This entry is not in your list.");
    }
}
LOG* createNewLog(char* username)
{
    char *fileName = malloc(sizeof(char) * (strlen(username) + 1));
    strncpy(fileName, username, strlen(username));
    LOG* newLog = malloc(sizeof(LOG));
    newLog->username = malloc(sizeof(char) * (strlen(username) + 3));
    strncpy(newLog->username, username, strlen(username)-4);
    FILE* f = fopen(fileName, "w");
    fprintf(f,"%s\n",username);
    newLog->recentAdded = NULL;
    fclose(f);
    return newLog;
}