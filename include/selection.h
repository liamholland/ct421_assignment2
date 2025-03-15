#ifndef SELECT
#define SELECT

unsigned int* tournamentSelection(unsigned int* population, int popSize, int returnSetSize, int tournamentSize, int comparisonLength);

unsigned int* elitism(unsigned int* population, int popSize, int returnSetSize, int comparisonLength);

int getBestStrat(unsigned int* list, int listLength, int comparisonLength);

int getMostCommonStrat(unsigned int* list, int listLength);

#endif