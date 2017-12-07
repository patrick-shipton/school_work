/* 
File is multiSpawn.c

Purpose:
a program that takes 10 unsigned int from a binary file and creates a child for each number that morphs into isPrime.c

input:
path to binary file

output:
prints the numbers that are prime
-1 - if an error occured
0  - if success

Assumption:
The input file contains at least 10 unsigned integers
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

#define MAX_INPUT 10

int main(int argc, char *argv[]){
	int i;
	int status;
	FILE *file;
	char numStr[32];
	unsigned int n[MAX_INPUT];
	int cpid[MAX_INPUT];
	
	
	if (argc != 2) {
		printf(" Usage: %s filename \n",argv[0]);
		return(1);
	}
	
	file = fopen(argv[1],"rb");
	if (file == NULL) {
		printf("file %s does not exist \n",argv[1]);
		return(1);
	}
	
	for(i=0; i<MAX_INPUT; i++){
		fread(&n[i], sizeof(unsigned int), 1, file);
		sprintf(numStr, "%u", n[i]);
		//printf("Num%u %s \n",i, numStr);

		cpid[i] = fork();
		if (cpid[i] == 0){
			morph(numStr);
		}
	}
	int currentPID = -1;
	while ((currentPID = waitpid(-1, &status, 0)) > 0){
		if (WIFEXITED(status) != 0){
			int returned = WEXITSTATUS(status);
			if(returned == 0){
				//printf("%d returned not prime\n", currentPID);
			} else if (returned == 1){
				for(i=0; i<MAX_INPUT; i++){
					if(cpid[i] == currentPID)break;
				}
				printf("%u is a prime number \n", n[i]);
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

