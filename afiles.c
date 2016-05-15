#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "afiles.h"

#define ERROR_FILE_OPEN -3


int FileLength(const char *filename)
{
	FILE *f = fopen(filename, "r");
	if (f == NULL) 
	{
		printf("Ошибка: невозможно открыть файл \"%s\"!\n", filename);
		exit(ERROR_FILE_OPEN);
	}
	struct stat st;
	int nFileLen = 0;
	int res = stat(filename, &st);
	if (res == 0)
		nFileLen = st.st_size;
	return nFileLen;
}

/*Копирует файл в массив*/
int FileToMass(const char *filename, char *mass, int lengthf) 
{
	FILE *f = fopen(filename, "r");
	if (f == NULL) 
	{
		printf("Ошибка: невозможно открыть файл \"%s\"!\n", filename);
        	exit(ERROR_FILE_OPEN);
	}
	fread(mass, lengthf, 1, f);
	fclose(f);
	mass[lengthf] = '\0';
	return 0;
}

