
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hashtable.h"


int tests_run = 0;
#define FAIL() printf("\nfailure in %s() line %d\n", __func__, __LINE__)
#define _assert(test) do { if (!(test)) { FAIL(); return 1; } } while(0)
#define _verify(test) do { int r=test(); tests_run++; if(r) return r; } while(0)

static unsigned int hashString(const void *data) {
	unsigned int hash = 5381;
    int c;

    char *str = (char *)data;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

static bool eqString(const void *a, const void *b) {
	return strcmp((const char *)a, (const char *)b) == 0;
}

static unsigned int hashInt(const void *data) {
	int *i = (int *)data;
	return *i;
}

static bool eqInt(const void *a, const void *b) {
	return *((int *)a) == *((int *)b);
}

static int testEmptyHashtable() {
	fbht_HashTable *t = fbht_create(hashString, eqString);

	_assert(fbht_getLength(t) == 0);
	_assert(fbht_getNumBuckets(t) == 32);

	fbht_destroy(t);
	return 0;
}

static int testBasicInsert() {
	fbht_HashTable *t = fbht_create(hashString, eqString);

	const char *val = "test_value";
	_assert(fbht_insert(t, (void *)val));
	_assert(!fbht_insert(t, (void *)val));

	fbht_destroy(t);
	return 0;
}

static int testNumBucketIncrease() {
	fbht_HashTable *t = fbht_create(hashInt, eqInt);

	for (int i = 0; i <= 17; ++i) {
		int *ip = malloc(sizeof(int));
		*ip = i;
		fbht_insert(t, (void *)ip);	
	}

	_assert(fbht_getNumBuckets(t) == 64);

	fbht_destroy(t);
	return 0;
}

static int testResizeKeepsData() {
	fbht_HashTable *t = fbht_create(hashInt, eqInt);

	for (int i = 0; i <= 32; ++i) {
		int *ip = malloc(sizeof(int));
		*ip = i;
		fbht_insert(t, (void *)ip);	
	}

	for (int i = 0; i <= 32; ++i) {
		_assert(fbht_contains(t, (void *)&i));
	}

	fbht_destroy(t);
	return 0;
}

static int allTests() {
	_verify(testEmptyHashtable);
	_verify(testBasicInsert);
	_verify(testNumBucketIncrease);
	_verify(testResizeKeepsData);
	return 0;
}

int main(int argc, const char *argv[]) {
	int result = allTests();
    if (result == 0)
        printf("PASSED\n");
    printf("Tests run: %d\n", tests_run);
	return 0;
}
