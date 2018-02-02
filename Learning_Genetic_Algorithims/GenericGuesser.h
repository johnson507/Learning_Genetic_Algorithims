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
	virtual int Get_Fitness() { return Fitness; };
	T* Get_Genes() { return &Genes; };

private:

	//variable
	int Fitness;
	T Genes;

};

/*Generic Guesser
This is a base class that has general functionality for STL Containers. Specific behavior must be implement via child classes.
*/
template<typename T>
class GenericGuesser
{
public:
	GenericGuesser();
	~GenericGuesser();

	//Functions
	Chromosome<T> Get_Best(T* const goal, T* const genes, int const optimalFitness);

	//Acessors
	int Get_Generation() const { return generation; };//only let the user access this but not change it

protected:
	//Functions
	virtual void Display(Chromosome<T>* const guess);
	virtual int Get_Fitness(T* const guess);
	virtual Chromosome<T> Mutate(T* const parent);
	virtual Chromosome<T> Generate_Parent(int const wordLength);
	void Init(T* const goal, T* const genes);

	//Variables
	clock_t startTime;
	Chromosome<T> bestParent;
	T* target;
	T* geneSet;
	int bestFitness;
	int generation = 0;//how many generations have gone through
};


