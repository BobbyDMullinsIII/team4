//Tests excluding #include and #define statements functionality
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PIE 3.14

//Tests declaring integer global variable functionality
short sa;

//Tests assigning to integer global variable functionality
sa = 1;

//Tests declaring and assigning to integer global variable functionality
short sb = 2;


int main(int argc, char *argv[]) 
{
	//Tests declaring integer inside main functionality
	short sc;
	
	//Tests assigning to integer inside main functionality
	sc = 3;	
	
	//Tests declaring and assigning to integer inside main functionality
	short sd = 4;
	
	
	//Tests addition functionality
	int addnum = 5 + 7;
	
	//Tests printf outputting integersfunctionality
	printf("Sum: %d", addnum);
	
	//Tests subtraction functionality
	int subnum = 9 - 7;
	
	//Tests printf outputting integers functionality again
	printf("Difference: %d", subnum);
	
	
	//Tests return statement functionality
	return 0;
}