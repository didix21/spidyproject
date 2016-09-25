#ifndef VAR_H_INCLUDED
#define VAR_H_INCLUDE
#include <vector>

int Inputs = 4;
int Outputs = 4;

class network
{

};

class genes
{

};

class genomes
{

    public:
    std::vector<genes> GenesVec;
    int fitness;
    int adjustedFitness;
    std::vector<network> NetworkVec;
    int maxneuron;
    int globalRank;
    int mutationRates[7];
};


class species
{
    public:
    species();
    int topFitness;
    int staleness;
    std::vector<genomes> GenomesVec;
    int averageFitness;

};

class Pool
{
    public:
    Pool();
    std::vector<species> SpeciesVec;
    int generation;
    int innovation;
    int currentSpecies;
    int currentGenome;
    int currentFrame;
    int maxFitness;
};

Pool::Pool(){
generation=0;
innovation=Outputs;
currentFrame=0;
currentGenome=1;
currentSpecies=1;
maxFitness=0;
}

species::species(){
topFitness=0;
staleness=0;
genomes=0;
}




#endif // VAR_H_INCLUDED
