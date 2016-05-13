#include <stdio.h>
#include <stdlib.h>
#include "input.h"

#define MS_PATH  256

const char *path = NULL;

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		fprintf(stderr, "Ошибка: вы не ввели путь к анализируемому файлу!!! \n");
		exit(EXIT_FAILURE);
	}
	 if (argc > 2)
        {
                fprintf(stderr, "Ошибка: вы ввели большое количество аргументов!\n");
                exit(EXIT_FAILURE);
        }

	path = argv[1];
	printf("%s\n",path);
	char *code = NULL;
	FileToMass(path, code); 
	return 0;
}
