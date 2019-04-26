/*
 * =====================================================================================
 *
 *       Filename:  hash-table.h
 *
 *    Description:  Hash table for string with chaining collision handler method implementation.
 *
 *        Version:  1.0
 *        Created:  23/04/2019 00:17:04
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Felipe Nunes 
 *   Organization:  UFPB
 *
 * =====================================================================================
 */

#include "sll.h"
#include <math.h>

#define NBUCKETS 524288

/*
 * adapted implementation of one-at-a-time jenkins hash function
 * which can be found in http://burtleburtle.net/bob/hash/doobs.html
 */

inline size_t string_hash( const char* str ){
	size_t hash = 0;
	for(size_t i = 0; str[i] != '\0'; i++){
		hash += str[i];
		hash += (hash << 19);
		hash ^= (hash >> 10);
	}
	hash += (hash << 6);
	hash ^= (hash >> 20);
	hash += (hash << 28);

	return hash & (NBUCKETS-1);
}

void table_insert( tSLL** table, const char* str ){
	sll_preppend(table, str); 
}

int compute_collisions( tSLL** table ){
	int cols = 0;
	for(int i = 0; i < NBUCKETS; i++){
		if(table[i] == NULL) continue;
		if(table[i]->size > 1) cols++;
	}

	return cols;
}

void table_deallocate( tSLL** table ){
	for(size_t i = 0; i < NBUCKETS; i++){
		if(table[i] == NULL) continue;
		sll_deallocate(&table[i]);
		free(table[i]);
	}
}

