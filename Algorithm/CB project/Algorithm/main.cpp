#include <iostream>
#include <string>
#include "var.h"


using namespace std;

string InputsNames[] = {"Servi1","Servi2","Servi3","Servi4"};
string OutputsNames[] = {"Servo1","Servo2","Servo3","Servo4"};

void Pool::addToSpecies(genome child){

}

void Pool::initializePool()
{
    for(int i=0;i<Population;++i)
    {
        genome basic = basicGenome();
        Pool::addToSpecies(basic);
        //cout << i;
    }
}

genome basicGenome()
{
    genome genome;
    //innovation = 1;
    genome.maxneuron = Inputs;
    return genome;
}

int main()
{
    Pool pool;

    pool.initializePool();

    //cout << "Hello world!" << endl;
    //cout << pool.currentFrame;


    return 0;
}
