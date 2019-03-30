#ifndef database_h
#define database_h

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
	DATABASE* next;

};

typedef struct database DATABASE;

void printDatabase(DATABASE* firstNode);
int createDatabase(const char *filename, DATABASE* firstNode);

#endif