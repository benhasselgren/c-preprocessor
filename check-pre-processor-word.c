//---------------------------------------------------DETAILS---------------------------------------------------
/*
Author: Ben Hasselgren
Description: This program checks to see what pre-processor word it is and then executes accordingly to each word.
Last date modified: 14/02/2019
*/

//---------------------------------------------------HELP SOURCES---------------------------------------------------
/*
 https://cboard.cprogramming.com/c-programming/90116-appending-char-string-char-array.html
 https://stackoverflow.com/questions/8206014/passing-an-array-of-structs-in-c
 Help from practical demonstrator with passing an array of structs through this function
*/

#include "check-pre-processor-word.h"
#include <stdio.h>
#include <string.h>

/*
This program checks to see what pre-processor word it is and if it's #include then it reads in the relevant file.
if it's #define then adds variable to struct

*/
void check_pre_processor_word(char c,  FILE *file,  FILE *newFile, define_variable df[], int *sSize)
{
	//Deals with #include line
	FILE *header_file;
	char *header_file_name = "";
	
	//Deals with #define line
	char *variable_name = "";
	char *variable_value = "";
	
	//Variables that tie together characters to make words in code below
	int value = 0;
	int i = 0;
    int len = strlen(header_file_name);
	
	// if the next character is 'i', then it is #include
    if((c=fgetc(file))=='i') 
	{
		while((c=fgetc(file))!=EOF)  
		{
			if(c == '\n')
			{
				//if new line character then read header file into new .o file
				header_file = fopen (header_file_name,"r");
				char e;
				while((e=fgetc(header_file))!=EOF)
				{
					fputc(e,newFile);
				}
				
				//Close file and return from function
				fclose(header_file);
				return;
			}
			else if (c == '"')
			{
				//If character is == " then loop until next " to obtain header file name
				while((c=fgetc(file))!=EOF)
				{
					if(c == '"')
					{
						//if " character then break out of while loop
						break;
					}
					else
					{
						//If any character (except ") then append to header name string
						header_file_name[i] = c;
						header_file_name[i + 1] = '\0';
						i++;
					}
				}
			}
		}
	}
	else
	{
		//If 2nd character not i, then has to be d
		while((c=fgetc(file))!=EOF)
		{
			if (c == ' ')
			{
				//If characeter == space then loop to obtain variable name
				int i = 0;
				while((c=fgetc(file))!=EOF)
				{
					if(c == ' ')
					{
						//If characeter space again then add variable_name to struct then loop again to obtain value 
						strcpy(df[*sSize].name, variable_name);
						i = 0;
						while((c=fgetc(file))!=EOF)
						{
							if(c =='\n')
							{
								//If \n character then add variable_value to struct and return from function
								strcpy(df[*sSize].value, variable_value);
								(*sSize) ++;
								return;
							}
							else
							{
								//If not \n then append character to variable_value string
								variable_value[i] = c;
								variable_value[i + 1] = '\0';
								i++;
							}
						}
					}
					else
					{
						//If not space character then append character to variable_name string
						variable_name[i] = c;
						variable_name[i + 1] = '\0';
						i++;
					}
				}
			}
			else{
				//if not space character, then continue to next loop iteration
				continue;
			}
		}
	}
}