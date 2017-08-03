
#include "hashtable.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUCKET_EMPTY 0

typedef struct {
	unsigned int length;
	unsigned int numBuckets;
	unsigned int (*hashFunction)(void*);
	bool (*eqFunction)(void *, void *);
	void **data;
} InternalHashTable;

typedef union {
	InternalHashTable internal;
	HashTable public;
} TableUnion;


// create and destroy

HashTable ht_create(
	unsigned int(*hashFunction)(void *), 
	bool (*eqFunction)(void *, void *)
) {
	static unsigned int kInitialSize = 32;
	TableUnion u;
	u.internal.length = 0;
	u.internal.numBuckets = kInitialSize;
	u.internal.hashFunction = hashFunction;
	u.internal.eqFunction = eqFunction;
	
	u.internal.data = calloc(kInitialSize, sizeof(void **));
	
	return u.public;
}

void ht_destroy(HashTable t) {
	TableUnion u;
	u.public = t;
	free(u.internal.data);
}


// accessors

unsigned int ht_getLength(HashTable t) {
	TableUnion u;
	u.public = t;
	return u.internal.length;
}

unsigned int ht_getNumBuckets(HashTable t) {
	TableUnion u;
	u.public = t;
	return u.internal.numBuckets;
}


// mutators

bool ht_insert(HashTable t, void *newValue) {
	TableUnion u;
	u.public = t;

	unsigned int hash = u.internal.hashFunction(newValue);
	unsigned int bucket = hash % u.internal.numBuckets;
	const unsigned int startBucket = bucket;

	while (u.internal.data[bucket] != BUCKET_EMPTY) {
		void *bucketValue = u.internal.data[bucket];

		bool alreadyExists = u.internal.eqFunction(bucketValue, newValue);
		if (alreadyExists) {
			return false;
		}

		if (++bucket == startBucket) { 
			// TODO resize table
		}
	}

	u.internal.length += 1;
	u.internal.data[bucket] = newValue;

	return true;
}