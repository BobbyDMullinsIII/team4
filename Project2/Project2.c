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
#include <ctype.h>

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

char next_token(char* line) {
	static char* p;
	if (p == NULL)
		p = line;
	else {
		char next_token = p[0];
		p++;
		return next_token;
	}
}

int main()
{
	//Comment block to have at the top of Pep/9 output file to signify Project 2
	printf(";*****************************\n");
	printf(";**********PROJECT 2**********\n");
	printf(";*****************************\n");
	
	int LINE_NUMBER;
	int LINE_CONTENT;
	long lSize;		//Size of stdin to pass to buffer
	char *buffer;	//Buffer to store contents of stdin
	
	
	fseek(stdin, 0L, SEEK_END);
	lSize = ftell(stdin);
	rewind(stdin);	//What rewind does is it sets the file position to the beginning of the file for the stream pointed to by stream.

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

	int i, j = 0;					//For loop variables
	int boolcounter = 0;			//Counts bool variables for naming and output in Pep/9
	int shortcounter = 0;			//Counts short variables for naming and output in Pep/9
	int stringcounter = 0;			//Counts string variable counter to store .ASCII text for STRO output 
	char stringarray[50][200];		//Array of strings (2d array of chars in c) for storing all .ASCII variables to put at the end of Pep/9 program
	
	//Prints initial branch to main because every program should have a main branch in Pep/9
	printf("\n	BR	main\n\n");
	
	//Main token for going through each line in file 
	//(Has newline character as delimiter)
	char *end_token;	//Required for strtok_r
	char *token = strtok_r(buffer, "\n", &end_token);

	
	//While loop tokenizes each line within file
	while(token != NULL)
	{		
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
			char *inside = strtok_r(token, "	 ", &end_inside);

			//While loop tokenizes each string of characters within line and checks each one for output
			while(inside != NULL)
			{
				//printf("%s\n", inside);	//Outputs current 'inside' string/char pointer for testing purposes
					
				//If statements to go through each instruction type
				//Converts "main()" to "BR	MAIN" instruction
				if(strcmp(inside,"main()") == 0)
				{
					printf("frstCalc:.WORD	0x0000 \n");	//First word variable for adding or subtracting two numbers
					printf("scndCalc:.WORD	0x0000\n");		//Second word variable for adding or subtracting two numbers
					
					printf("\nmain:");	//Main branch before program after global data
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
					char tempstring[500];	//TempString to copy from line
					
					int startingIndex = 8; //Will always start at index 8
					int endingIndex = startingIndex; //This will get rid of extra characters that are not needed.
					
					i = 7;
					int in = 1;
					int index = 0;
					while (in == 1)
					{
						//First quote
						if (token[i] == '"')
						{
							token[i] = '0'; //setting the char at index i = to a char that will not pass the if check, and this is to get all strings.
							i++;
							while (token[i] != '"') //Will run through loop as long as the index of token at i != '"'.
							{
								tempstring[index] = token[i]; //Copies token at index i into tempstring.
								index++;
								i++;
							}	//Will break out of loop as soon as char i is = to a '"' and enter the if below.
							
							//Second quote
							if (token[i] == '"')
							{
								token[i] = '0';	//setting the char at index i = to a char that will not pass the if check, and this is to get all strings.
								i++;
							}
							in = 0;
						}
						i++;
					}
					//Copy tempstring to stringarray and will clear the tempstring.
					strcpy(stringarray[stringcounter],tempstring);
					memset(tempstring, '\0', index);

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
					
					printf("	DECI	short%d,d\n", shortcounter - 1);
				}	
				//Converts "short" to (Input Pep/9 equivalent here)
				if(strcmp(inside,"short") == 0)
				{
					/********************************************************************************/
					/* Converting c to Pep/9 code for declaring short goes here */
					/********************************************************************************/	
					
					inside = strtok_r(NULL, " 	", &end_inside);//Go to next token
					
					//Checks last character in token to see if there is nothing else within the same line, such as an assignment variable
					//If there is not, go to next token
					if(inside[strlen(inside)-1] == ';')
					{		
						//Assigns short variable name and ends there to go to next line
						printf("short%d:	.WORD	0x0000\n", shortcounter);
					}
					else
					{		
						//Assigns short variable name and goes to next token
						printf("short%d:	.WORD	0x0000\n", shortcounter);
						//inside = strtok_r(NULL, " 	", &end_inside);//Go to next token (THIS CAUSES A SEGMENTATION FAULT FOR SOME REASON)

						//Checks if next token is an equal sign
						if(strcmp(inside,"=") == 0)
						{
							inside = strtok_r(NULL, " 	", &end_inside);//Go to next token
							
							//Checks if first number has semicolon after it
							if(inside[strlen(inside)-1] == ';')
							{
								
							}
								
						}
						
					}
										
					shortcounter++;	//Increases counter for next short
				}
				//Converts "bool" to (Input Pep/9 equivalent here)
				if(strcmp(inside,"bool") == 0)
				{
					/********************************************************************************/
					/* Converting c to Pep/9 code for declaring bool goes here */
					/********************************************************************************/
					
					printf("bool%d:	.WORD	0x0000\n", boolcounter);
					
					boolcounter++;	//Increases counter for next bool
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
		
		printf("\nstring%d: .ASCII	\"\\n%s\\x00\"\n", i, stringarray[i]);
		
	}
	
	//Test to see what buffer has
	//printf(buffer); //Here buffer contains #include <stdio.h>
	
	//printf(linecounter);

	printf("\n	.END\n");	//Required to signify end of code in Pep/9
	
	free(buffer);	//Free the buffer before ending program
	
	return 0;	//End program
}		
