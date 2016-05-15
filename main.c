#include <stdio.h>
#include <stdlib.h>
#include "afiles.h"
#include "canalyze.h"

#define MS_PATH  256
#define SECCESS 0
#define FAIL -1
#define HEADER_WIDTH 90

const char *path = NULL;

/*Выводит массив строк на экран 
	(в массиве обязательно должен быть '\0')*/
int PrintMass(char *mass, int len)
{
	int i = 0;
	for (i = 0; mass[i] != '\0'; i++)
		printf("%c", mass[i]);
	return SECCESS;
}

int PrintHeader(const char *header)
{
	int i, fault;
	for (i = 0; header[i] != '\0'; i++);
	int length = i;
	if (length % 2 == 0)
		fault = 1;
	else
		fault = 0;
	printf("\n|");
	for (i = 0; i < HEADER_WIDTH; i++)
		printf("=");
	printf("|\n");
	for (i = 0; i < (HEADER_WIDTH - length / 2) / 2; i++)
		printf(" ");
	for (i = 0; i < length; i++)
                printf("%c", header[i]);
	for (i = 0; i < (HEADER_WIDTH - length / 2) / 2 - fault; i++)
                printf(" ");
	printf("\n|");
	for (i = 0; i < HEADER_WIDTH; i++)
                printf("=");
	printf("|\n");
	return SECCESS;
}

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		fprintf(stderr, "Ошибка: вы не ввели путь к анализируемому файлу!\n");
		exit(EXIT_FAILURE);
	}
	 if (argc > 2)
        {
                fprintf(stderr, "Ошибка: вы ввели большое количество аргументов!\n");
                exit(EXIT_FAILURE);
        }

	path = argv[1];
	/*Копирование содержимого файла в массив*/
	char *code = NULL;
	int length = 0;
	length = FileLength(path); 
	code = (char*)malloc(length*sizeof(char));
	FileToMass(path, code, length);
	/*Вывод файла на экран*/
	PrintHeader("Содержимое файла");
	PrintMass(code, length);
	PrintHeader("Имя найденной функции/количество ее вызовов");
	run_analyze(code); 
	printf("\n");
	return SECCESS;
}
