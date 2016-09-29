#include <iostream>
#include <stdio.h>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <ctime>
#include <iostream>
#include <fstream>
//#include <random>
#include "var.h"


using namespace std;

string InputsNames[] = {"Servi1","Servi2","Servi3","Servi4"};
string OutputsNames[] = {"Servo1","Servo2","Servo3","Servo4"};

bool sameSpecies(genome genome1,genome genom2)
{
    float dd = DeltaDisjoint*disjoint(genome1.GenesVec,genom2.GenesVec);
    float dw = DeltaWeights*weights(genome1.GenesVec,genom2.GenesVec);

    return ((dd+dw) < DeltaDisjoint);
}

float disjoint(std::vector<gene> genes1,std::vector<gene> genes2)
{
    int length = max(findmax(genes1),findmax(genes2));
    bool i1[length]={};
    bool i2[length]={};

    //Find the max number of innovation

    //Create 2 arrays i1 and i2 initialized to 0(false)

    //Fill each array if the innovation index is in the genome

    for(unsigned int i=0;i<genes1.size();++i)
    {
        i1[genes1[i].innovation]=true;
    }

    for(unsigned int i=0;i<genes2.size();++i)
    {
        i2[genes2[i].innovation]=true;
    }

    float disjointGenes = 0;

    for(unsigned int i=0;i<genes1.size();++i)
    {
        if(!(i2[genes1[i].innovation]))
        {
            disjointGenes +=1;
        }
    }

    for(unsigned int i=0;i<genes2.size();++i)
    {
        if(!(i1[genes2[i].innovation]))
        {
            ++disjointGenes;
        }
    }

    float n = max(genes1.size(),genes2.size());
    //Searc#include <stdlib.h>h disjoints and count them

    return disjointGenes/n;
}

int findmax(std::vector<gene> gene)
{
    int maxi=0;

    for(unsigned int i=0;i<gene.size();++i)
        {
            if(gene[i].innovation>maxi)
            {
                maxi=gene[i].innovation;
            }
        }
    return maxi;
}

float weights(std::vector<gene> genes1,std::vector<gene> genes2)
{
    int length = max(findmax(genes1),findmax(genes2));
    bool i2[length]={};
    int i2l[length]={};

    for(unsigned int i=0;i<genes2.size();++i)
    {
        i2[genes2[i].innovation]=true;
        i2l[genes2[i].innovation]=i;
    }

    float sum=0;
    float coincident=0;

    for(unsigned int i=0;i<genes1.size();++i)
    {
        if(genes1[i].innovation<length)
        {
            if((i2[genes1[i].innovation]) == true)
            {
                sum += abs(genes1[i].weight-genes2[i2l[genes2[i].innovation]].weight);
                ++coincident;
            }
        }
    }

    return sum/coincident;
}

void Pool::addToSpecies(genome child)
{
    bool foundSpecie = false;
    for (unsigned int s=0;s<SpeciesVec.size();++s)
    {
        if (!(foundSpecie) && (sameSpecies(child, SpeciesVec[s].GenomesVec[0])))
        {
            SpeciesVec[s].GenomesVec.push_back(child);
            foundSpecie = true;
        }
    }
    if (!foundSpecie)
    {
        specie newspecie;
        newspecie.GenomesVec.push_back(child);
        SpeciesVec.push_back(newspecie);
    }
    specie specie = SpeciesVec[0];
}

void Pool::initializePool()
{
    for(int i=0;i<Population;++i)
    {
        genome basic = basicGenome(&innovation);
        addToSpecies(basic);
        //cout << SpeciesVec.size();
        //cout << i;
    }
}

genome basicGenome(int* innovation)
{
    genome genome;
    //innovation = 1;
    genome.maxneuron = Inputs;
    genome.mutate(innovation);

    return genome;
}

