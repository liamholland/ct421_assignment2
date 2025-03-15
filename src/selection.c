#include <stdlib.h>
#include <string.h>
#include "selection.h"
#include "fitness.h"

//private helper functions
int compareAtoB(const void* a,const void* b);
void randomSample(unsigned int* list, int listSize, unsigned int* sample, int sampleSize);

int fitnessComparisonLength;    //used to communicate size for strat comps

unsigned int* tournamentSelection(unsigned int* population, int popSize, int returnSetSize, int tournamentSize, int comparisonLength) {
    //copy the population
    unsigned int* popCopy = (unsigned int*)malloc(sizeof(unsigned int) * popSize);
    memcpy(popCopy, population, sizeof(unsigned int) * popSize);

    //create the return set
    unsigned int* tournamentWinners = (unsigned int*)malloc(sizeof(unsigned int) * returnSetSize);
    int numWinners = 0;

    //create the tournament list
    unsigned int* tournament = (unsigned int*)malloc(sizeof(unsigned int) * tournamentSize);

    //set the comparison length
    fitnessComparisonLength = comparisonLength;

    do {
        randomSample(popCopy, popSize, tournament, tournamentSize);     //get a random sample
        tournamentWinners[numWinners] = getBestStrat(tournament, tournamentSize, comparisonLength);
    }while(++numWinners < returnSetSize);

    free(popCopy);
    free(tournament);

    return tournamentWinners;
}

unsigned int* elitism(unsigned int* population, int popSize, int returnSetSize, int comparisonLength) {
    //copy the population
    unsigned int* popCopy = (unsigned int*)malloc(sizeof(unsigned int) * popSize);
    memcpy(popCopy, population, sizeof(unsigned int) * popSize);
    
    //set the comparison length
    fitnessComparisonLength = comparisonLength;

    //sort the list by fitness
    qsort(popCopy, popSize, sizeof(unsigned int), &compareAtoB);

    //take the first n entries
    unsigned int* elites = (unsigned int*)malloc(sizeof(unsigned int) * returnSetSize);
    memcpy(elites, popCopy, returnSetSize);

    free(popCopy);

    return elites;
}

int compareAtoB(const void* a,const void* b) {
    int stratA = *(unsigned int*)a;
    int stratB = *(unsigned int*)b;

    return performanceStratAvsStratB(stratA, stratB, fitnessComparisonLength);
}

int getBestStrat(unsigned int* list, int listLength, int comparisonLength) {
    int best = -1;
    int bestFit = -1;

    for(int i = 0; i < listLength; i++) {
        int fit = fitness(list[i], comparisonLength);
        
        if(best < 0 || fit > bestFit) {
            best = list[i];
            bestFit = fit;
        }
    }

    return best;
}

int getMostCommonStrat(unsigned int* list, int listLength) {
    int* freq = (int*)calloc(32, sizeof(int));

    for(int i = 0; i < listLength; i++) {
        freq[list[i]]++;
    }

    int mostCommonStrat = -1;
    int highestFreq = 0;
    for(int i = 0; i < 32; i++) {
        if(mostCommonStrat == -1 || freq[i] > highestFreq) {
            mostCommonStrat = i;
            highestFreq = freq[i];
        }
    }

    return mostCommonStrat;
}

void randomSample(unsigned int* list, int listSize, unsigned int* sample, int sampleSize) {
    int numSelected = 0;

    while(numSelected < sampleSize) {
        sample[numSelected++] = list[rand() % listSize];
    }
}
