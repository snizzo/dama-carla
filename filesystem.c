
#include "filesystem.h"

/*
 * MEMLEAK RISK
 * 
 * This function returns a heap allocated string which is the result
 * from the concatenation of str1 and str2
 */
char * buildFilePath(char * str1, char * str2)
{
	
	unsigned long len = strlen(str1)+strlen(str2)+1;
	
	char * destination = (char *) malloc(sizeof(char)*len);
	
	strcpy(destination, str1);
	strcat(destination, str2);
	
	return destination;
}

/* 
 * MEMLEAK RISK
 * 
 * This function returns a pointer to a heap allocated struct token.
 * You don't have to allocate it previously but
 * you MUST free() it after use, in order to avoid memleak problems.
 */
struct token * getTokens(char * record)
{
	struct token * t = (struct token *) malloc(sizeof(struct token));
	
	char * pos;
	char * key = strtok_r(record, "|", &pos);
	strcpy(t->key, key);
	char * value = strtok_r(NULL, "|", &pos);
	strcpy(t->value, value);
	
	return t;
}

/*
 * writes a record with that value into a set of records
 */
int saveRecord(char * set, char * record, char * value)
{
	FILE * fp;
	
	char * folder = "data/";
	
	char * destination = buildFilePath(folder, set);
	
	//append to the end of file
	fp = fopen(destination, "a+");
	fprintf(fp, "%s|%s\n", record, value);
	fclose(fp);
	
	free(destination);
	
	return 0;
}

/*
 * read a single record value
 */
char * readRecord(char * set, char * record)
{
	FILE * fp;
	char * folder = "data/";
	char * destination = buildFilePath(folder, set);
	char current[100];
	
	fp = fopen(destination, "r");
	
	
	//iterate until end of file is reached
	do{
		fscanf(fp,"%s\n", current);
		
		printf("found: %s\n", current);
		
		struct token * tokens = getTokens(current);
		
		printf("key: %s\n", tokens->key);
		printf("value: %s\n", tokens->value);
		
		free(tokens);
		
		
	}while(!feof(fp));
	
	
	fclose(fp);
	free(destination);
	
	return set;
}
