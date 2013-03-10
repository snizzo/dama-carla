
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
 * 
 * example:
 * 
 * saveRecord("config", "username", "password");
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
 * 
 * example:
 * 
 * char * value = readRecord("config", "matrioska");
	
	printf("value found: %s\n", value);
	
	free(value);
 * 
 */
char * readRecord(char * set, char * record)
{
	FILE * fp;
	char * folder = "data/";
	char * destination = buildFilePath(folder, set);
	char * value = NULL;
	char current[100];
	
	fp = fopen(destination, "r");
	
	
	//iterate until end of file is reached
	do{
		fscanf(fp,"%s\n", current);
		
		struct token * tokens = getTokens(current);
		
		if(strcmp(tokens->key, record)==0){
			value = (char *) malloc(sizeof(char)*strlen(tokens->value));
			strcpy(value, tokens->value);
			free(tokens);
			break;
		}
		
		free(tokens);
		
	}while(!feof(fp));
	
	fclose(fp);
	free(destination);
	
	return value;
}

int deleteRecord(char * set, char * record)
{
	FILE * original, * temp;
	char * dataFolder = "data/";
	char * tempFolder = "temp/";
	char * dataDestination = buildFilePath(dataFolder, set);
	char * tempDestination = buildFilePath(tempFolder, set);
	char current[100];
	
	original = fopen(dataDestination, "r");
	temp = fopen(tempDestination, "w");
	
	//iterate until end of file is reached
	do{
		fscanf(original,"%s\n", current);
		
		struct token * tokens = getTokens(current);
		
		if(strcmp(tokens->key, record)!=0){
			//append to the end of file
			fprintf(temp, "%s|%s\n", tokens->key, tokens->value);
		}
		
		free(tokens);
		
	}while(!feof(original));
	
	fclose(original);
	fclose(temp);
	
	original = fopen(dataDestination, "w");
	temp = fopen(tempDestination, "r");
	
	//iterate until end of file is reached
	do{
		
		fscanf(temp,"%s\n", current);
		fprintf(original, "%s\n", current);
		
	}while(!feof(temp));
	
	fclose(original);
	fclose(temp);
	
	free(dataDestination);
	free(tempDestination);
	
	return 1;
}
