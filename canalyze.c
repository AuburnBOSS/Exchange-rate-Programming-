#include <stdio.h>
#include <stdlib.h>
#include "canalyze.h"

#define MAXT 100000

struct token_t
{
	int id;
	int start;
	int len;
} table[MAXT];

int i_id = 1;

int comparison(char *token, const char * word, int l)
{
	int i;
	for (i = 0; i < l; i++)
		if (token[i] != word[i])
			return 0;
	return 1;
}

int analyze(char *token, int l)
{
	if (comparison(token, "{", l))
	{
		table[i_id].id = 1;
	}
	if (comparison(token, "}", l))
	{
		table[i_id].id = 2;
	}
	if (comparison(token, "(", l))
	{
		table[i_id].id = 3;
	}
	if (comparison(token, ")", l))
	{
		table[i_id].id = 4;
	}
	if (comparison(token, ";", l))
	{
		table[i_id].id = 5;
	}
	if (comparison(token, ",", l) || comparison(token, "!", l) || comparison(token, "+=", l) || comparison(token, "-", l) ||
		comparison(token, "!=", l) || comparison(token, "*", l) || comparison(token, "*=", l) || comparison(token, "/", l) || 
		comparison(token, "/=", l) || comparison(token, "%", l) || comparison(token, "%=", l) || comparison(token, "=", l) || 
		comparison(token, "==", l) ||comparison(token, "+", l) || comparison(token, "++", l) || comparison(token, "sizeof", l) ||
		comparison(token, "--", l) || comparison(token, "-=", l) || comparison(token, "->", l) || comparison(token, "&", l) || 
		comparison(token, "&&", l) || comparison(token, "&=", l) || comparison(token, "|", l) || comparison(token, "||", l) || 
		comparison(token, "|=", l) || comparison(token, ">", l) || comparison(token, ">>", l) || comparison(token, ">>=", l) ||
		comparison(token, "<", l) || comparison(token, "<<", l) || comparison(token, "<<=", l) || comparison(token, "new", l) || 
		comparison(token, "#include", l) || comparison(token, "delete", l))
	{
		table[i_id].id = 6;
	}
	if (comparison(token, "int", l) || comparison(token, "short", l) || comparison(token, "long", l)
		|| comparison(token, "char", l) || comparison(token, "float", l) || comparison(token, "double", l) 
		|| comparison(token, "void", l))
	{
		table[i_id].id = 9;
	}
	if (table[i_id].id == 0 && table[i_id - 1].id == 9)
		table[i_id].id = 8;
	return 0;
}

int skip_spaces(char *mass, int p)
{
	int s = 0;
	while (mass[p] == ' ' || mass[p] == '\t' || mass[p] == '\n')
		{
			p++;
			s++;
		}
	return s;
}


int length_token(char *mass, int p)
{
	int buff = p;
	if (mass[p] == '(' || mass[p] == ')' || mass[p] == '{'
		|| mass[p] == '}' || mass[p] == ';')
		return 1;
	if (mass[p] == ',') return 1;
	if (mass[p] == '!')	if (mass[p + 1] == '=') return 2;
						else return 1;
	if (mass[p] == '*')	if (mass[p + 1] == '=') return 2;
						else return 1;
	if (mass[p] == '/')	if (mass[p + 1] == '=') return 2;
						else return 1;
	if (mass[p] == '%')	if (mass[p + 1] == '=') return 2;
						else return 1;
	if (mass[p] == '=')	if (mass[p + 1] == '=') return 2;
						else return 1;
	if (mass[p] == '+')	if (mass[p + 1] == '+' || mass[p + 1] == '=') return 2;
						else return 1;
	if (mass[p] == '&')	if (mass[p + 1] == '&' || mass[p + 1] == '=') return 2;
						else return 1;
	if (mass[p] == '|')	if (mass[p + 1] == '|' || mass[p + 1] == '=') return 2;
						else return 1;
	if (mass[p] == '-')	if (mass[p + 1] == '-' || mass[p + 1] == '=' || mass[p + 1] == '>') return 2;
						else return 1;
	if (mass[p] == '>')	if (mass[p + 1] == '>' || mass[p + 1] == '=')  
		if (mass[p + 1] == '>' && mass[p + 2] == '=') return 3;
						else return 2; 
						else return 1;
	if (mass[p] == '<')	if (mass[p + 1] == '<' || mass[p + 1] == '=')
		if (mass[p + 1] == '<' && mass[p + 2] == '=') return 3;
						else return 2;
						else return 1;
	while (mass[p] != ' ' && mass[p] != '\t' && mass[p] != '\n'
		&& mass[p] != '(' && mass[p] != ')' && mass[p] != '{'
		&& mass[p] != '}' && mass[p] != ';' && mass[p] != '>' 
		&& mass[p] != '<' && mass[p] != '=' && mass[p] != '+'
		&& mass[p] != '-' && mass[p] != '&'	&& mass[p] != '|'
		&& mass[p] != '%' && mass[p] != ',' && mass[p] != '*' 
		&& mass[p] != '/' && mass[p] != '!')
		p++;
	return p - buff;
}

