
#include <stdio.h>
#include <string.h>
#include "hashtable.h"


int tests_run = 0;
#define FAIL() printf("\nfailure in %s() line %d\n", __func__, __LINE__)
#define _assert(test) do { if (!(test)) { FAIL(); return 1; } } while(0)
#define _verify(test) do { int r=test(); tests_run++; if(r) return r; } while(0)

unsigned int hashString(void *data) {
	unsigned int hash = 5381;
    int c;

    char *str = (char *)data;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

bool eqString(void *a, void *b) {
	return strcmp((const char *)a, (const char *)b) == 0;
}

int testEmptyHashtable() {
	HashTable t = ht_create(hashString, eqString);

	_assert(ht_getLength(t) == 0);
	_assert(ht_getNumBuckets(t) == 32);

	ht_destroy(t);
	return 0;
}

int testBasicInsert() {
	HashTable t = ht_create(hashString, eqString);

	const char *val = "test_value";
	_assert(ht_insert(t, (void *)val));
	_assert(!ht_insert(t, (void *)val));

	ht_destroy(t);
	return 0;
}

int allTests() {
	_verify(testEmptyHashtable);
	_verify(testBasicInsert);
	return 0;
}

int main(int argc, const char *argv[]) {
	int result = allTests();
    if (result == 0)
        printf("PASSED\n");
    printf("Tests run: %d\n", tests_run);
	return 0;
}
