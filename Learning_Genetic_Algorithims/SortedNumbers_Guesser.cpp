#include "SortedNumbers_Guesser.h"
#include "SortedNumbers_Guesser.h"
#include <string>

template<typename T>
SortedNumbers_Guesser<T>::SortedNumbers_Guesser()
{
}

template<typename T>
SortedNumbers_Guesser<T>::~SortedNumbers_Guesser()
{
}

template<typename T>
void SortedNumbers_Guesser<T>::Display(Chromosome<T>* const guess)
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

template class SortedNumbers_Guesser<vector<int>>;
template class Chromosome<vector<int>>;

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
	if(_numbersInSequenceCount != fitnessB->Get_CountOfNumbers())
	return false;

	if (_numbersInSequenceCount > fitnessB->Get_CountOfNumbers())
		return _totalGap > fitnessB->Get_TotalGap();
}

string Fitness::To_String()
{
	return "Sequential: " + to_string(_numbersInSequenceCount) + " Total Gap: " + to_string(_totalGap);
}


