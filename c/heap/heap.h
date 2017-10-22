
#include <stdbool.h>

struct _hp_Heap;
typedef struct _hp_Heap hp_Heap;


// create and destroy

hp_Heap *hp_create(
    int(*cmpFunction)(const void *, const void *)
);
void hp_destroy(hp_Heap *h);


// accessors

unsigned int hp_getSize(const hp_Heap *h);


// mutators

void hp_insert(hp_Heap *h, const void *value);
const void *hp_pop(hp_Heap *h);