void genome::mutate(int* innovation)
{

    for (unsigned int i=0;i<ARRAY_SIZE(mutationRates);++i)
    {
        float r=(float)(rand())/(RAND_MAX);
        if(r<0.5)
        {
            mutationRates[i] *= 0.98;
        }else{
            mutationRates[i] *= 1.05263;
        }
    }

    if(RANDOM<mutationRates[0])
    {
        pointMutate();
    }

    for(float p=mutationRates[1];p>0;--p)
    {
        if(RANDOM<p)
        {
            linkMutate(false,innovation);
        }
    }

    for(float p=mutationRates[2];p>0;--p)
    {
        if(RANDOM<p)
        {
            linkMutate(true,innovation);
        }
    }

    for(float p=mutationRates[3];p>0;--p)
    {
        if(RANDOM<p)
        {
            nodeMutate(innovation);
        }
    }

    for(float p=mutationRates[4];p>0;--p)
    {
        if(RANDOM<p)
        {
            enableDisableMutate(true);
        }
    }

    for(float p=mutationRates[5];p>0;--p)
    {
        if(RANDOM<p)
        {
            enableDisableMutate(false);
        }
    }


}

void genome::pointMutate()
{
    for(unsigned int i=0;i<GenesVec.size();++i)
    {
        if(RANDOM<PerturbChance)
        {
           GenesVec[i].weight += RANDOM*mutationRates[6]*2-mutationRates[6];
        }else{
            GenesVec[i].weight += RANDOM*4-2;
        }
    }
}

void genome::linkMutate(bool forceBias,int* innovation)
{
    int neuron1 = randomNeuron(false);
    int neuron2 = randomNeuron(true);

    gene newLink;
    if((neuron1<=Inputs) && (neuron2<=Inputs))
    {
        return;
    }

    if (neuron2<=Inputs)
    {
        swap(neuron1,neuron2);
    }

    newLink.into = neuron1;
    newLink.out = neuron2;

    if (forceBias)
    {
        newLink.into = Inputs;
    }

    if(containsLink(newLink))
    {
        return;
    }

    ++*innovation;
    newLink.innovation = *innovation;
    newLink.weight = RANDOM*4-2;

    GenesVec.push_back(newLink);
}

int genome::randomNeuron(bool nonInput)
{
    bool neurons[MaxNodes+Outputs]={};

    if (!nonInput)
    {
        for(int i=0;i<Inputs;++i)
        {
            neurons[i]=true;
        }
    }

    for(int i=0;i<Outputs;++i)
    {
        neurons[MaxNodes+i]=true;
    }

    int sum=0;

    for(int i=0;i<(MaxNodes+Outputs);++i)
    {
        if(neurons[i])
        {
            ++sum;
        }
    }
    if(sum==0){
        return 0;
    }

    int neuronsl[sum] = {};

    int x=0;
    for(int i=0;i<(MaxNodes+Outputs);++i)
    {
        if(neurons[i])
        {
            neuronsl[x]=i;
            x++;
        }
    }
    int randnum = rand()%sum;

    return neuronsl[randnum];

}

int Pool::newInnovation()
{
    return ++innovation;
}

bool genome::containsLink(gene Link)
{
    for(unsigned int i=0;i<GenesVec.size();i++)
    {
        if((GenesVec[i].into == Link.into)&&(GenesVec[i].out==Link.out))
        {
            return true;
        }
    }
    return false;
}

void genome::nodeMutate(int* innovation)
{
    if(GenesVec.size()==0)
    {
        return;
    }
    ++maxneuron;

    int genernd = rand()%(GenesVec.size());

    if(!GenesVec[genernd].enabled)
    {
        return;
    }

    gene gene1 = copyGene(GenesVec[genernd]);
    gene1.out = maxneuron;
    gene1.weight = 1;
    ++*innovation;
    gene1.innovation = *innovation;
    gene1.enabled = true;
    GenesVec.push_back(gene1);

    gene gene2 = copyGene(GenesVec[genernd]);
    gene2.out = maxneuron;
    ++*innovation;
    gene2.innovation = *innovation;
    gene2.enabled = true;
    GenesVec.push_back(gene2);
}

