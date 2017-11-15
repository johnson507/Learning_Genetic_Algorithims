#include "StringGuesser.h"
#include <cmath>
#include <random>
#include <ctime>


StringGuesser::StringGuesser()
{
	
}


StringGuesser::~StringGuesser()
{
}

void StringGuesser::Init(string goal)
{
	startTime = clock();
	generation = 0;
	target = goal;
	bestParent = Generate_Parent(target.length());
	bestFitness = Get_Fitness(bestParent);

	Display(bestParent);//show the inital starting gene
}

string StringGuesser::Guess(string goal)
{
	Init(goal);

	string child;

	while (true)
	{
		generation++;
		child = Mutate(bestParent);
		int childFitness = Get_Fitness(child);

		if (bestFitness >= childFitness)
			continue;

		Display(child);

		if (childFitness >= bestParent.length())
			break;

		bestFitness = childFitness;
		bestParent = child;
	}

	return child;
}

void StringGuesser::Display(const string guess)
{
	clock_t currentTime = clock() - startTime;
	float deltaTime = (float)currentTime / CLOCKS_PER_SEC;
	int currentFitness = Get_Fitness(guess);

	printf("%s Seconds: %f Fitness: %i  Generation: %i \n", guess.c_str(), deltaTime, currentFitness, generation);
}

//MUTATE
/*
Creates a new randomly mutated child string from the given parent. The parent is not changed.

@param: parent, the input original string.
@return: the mutated child from the parent.
*/
string StringGuesser::Mutate(const string parent)
{
	random_device seed;
	mt19937 rndGenerator(seed());
	uniform_int_distribution<int> distRange(0, parent.length());//prepare the random distribution from the parent string's indices

	int index = distRange(rndGenerator);//choose a random index 
	string childGenes = parent;//copy the child from the parent so we don't change the parent
	string chosenGenes = Utilities::Random::Sample(&geneSet, 2);//create a string from two random sampled chars

	char alternate = chosenGenes[0];
	char newGene = chosenGenes[1];//choose these two chars but create an alternative in case the char chosen was the same as before

	childGenes[index] = (newGene == childGenes[index]) ? alternate : newGene;//replace the corresponding index with the randomly chosen char

	return childGenes;//the child genes are now mutated from the original parent
}

int StringGuesser::Get_Fitness(const string guess)
{
	//need to loop through the guess and the actual value and compare each value, adding the sum of each correct guess
	int fitness_Sum = 0;

	for (int i = 0; i < guess.length(); ++i)
	{
		if (guess[i] == target[i])
			fitness_Sum++;
	}

	return fitness_Sum;
}

string StringGuesser::Generate_Parent(int wordLength)
{
	string genes = "";

	while (genes.size() < wordLength)
	{
		int sampleSize = fmin(wordLength - genes.size(), geneSet.size());
		genes.append(Utilities::Random::Sample(&geneSet, sampleSize));
	}

	return genes;
}
