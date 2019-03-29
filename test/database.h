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
void printDatabase(struct database* firstNode);
int createDatabase(const char *filename, struct database *firstNode);