gene copyGene(gene genes)
{
    gene genecopy;
    genecopy.into=genes.into;
    genecopy.out=genes.out;
    genecopy.weight=genes.weight;
    genecopy.enabled=genes.enabled;
    genecopy.innovation=genes.innovation;

    return genecopy;
}

void genome::enableDisableMutate(bool enable)
{
    std::vector<int> candidates;
    for(unsigned int i=0;i<GenesVec.size();++i)
    {
        if(GenesVec[i].enabled== !enable)
        {
            candidates.push_back(i);
        }

        if(candidates.size()==0)
        {
            return;
        }

        int genernd = rand()%(candidates.size());
        GenesVec[genernd].enabled = !GenesVec[genernd].enabled;
    }
}

void customWriteFile(Pool pool)
{
    ofstream file;
    file.open("Testcopy.txt");
    file << "Pool generation:" SPACE;
    file << pool.generation SPACE;
    file << pool.innovation SPACE;
    file << pool.currentSpecies SPACE;
    file << pool.currentGenome SPACE;
    file << pool.currentFrame SPACE;
    file << pool.maxFitness SPACE;

    file << "Number of species:" SPACE;
    file << pool.SpeciesVec.size() SPACE;
    for(unsigned int i=0;i<pool.SpeciesVec.size();++i)
    {
        file << TAB "Specie:" << i SPACE;
        file << TAB pool.SpeciesVec[i].averageFitness SPACE;
        file << TAB pool.SpeciesVec[i].topFitness SPACE;
        file << TAB pool.SpeciesVec[i].staleness SPACE;
        file << TAB "Number of genomes:" SPACE;
        file << TAB pool.SpeciesVec[i].GenomesVec.size() SPACE;
        for(unsigned int x=0;x<pool.SpeciesVec[i].GenomesVec.size();++x)
        {
            file << TAB TAB "Genome:" << x SPACE;
            file << TAB TAB pool.SpeciesVec[i].GenomesVec[x].fitness SPACE;
            file << TAB TAB pool.SpeciesVec[i].GenomesVec[x].maxneuron SPACE;
            file << TAB TAB pool.SpeciesVec[i].GenomesVec[x].globalRank SPACE;
            file << TAB TAB pool.SpeciesVec[i].GenomesVec[x].adjustedFitness SPACE;
            file << TAB TAB pool.SpeciesVec[i].GenomesVec[x].mutationRates[0] SPACE;
            file << TAB TAB pool.SpeciesVec[i].GenomesVec[x].mutationRates[1] SPACE;
            file << TAB TAB pool.SpeciesVec[i].GenomesVec[x].mutationRates[2] SPACE;
            file << TAB TAB pool.SpeciesVec[i].GenomesVec[x].mutationRates[3] SPACE;
            file << TAB TAB pool.SpeciesVec[i].GenomesVec[x].mutationRates[4] SPACE;
            file << TAB TAB pool.SpeciesVec[i].GenomesVec[x].mutationRates[5] SPACE;
            file << TAB TAB pool.SpeciesVec[i].GenomesVec[x].mutationRates[6] SPACE;
            file << TAB TAB "Number of genes:" SPACE;
            file << TAB TAB pool.SpeciesVec[i].GenomesVec[x].GenesVec.size() SPACE;
            for(unsigned int y=0;y<pool.SpeciesVec[i].GenomesVec[x].GenesVec.size();++y)
            {
                file << TAB TAB TAB "Gene:" << y SPACE;
                file << TAB TAB TAB pool.SpeciesVec[i].GenomesVec[x].GenesVec[y].enabled SPACE;
                file << TAB TAB TAB pool.SpeciesVec[i].GenomesVec[x].GenesVec[y].innovation SPACE;
                file << TAB TAB TAB pool.SpeciesVec[i].GenomesVec[x].GenesVec[y].into SPACE;
                file << TAB TAB TAB pool.SpeciesVec[i].GenomesVec[x].GenesVec[y].out SPACE;
                file << TAB TAB TAB pool.SpeciesVec[i].GenomesVec[x].GenesVec[y].weight SPACE;
            }
        }
    }
    file.close();
}

