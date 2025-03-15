#include <stdio.h>
#include "fitness.h"
#include "selection.h"

#define REWARD_CC 3
#define REWARD_CD 0
#define REWARD_DC 5
#define REWARD_DD 1

#define NUM_FIXED_STRATS 32  //length of strats array

//fixed strategies
unsigned int strats[] = {
    0b000,  // always defect
    0b001,  // 1    DDC
    0b010,  // evil tit-for-tat
    0b011,  // 3    DCC
    0b100,  // 4    CDD
    0b101,  // 5    CDC
    0b110,  // tit-for-tat
    0b111   // always cooperate
};

int fitness(int strategy, int comarisonLength) {
    int fitness = 0;
    
    for(int i = 0; i < NUM_FIXED_STRATS; i++) {
        fitness += performanceStratAvsStratB(strategy, i, comarisonLength);
    }

    return fitness;
}

int performanceStratAvsStratB(int stratA, int stratB, int comparisonLength) {
    int nextA;
    int lastA = (stratA & 0b100) >> 2;
    int last2A;

    int nextB;
    int lastB = (stratB & 0b100) >> 2;
    int last2B;

    int totalRewardA = 0;
    int totalRewardB = 0;

    totalRewardA += rewardForAvsB(lastA, lastB);
    totalRewardB += rewardForAvsB(lastB, lastA);

    nextA = lastB ? (stratA & 0b010) >> 1 : stratA & 0b001;
    nextB = lastA ? (stratB & 0b010) >> 1 : stratB & 0b001;

    last2A = lastA;
    lastA = nextA;
    last2B = lastB;
    lastB = nextB;

    for(int i = 0; i < comparisonLength; i++) {
        totalRewardA += rewardForAvsB(lastA, lastB);
        totalRewardB += rewardForAvsB(lastB, lastA);

        if(last2B == lastB && stratA >= 8) {
            nextA = last2B & lastB ? (stratA & 0b10000) >> 4 : (stratA & 0b01000) >> 3;
        }
        else {
            nextA = lastB ? (stratA & 0b010) >> 1 : stratA & 0b001;
        }

        if(last2A == lastA && stratB >= 8) {
            nextB = last2A & lastA ? (stratB & 0b10000) >> 4 : (stratB & 0b01000) >> 3;
        }
        else {
            nextB = lastA ? (stratB & 0b010) >> 1 : stratB & 0b001;
        }

        last2A = lastA;
        lastA = nextA;
        last2B = lastB;
        lastB = nextB;    
    }

    //return total reward
    return totalRewardA - totalRewardB;
}

int rewardForAvsB(int moveA, int moveB) {
    if(moveA && moveB) {            //both C
        return REWARD_CC;
    } else if(moveA > moveB) {      //A C and B D
        return REWARD_CD;
    } else if(moveA < moveB) {      //A D and B C
        return REWARD_DC;
    } else if(!moveA && !moveB) {   //both D
        return REWARD_DD;
    }
}

void testFitness() {
    for(int i = 0; i < 32; i++) {
        printf("%d: %d\n", i, fitness(i, 50));
    }
}
