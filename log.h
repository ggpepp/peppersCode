struct titleList
{
    char* title;
    struct titleList* next;
};
typedef struct titleList TITLELIST;
struct log
{
    char* username;
    TITLELIST* recentAdded;
};
typedef struct log LOG;
void printToFile(LOG* info, char* fileName);
LOG* readFile(char* fileName);
TITLELIST* addToLog(TITLELIST* inputLog,char* add);
void deleteFromLog(LOG* userLog, char* search);
LOG* createNewLog(char* username);