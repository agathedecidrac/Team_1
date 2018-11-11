#include "random.h"



Random::Random(unsigned long int _seed) {
    initialize (_seed);
}



void Random::initialize (unsigned long int _seed){
    seed=_seed;
    if (seed==0) {
        std::random_device rd;
        seed=rd();
    }
    rng = std::mt19937(seed);
}


//But: générer des nouvelles occurences d'allèles selon la loi multinomiale
std::vector<int> Random::multinomial (std::vector<int> CurrentAlleles){
    std::vector<int> NewAlleles;

    for(int i(0); i<CurrentAlleles.size(); ++i){
        int population_n(getPopulationSize());
        int population_p(getPopulationSize());

        for (int j(0); j<i; ++j){ //calcul des populations utiles pour le calcul de p_sucess et n_trials
            population_n -= NewAlleles[j];
            population_p -= CurrentAlleles[j];
        }
        NewAlleles[i] = binomial(population_n,CurrentAlleles[i]/population_p);
    }

    return NewAlleles;

}



//utlile pour la distribution multinomiale
int Random::binomial(int n_trials, double p_succes){
    std::binomial_distribution<int> bin (n_trials,p_succes);
    return bin(rng);
}



Random::~Random() {}