
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "heap.h"

int tests_run = 0;
#define FAIL() printf("\nfailure in %s() line %d\n", __func__, __LINE__)
#define _assert(test) do { if (!(test)) { FAIL(); return 1; } } while(0)
#define _verify(test) do { int r=test(); tests_run++; if(r) return r; } while(0)

static int cmpString(const void *d1, const void *d2) {
    const char *s1 = (const char *)d1;
    const char *s2 = (const char *)d2;

    const unsigned int len1 = strlen(s1);
    const unsigned int len2 = strlen(s2);
    const unsigned int len = len1 < len2 ? len1 : len2;

    for (int i = 0; i < len; ++i) {
        char c1 = s1[i];
        char c2 = s2[i];
        
        if (c1 < c2) {
            return -1;
        }
        if (c1 > c2) {
            return 1;
        }
    }

    if (len1 < len2) {
        return -1;
    }
    if (len1 > len2) {
        return 1;
    }
    return 0;
}

static int testEmptyHeap() {
    hp_Heap *h = hp_create(cmpString);

    _assert(hp_getSize(h) == 0);

    hp_destroy(h);
    return 0;
}

static int allTests() {
    _verify(testEmptyHeap);
    return 0;
}

int main(int argc, const char *argv[]) {
    int result = allTests();
    if (result == 0)
        printf("PASSED\n");
    printf("Tests run: %d\n", tests_run);
    return 0;
}
