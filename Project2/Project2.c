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
char stop[] = "STOP";

//Branch commands
char br[] 	= "BR";
char brle[]	= "BRLE";
char brlt[]	= "BRLT";
char breq[] = "BREQ";
char brne[]	= "BRNE";
char brge[] = "BRGE";
char brgt[] = "BRGT";

//Main command
char start[] = "MAIN";

//Loads and Stores
char cpba[] = "CPBA";
char lbwa[]	= "LDWA";
char stwa[]	= "STWA";
char stba[]	= "STBA";

//Stack commands
char addsp[]= "ADDSP";
char subsp[]= "SUBSP";

//Operations
char adda[]	= "ADDA";
char suba[] = "SUBA";
char anda[]	= "ANDA";
char ora[]	= "ORA";
char nota[]	= "NOTA";
char nega[]	= "NEGA";
char asla[]	= "ASLA";
char asra[] = "ASRA";
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
	
	char fileName[20];
	char correctFile;
	int fileContents;
	
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
			fileContents = fgetc(file);
			if ( feof(file) )
			{
				break;
			}
			printf("%c", fileContents);
		}
		fclose(file);
		
		
		return 0;
		
		//printf("OK\n");
	}
	else if (correctFile == 'N'||correctFile == 'n')
	{
		return 0;
	}
	
}
