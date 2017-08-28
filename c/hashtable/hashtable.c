
#include "hashtable.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUCKET_EMPTY NULL

struct _fbht_HashTable {
	unsigned int length;
	unsigned int numBuckets;
	unsigned int (*hashFunction)(const void *);
	bool (*eqFunction)(const void *, const void *);
	const void **data;
};

// create and destroy

fbht_HashTable *fbht_create(
	unsigned int(*hashFunction)(const void *),
	bool (*eqFunction)(const void *, const void *)
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

unsigned int fbht_getLength(const fbht_HashTable *t) {
	return t->length;
}

unsigned int fbht_getNumBuckets(const fbht_HashTable *t) {
	return t->numBuckets;
}

bool fbht_contains(const fbht_HashTable *t, const void *value) {
	const unsigned int hash = t->hashFunction(value);
	unsigned int bucket = hash % t->numBuckets;

	for (const void *bucketValue = t->data[bucket];
		bucketValue != BUCKET_EMPTY;
		bucket = (bucket + 1) % t->numBuckets,
		bucketValue = t->data[bucket]) {

		bool contains = t->eqFunction(bucketValue, value);
		if (contains) {
			return true;
		}
	}

	return false;
}


// mutators

static bool _insert(fbht_HashTable *t, const void *newValue) {
	const unsigned int hash = t->hashFunction(newValue);
	unsigned int bucket = hash % t->numBuckets;

	for (const void *bucketValue = t->data[bucket];
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

static void _resizeTable(fbht_HashTable *t) {

	const unsigned int numBuckets = t->numBuckets;
	const void **data = t->data;
	
	const unsigned int newNumBuckets = numBuckets * 2;
	const void **newData = calloc(newNumBuckets, sizeof(void *));

	t->numBuckets = newNumBuckets;
	t->length = 0;
	t->data = newData;

	for (int i = 0; i < numBuckets; ++i) {
		const void *val = data[i];
		if (val != BUCKET_EMPTY) {
			_insert(t, val);
		}
	}
}

bool fbht_insert(fbht_HashTable *t, const void *newValue) {
	if (t->length >= (t->numBuckets / 2)) {
		_resizeTable(t);
	}
	return _insert(t, newValue);
}
