#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "population.h"
#include "selection.h"
#include "fitness.h"
#include "mutation.h"
#include "crossover.h"

#define MAX_ITERATIONS 50
#define POP_SIZE 50
#define NUM_ELITES 5
#define TOURNAMENT_SIZE 5
#define FITNESS_COMP_LENGTH 50
#define NUM_PARENTS 10
#define CONVERGENCE_CHECK_LENGTH 20
#define MUT_RATE 0.005

void runGA();

int main(int argc, char const *argv[]) {
    srand(time(NULL));

    // testFitness();

    runGA();

    return 0;
}

void runGA() {

    //initialise population
    unsigned int* population = populateRandomly(POP_SIZE);

    printf("most common strat at start: %d\n", getMostCommonStrat(population, POP_SIZE));

    int lastAvergaeFitness;
    unsigned int* fitnessAtIterationI = (unsigned int*)malloc(sizeof(unsigned int) * MAX_ITERATIONS);

    printf("STARTING GA\n");

    clock_t startTime = clock();

    //main loop
    for(int i = 0; i < MAX_ITERATIONS; i++) {

        //calculate fitness
        //do this first to see the starting fitness in results
        int totalFitness = 0;
        for(int j = 0; j < POP_SIZE; j++) {
            totalFitness += fitness(population[j], FITNESS_COMP_LENGTH);
        }

        lastAvergaeFitness = totalFitness / POP_SIZE;
        fitnessAtIterationI[i] = lastAvergaeFitness;

        //select parents
        unsigned int* tournamentWinners = tournamentSelection(population, POP_SIZE, NUM_PARENTS, TOURNAMENT_SIZE, FITNESS_COMP_LENGTH);

        //crossover
        //this is just duplicating the chosen parents into the next generation
        unsigned int* crossed = fill(tournamentWinners, NUM_PARENTS, POP_SIZE);
        free(tournamentWinners);

        //reconstruct next set
        free(population);
        population = crossed;

        //mutate
        oneBitMutation(population, POP_SIZE, MUT_RATE);
    }

    clock_t endTime = clock();
    double runTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;

    printf("DONE\n");

    //report stats
    printf("ran for: %.3fs\nlast average fitness: %d\nbest strat in population: %d\nmost common strat: %d\n",
        runTime,
        lastAvergaeFitness,
        getBestStrat(population, POP_SIZE, FITNESS_COMP_LENGTH),
        getMostCommonStrat(population, POP_SIZE));

    free(population);

    FILE* f = fopen("results.csv", "w+");

    //output the fitness
    for(int i = 0; i < MAX_ITERATIONS; i++) {
        fprintf(f, "%d\n", fitnessAtIterationI[i]);
    }
    
    fclose(f);
}
