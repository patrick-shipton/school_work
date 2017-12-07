/* 
File is singlePrime.c

Purpose:
a program that takes a unsigned int from a binary file and morphs into isPrime.c

input:
path to binary file

output:
-1 - if an error occured
0  - if the input number is not a prime number
1  - if the input number is a prime number

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
	//printf("Num1 %u", n);
	sprintf(numStr, "%d", n);
	//printf("Num2 %s", numStr);
	if(morph(numStr) == -1){
		printf("morph failed");
	}

	if (file != NULL) fclose(file);
	
	exit(-1);
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

