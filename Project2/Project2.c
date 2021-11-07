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
char brne[]	= "BRNE"; //Make these enums?
char brge[]	= "BRGE";
char brgt[]	= "BRGT";

//Main command
char start[]= "MAIN";

//Loads and Stores
char cpba[]	= "CPBA";
char lbwa[]	= "LDWA";
char stwa[]	= "STWA";
char stba[]	= "STBA";
char ldba[] = "LDBA";

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

int subset_str(const char *needle, const char *hay)
{
	if(!hay)
		return 0;
	while(*needle){
		if (!strchr(hay, *needle))
			return 0;
		needle++;
	}
	return 1;
}

int main()
{
	printf("*****************************\n");
	printf("**********PROJECT 2**********\n");
	printf("*****************************\n\n");
		
	while(1)
	{
		char fileName[200];
		char correctFile;
		
		char fileContents[100000];
		char *tokens;
		int lineNumber = 0;
	
		printf("\nPlease input a .c file to be processed\n");
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
			FILE *fp;
			long lSize;
			char *buffer;
			
			int i;						//For loop variable
			int stringcounter = 0;		//Counts string variable counter to store .ASCII text for STRO output 
			char stringarray[50][200];	//Array of strings (2d array of chars in c) for storing all .ASCII variables to put at the end of Pep/9 program

			fp = fopen ( fileName , "r" );
			if( !fp ) perror(fileName),exit(1);

			fseek( fp , 0L , SEEK_END);
			lSize = ftell( fp );
			rewind( fp );

			/* allocate memory for entire content */
			buffer = calloc( 1, lSize+1 );
			if( !buffer ) fclose(fp),fputs("memory alloc fails",stderr),exit(1);

			/* copy the file into the buffer */
			if( 1!=fread( buffer , lSize, 1 , fp) )
				fclose(fp),free(buffer),fputs("entire read fails",stderr),exit(1);

			//If statements to go through each instruction type
			//Converts "main()" to "BR	MAIN" instruction
			if(subset_str("main()", buffer))
			{
				printf("\nBR	main\n\n");
				printf("main:");
			}
			//Converts "printf()" to "STRO	string#,d" instruction and a corresponding .ASCII string
			if(subset_str("printf", buffer))
			{
				//Code for storing string from inside "printf" statement inside stringarray goes here
				char tempstring[200] = "test tempstring";
				
				//Stores input string variable in stringarray
				strcpy(stringarray[stringcounter], tempstring); // valid

				printf("	STRO	string%d,d\n", stringcounter);
				stringcounter++;
			}	
			//Converts "return 0;" to "STOP" instruction
			if(subset_str("return 0;", buffer))
			{
				printf("\n	stop\n\n");
			}
			
			//Puts each of the .ASCII string variables between 'stop' and '.END' instructions
			for(i = 0; i < stringcounter; i++)
			{
				printf("string%d	.ASCII	\"%s\"\n", i, stringarray[i]);
			}
			
			//Required to signify end of code in Pep/9
			printf("\n	.END\n");

			fclose(fp);
			free(buffer);
		}
	
		
		//If correctFile is N or n then return 0 and exit out of while loop.
		else if (correctFile == 'N'||correctFile == 'n')
		{
			printf("\n");
		}
	}	
	
}
