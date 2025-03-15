#include <stdlib.h>
#include <stdio.h>
#include "population.h"

unsigned int* populateAllOnes(int popSize) {
    unsigned int* population = (unsigned int*)malloc(sizeof(unsigned int) * popSize);
    
    for(int i = 0; i < popSize; i++) {
        population[i] = 0b111;
    }

    return population;
}

unsigned int* populateRandomly(int popSize) {
    unsigned int* population = (unsigned int*)malloc(sizeof(unsigned int) * popSize);

    for(int i = 0; i < popSize; i++) {
        population[i] = rand() % 32;
    }

    return population;
}