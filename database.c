#include "database.h"
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

void printDatabase(DATABASE* currNode)
{
	//printf("%s ",currNode->tconst);
	//printf("%s ",currNode->titleType);
	printf("%s ",currNode->primaryTitle);
	//printf("%s ",currNode->originalTitle);
	//printf("%s ",currNode->isAdult);
	printf("%s ",currNode->startYear);
	//printf("%s ",currNode->endYear);
	printf("%s ",currNode->runtimeMinutes);
	printf("%s\n",currNode->genres);

}

/*This function builds a singlely linked list of the data that is parsed from the input file.

*/
int createDatabase(const char *filename, DATABASE *firstNode)
{ 
	unsigned int size = 0;
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
	if (size != fread(storage, sizeof(char), size, f))//Checks to see that the size of the storage array is the same as the size of the file.
	{ 
		free(storage);
		return -2; // -2 means file reading fail 
	}
	fclose(f);
	char currString[250];
	int currentState = 0;
	int stringLength = 0;
	int stringIterator = 0;
	DATABASE* currNode = firstNode;
	for(int i = 0; i < size; i++)//Creates the individual data sections that are to be used in the database structure.
	{
		if (storage[i] == '\n') 
		{
			currNode->genres = (char*)malloc(sizeof(char)*(strlen(currString) + 1));
			strncpy(currNode->genres,currString,strlen(currString));
			DATABASE* new = malloc(sizeof(DATABASE*));
			currNode->next = new;
			currNode = currNode->next;
			currentState = 0;
			lines++;
			stringIterator = 0;
			currString[0] = '\0';
		}
		else if(storage[i] == '\t')//This section divides the data into the different parts of the node. 
		{

			stringLength = strlen(currString);

			if(currentState == 0)
			{
				currNode->tconst = (char*)malloc(sizeof(char)*(stringLength + 1));
				strncpy(currNode->tconst,currString,stringLength);
			}

			else if(currentState == 1)
			{
				currNode->titleType = (char*)malloc(sizeof(char)*(stringLength + 1));
				strncpy(currNode->titleType,currString,stringLength);
			}
		
			else if(currentState == 2)
			{
				currNode->primaryTitle = (char*)malloc(sizeof(char)*(stringLength + 1));
				strncpy(currNode->primaryTitle,currString,stringLength);
			}

			else if(currentState == 3)
			{
				currNode->originalTitle = (char*)malloc(sizeof(char)*(stringLength + 1));
				strncpy(currNode->originalTitle,currString,stringLength);
			}

			else if(currentState == 4)
			{

				currNode->isAdult = (char*)malloc(sizeof(char)*(stringLength + 1));
				strncpy(currNode->isAdult,currString,stringLength);
			}

			else if(currentState == 5)
			{
				currNode->startYear = (char*)malloc(sizeof(char)*(stringLength + 1));
				strncpy(currNode->startYear,currString,stringLength);
			}

			else if(currentState == 6)
			{
				currNode->endYear = (char*)malloc(sizeof(char)*(stringLength + 1));
				strncpy(currNode->endYear,currString,stringLength);
			}

			else if(currentState == 7)
			{
				currNode->runtimeMinutes = (char*)malloc(sizeof(char)*(stringLength + 1));
				strncpy(currNode->runtimeMinutes,currString,stringLength);
			}

			else
			{
				printf("Broken Code");
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