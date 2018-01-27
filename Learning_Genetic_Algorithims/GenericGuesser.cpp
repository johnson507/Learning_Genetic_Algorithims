#include "GenericGuesser.h"
#include <cmath>
#include <random>
#include <ctime>
#include <string>

template<typename T>
Chromosome<T>::Chromosome() {}

template<typename T>
Chromosome<T>::Chromosome(int const fitness, T* const genes)
{
	Fitness = fitness;
	Genes = *genes;
}

template<typename T>
Chromosome<T>::~Chromosome() {}

template<typename T>
GenericGuesser<T>::GenericGuesser() {}

template<typename T>
GenericGuesser<T>::~GenericGuesser() {}


template<typename T>
void GenericGuesser<T>::Init(T* const goal, T* const genes)
{
	startTime = clock();
	generation = 0;
	target = goal;
	geneSet = genes;
	bestParent = Generate_Parent(target->size());
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
template<typename T>
Chromosome<T> GenericGuesser<T>::Get_Best(T* const goal, T* const genes, int const optimalFitness)
{
	Init(goal, genes);

	Chromosome<T> child;

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

template<typename T>
void GenericGuesser<T>::Display(Chromosome<T>* const guess){}

//MUTATE
/*
Creates a new randomly mutated child  from the given parent. The parent is not changed.

@param: "parentGenes", the original input.
@return: the mutated child from the parent.
*/
template<typename T>
Chromosome<T> GenericGuesser<T>::Mutate(T* const parentGenes)
{
	random_device seed;
	mt19937 rndGenerator(seed());
	uniform_int_distribution<int> distRange(0, parentGenes->size() - 1);//prepare the random distribution from the parent's indices

	int index = distRange(rndGenerator);//choose a random index 
	T childGenes = *parentGenes;//copy the child from the parent so we don't change the parent
	T chosenGenes = Utilities::Random::Sample(geneSet, 2);//create a new geneset from two random sampled genes

	auto alternate = chosenGenes[0];
	auto newGene = chosenGenes[1];//choose these two chars but create an alternative in case the char chosen was the same as before

	childGenes[index] = (newGene == childGenes[index]) ? alternate : newGene;//replace the corresponding index with the randomly chosen char

	T* genes = &childGenes;
	int fitness = Get_Fitness(genes);

	return Chromosome<T>(fitness, genes);//the child genes are now mutated from the original parent
}

/*
Loops through the guess and the actual value and compare each value, adding the sum of each correct guess

@param: "guess", the input we are getting the fitness for, in comparison to the target variable
@return: the fitness of the input
*/
template<typename T>
int GenericGuesser<T>::Get_Fitness(T* const guess)
{
	int fitness_Sum = 0;

	for (int i = 0; i < guess->size(); ++i)
	{
		if (guess->at(i) == target->at(i))
			fitness_Sum++;
	}

	return fitness_Sum;
}

/*
Creates the first generation to the required size.

@params: the length the parent should be
@return: the chromosome of the parent
*/
template<typename T>
Chromosome<T> GenericGuesser<T>::Generate_Parent(int const wordLength)
{
	T genes;

	while (genes.size() < wordLength)
	{
		int sampleSize = fmin(wordLength - genes.size(), geneSet->size());

		T newGenes = Utilities::Random::Sample(geneSet, sampleSize);
		genes.insert(genes.end(), newGenes.begin(), newGenes.end());
	}

	int fitness = Get_Fitness(&genes);

	return Chromosome<T>(fitness, &genes);
}

template class GenericGuesser<string>;
template class Chromosome<string>;

template class GenericGuesser<vector<int>>;
template class Chromosome<vector<int>>;