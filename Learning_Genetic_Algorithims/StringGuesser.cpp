#include "StringGuesser.h"


template <typename T>
StringGuesser<T>::StringGuesser()
{
}

template <typename T>
StringGuesser<T>::~StringGuesser()
{
}

template<typename T>
void StringGuesser<T>::Display(Chromosome<T>* const guess)
{
	clock_t currentTime = clock() - startTime;
	float deltaTime = (float)currentTime / CLOCKS_PER_SEC;

	printf("%s Seconds: %f Fitness: %i  Generation: %i \n", guess->Get_Genes()->c_str(), deltaTime, guess->Get_Fitness(), generation);
}

template class StringGuesser<string>;
template class Chromosome<string>;
