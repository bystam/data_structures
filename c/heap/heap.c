
#include "heap.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define _LEFT_CHILD(k) (2*k + 1)
#define _RIGHT_CHILD(k) (2*k + 2)
#define _PARENT(k) ((k - 1)/2)
#define _HEAD 0

struct _hp_Heap {
    unsigned int size;
    unsigned int length;
    int (*cmpFunction)(const void *, const void *);
    const void **data;
};

// create and destroy

hp_Heap *hp_create(
    int(*cmpFunction)(const void *, const void *)
) {
    static unsigned int kInitialLength = 32;

    hp_Heap *h = (hp_Heap *)malloc(sizeof(hp_Heap));

    h->size = 0;
    h->length = kInitialLength;
    h->cmpFunction = cmpFunction;

    h->data = calloc(kInitialLength, sizeof(void *));

    return h;
}

void hp_destroy(hp_Heap *h) {
    free(h->data);
    free(h);
}


// accessors

unsigned int hp_getSize(const hp_Heap *h) {
    return h->size;
}

// mutators

void hp_insert(hp_Heap *h, const void *value) {
    const unsigned int last = h->size;
    h->data[last] = value;
    h->size += 1;

    // raise
    unsigned int k = last;
    unsigned int parent = _PARENT(k);
    const void *parentVal = h->data[parent];

    // while value is bigger, swap value with parent
    while (h->cmpFunction(value, parentVal) < 0 && k != _HEAD) {
        h->data[parent] = value;
        h->data[k] = parentVal;

        k = parent;
        parent = _PARENT(k);
        parentVal = h->data[parent];
    }
}

const void *hp_pop(hp_Heap *h) {
    if (h->size == 0) {
        return NULL;
    }

    const void *value = h->data[_HEAD];
    const unsigned int last = h->size - 1;
    const void *lastVal = h->data[last];
    h->data[_HEAD] = lastVal;

    unsigned int k = _HEAD;
    while (k < last) {
        unsigned int left = _LEFT_CHILD(k);
        unsigned int right = _LEFT_CHILD(k);
        const void *currVal = h->data[k];
        const void *leftVal = h->data[left];
        const void *rightVal = h->data[right];

        bool biggerThanChildren = (h->cmpFunction(currVal, leftVal) < 0
                                && h->cmpFunction(currVal, rightVal) < 0)
        if (biggerThanChildren) {
            break;
        }

        bool rightIsBigger = h->cmpFunction(leftVal, rightVal) > 0;
    }

    return value;
}