#include <stdio.h>
struct database
{
	char* tconst;
	char* titleType;
	char* primaryTitle;
	char* originalTitle;
	char* isAdult;
	char* startYear;
	char* endYear;
	char* runtimeMinutes;
	char* genres;
	struct database* next;

};

typedef struct database DATABASE;
void printDatabase(DATABASE* firstNode);
DATABASE* createDataNode();
void freeDatabaseNode(DATABASE* node);
int createDatabase(const char *filename, DATABASE* firstNode);