/* 
File is createBinary.c

Purpose:
a program that creates a binary file for testing the prime number program 

input:
a sequence of numbers to be tested

output:
0 - if success
1 - if an error occured
a binary file with the name.   

Assumption:
1. the program does not check if the number is a positive integer
2. the program overwrites that file testPrime.bin

*/ 

/**************************************************************/
// INCLUDE FILES
//
#include "stdio.h"
#include "stdlib.h"
#include <unistd.h>


/*************************************************************/
// PROTYPES
//
int morph(char *number);

/*************************************************************/


int main(int argc, char *argv[]){
	int i;
	FILE *file;
	char numStr[32];
	unsigned int n;
	int rc = 0;
	
	unsigned int number;
	
	if (argc != 2) {
		printf(" Usage: %s filename \n",argv[0]);
		return(1);
	}
	
	file = fopen(argv[1],"rb");
	if (file == NULL) {
		printf("file %s does not exist \n",argv[1]);
		return(1);
	}
		
	fread(&n, sizeof(unsigned int), 1, file);
	printf("Num1 %d", n);
	sprintf(numStr, "%d", n);
	printf("Num2 %s", numStr);
	morph(numStr);
	
	if (file != NULL) fclose(file);
	
	exit(0);
}


int morph(char *number){
	int rc;
	char* argv[3];
	argv[0] = "./prime";
	argv[1] = number;
	argv[2] = NULL;

	rc = execvp(argv[0], argv);
	if(rc > 0){
		return -1;
	}
	return 0;
}

