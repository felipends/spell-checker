/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  Main file with implementation of the spell-checker.
 *
 *        Version:  1.0
 *        Created:  23/04/2019 20:18:24
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Felipe Nunes, 
 *   Organization:  UFPB
 *
 * =====================================================================================
 */
#include "hash-table.h"
#include <assert.h>
#include <time.h>

int main( int argc, char* argv[] ){
	clock_t start_t, end_t;
	double total_t;	
	FILE* dic, * test;

	dic = fopen("./instances/dic.txt", "rb");
	test = fopen(argv[1], "rb");
	
	assert(dic != NULL && test != NULL && argc > 1);
	
	int palavras_count = 0;
	char palavra[SLEN];
	tSLL* table[NBUCKETS] = { NULL }; //table firstly initialized as a NULL pointers to list because of the chaining collision handle method

	tSLL* palavras_teste = NULL; 

	tSLL* fail_list = NULL;

	//hash table construction
	while(1){
		if(feof(dic)) break;
		fscanf(dic, "%s", palavra);
		table_insert(&table[string_hash(palavra)], palavra);
		palavras_count++;
	}
	
	size_t colisions = compute_collisions(table);
	printf("%lu\n", colisions);
	//load instace to memory
	while(1){
		if(feof(test)) break;
		fscanf(test, "%s", palavra);

		sll_preppend(&palavras_teste, palavra);
	}

	//check file x dic
	start_t = clock();
	int search_result;
	size_t hash_test;
	Node* no = malloc(sizeof(Node));
	no = palavras_teste->head;
	while(1){
		hash_test = string_hash(no->value);
        if(table[hash_test] == NULL) search_result = 0;
        else search_result = sll_search(table[hash_test]->head, no->value);
		if(!search_result){
			sll_preppend(&fail_list, no->value); 
		}
		
		if(no->next == NULL) break;
		no = no->next;
	}
	end_t = clock();
	total_t = (double) (end_t - start_t)/CLOCKS_PER_SEC;

    //print result
	printf("temp total da verificação: %lf\n", total_t);
	printf("quantidade de palavras que falharam: %lu\n", fail_list->size);
		
	//sll_print_list(palavras_teste->head);
	
	//memory dealloc
	table_deallocate(table);
	sll_deallocate(&fail_list);
	sll_deallocate(&palavras_teste);

	free(palavras_teste);
	free(fail_list);

	fclose(dic);
	fclose(test);
	
	return 0;
}

