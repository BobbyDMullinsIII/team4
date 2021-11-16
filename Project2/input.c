//Tests excluding #include and #define statements functionality
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define PIE 3.14

//Tests declaring and assigning to integer global variable functionality
short sa = 1;
short sb = 2;

//Tests main functionality
int main() 
{
	//Tests regular printf functionality
	printf ("Printf statement check string.");
	
	//Tests declaring integer inside main functionality
	short sc;
	
	//Tests assigning to integer inside main functionality
	sc = 3;	
	
	//Tests declaring and assigning to integer inside main functionality
	short sd = 4;
	
	//printf("%hd", sd);

	//Tests scanf inputting integers functionality
	short inputnum;
	short inputnum2;
	printf ("Input two integers: ");
	scanf ("%hd", &inputnum);
	scanf ("%hd", &inputnum2);
	
	//Tests addition functionality
	short addnum = 5 + 7;
	
	//Tests printf outputting integers functionality
	printf ("Sum: %hd\n", addnum);
	
	//Tests subtraction functionality
	short subnum = 9 - 7;
	
	//Tests printf outputting integers functionality again
	printf ("Difference: %hd\n", subnum);
	
	//Test AND functionality
	short andnum = (inputnum && inputnum2);
	printf ("and: %hd\n", andnum);
	
	//Test OR functionality
	short ornum = (inputnum || inputnum2);
	printf ("or: %hd\n", ornum);
	
	//Test NEG functionality
	short negnum = !(inputnum);
	printf ("neg: %hd\n");
	
	
	//Tests return statement functionality
	return 0;
}