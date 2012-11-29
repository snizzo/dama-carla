#include <stdio.h>

main()
{
	int c = 0;
	
	int spaces = 0;
	int tabs = 0;
	int newlines = 0;
	
	while( (c=getchar()) !=EOF ){
		if(c=='\n')
			spaces += 1;
		if(c=='\t')
			tabs += 1;
		if(c=='\n')
			newlines += 1;
	}
	
	printf("spaces  : %i \n", spaces);
	printf("tabs    : %i \n", tabs);
	printf("newlines: %i \n", newlines);
	
	return 0;
}

