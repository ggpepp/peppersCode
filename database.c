#include "database.h"
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

void printDatabase(struct database* currNode)
{
	printf("%s ",currNode->tconst);
	printf("%s ",currNode->titleType);
	printf("%s ",currNode->primaryTitle);
	printf("%s ",currNode->originalTitle);
	printf("%s ",currNode->isAdult);
	printf("%s ",currNode->startYear);
	printf("%s ",currNode->endYear);
	printf("%s ",currNode->runtimeMinutes);
	printf("%s\n",currNode->genres);

}


int createDatabase(const char *filename, struct database *firstNode)
{ 
	int size = 0;
	int lines = 0;
	char *storage;
	FILE *f = fopen(filename, "rb");
	if (f == NULL) 
	{ 
		storage = NULL;
		return -1; // -1 means file opening fail 
	} 
	fseek(f, 0, SEEK_END);
	size = ftell(f);
	fseek(f, 0, SEEK_SET);
	storage = (char *)malloc(size+1);
	if (size != fread(storage, sizeof(char), size, f)) 
	{ 
		free(storage);
		return -2; // -2 means file reading fail 
	}
	fclose(f);
	char currString[250];
	int currentState = 0;
	int stringLength = 0;
	int stringIterator = 0;
	struct database* currNode = firstNode;
	for(int i = 0; i < size-1; i++)
	{

		if (storage[i] == '\n') {
			struct database* new = malloc(sizeof(struct database*));
			currNode->next = new;
			currNode = currNode->next;
			currentState = 0;
			lines++;
			stringIterator = 0;
			currString[0] = '\0';
		}
		else if((int)storage[i] == 9)
		{

			stringLength = strlen(currString);
			switch (currentState)
			{
				case 0:
					currNode->tconst = (char*)malloc(stringLength + 1);
					currNode->tconst = currString;
					break;

				case 1:
					currNode->titleType = (char*)malloc(stringLength + 1);
					currNode->titleType = currString;
					break;
			
				case 2:
					currNode->primaryTitle = (char*)malloc(stringLength + 1);
					currNode->primaryTitle = currString;
					printf("%s\n", currNode->primaryTitle);
					break;

				case 3:
					currNode->originalTitle = (char*)malloc(stringLength + 1);
					currNode->originalTitle = currString;
					break;

				case 4:
					currNode->isAdult = (char*)malloc(stringLength + 1);
					currNode->isAdult = currString;
					break;

				case 5:
					currNode->startYear = (char*)malloc(stringLength + 1);
					currNode->startYear = currString;
					break;

				case 6:
					currNode->endYear = (char*)malloc(stringLength + 1);
					currNode->endYear = currString;
					break;

				case 7:
					currNode->runtimeMinutes = (char*)malloc(stringLength + 1);
					currNode->runtimeMinutes = currString;
					break;

				case 8:
					currNode->genres = (char*)malloc(stringLength + 1);
					currNode->genres = currString;
				default:
					printf("Broken Code");
					break;
			}
			currentState++;
			stringIterator = 0;
		}
		else
		{
			currString[stringIterator] = storage[i];
			currString[stringIterator + 1] = '\0';
			stringIterator++;
		}
		
	}
	
	return lines;
}