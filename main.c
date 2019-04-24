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
	
	assert(dic != NULL || test != NULL);
	
	int palavras_count = 0;
	char palavra[SLEN];
	tSLL* table[NBUCKETS] = { NULL }; //table firstly initialized as a NULL pointers to list because of the chaining collision handle method
	
	tSLL* fail_list = NULL;
	
	//hash table construction
	while(1){
		if(feof(dic)) break;
		fscanf(dic, "%s", palavra);
		table_insert(&table[string_hash(palavra)], palavra);
		palavras_count++;
	}
	printf("%d\n", compute_collisions(table));
	//check file x dic
	start_t = clock();
	int search_result;
	int fail_count = 0;
	while(1){
		if(feof(test)) break;
		fscanf(test, "%s", palavra);
		search_result = sll_search(table[string_hash(palavra)], palavra);
		if(search_result == 0){
			fail_count++;
			sll_preppend(&fail_list, palavra);
		}
	}
	end_t = clock();
	total_t = (double) (end_t - start_t)/CLOCKS_PER_SEC;
	printf("%lf\n", total_t);
	printf("%d\n", fail_count);
		
	//sll_print_list(fail_list->head);
	return argc;
}

