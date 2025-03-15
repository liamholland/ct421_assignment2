#include <stdlib.h>
#include "mutation.h"

void oneBitMutation(unsigned int* population, int popSize, double mutRate) {
    int mutRateValue = (int)(1000 * mutRate);

    for(int i = 0; i < popSize; i++) {
        if(rand() % 1001 <= mutRateValue) {
            //mutate a random bit
            population[i] = population[i] ^ (1 << (rand() % 3));
        }
    }
}