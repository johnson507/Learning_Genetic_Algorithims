#include "StringGuesser.h"
#include <cmath>
#include <random>
#include <ctime>


Chromosome::Chromosome(){}

Chromosome::Chromosome(int const fitness, string const genes)
{
	Fitness = fitness;
	Genes = genes;
}

Chromosome::~Chromosome(){}

StringGuesser::StringGuesser(){}

StringGuesser::~StringGuesser(){}



void StringGuesser::Init(string const goal, string const genes)
{
	startTime = clock();
	generation = 0;
	target = goal;
	geneSet = genes;
	bestParent = Generate_Parent(target.length());
	bestFitness = bestParent.Get_Fitness();

	Display(&bestParent);//show the inital starting gene
}

/*
Given a set of genes, the algorithim will return an optimal solution.

@param: "Goal", the target to find
@param: "Genes", the data that can be used to find the target
@param: "optimalFitness", the value the algorithim will stop at 
@return: the chromosome of the child
*/
Chromosome StringGuesser::Get_Best(string const goal, string const genes, int const optimalFitness)
{
	Init(goal, genes);

	Chromosome child(0,"");

	while (true)//loop until the solution is found
	{
		generation++;
		child = Mutate(bestParent.Get_Genes());

		if (bestFitness >= child.Get_Fitness())//kill this generation if its no better
			continue;

		Display(&child);

		if (child.Get_Fitness() >= optimalFitness)//end when found solution
			break;

		bestFitness = child.Get_Fitness();
		bestParent = child;//now the best child becomes a parent
	}

	return child;//the target solution
}

void StringGuesser::Display(Chromosome* const guess)
{
	clock_t currentTime = clock() - startTime;
	float deltaTime = (float)currentTime / CLOCKS_PER_SEC;

	printf("%s Seconds: %f Fitness: %i  Generation: %i \n", guess->Get_Genes().c_str(), deltaTime, guess->Get_Fitness(), generation);
}

//MUTATE
/*
Creates a new randomly mutated child string from the given parent. The parent is not changed.

@param: "parentGenes", the input original string.
@return: the mutated child from the parent.
*/
Chromosome StringGuesser::Mutate(string const parentGenes)
{
	random_device seed;
	mt19937 rndGenerator(seed());
	uniform_int_distribution<int> distRange(0, parentGenes.length());//prepare the random distribution from the parent string's indices

	int index = distRange(rndGenerator);//choose a random index 
	string childGenes = parentGenes;//copy the child from the parent so we don't change the parent
	string chosenGenes = Utilities::Random::Sample(&geneSet, 2);//create a string from two random sampled chars

	char alternate = chosenGenes[0];
	char newGene = chosenGenes[1];//choose these two chars but create an alternative in case the char chosen was the same as before

	childGenes[index] = (newGene == childGenes[index]) ? alternate : newGene;//replace the corresponding index with the randomly chosen char

	string genes = childGenes;
	int fitness = Get_Fitness(genes);

	return Chromosome(fitness, genes);//the child genes are now mutated from the original parent
}

/*
Loops through the guess and the actual value and compare each value, adding the sum of each correct guess

@param: "guess", the input we are getting the fitness for, in comparison to the target variable
@return: the fitness of the input
*/
int StringGuesser::Get_Fitness(string const guess)
{
	int fitness_Sum = 0;

	for (int i = 0; i < guess.length(); ++i)
	{
		if (guess[i] == target[i])
			fitness_Sum++;
	}

	return fitness_Sum;
}

/*
Creates the first generation to the required size.

@params: the length the parent should be 
@return: the chromosome of the parent
*/
Chromosome StringGuesser::Generate_Parent(int const wordLength)
{
	string genes = "";

	while (genes.size() < wordLength)
	{
		int sampleSize = fmin(wordLength - genes.size(), geneSet.size());
		genes.append(Utilities::Random::Sample(&geneSet, sampleSize));
	}

	int fitness = Get_Fitness(genes);

	return Chromosome (fitness, genes);
}
