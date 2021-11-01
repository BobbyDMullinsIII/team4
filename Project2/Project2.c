/********************************************************************************
* Program Name: Project2.c
* Programmer: Group 4 (Alexander Simpson, Austen Boda, Bobby Mullins, Ethan Morgan, Ty Seiber)
* Class: CSCI 2160-001
* Project: Project 2
* Date: 2021-10-24
* Purpose: Project2.c file for converting c code into Pep/9 code 
********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//End program
char stop[]	= "STOP";

//Branch commands
char br[]	= "BR";
char brle[]	= "BRLE";
char brlt[]	= "BRLT";
char breq[]	= "BREQ";
char brne[]	= "BRNE";
char brge[]	= "BRGE";
char brgt[]	= "BRGT";

//Main command
char start[]= "MAIN";

//Loads and Stores
char cpba[]	= "CPBA";
char lbwa[]	= "LDWA";
char stwa[]	= "STWA";
char stba[]	= "STBA";

//Stack commands
char addsp[]	= "ADDSP";
char subsp[]	= "SUBSP";

//Operations
char adda[]	= "ADDA";
char suba[]	= "SUBA";
char anda[]	= "ANDA";
char ora[]	= "ORA";
char nota[]	= "NOTA";
char nega[]	= "NEGA";
char asla[]	= "ASLA";
char asra[]	= "ASRA";
char rola[]	= "ROLA";
char rora[]	= "RORA";

//Output Traps
char nopa[]	= "NOPA";
char nop[]	= "NOP";
char deci[]	= "DECI";
char deco[]	= "DECO";
char hexo[]	= "HEXO";
char stro[]	= "STRO";

int main()
{
	while(1)
	{
		char fileName[200];
		char correctFile;
		//int fileContents[];
		char fileContents2[100000];
		char *tokens;
		int lineNumber = 0;
		printf("*****************************\n");
		printf("**********PROJECT 2**********\n");
		printf("*****************************\n\n");
	
		printf("Please input a .c file to be processed\n");
		scanf("%s", fileName);
	
		//Code block checks if input file has an extension and if that extension '.c'
		//If it is not, exit program
		int correctExt = 0;
		char *pointer = strrchr(fileName, '.');
	
		//Checks if there is an extension in the first place
		//If there isn't, give error message and exit program.
		if (pointer != 0)
		{
			//Checks if the extension is '.c'
			//If it isn't, give error message and exit program.
			if(strcmp(pointer, ".c") != 0)
			{
				printf("Input file has wrong file extension. Must be '.c'. Exiting Program.\n");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			printf("Input file does not have an extension. Must be '.c'. Exiting Program.\n");
			exit(EXIT_FAILURE);
		}
	
		printf("Input file has Correct file extension.\n");
		printf("The file you selected was: %s \n", fileName);
		printf("Is this the correct file? Y/N\n");
	
		scanf(" %c", &correctFile);
		
		//Checks to see if user input was Y or y
		if (correctFile == 'Y'||correctFile == 'y')
		{
			FILE *file;
			file = fopen(fileName, "r");
			if(file == NULL) 
			{
				perror("Error in opening file");
				return(-1);
			}
		
		
			while(1)
			{
				if (fgets(fileContents2, 100000, file) != NULL){
					if ( feof(file) )
					break;
				
				lineNumber++;
				tokens = strtok(fileContents2, " \n");
				while (tokens != NULL)
				{
					printf("%d: %s\n", lineNumber, tokens);
					
					tokens = strtok(NULL, " \n");
					//break;
				}
				
					//fileContents2 = fgetc(fileContents2, 100000, file);
				}
				
				//printf("%c", fileContents);
				
			}
			fclose(file);
			printf("\n");
			//printf("OK\n");
		}
		//If correctFile is N or n then return 0 and exit out of while loop.
		else if (correctFile == 'N'||correctFile == 'n')
		{
			printf("\n");
		}
	}
}