#include <stdio.h>
#include <stdlib.h>
#include "input.h"

#define ERROR_FILE_OPEN -3

/*Копирует файл в массив*/
int FileToMass(const char *filename, char *code) 
{
	FILE *f = fopen(filename, "r");
	if (f == NULL) 
	{
		printf("Ошибка: невозможно открыть файл %s!\n", filename);
        	exit(ERROR_FILE_OPEN);
	}
	if((fgets(buf, SIZE, f) == NULL) && ferror(f))
	{
		fprintf(stderr, "Error reading from stream\n");
		exit(2);
	}
	fclose(f);
	return 0;
}
