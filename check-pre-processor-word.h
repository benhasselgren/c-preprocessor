#pragma once
#include <stdio.h>

//To store #define variables
typedef struct
{
	char name[16];
	char value[16];
} define_variable;

void check_pre_processor_word(char c, FILE *file, FILE *newFile, define_variable df[], int *sSize);
