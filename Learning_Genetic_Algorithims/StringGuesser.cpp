#include "StringGuesser.h"
#include <cmath>
#include <random>
#include <ctime>

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
StringGuesser<T>::StringGuesser() {}

template<typename T>
StringGuesser<T>::~StringGuesser() {}


template<typename T>
void StringGuesser<T>::Init(T* const goal, T* const genes)
{
	startTime = clock();
	generation = 0;
	target = goal;
	geneSet = genes;
	bestParent = Generate_Parent(target->length());
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
Chromosome<T> StringGuesser<T>::Get_Best(T* const goal, T* const genes, int const optimalFitness)
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
void StringGuesser<T>::Display(Chromosome<T>* const guess)
{
	clock_t currentTime = clock() - startTime;
	float deltaTime = (float)currentTime / CLOCKS_PER_SEC;

	printf("%s Seconds: %f Fitness: %i  Generation: %i \n", guess->Get_Genes()->c_str(), deltaTime, guess->Get_Fitness(), generation);
}

//MUTATE
/*
Creates a new randomly mutated child string from the given parent. The parent is not changed.

@param: "parentGenes", the input original string.
@return: the mutated child from the parent.
*/
template<typename T>
Chromosome<T> StringGuesser<T>::Mutate(T* const parentGenes)
{
	random_device seed;
	mt19937 rndGenerator(seed());
	uniform_int_distribution<int> distRange(0, parentGenes->length());//prepare the random distribution from the parent string's indices

	int index = distRange(rndGenerator);//choose a random index 
	T childGenes = *parentGenes;//copy the child from the parent so we don't change the parent
	T chosenGenes = Utilities::Random::Sample(geneSet, 2);//create a string from two random sampled chars

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
int StringGuesser<T>::Get_Fitness(T* const guess)
{
	int fitness_Sum = 0;

	for (int i = 0; i < guess->length(); ++i)
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
Chromosome<T> StringGuesser<T>::Generate_Parent(int const wordLength)
{
	T genes;

	while (genes.size() < wordLength)
	{
		int sampleSize = fmin(wordLength - genes.size(), geneSet->size());
		genes.append(Utilities::Random::Sample(geneSet, sampleSize));
	}

	int fitness = Get_Fitness(&genes);

	return Chromosome<T>(fitness, &genes);
}

template class StringGuesser<string>;
template class Chromosome<string>;