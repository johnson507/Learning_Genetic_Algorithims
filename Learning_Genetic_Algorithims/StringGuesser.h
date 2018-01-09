#pragma once

#include "Utilities.h"
#include <time.h>

using namespace std;

//Chromosomes are containers for the data we're trying to find
template <typename T>
class Chromosome
{

public:

	Chromosome();
	Chromosome(int fitness, T* genes);
	~Chromosome();

	//Accessors
	int Get_Fitness() { return Fitness; };
	T* Get_Genes() { return &Genes; };

private:

	//variable
	int Fitness;
	T Genes;

};

template<typename T>
class StringGuesser
{
public:
	StringGuesser();
	~StringGuesser();

	//Functions
	Chromosome<T> Get_Best(T* const goal, T* const genes, int const optimalFitness);

	//Acessors
	int Get_Generation() const { return generation; };//only let the user access this but not change it

private:
	//Functions
	void Display(Chromosome<T>* const guess);
	int Get_Fitness(T* const guess);
	Chromosome<T> Mutate(T* const parent);
	Chromosome<T> Generate_Parent(int const wordLength);
	void Init(T* const goal, T* const genes);

	//Variables
	clock_t startTime;
	Chromosome<T> bestParent;
	T* target;
	T* geneSet;
	int bestFitness;
	int generation = 0;//how many generations have gone through
};


