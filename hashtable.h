
#include <stdbool.h>

struct _fbht_HashTable;
typedef struct _fbht_HashTable fbht_HashTable;


// create and destroy

fbht_HashTable *fbht_create(
	unsigned int(*hashFunction)(void *), 
	bool (*eqFunction)(void *, void *)
);
void fbht_destroy(fbht_HashTable *t);


// accessors

unsigned int fbht_getLength(fbht_HashTable *t);
unsigned int fbht_getNumBuckets(fbht_HashTable *t);


// mutators

// returns true if value was not already present
bool fbht_insert(fbht_HashTable *t, void *value);
