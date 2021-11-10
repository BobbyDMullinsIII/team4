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

/******************************/
/*Pep/9 Instructions Reference*/
/******************************/

//Main command
char start[]= "MAIN";

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

//Loads and Stores
char cpba[]	= "CPBA";
char ldwa[]	= "LDWA";
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
	//Comment block to have at the top of Pep/9 output file to signify Project 2
	printf(";*****************************\n");
	printf(";**********PROJECT 2**********\n");
	printf(";*****************************\n");
	
	long lSize;		//Size of stdin to pass to buffer
	char *buffer;	//Buffer to store contents of stdin
	
	fseek(stdin, 0L, SEEK_END);
	lSize = ftell(stdin);
	rewind(stdin);

	//Allocated memory for all of the contents of the file and exits program if buffer is equal to 0
	buffer = calloc(1, lSize + 1);
	if(buffer == 0) 
	{
		fputs("Memmory allocation error", stderr);	//Outputs memory allocation error message to standard error
		exit(1);
	}

	//Copies the entire file into the buffer and exits if result not equal to 1
	if(fread(buffer , lSize, 1, stdin) != 1)
	{	
		free(buffer);	//Free the buffer before exiting program
		fputs("File read error", stderr);	//Outputs file read error message to standard error
		exit(1);
	}

	int i;						//For loop variable
	int stringcounter = 0;		//Counts string variable counter to store .ASCII text for STRO output 
	char stringarray[50][200];	//Array of strings (2d array of chars in c) for storing all .ASCII variables to put at the end of Pep/9 program
	
	//Main token for going through each line in file 
	//(Has newline character as delimiter)
	char *end_token;	//Required for strtok_r
	char *token = strtok_r(buffer, "\n", &end_token);
	
	//While loop tokenizes each line within file
	while(token != NULL)
	{
		//printf("%s\n", token);	//Outputs current 'token' string/char pointer for testing purposes
		
		/********************************************************************************/
		/* This only works if there is a maximum of 1 tab per each line */
		/********************************************************************************/
		//Goes to next token if line is determined to be comment or #include or #define directive
		if(token[0] =='/' || token[1] =='/' || token[0] =='#')
		{
			token = strtok_r(NULL, "\n", &end_token);
		}
		else
		{
			//Inside token for going through each item on same line 
			//(Has both space and tab characters as delimiters)
			char *end_inside;	//Required for strtok_r
			char *inside = strtok_r(token, " 	", &end_inside);
		
			//While loop tokenizes each string of characters within line and checks each one for output
			while(inside != NULL)
			{
				//printf("%s\n", inside);	//Outputs current 'inside' string/char pointer for testing purposes
					
				//If statements to go through each instruction type
				//Converts "main()" to "BR	MAIN" instruction
				if(strcmp(inside,"main()") == 0)
				{
					printf("\n	BR	main\n\n");
					printf("main:");
				}
				//Converts "printf()" to "STRO	string#,d" instruction and a corresponding .ASCII string
				if(inside[0] == 'p' 
				&& inside[1] == 'r'
				&& inside[2] == 'i' 
				&& inside[3] == 'n' 
				&& inside[4] == 't'
				&& inside[5] == 'f')
				{
					//Code for storing string from inside "printf" statement inside stringarray goes here
					char *tempstring;	//TempString to copy from line
							
					//strcpy(stringarray[stringcounter], tempstring);
					
					printf("	STRO	string%d,d\n", stringcounter);
					stringcounter++;			
				}	
				//Converts "scanf()" to (Input Pep/9 equivalent here)
				if(inside[0] == 's' 
				&& inside[1] == 'c' 
				&& inside[2] == 'a' 
				&& inside[3] == 'n'
				&& inside[4] == 'f')
				{
					/********************************************************************************/
					/* Converting c to Pep/9 code for scanning from input or console goes here */	
					/********************************************************************************/
				}	
				//Converts "short" to (Input Pep/9 equivalent here)
				if(strcmp(inside,"short") == 0)
				{
					/********************************************************************************/
					/* Converting c to Pep/9 code for declaring short goes here */
					/********************************************************************************/
				}
				//Converts "bool" to (Input Pep/9 equivalent here)
				if(strcmp(inside,"bool") == 0)
				{
					/********************************************************************************/
					/* Converting c to Pep/9 code for declaring bool goes here */
					/********************************************************************************/
				}
				//Converts "return 0;" to "STOP" instruction
				if(strcmp(inside,"return") == 0)
				{	
					printf("\n	stop\n\n");
				}	

				//Goes to next token within same line unless end of line
				//(Has both space and tab characters as delimiters)
				inside = strtok_r(NULL, " 	", &end_inside);
															
			}				
			
			token = strtok_r(NULL, "\n", &end_token);	//Goes to next line unless end of file					
		}
	}
	
	//Puts all of the .ASCII string variables stored in array between 'stop' and '.END' instructions
	for(i = 0; i < stringcounter; i++)
	{
		printf("string%d: .ASCII	\"%s\\x00\"\n", i, stringarray[i]);
	}
			
	printf("\n	.END\n");	//Required to signify end of code in Pep/9
	
	free(buffer);	//Free the buffer before ending program
	
	return 0;	//End program
}		
