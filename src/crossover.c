#include <stdlib.h>

unsigned int* fill(unsigned int* parents, int numParents, int returnSetSize) {
    unsigned int* returnSet = (unsigned int*)malloc(sizeof(unsigned int) * returnSetSize);

    int parentIndex = 0;
    int returnIndex = 0;

    while(returnIndex < returnSetSize) {
        returnSet[returnIndex++] = parents[parentIndex++ % numParents];
    }

    return returnSet;
}