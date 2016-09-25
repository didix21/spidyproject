#ifndef VAR_H_INCLUDED
#define VAR_H_INCLUDE
#include <vector>

int Inputs = 4;
int Outputs = 4;

float MutateConnectionsChance = 0.25;
float PerturbChance=0.9;
float CrossoverChance=0.75;
float LinkMutationChance=2.0;
float NodeMutationChance=0.5;
float BiasMutationChance=0.4;
float StepSize=0.1;
float DisableMutationChance=0.4;
float EnableMutationChance=0.2;

class gene
{
    public:
    gene();
    int into;
    int out;
    float weight;
    bool enabled;
    int innovation;
};

class neuron
{
    std::vector<gene> IncomingVec;
    float value;
};

class genome
{
    public:
    genome();
    std::vector<gene> GenesVec;
    int fitness;
    int adjustedFitness;
    std::vector<neuron> Network;
    int maxneuron;
    int globalRank;
    float mutationRates[7];
};


class species
{
    public:
    species();
    int topFitness;
    int staleness;
    std::vector<genome> GenomesVec;
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
averageFitness=0;
}

genome::genome(){
fitness=0;
adjustedFitness=0;
maxneuron=0;
globalRank=0;
mutationRates[0]=MutateConnectionsChance;
mutationRates[1]=LinkMutationChance;
mutationRates[2]=BiasMutationChance;
mutationRates[3]=NodeMutationChance;
mutationRates[4]=EnableMutationChance;
mutationRates[5]=DisableMutationChance;
mutationRates[6]=StepSize;
}

gene::gene(){
into=0;
out=0;
weight=0.0;
enabled=true;
innovation=0;
}

genome copyGenome(genome);//Funcio que copia dos genomes;
genome basicGenome();//Creates a new genome;

gene copyGene(gene);

std::vector<neuron> generateNetwork(genome);

#endif // VAR_H_INCLUDED
