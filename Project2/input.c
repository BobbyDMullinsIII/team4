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
	
	
	//Tests scanf inputting integers functionality
	short inptnum;
	printf ("Input an integer: ");
	scanf ("%hd", &inptnum);
	
	//Tests addition functionality
	short addnum = 5 + 7;
	
	//Tests printf outputting integers functionality
	printf ("Sum: %hd\n", addnum);
	
	//Tests subtraction functionality
	short subnum = 9 - 7;
	
	//Tests printf outputting integers functionality again
	printf ("Difference: %hd\n", subnum);
	
	//Test AND functionality
	bool andbool = (0 && 1);
	printf ("andbool: %hd\n", andbool);
	
	//Test OR functionality
	bool orbool = (0 || 1);
	printf ("orbool: %hd\n", orbool);
	
	//Test NEG functionality
	bool negbool = !(0 || 1);
	printf ("negbool: %hd\n", negbool);
	
	
	//Tests return statement functionality
	return 0;
}