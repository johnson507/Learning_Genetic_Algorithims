#pragma once

#include "Utilities.h"
#include <time.h>

using namespace std;

//Chromosomes are containers for the data we're trying to find
class Chromosome
{

public:

	Chromosome();
	Chromosome(int fitness, string genes);
	~Chromosome();

	//Accessors
	int Get_Fitness() { return Fitness; };
	string Get_Genes() { return Genes; };

private:

	//variable
	int Fitness;
	string Genes;

};

class StringGuesser
{
public:
	StringGuesser();
	~StringGuesser();

	//Functions
	Chromosome Get_Best(string const goal, string const genes, int const optimalFitness);

	//Acessors
	int Get_Generation() const { return generation; };//only let the user access this but not change it

private:
	//Functions
	void Display(Chromosome* const guess);
	int Get_Fitness(string const guess);
	Chromosome Mutate(string const parent);
	Chromosome Generate_Parent(int const wordLength);
	void Init(string const goal, string const genes);

	//Variables
	clock_t startTime;
	Chromosome bestParent;
	string target;
	string geneSet;
	int bestFitness;
	int generation = 0;//how many generations have gone through
};


