
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "linked_list.h"
#include "bubble_sort.h"

#define CONTINUE {printf("hit <cr> to continue \n"); getchar();}

void populatePerson(char *firstName, char *familyName, int *id);


int main(int argc, char* argv[])
{
	char firstName[NAME_LENGTH];
	char familyName[NAME_LENGTH];
	int id;
	struct personalInfo *empHead = NULL;
	struct personalInfo *p = NULL, *q = NULL;
	int i;
    int rc = 0;
	
	for (i = 0; i < 20; i++) {
	// add code for testing
		populatePerson(firstName, familyName, &id);
		insertToList(&empHead, id, firstName, familyName);
	}

	printList(empHead);

    printf("test SearchById \n");
	q = p = searchById(empHead, 111);
    if(p == NULL) { 
        printf("search by id failed \n");
    } else {
        printNode(p);
    }
    CONTINUE;
	if (p != NULL) {
	    for (i = 0; i < 4; i++) {
		    populatePerson(firstName, familyName, &id);
		    p = insertAfter(p, id, firstName, familyName);
	    }
    }
	printList(empHead);

    // test delete after
    
	rc = deleteAfter(q, &id, firstName, familyName);
    printf("deleteAfter rc = %d \n",rc);
	printList(empHead);
    CONTINUE;


	p = searchById(empHead, 111);
	if (p != NULL) {
		printf("\n found name to delete \n");
		printNode(p);
		strncpy(firstName, p->firstName, NAME_LENGTH);
		deleteNodeByName(&empHead, firstName, familyName, &id);
	}

	

	bubbleSort(&empHead);

	printf("\n\n sorted list \n\n");
	printList(empHead);

//	getchar();

	printf("\n\n remove duplicates \n\n");
	removeDuplicates(empHead);
	printList(empHead);
    deleteList(&empHead);
//	getchar();

	return 0;
}


	

/***************************************************************************/
/* purpose: the function populate the personal info

input/output
struct personalInfo *p - allocated memory to the struct pointer which the function assigns values.




*/

void populatePerson(char *firstName, char *familyName, int *id)
{
	static int initRand = 0;
	int j;
	char *first[5] = { "John", "Don", "Edna", "Bev", "Miya" };
	char *family[5] = { "Broker", "Smith", "Tower", "Little", "Bronson" };

	if (!initRand) {
		srand(1557);
		initRand ++;
	}
	// populate the first  name using a random i ndex to the first name array 
	j = rand() % 5;
	// copy the first name to the structure pointed by p using strcpy
	strncpy(firstName, first[j], NAME_LENGTH);

	// populate the first  name using a random i ndex to the first name array 
	j = rand() % 5;
	// copy the family name to the structure pointed by p using strcpy
	strncpy(familyName, family[j], NAME_LENGTH);

	// populate the student id using the random numnber in the range of 0-4096  
	*id = rand() % 150;

}






