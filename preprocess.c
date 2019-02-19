//---------------------------------------------------DETAILS---------------------------------------------------
/*
Author: Ben Hasselgren
Description: This program reads the file inputed by user and outputs the modified file into the new .o file by calling the relevant functions.
Last date modified: 19/02/2019
*/

//---------------------------------------------------HELP SOURCES---------------------------------------------------
/*
Workbook from course supplied by napier university. (Chapter 4 - 5)
*/

#include <stdlib.h>
#include <stdio.h>
#include "check-comment.h"
#include "check-pre-processor-word.h"
#include "check-define-variable.h"

//This function is the .exe file that is executed to modify the orignal .c file to the new .o file
int main(int argc, char **argv)
{
	FILE *file , *newFile;
	
	//Tracks character
	char c;
	
	//Initialises struct
	define_variable define_list[20];
	int struct_size = 0;
	
	//Counters (Comment lines & non-empty lines)
	int commentCounter = 0;
	int nonEmptyCounter = 0;
	
	//Open the first file in read mode and check if it exists
    file = fopen (argv[2],"r"); 
	if (!file)
	{
		printf("ERROR: File does not exist.\n");
		return;
	}
	
	//Create's newFile name and opens the new file in write mode
	char *newFileName = argv[2];
	newFileName[strlen(newFileName)-2] = '\0';
	//Add .o extension to newFilename
	strcat(newFileName, ".o");
    newFile = fopen(newFileName,"w");   
	
	
	//Check if -c argument exists and assign to keepComments variable if it does
	char keepComments[3] = "";
	if (argv[3])
	{
		if (strcmp(argv[3],"-c") == 0)
		{
			strcpy(keepComments, argv[3]);
			keepComments[2] = '\0';
		}
		else
		{
			printf("ERROR: Command not understood.\n");
			printf("For a preprocessed .o file WITH NO comments then use:\n");
			printf("preprocessor -i 'filename.c' -c\n");
			printf("For a preprocessed .o file WITH comments then use:\n");
			printf("preprocessor -i 'filename.c'\n");
			return;
		}
	}
	
	//Check if -i argument is spelled properly
	if (strcmp(argv[1],"-i") == 0)
	{
		//Read the file character by character
		while((c=fgetc(file))!=EOF)   	
		{	
			if (c == '\n' ||  c == '\t')
			{
				//If line starts with new line or tab then add to file
				fputc(c,newFile);
			}
			else if( c == '/')   
			{
				//If line starts with slash then check if it is a comment
				nonEmptyCounter = nonEmptyCounter + 1;
				check_comment(c, file, newFile, &commentCounter, keepComments);
			}
			else if (c == '#')
			{
				//Checks what pre-processor word it is and if #include then read in file or if #define store variable in struct
				nonEmptyCounter = nonEmptyCounter + 1;
				check_pre_processor_word(c, file, newFile, define_list, &struct_size);
			}
			else
			{
				nonEmptyCounter = nonEmptyCounter + 1;
				//If doesn't start with slash and not empty line, then loop through line adding every character.
				
				//Check first word on line to see if it is define variable
				int isNewLine = check_define_variable(c, file, newFile, define_list, &struct_size);
				
				//If it's a new line then continue to next iteration
				if(isNewLine == 1)
				{
					continue;
				}
				
				//Else loop through line
				while((c=fgetc(file))!=EOF)  
				{
					if( c == '/')   
					{
						//If '/' character at end of code line then check if it's a comment
						int isComment = check_comment(c, file, newFile, &commentCounter, keepComments);
						
						//If it is then add '\n' character to .o file
						if (isComment == 1)
						{
							//Need to break out or you will go straight to next line without looping from the start of the first loop
							break;
						}
					}
					else if( c == '\n')   
					{
						//If \n then break out of loop
						fputc('\n',newFile);
						break;
					}
					else
					{
						//Else check to see if line contains any define variables
						int isNewLine = check_define_variable(c, file, newFile, define_list, &struct_size);	
						
						//If it's a new line character then break out loop
						if(isNewLine == 1)
						{
							break;
						}
					}					
				}
			}
		}
		
		//Print out counters
		printf("Number of comments: %d\n", commentCounter);
		printf("Number of non-empty lines: %d\n", nonEmptyCounter);
	}
	else
	{
		//If -i command mispelled then output error
		printf("ERROR: Command not understood.\n");
		printf("For a preprocessed .o file WITH NO comments then use:\n");
		printf("preprocessor -i 'filename.c' -c\n");
		printf("For a preprocessed .o file WITH comments then use:\n");
		printf("preprocessor -i 'filename.c'\n");
	}
    //Close both the files at the end of the program
    fclose(file);
    fclose(newFile);
	
    return 0;
}