
#include "hashtable.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUCKET_EMPTY 0

struct _fbht_HashTable {
	unsigned int length;
	unsigned int numBuckets;
	unsigned int (*hashFunction)(void*);
	bool (*eqFunction)(void *, void *);
	void **data;
};

// create and destroy

fbht_HashTable *fbht_create(
	unsigned int(*hashFunction)(void *), 
	bool (*eqFunction)(void *, void *)
) {
	static unsigned int kInitialSize = 32;

	fbht_HashTable *t = (fbht_HashTable *)malloc(sizeof(fbht_HashTable));

	t->length = 0;
	t->numBuckets = kInitialSize;
	t->hashFunction = hashFunction;
	t->eqFunction = eqFunction;
	
	t->data = calloc(kInitialSize, sizeof(void *));
	
	return t;
}

void fbht_destroy(fbht_HashTable *t) {
	free(t->data);
	free(t);
}


// accessors

unsigned int fbht_getLength(fbht_HashTable *t) {
	return t->length;
}

unsigned int fbht_getNumBuckets(fbht_HashTable *t) {
	return t->numBuckets;
}


// mutators

static void _resizeTable(fbht_HashTable *t) {
	// TODO
}

bool fbht_insert(fbht_HashTable *t, void *newValue) {

	if (t->length == t-> numBuckets) {
		_resizeTable(t);
	}

	unsigned int hash = t->hashFunction(newValue);
	unsigned int bucket = hash % t->numBuckets;

	for (void *bucketValue = t->data[bucket];
		bucketValue != BUCKET_EMPTY;
		bucket = (bucket + 1) % t->numBuckets,
		bucketValue = t->data[bucket]) {

		bool alreadyExists = t->eqFunction(bucketValue, newValue);
		if (alreadyExists) {
			return false;
		}
	}

	t->length += 1;
	t->data[bucket] = newValue;

	return true;
}
