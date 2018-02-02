#include "SortedNumbers_Guesser.h"
#include "SortedNumbers_Guesser.h"
#include <string>
#include "GenericGuesser.h"

template<typename T>
SortedNumbers_Guesser<T>::SortedNumbers_Guesser()
{
}

template<typename T>
SortedNumbers_Guesser<T>::~SortedNumbers_Guesser()
{
}

template<typename T>
Chromosome_SortedNumbers<T> SortedNumbers_Guesser<T>::Get_Best(T * const goal, T * const genes, const Fitness optimalFitness)
{
	if (!(optimalFitness > bestParent.Get_Fitness()))
		return bestParent;

	while (true)
	{
		Chromosome_SortedNumbers<T> child = Mutate(bestParent.Get_Genes());

		if (!(child.Get_Fitness() > bestParent.Get_Fitness()))
			continue;

		Display(&child);

		if (!(optimalFitness > child.Get_Fitness()))
			return child;

		bestParent = child;
	}
}

template<typename T>
void SortedNumbers_Guesser<T>::Display(Chromosome_SortedNumbers<T>* const guess)
{
	clock_t currentTime = clock() - startTime;
	float deltaTime = (float)currentTime / CLOCKS_PER_SEC;

	string result = "[ ";

	for (auto it = guess->Get_Genes()->begin(); it != guess->Get_Genes()->end(); ++it)
		result += to_string(*it) + ", ";

	result += "]";

	printf("%s Seconds: %f Fitness: %i  Generation: %i \n", result.c_str(), deltaTime, guess->Get_Fitness(), generation);
}

template<typename T>
//Returns a count of the adjacent numbers in ascending order
int SortedNumbers_Guesser<T>::Get_Fitness(T * const guess)
{
	int fitness = 1;//start as once since the inital position dosent have a gene to the left ie correct by default

	for (size_t i = 1; i < guess->size(); i++)
	{
		if (guess->at(i) > guess->at(i - 1))
			++fitness;
	}

	return fitness;
}

template<typename T>
Chromosome_SortedNumbers<T> SortedNumbers_Guesser<T>::Mutate(T * const parent)
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

	return Chromosome_SortedNumbers<T>(fitness, genes);//the child genes are now mutated from the original parent	
}



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

bool Fitness::operator>(const Fitness * fitnessB)
{
	if (_numbersInSequenceCount != fitnessB->Get_CountOfNumbers())
		return  (_numbersInSequenceCount > fitnessB->Get_CountOfNumbers());
	else
		return _totalGap < fitnessB->Get_TotalGap();//this is a greater fitness because it brings us closer to the answer
}

string Fitness::To_String()
{
	return "Sequential: " + to_string(_numbersInSequenceCount) + " Total Gap: " + to_string(_totalGap);
}
#pragma endregion


template<typename T>
Chromosome_SortedNumbers<T>::Chromosome_SortedNumbers()
{
}

template<typename T>
Chromosome_SortedNumbers<T>::Chromosome_SortedNumbers(Fitness fitness, T * genes)
{
	this->_fitness = fitness;
	this->_genes = *genes;
}

template<typename T>
Chromosome_SortedNumbers<T>::~Chromosome_SortedNumbers()
{
}

template class SortedNumbers_Guesser<vector<int>>;
template class Chromosome<vector<int>>;
template class Chromosome_SortedNumbers<vector<int>>;