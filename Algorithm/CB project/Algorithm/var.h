#ifndef VAR_H_INCLUDED
#define VAR_H_INCLUDE
#include <vector>

#define ARRAY_SIZE(array) (sizeof((array))/sizeof((array[0])))

#define SPACE <<"\n"

#define TAB "\t"<<

#define RANDOM (float)(rand())/(RAND_MAX)


int Inputs = 4;
int Outputs = 4;

float DeltaDisjoint = 2.0;
float DeltaWeights = 0.4;
float DeltaThreshold = 1.0;

float MutateConnectionsChance = 0.25;
float PerturbChance=0.9;
float CrossoverChance=0.75;
float LinkMutationChance=2.0;
float NodeMutationChance=0.5;
float BiasMutationChance=0.4;
float StepSize=0.1;
float DisableMutationChance=0.4;
float EnableMutationChance=0.2;

int MaxNodes=10000;

class gene  // This class is the gene that creates a genome
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
    public:
    neuron();
    std::vector<gene> IncomingVec; //No estic segur d'aixo.
    float value;
};

class genome
{
    public:
    genome();
    void generateNetwork(); //Send a genome to generate the NN
    int randomNeuron(bool nonInput); //
    bool existLink(gene link); //Search if the link exist
    void pointMutate(); // Mutate the weights
    void linkMutate(bool forceBias,int* innovation); //Mutate links between nodes
    void nodeMutate(int* innovation); //
    void enableDisableMutate(bool enable); //Enable or disable a genome
    void mutate(int* innovation); //Mutates a genome with all the options
    bool containsLink(gene Link);

    std::vector<gene> GenesVec;
    int fitness;
    int adjustedFitness;
    std::vector<neuron> Network;
    int maxneuron;
    int globalRank;
    float mutationRates[7];
};


class specie
{
    public:
    specie();
    void calculateAverageFitness();
    void breedChild();

    int topFitness;
    int staleness;
    std::vector<genome> GenomesVec;
    int averageFitness;

};

class Pool
{
    public:
    Pool();
    void rankGlobally();
    void totalAverageFitness();
    void cullSpecies(bool cutToOne);
    void removeStaleSpecies();
    void removeWeakSpecies();
    void addToSpecies(genome child);
    void newGeneration();
    void initializePool();
    void initializeRun();
    void evaluateCurrent();
    void nextGenome();
    int newInnovation();

    int Population;
    std::vector<specie> SpeciesVec;
    int generation;
    int innovation;
    int currentSpecies;
    int currentGenome;
    int currentFrame;
    int maxFitness;
};

Pool::Pool(){
SpeciesVec.clear();
generation=0;
innovation=Outputs;
currentFrame=0;
currentGenome=1;
currentSpecies=1;
maxFitness=0;
Population=100;
}

specie::specie(){
GenomesVec.clear();
topFitness=0;
staleness=0;
averageFitness=0;
}

genome::genome(){
GenesVec.clear();
Network.clear();
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

neuron::neuron(){
IncomingVec.clear();
value=0.0;
}

genome copyGenome(genome genomes);//Funcio que copia dos genomes;

genome basicGenome(int* innovation);//Creates a new genome;

gene copyGene(gene genes);

void evaluateNetwork(std::vector<neuron> network,float * Inputs,float * Outputs); //Calculate the output of a network

genome crossover(genome g1,genome g2);

float disjoint(std::vector<gene> genes1,std::vector<gene> genes2);

float weights(std::vector<gene> genes1,std::vector<gene> genes2);

bool sameSpecies(genome genome1,genome genome2);

bool fitnessAlreadyMeasured();

void writeFile();

void savePool();

void loadFile();

void loadPool();

void playTop();

void customWriteFile(Pool pool);

Pool customReadFile();

int findmax(std::vector<gene>);

//std::vector<neuron> generateNetwork(genome genomes);

//int randomNeuron(gene genes,bool nonInput);

//bool existLink(gene genes,gene link); //Problably move to the gene class

//void pointMutate(genome genomes); //Problably move to the genome class

//std::vector<gene> linkMutate(genome genomes, bool forceBias); //Problably mode to the genome class

//std::vector<gene> nodeMutate(genome genomes); //Problably mode to the genome class

//bool enableDisableMutate(genome genomes, bool enable); //Problably mode to the genome class

//genome mutate(genome genomes); //Problably move to the genome class

//void rankGlobally(Pool PoolRank);

//float calculateAverageFitness(specie species);

//float totalAverageFitness();

//std::vector<specie> cullSpecie(specie species,bool cutToOne);

//genome breedChild(std::vector<specie> species);

//std::vector<specie> removeStaleSpecies();

//std::vector<specie> removeWeakSpecies();

//void addToSpecies(genome child);

//void newGeneration();

//void initializePool();

//void evalutateCurrent();

//void nextGenome();

#endif // VAR_H_INCLUDED
