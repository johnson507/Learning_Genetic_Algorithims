#include "GenericGuesser.h"
#include <cmath>
#include <random>
#include <ctime>
#include <string>


#pragma region  Fitness_Region

Fitness::Fitness()
{
}

Fitness::Fitness(int numbersInSequenceCount, int totalGap)
{
	_numbersInSequenceCount = numbersInSequenceCount;
	_totalGap = totalGap;
}

Fitness::~Fitness()
{
}

//To avoid the other equilency operators, various logical tricks are used
bool Fitness::operator>(const Fitness * fitnessB)
{
	if (this->_numbersInSequenceCount != fitnessB->Get_CountOfNumbers())
		return  (this->_numbersInSequenceCount > fitnessB->Get_CountOfNumbers());
	else
		return this->_totalGap < fitnessB->Get_TotalGap();//this is a greater fitness because it brings us closer to the answer
}

string Fitness::To_String()
{
	return "Sequential: " + to_string(_numbersInSequenceCount) + " Total Gap: " + to_string(_totalGap);
}
#pragma endregion

template<typename T>
Chromosome<T>::Chromosome() {}

template<typename T>
Chromosome<T>::Chromosome(Fitness const fitness, T* const genes)
{
	_fitness = fitness;
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
Chromosome<T> GenericGuesser<T>::Get_Best(T * const goal, T * const genes, const Fitness* optimalFitness)
{
	Init(goal, genes);

	auto derefOptimalFitness = *optimalFitness;

	if (!(derefOptimalFitness > &bestParent.Get_Fitness()))
		return bestParent;

	while (true)
	{
		Chromosome<T> child = Mutate(bestParent.Get_Genes());
		++generation;

		if (bestParent.Get_Fitness() > &child.Get_Fitness())//discard smaller children
			continue;
		if (!(child.Get_Fitness() > &bestParent.Get_Fitness()))//if the child is equal, use it
		{
			bestParent = child;
			continue;
		}

		Display(&child);

		if (!(derefOptimalFitness > &child.Get_Fitness()))
			return child;

		bestParent = child;
	}
}



template<typename T>
void GenericGuesser<T>::Display(Chromosome<T>* const guess)
{
	clock_t currentTime = clock() - startTime;
	float deltaTime = (float)currentTime / CLOCKS_PER_SEC;

	string result = "[ ";

	for (auto it = guess->Get_Genes()->begin(); it != guess->Get_Genes()->end(); ++it)
		result += to_string(*it) + ", ";

	result += "]";

	printf("%s Seconds: %f Fitness: %s  Generation: %i \n", result.c_str(), deltaTime, guess->Get_Fitness().To_String().c_str(), generation);
}

template<typename T>
//Returns a count of the adjacent numbers in ascending order
Fitness GenericGuesser<T>::Get_Fitness(T * const guess)
{
	int fitness = 1;//start as once since the inital position dosent have a gene to the left ie correct by default
	int gap = 0;

	for (size_t i = 1; i < guess->size(); i++)
	{
		if (guess->at(i) > guess->at(i - 1))
			++fitness;
		else
			gap += guess->at(i - 1) - guess->at(i);
	}

	return Fitness(fitness, gap);
}

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
	Fitness fitness = Get_Fitness(genes);

	return Chromosome<T>(fitness, genes);//the child genes are now mutated from the original parent
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

	Fitness fitness = Get_Fitness(&genes);

	return Chromosome<T>(fitness, &genes);
}

template class GenericGuesser<string>;
template class Chromosome<string>;

template class GenericGuesser<vector<int>>;
template class Chromosome<vector<int>>;