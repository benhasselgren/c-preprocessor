//---------------------------------------------------DETAILS---------------------------------------------------
/*
Author: Ben Hasselgren
Description: This program checks for define variables in lines of text.
Last date modified: 18/02/2019
*/

//---------------------------------------------------HELP SOURCES---------------------------------------------------
/*
https://stackoverflow.com/questions/11573974/write-to-txt-file
*/

#include "check-define-variable.h"
#include <stdio.h>
#include <string.h>

/*
This program loops through all the lines of text that are not comments, pre-processor lines, new lines, etc.
and checks to to see if they contain any define variables and if so write the define value to file,
else add the word to file.
*/

int check_define_variable(char c, FILE *file, FILE *newFile, define_variable df[], int *sSize)
{
	//Stores every string split by space characters on line
	char *word = "";
	int i = 0;
	
	//Stores space or newline character after word
	char d;
	
	//Is define variable
	int isDefine = 0;
	
	//Add current character to start of string first
	word[i] = c;
	word[i + 1] = '\0';
	
	//Tracks is it's a new line character
	int isNewLine = 0;
	
	//Copy word into variable
	while((c=fgetc(file))!=EOF)  
	{
		if(c == ' ')
		{
			d = ' ';
			break;
		}
		else if(c == '\n')
		{
			d = '\n';
			isNewLine = 1;
			break;
		}
		else
		{
			i++;
			word[i] = c;
			word[i + 1] = '\0';
		}
	}	
	
	//Check to see if word is a define variable
	for (int c = 0; c < *sSize; c ++)
	{
		if(strcmp(df[c].name, word) == 0)
		{
			//If so change word to correct define value
			strcpy(word, df[c].value);
			break;
		}
	}
	

	//Read word into file (by character)
	for (int w_counter = 0; w_counter < strlen(word); w_counter ++)
	{
		fputc(word[w_counter], newFile);
	}
	//Make sure to add the space or newline character after word in .o file (was stored in d variable earlier)
	fputc(d, newFile);
	
	
	return isNewLine;
	
}	