int find_func(char *mass)
{
	int i, start, finish, fl = 0, sum = 0;
	for (i = 0; i <= i_id - 3; i++)
		if (table[i].id == 9 && table[i + 1].id == 8 && table[i + 2].id == 3)
		{
			int j, p;
			start = table[i].start;
			for (j = i; table[j].id != 4 && j <= i_id - 3; j++);
			if (table[j + 1].id == 5)
			{
				finish = j + 1;
				printf("\n");
				/*for (j = start; j <= finish; j++)
					printf("%c", mass[j]);*/
				for (j = 0; j < table[i + 1].len; j++)
					printf("%c", mass[table[i + 1].start + j]);
				printf(": ");
				sum = 0;
				for (p = 0; mass[p] != '\0'; p++)
				{
					fl = 0;
					if (mass[p] == mass[table[i + 1].start])
					{
						fl = 1;
						for (j = 0; j < table[i + 1].len; j++)
							if (mass[table[i + 1].start + j] != mass[p + j])
								fl = 0;
					}
					if (fl == 1)
					{
						fl = 0;
						for (j = 0; j < MAXT; j++)
							if (table[j].start == p)
								fl = 1;
					}
					sum += fl;
				}
				printf("%d", sum - 1);
			}
			if (table[j + 1].id == 1)
			{
				for (; table[j].id != 2 && j <= i_id; j++);
				finish = table[j].start;
				printf("\n");
				/*for (j = start; j <= finish; j++)
					printf("%c", mass[j]);*/
				for (j = 0; j < table[i + 1].len; j++)
					printf("%c", mass[table[i + 1].start + j]);
				printf(": ");
				sum = 0;
				for (p = 0; mass[p] != '\0'; p++)
				{
					fl = 0;
					if (mass[p] == mass[table[i + 1].start])
					{
						fl = 1;
						for (j = 0; j < table[i + 1].len; j++)
							if (mass[table[i + 1].start + j] != mass[p + j])
								fl = 0;
					}
					if (fl == 1)
					{
						fl = 0;
						for (j = 0; j < MAXT; j++)
							if (table[j].start == p)
								fl = 1;
					}
					sum += fl;
				}
				printf("%d", sum - 1);
			}
		}

}


int run_analyze(char *mass)
{
	int i = 0, len = 0, j;
	char *buff;
	for (i = 0; i < MAXT; i++)
	{
		table[i].id = 0;
		table[i].len = 0;
		table[i].start = 0;
	}
	for (i = 0; mass[i] != '\0'; i++)
		{
			i += skip_spaces(mass, i);
			len = length_token(mass, i);
			if (len > 0)
			{
				buff = (char*)malloc((len)*sizeof(char));
				for (j = 0; j < len; j++)
					buff[j] = mass[i + j];
				analyze(buff, len);
				table[i_id].start = i;
				table[i_id].len = len;
				i_id++;
			}
			i += len - 1;
		}
	find_func(mass);
	/*for (i = 1; i < 100; i++)
	{
		printf("\nTable[%d].id = %d\tTable[%d].start = %d\tTable[%d].len = %d\t", i, table[i].id, i, table[i].start, i, table[i].len);
		int j;
		for (j = 0; j < table[i].len; j++)
			printf("%c", mass[table[i].start + j]);
	}*/
return 0;
}
	
