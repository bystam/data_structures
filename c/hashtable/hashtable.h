
#include <stdbool.h>

struct _fbht_HashTable;
typedef struct _fbht_HashTable fbht_HashTable;


// create and destroy

fbht_HashTable *fbht_create(
    unsigned int(*hashFunction)(const void *), 
    bool (*eqFunction)(const void *, const void *)
);
void fbht_destroy(fbht_HashTable *t);


// accessors

unsigned int fbht_getLength(const fbht_HashTable *t);
unsigned int fbht_getNumBuckets(const fbht_HashTable *t);
bool fbht_contains(const fbht_HashTable *t, const void *value);

// mutators

// returns true if value was not already present
bool fbht_insert(fbht_HashTable *t, const void *value);
