#ifndef CANALYZE_H
#define CANALYZE_H

int comparison(char *token, const char * word, int l);
int analyze(char *token, int l);
int skip_spaces(char *mass, int p);
int length_token(char *mass, int p);
int find_func(char *mass);
int run_analyze(char *mass);

#endif