Pool customReadFile()
{
    Pool pool;
    std::string::size_type sz;
    ifstream file;
    string line;
    file.open("Test.txt");

    READ;

    READ;
    pool.generation = atoi( line.c_str() );

    READ;
    pool.innovation = atoi( line.c_str() );
    READ;
    pool.currentSpecies = atoi( line.c_str() );
    READ;
    pool.currentGenome = atoi( line.c_str() );
    READ;
    pool.currentFrame = atoi( line.c_str() );
    READ;
    pool.maxFitness = atoi( line.c_str() );

    READ;
    READ;
    int iter = atoi( line.c_str() );

    for(int i=0;i<iter;++i)
    {
        specie specieread;
        READ;

        READ;
        specieread.averageFitness = atoi( line.c_str() );
        READ;
        specieread.topFitness = atoi( line.c_str() );
        READ;
        specieread.staleness = atoi( line.c_str() );

        READ;
        READ;
        int iter2 = atoi( line.c_str() );

        pool.SpeciesVec.push_back(specieread);

        for(int x=0;x<iter2;++x)
        {
            genome genomeread;
            READ;
            READ;
            genomeread.fitness = atoi( line.c_str() );
            READ;
            genomeread.maxneuron = atoi( line.c_str() );
            READ;
            genomeread.globalRank = atoi( line.c_str() );
            READ;
            genomeread.adjustedFitness = atoi( line.c_str() );
            READ;
            genomeread.mutationRates[0] = atof( line.c_str() );
            READ;
            genomeread.mutationRates[1] = atof( line.c_str() );
            READ;
            genomeread.mutationRates[2] = atof( line.c_str() );
            READ;
            genomeread.mutationRates[3] = atof( line.c_str() );
            READ;
            genomeread.mutationRates[4] = atof( line.c_str() );
            READ;
            genomeread.mutationRates[5] = atof( line.c_str() );
            READ;
            genomeread.mutationRates[6] = atof( line.c_str() );

            READ;
            READ;
            int iter3 = atoi( line.c_str() );

            pool.SpeciesVec[i].GenomesVec.push_back(genomeread);

            for(int z=0;z<iter3;++z)
            {
                gene geneRead;
                READ;
                READ;
                geneRead.enabled = atoi( line.c_str() );
                READ;
                geneRead.innovation = atoi( line.c_str() );
                READ;
                geneRead.into = atoi( line.c_str() );
                READ;
                geneRead.out = atoi( line.c_str() );
                READ;
                geneRead.weight = atof( line.c_str() );
                pool.SpeciesVec[i].GenomesVec[x].GenesVec.push_back(geneRead);
            }
        }
    }

    file.close();

    return pool;

}

genome crossover(genome genome1,genome genome2)
{
    if(genome2.fitness>genome1.fitness)
    {
        swap(genome1,genome2);
    }

    genome child;

    int length = findmax(genome2.GenesVec);
    bool innovation2[length] = {};
    int innovation2l[length] = {};
    for(unsigned int i=0;i<genome2.GenesVec.size();++i)
    {
        innovation2[genome2.GenesVec[i].innovation]=true;
        innovation2l[genome2.GenesVec[i].innovation]=i;
    }

    for(unsigned int i=0;i<genome1.GenesVec.size();++i)
    {
        if ((innovation2[genome1.GenesVec[i].innovation]) && (RANDOM<=0.5) && (genome2.GenesVec[innovation2l[genome1.GenesVec[i].innovation]].enabled))
        {
            child.GenesVec.push_back(copyGene(genome2.GenesVec[innovation2l[genome1.GenesVec[i].innovation]]));
        }else{
            child.GenesVec.push_back(copyGene(genome1.GenesVec[i]));
        }
    }

    return child;
}

