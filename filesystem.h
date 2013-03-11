#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct token {
	char key[100];
	char value[100];
};

int isPresentRecord(char * set, char * record);
int saveRecord(char * set, char * record, char * value);
char * readRecord(char * set, char * record);
char * buildFilePath(char * str1, char * str2);
struct token * getTokens(char * record);
int deleteRecord(char * set, char * record);

#endif
