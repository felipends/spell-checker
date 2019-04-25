# Spell-checker Hash-table based

An example of spell-checking algorithm using a hash-table based dictionary.

Using as reference for the dictionary the file `instances/dic.txt`.

## Usage

`$ gcc -O3 main.c -o run`

`$ ./run instances/constituicao.txt`

## Some results

### For the dictionary

Using `instances/dic.txt`

* 307855 words on the dictionary
* 262144 buckets
* 86008 collisions (handled by chaining) 
* 2 elemnts per colision avarage

### For the test

Using `instances/constituicao.txt` as instance

* 6982 words checked
* 4787 words failed the spell-checking
* total checkage time 2.524ms

## Hash function initially used

```C
size_t string_hash( const char* str ){
	size_t hash = 0;
	for(size_t i = 0; i < strlen(str); i++){
		hash += str[i];
		hash += (hash << 10);
		hash ^= (hash >> 6);
	}
	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);

	return hash & (NBUCKETS-1);
}
```

An adapted implemantation of one-at-a-time Bob Jenkins hash function, which can be found
[here](http://burtleburtle.net/bob/hash/doobs.html).

##  TODO

1. File formated output
2. Benchmark with others hash functions
