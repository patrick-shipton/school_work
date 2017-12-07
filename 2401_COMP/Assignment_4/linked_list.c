
/* 
File name is linked_list.c
 Purpose: file contains functions for manipulating singly linked list
 
 Created By
 Doron Nussbaum 2016
 
 Modifications:
 November 2017 - minor modifications
 
 
 Copyright 2017
 
 */

/******************************************************************/
// INCLUDE 

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "linked_list.h"


/************************************************************************/
// Define 



/************************************************************************/

/*
Purpose: insert a new node into the list as the first element
input
id - id of person
firstName - first name of person
familyName - family name of person

input/output
head - head of linked list

return
A pointer to the node that was allocated.  

NULL - if the operation was not successful

*/

PersonalInfo *insertToList(PersonalInfo **head, unsigned int id, char *firstName, char *familyName){
	PersonalInfo* person = NULL; 
	person = (PersonalInfo*) malloc(sizeof(PersonalInfo));
	
	//check person was created
	if(person == NULL){return NULL;}
	
	//fill person
	strcpy(person->firstName, firstName);
	strcpy(person->familyName, familyName);
	person->id = id;
	person->next = *head;
	
	*head = person;
	
	return person;
}


/************************************************************************/
/*
Purpose: insert a new node into the list after the given node  

Input
node - the node after which the new node must be added to the list
id - id of person
firstName - first name of person
familyName - family name of person


return
A pointer to the node that was allocated.  

NULL - if the operation was not successful

*/


PersonalInfo *insertAfter(PersonalInfo *node, unsigned int id, char *firstName, char *familyName){
	PersonalInfo* person = NULL; 
	person = (PersonalInfo*) malloc(sizeof(PersonalInfo));
	
	//check person was created
	if(person == NULL){return NULL;}
	
	//fill person
	strcpy(person->firstName, firstName);
	strcpy(person->familyName, familyName);
	person->id = id;
	
	person->next = node->next;
	node->next = person;
	
	return person;
}

/************************************************************************/
/*
Purpose: create a new node and insert it into the end of the list
Input
head - the head of the list
id - id of person
firstName - first name of person
familyName - family name of person


return
A pointer to the node that was allocated.  

NULL - if the operation was not successful

*/


PersonalInfo *insertLast(PersonalInfo **head, unsigned int id, char *firstName, char *familyName){
	//printf("insertLast\n");
	if(*head == NULL){
		return insertToList(head, id, firstName, familyName);
	}
	PersonalInfo* last = *head;

	PersonalInfo* person = NULL; 
	person = (PersonalInfo*) malloc(sizeof(PersonalInfo));
	
	//check person was created
	if(person == NULL){return NULL;}
	
	//fill person
	strcpy(person->firstName, firstName);
	strcpy(person->familyName, familyName);
	person->id = id;
	person->next = NULL;
	
	//printNode(last);

	while(last->next != NULL){
		last = last->next;
		//printNode(last);
	}
	
	
	last->next = person;
	//printf("\n");
	return person;
	
}


/************************************************************************/
/*
Purpose: search for the first node with the matching firstName
Input
head - the head of the list
firstName - first name of person

return
a pointer to the node that was found.
NULL - if no node was found or list empty

*/


PersonalInfo *searchByName(PersonalInfo *head, char *firstName){
	PersonalInfo* find = head;
	while(find != NULL){
		if(strcmp(find->firstName, firstName) == 0){
			return find;
		}
		find = find->next;
	}
	return NULL;
}

/************************************************************************/
/*
Purpose: search for the first node with the matching id
Input
head - the head of the list
id - id of person person

return
a pointer to the node that was allocated.  

NULL - if no node was found or list empty 

*/


PersonalInfo *searchById(PersonalInfo *head, unsigned int id){
	PersonalInfo* find = head;
	while(find != NULL){
		if(find->id == id){
			return find;
		}
		find = find->next;
	}
	return NULL;
}

/***************************************************************/

/*
Purpose: delete the first node from the list
Input
head - the head of the list

output
head - the head of the list
firstName - first name of delted record
familyName - family name of deleted recrod
id - id of deleted record


return

0 if node was deleted
1 if node was not deleted or list is empty

*/


int deleteFromList(PersonalInfo **head, unsigned int *id, char *firstName, char *familyName){
	if(*head == NULL){return 1;}
	
	if((*head)->next == NULL){
		free(*head);
		*head = NULL;
		return 0;
	}
	PersonalInfo* temp = (*head)->next;

	strcpy(firstName, (*head)->firstName);
	strcpy(familyName, (*head)->familyName);
	*id = (*head)->id;

	free(*head);

	*head = temp;

	return 0;
}


/***************************************************************/

/*
Purpose: delete the last node from the list
Input
head - the head of the list

output
head - the head of the list
firstName - first name of delted record
familyName - family name of deleted recrod
id - id of deleted record


return

0 if node was deleted  
1 if node was not deleted or list is empty 

*/


