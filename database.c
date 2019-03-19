#include "database.h"
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

void printDatabase(struct database* currNode)
{
	printf("%s ",currNode->titleId);
	printf("%s ",currNode->ordering);
	printf("%s ",currNode->title);
	printf("%s ",currNode->region);
	printf("%s ",currNode->language);
	printf("%s ",currNode->types);
	printf("%s ",currNode->attributes);
	printf("%s\n",currNode->isOriginalTitle);

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
	char currString[100];
	int currentState = 0;
	int stringLength = 0;
	int stringIterator = 0;
	struct database* currNode = firstNode;
	for(int i = 0; i < 100; i++)
	{

		if (storage[i] == '\n') {
			struct database* new = malloc(sizeof(struct database*));
			currNode->next = new;
			currNode = currNode->next;
			currentState = 0;
			lines++;
			stringIterator = 0;
		}
		else if((int)storage[i] == 9)
		{
			printf("%s\n", currString);
			stringLength = strlen(currString);
			switch (currentState)
			{
				case 0:
					currNode->titleId = (char*)malloc(stringLength + 1);
					currNode->titleId = currString;
					break;

				case 1:
					currNode->ordering = (char*)malloc(stringLength + 1);
					currNode->ordering = currString;
					break;
			
				case 2:
					currNode->title = (char*)malloc(stringLength + 1);
					currNode->title = currString;
					break;

				case 3:
					currNode->region = (char*)malloc(stringLength + 1);
					currNode->region = currString;
					break;

				case 4:
					currNode->language = (char*)malloc(stringLength + 1);
					currNode->language = currString;
					break;

				case 5:
					currNode->types = (char*)malloc(stringLength + 1);
					currNode->types = currString;
					break;

				case 6:
					currNode->attributes = (char*)malloc(stringLength + 1);
					currNode->attributes = currString;
					break;

				case 7:
					currNode->isOriginalTitle = (char*)malloc(stringLength + 1);
					currNode->isOriginalTitle = currString;
					break;

				default:
					//printf("Broken Code");
					break;
			}
			currentState++;
			stringIterator = 0;
		}
		else
		{
			currString[stringIterator] = storage[i];
			stringIterator++;
		}
		
	}

	
	return lines;
}