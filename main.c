#include <stdio.h>
#include <stdlib.h>
#include "input.h"

#define MS_PATH  256
#define SECCESS 0
#define FAIL -1

const char *path = NULL;

/*Выводит массив строк на экран 
	(в массиве обязательно должен быть '\0')*/
int PrintMass(char *mass)
{
	int i = 0;
	for (i = 0; mass[i] != '\0'; i++)
		printf("%c", mass[i]);
	return SECCESS;
}

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
	printf("Анализация файла \"%s\"\n",path);
	char *code = NULL;
	int lenth = 0;
	lenth = FileLenth(path); 
	code = (char*)malloc(lenth*sizeof(char));
	FileToMass(path, code, lenth);
	printf("Содержимое файла:\n");
	PrintMass(code); 
	return SECCESS;
}
