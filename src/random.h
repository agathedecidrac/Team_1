#ifndef RANDOM_H
#define RANDOM_H

#include <vector>
#include <iostream>
#include <random>
#include "simulation.h"



class Random {

public:
	Random(unsigned long int _seed=0);
    void initialize (unsigned long int _seed=0);


	std::vector<int> multinomial (std::vector<int> CurrentAlleles);
	int binomial(int n, double p);

    ~Random();

private:
	long int seed;
    std::mt19937 rng;


};

extern Random RNG;

#endif // RANDOM_H

