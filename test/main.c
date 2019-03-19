#include "load_to_memory.h"
#include <stdio.h>
#include <stdlib.h>
 
int main() 
{ 
	char *content; 
	int size;
	size = load_to_memory("data.tsv", &content);
	if (size < 0) 
	{ 
		puts("Data file is not present.\nMake sure that the \"data.tsv\" file is present and restart the program.\n");
		return 1;
	}
	else { 
		printf("%d\n", size);
		int i = 0;
		while(i < 72){
			printf("%c", content[i]);
			i++;
		}
		
	}
	return 0;
}