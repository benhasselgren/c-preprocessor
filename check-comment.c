//---------------------------------------------------DETAILS---------------------------------------------------
/*
Author: Ben Hasselgren
Description: This program checks each character to see if it is a comment and if it is the whole line is not added to new .o file.
Last date modified: 19/02/2019
*/

//---------------------------------------------------HELP SOURCES---------------------------------------------------
/*
 https://www.thedailyprogrammer.com/2016/02/c-program-to-remove-comments-from-file.html
*/

#include "check-comment.h"
#include <stdlib.h>
#include <stdio.h>

//This function checks to see if a line is a comment anf if it is then won't add line to new .o file (Also increases commentCounter)
//In some cases if the comment is at end of line of code, it can return a bool value to identify if a (\n) character needs to be added to line.
int check_comment(char c, FILE *file, FILE *newFile, int *commentCounter, char *keepComments)
{
	
	//Bool value == False
	int isComment = 0;
	
	//Record character after 'c' character
    char d;
	
	// if the next character is '/', then it is a comment
    if((d=fgetc(file))=='/')  
    {
		//Bool value == True
		isComment = 1;
		
		//Record character('s) after 'd' character
		char e;
		*commentCounter = *commentCounter +1;
		
		if (strcmp(keepComments,"-c") != 0)
		{
			//If there is no -c argument then discard comments
			while((e=fgetc(file))!=EOF)  
			{
				// if comment is newline character (\n) then break out of loop
				if(e=='\n') 
				{	
					fputc(e, newFile);
					break;
				}		  
			}
		}
		else
		{
			//If there IS -c argument then keep comments
			fputc(c,newFile);
			fputc(d, newFile);
			while((e=fgetc(file))!=EOF)  
			{
				// if comment is newline character (\n) then break out of loop
				if(e=='\n') 
				{	
					fputc(e, newFile);
					break;
				}
				else
				{
					fputc(e, newFile);
				}
			}
		}
    }
    else
    {
        //if not a comment then add first two character of line to newFile.
        fputc(c,newFile);
        fputc(d,newFile);
    }
	//Returns bool value if needed for commens at end of code lines
	return isComment;
}