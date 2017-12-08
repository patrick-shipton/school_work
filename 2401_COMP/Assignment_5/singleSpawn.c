/* 
File is singleSpawn.c

Purpose:
a program that takes a unsigned int from a binary file and creates a child that morphs into isPrime.c

input:
path to binary file

output:
prints whether the number from file is prime or not
-1 - if an error occured
0  - if success

*/ 

/**************************************************************/
// INCLUDE FILES
//
#include "stdio.h"
#include "stdlib.h"
#include <unistd.h>
#include <sys/wait.h>


/*************************************************************/
// PROTYPES
//
int morph(char *number);

/*************************************************************/


int main(int argc, char *argv[]){
	int i;
	int status;
	FILE *file;
	char numStr[32];
	unsigned int n;
	int rc = 0;
	int cpid;
	
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
	//printf("Num1 %u \n", n);
	sprintf(numStr, "%d", n);
	//printf("Num2 %s \n", numStr);

	cpid = fork();
	if (cpid == 0){
		morph(numStr);
	} else {
		wait(&status);
		if (WIFEXITED(status) != 0){
			int returned = WEXITSTATUS(status);
			if(returned == 0){
				printf("%u is NOT a prime number\n", n);
			} else if (returned == 1){
				printf("%u is a prime number \n", n);
			} else {
				printf("error\n");
				exit(-1);
			}
		} 
	}
	
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

