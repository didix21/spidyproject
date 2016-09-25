#ifndef VAR_H_INCLUDED
#define VAR_H_INCLUDE
#include <vector>

int Inputs = 4;
int Outputs = 4;

class species
{

};

class Pool
{
    std::vector<species> SpeciesVec;
    int generation=0;
    int innovation=Outputs;
    int currentSpecies = 1;
    int currentGenome = 1;
    int currentFrame = 0;
    int maxFitness = 0;
};



#endif // VAR_H_INCLUDED