int deleteLast(PersonalInfo **head, unsigned int *id, char *firstName, char *familyName){
	if(*head == NULL){return 1;}
	
	if((*head)->next == NULL){
		strcpy(firstName, (*head)->firstName);
		strcpy(familyName, (*head)->familyName);
		*id = ((*head)->id);
		(*head)->next = NULL;

		free(*head);
		*head = NULL;
		return 0;
	}

	PersonalInfo* last = *head;
	while(last->next->next != NULL){
		printNode(last);
		last = last->next;
	}
	//check bounds how does it act if list empty
	printf("last: ");printNode(last);
	PersonalInfo* temp = last->next;
	printf("temp: ");printNode(temp);
	
	strcpy(firstName, temp->firstName);
	strcpy(familyName, temp->familyName);
	*id = (temp->id);
	temp->next = NULL;
	free(temp);
	last->next = NULL;	
	
	return 0;
}



/************************************************************************/

/*
Purpose: delete the record after the given node 
Input
node - a node in the list

output
firstName - first name of delted record
familyName - family name of deleted recrod
id - id of deleted record


return
0 if node was deleted 
1 if node was not deleted (either input node is NULL or input node was the lastnode in the list)

*/


int deleteAfter(PersonalInfo *node, unsigned int *id, char *firstName, char *familyName){
	if(node == NULL || node->next == NULL){return 1;}
	PersonalInfo* temp = node->next;
	
	strcpy(firstName, temp->firstName);
	strcpy(familyName, temp->familyName);
	*id = (temp->id);
	
	node->next = temp->next;
	temp->next = NULL;
	
	free(temp);
	
	return 0;
}

/************************************************************************/

/*
Purpose: delete the first node with the matching firstName
Input
head - the head of the list
firstName - first name of person

output
head - the head of the list
firstName - first name of delted record
familyName - family name of deleted recrod
id - id of deleted record


return
0  if node was deleted
1 if node was not found (e.g., list is empty, no such node exists)

*/


int deleteNodeByName(PersonalInfo **head, char *firstName, char *familyName, unsigned int *id){
	if(*head == NULL){return 1;}
	PersonalInfo* find = *head;
	if(strcmp(find->firstName, firstName)){
		return deleteFromList(head, id, firstName, familyName);
	}
	do{
		if(strcmp(find->next->firstName, firstName)){
			return deleteAfter(find, id, firstName, familyName);
		}
		find = find->next;
	} while(find->next != NULL);
	if(strcmp(find->firstName, firstName)){
		return deleteLast(head, id, firstName, familyName);
	}
	return 1;
}
/************************************************************************/
/*
Purpose: deletes all nodes from the list
input/output
head - the head of the list


*/


void deleteList(PersonalInfo **head){
	PersonalInfo* find = *head;
	PersonalInfo* temp = NULL;
	while(find != NULL){
		temp = find->next;
		free(find);
		find = temp->next;
	}
	free(find);
	free(temp);
}



/************************************************************************/
/*
Purpose: prints the fields of a node
input:
node - a pointer to a given node

*/


void printNode(PersonalInfo *node){
	printf("%-20s %-20s %7d \n",node->firstName, node->familyName, node->id);

}


/************************************************************************/
/*
Purpose: prints all the records in the list

input
head - the head of the list
*/


void printList(PersonalInfo *head){
	PersonalInfo* find = head;
	while(find != NULL){
		printNode(find);
		find = find->next;
	}
}

/************************************************************************/
/*
Purpose: counts the number of nodes in the list
input
head - the head of the list

return 
the number of nodes in the list

*/


int listSize(PersonalInfo *head){
	int num = 0;
	PersonalInfo* find = head;
	while(find != NULL){
		num++;
		find = find->next;
	}
	return num;
}

/************************************************************************/
/*
Purpose: counts the number of nodes in the list with a matching firstName
input
head - the head of the list

return 
the number of nodes in the list that match the firstName


*/


int countRecords(PersonalInfo *head, char *firstName){
	int num = 0;
	PersonalInfo* find = head;
	while(find != NULL){
		if(strcmp(find->firstName, firstName) == 0){
			num++;
		}
		find = find->next;
	}
	return num;
}




/************************************************************************/
/*

Purpose: removes all duplicates records from the list.  Duplicate records are determined by their first name. 
You can assume that the listed is sorted by first name.

input
head - the head of the  list



*/


void removeDuplicates(PersonalInfo *head){
	PersonalInfo* find = head->next;
	PersonalInfo* prev = head;
	while(find != NULL){
		//printf("\nPrinting nodes\n");
		//printNode(find);
		//printNode(prev);
		if(prev != NULL && find != NULL){
			if(strcmp(find->firstName, prev->firstName) == 0){
				//printf("!!removing\n");
				prev->next = find->next;
				free(find);
				find = prev;
			}
		}
		prev = find;
		find = find->next;
	}
}

