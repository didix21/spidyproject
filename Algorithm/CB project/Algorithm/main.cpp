#include <iostream>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <ctime>
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

    for(unsigned int i=0;i<genes1.size();i++)
    {
        i1[genes1[i].innovation]=true;
    }

    for(unsigned int i=0;i<genes2.size();i++)
    {
        i2[genes2[i].innovation]=true;
    }

    float disjointGenes = 0;

    for(unsigned int i=0;i<genes1.size();i++)
    {
        if(!(i2[genes1[i].innovation]))
        {
            disjointGenes +=1;
        }
    }

    for(unsigned int i=0;i<genes2.size();i++)
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

    for(unsigned int i=0;i<gene.size();i++)
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

    for(unsigned int i=0;i<genes2.size();i++)
    {
        i2[genes2[i].innovation]=true;
        i2l[genes2[i].innovation]=i;
    }

    float sum=0;
    float coincident=0;

    for(unsigned int i=0;i<genes1.size();i++)
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
    for (unsigned int s=0;s<SpeciesVec.size();s++)
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
        genome basic = basicGenome();
        addToSpecies(basic);
        //cout << SpeciesVec.size();
        //cout << i;
    }
}

genome basicGenome()
{
    genome genome;
    //innovation = 1;
    genome.maxneuron = Inputs;
    mutate(genome);

    return genome;
}

void genome::mutate()
{

    for (unsigned int i=0;i<ARRAY_SIZE(mutationRates);i++)
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

    for(float p=mutationRates[1];p>0;p--)
    {
        if(RANDOM<p)
        {
            linkMutate(false);
        }
    }

    for(float p=mutationRates[2];p>0;p--)
    {
        if(RANDOM<p)
        {
            linkMutate(true);
        }
    }

    for(float p=mutationRates[3];p>0;p--)
    {
        if(RANDOM<p)
        {
            nodeMutate();
        }
    }

    for(float p=mutationRates[4];p>0;p--)
    {
        if(RANDOM<p)
        {
            enableDisableMutate(true);
        }
    }

    for(float p=mutationRates[5];p>0;p--)
    {
        if(RANDOM<p)
        {
            enableDisableMutate(false);
        }
    }


}

void genome::pointMutate()
{
    for(unsigned int i=0;i<GenesVec.size();i++)
    {
        if(RANDOM<PerturbChance)
        {
           GenesVec[i].weight += RANDOM*mutationRates[6]*2-mutationRates[6];
        }else{
            GenesVec[i].weight += RANDOM*4-2;
        }
    }
}

void genome::linkMutate(bool forceBias)
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
    newLink.innovation = newInnovation();
    newLink.weight = RANDOM*4-2;
}

int genome::randomNeuron(bool nonInput)
{

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

void genome::nodeMutate(){}

void genome::enableDisableMutate(bool enable){};

int main()
{

    srand (time(NULL));
    Pool pool;
    std::vector<int> myintVec;
    //int tam;

    //tam = myintVec.size();

    myintVec.push_back(10);
    pool.initializePool();

    pool.SpeciesVec[0].GenomesVec[0].mutate();
    //tam = myintVec.size();
    cout << "Hello world!" << endl;
    //cout << myintVec[0];
    //cout << r;


    return 0;
}
