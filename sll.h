/*
 * =====================================================================================
 *
 *       Filename:  sll.h
 *
 *    Description:  Singly linked list implementation
 *
 *        Version:  1.0
 *        Created:  22/04/2019 23:44:14
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Felipe Nunes
 *   Organization:  UFPB
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SLEN 50 //max length of string

typedef struct Node{
	char value[SLEN];
	struct Node* next;
} Node;

typedef struct tSLL{
	Node* head;
	size_t size;
}tSLL;

inline void sll_preppend( tSLL** list, const char* val ){
	if( (*list) == NULL){
		(*list) = (tSLL*)malloc(sizeof(tSLL));
		(*list)->head = (Node*)malloc(sizeof(Node));
		strncpy((*list)->head->value, val, strlen(val));
		(*list)->head->next = NULL;
	} else {
		Node* no = (Node*)malloc(sizeof(Node));
		strncpy(no->value, val, strlen(val));
		no->next = (*list)->head;
		
		(*list)->head = no;
	}

	(*list)->size++;
}

//1 if foind 0 if not
inline int sll_search( const Node* no, const char* val ){
	while(1){
		if(strncmp(no->value, val, SLEN) == 0) {
			return 1;
		}

		if(no->next == NULL) break;

		no = no->next;
	}
	return 0;
}

void sll_print_list( const Node* head, FILE* output ){
	size_t count_word = 0;
    while(1){
        count_word++;
		fprintf(output, "%ld - %s\n", count_word, head->value);
		if(head->next == NULL) break;
		head = head->next;
	}
}

int collisions_check( const tSLL* list ){
	
	if(list == NULL) return 0;
	
	return list->size;
}

void sll_deallocate( tSLL** list ){
	Node** nop = malloc(sizeof(Node*));
	Node** non = malloc(sizeof(Node*));
	(*non) = (*list)->head;
	while(1){
		(*nop) = (*non)->next;
		free(*non);
		if((*nop) == NULL) break;
		(*non) = (*nop);
	}
	(*list)->size = 0;
	free(non);
	free(nop);
}
