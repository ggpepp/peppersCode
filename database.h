struct database
{
	char* titleId;
	char* ordering;
	char* title;
	char* region;
	char* language;
	char* types;
	char* attributes;
	char* isOriginalTitle;
	struct database* next;

};
void printDatabase(struct database* firstNode);
int createDatabase(const char *filename, struct database *firstNode);