void Pool::cullSpecies(bool cutToOne)
{
    for(unsigned int i=0;i<SpeciesVec.size();++i)
    {
        std::vector<genome> Genomecopy;
        Genomecopy = SpeciesVec[i].GenomesVec;

        bool visited[Genomecopy.size()]={};
        int index=0;

        SpeciesVec[i].GenomesVec.clear();
        int maxFitness = 0;

        for(unsigned int z=0;z<Genomecopy.size();++z)
        {
            maxFitness = 0;
            index = 0;
            for(unsigned int x=0;x<Genomecopy.size();++x)
            {
                if(!visited[x])
                {
                    if(maxFitness<Genomecopy[x].fitness)
                    {
                        maxFitness=Genomecopy[x].fitness;
                        index = x;
                    }
                }
            }
            SpeciesVec[i].GenomesVec.push_back(Genomecopy[index]);
        }

        unsigned int remaining = floor(SpeciesVec[i].GenomesVec.size()/2);
        if(cutToOne)
        {
            remaining = 1;
        }
        while(SpeciesVec[i].GenomesVec.size()>remaining)
        {
            SpeciesVec[i].GenomesVec.pop_back();
        }
    }
}
genome copyGenome(genome g1)
{
    genome g2;

    for(unsigned int i=0;i<g1.GenesVec.size();++i)
    {
        g2.GenesVec.push_back(g1.GenesVec[i]);
    }

    g2.maxneuron=g1.maxneuron;
    for(unsigned int i=0;i<7;++i)
    {
        g2.mutationRates[i] = g1.mutationRates[i];
    }


    return g2;

}
void specie::breedChild(int* innovation)
{
    genome child;
    int genernd;
    if(RANDOM < CrossoverChance)
    {
        genernd = rand()%(GenomesVec.size());
        genome g1 = GenomesVec[genernd];
        genernd = rand()%(GenomesVec.size());
        genome g2 = GenomesVec[genernd];
        child = crossover(g1,g2);
    }else{
        genernd = rand()%(GenomesVec.size());
        genome g = GenomesVec[genernd];
        child = copyGenome(g);
    }
    child.mutate(innovation);
    GenomesVec.push_back(child);
}


void Pool::removeStaleSpecies()
{
    std::vector<specie> survived;
    for(unsigned int i=0;i<SpeciesVec.size();++i)
    {

        std::vector<genome> Genomecopy;
        Genomecopy = SpeciesVec[i].GenomesVec;

        bool visited[Genomecopy.size()]={};
        int index=0;

        SpeciesVec[i].GenomesVec.clear();
        int maxFitness = 0;

        for(unsigned int z=0;z<Genomecopy.size();++z)
        {
            maxFitness = 0;
            index = 0;
            for(unsigned int x=0;x<Genomecopy.size();++x)
            {
                if(!visited[x])
                {
                    if(maxFitness<Genomecopy[x].fitness)
                    {
                        maxFitness=Genomecopy[x].fitness;
                        index = x;
                    }
                }
            }
            SpeciesVec[i].GenomesVec.push_back(Genomecopy[index]);
        }

        if(SpeciesVec[i].GenomesVec[0].fitness > SpeciesVec[i].topFitness)
        {
            SpeciesVec[i].topFitness = SpeciesVec[i].GenomesVec[0].fitness;
            SpeciesVec[i].staleness = 0;
        }else{
            ++SpeciesVec[i].staleness;
        }

        if((SpeciesVec[i].staleness < StaleSpecies)||(SpeciesVec[i].topFitness >= maxFitness))
        {
            survived.push_back(SpeciesVec[i]);
        }
    }
    SpeciesVec.clear();

    SpeciesVec = survived;
}
int main()
{

    srand (time(NULL));
    Pool pool;
    //std::vector<int> myintVec;
    //int tam;

    //tam = myintVec.size();

    //myintVec.push_back(10);
    //pool.initializePool();

    //cout << pool.innovation <<endl;
    //cout << pool.SpeciesVec.size() <<endl;
    //pool.SpeciesVec[0].GenomesVec[0].mutate(&pool.innovation);
    //tam = myintVec.size();
    cout << "Hello world!" << endl;

    //customWriteFile(pool);
    pool = customReadFile();
    customWriteFile(pool);
    //cout << myintVec[0];
    //cout << r;


    return 0;
}
