#include "IntVectorGuesser.h"
#include <string>

template<typename T>
IntVectorGuesser<T>::IntVectorGuesser()
{
}

template<typename T>
IntVectorGuesser<T>::~IntVectorGuesser()
{
}

template<typename T>
void IntVectorGuesser<T>::Display(Chromosome<T>* const guess)
{
	clock_t currentTime = clock() - startTime;
	float deltaTime = (float)currentTime / CLOCKS_PER_SEC;

	string result;
	
	for (auto it = guess->Get_Genes()->begin() + (guess->Get_Genes()->size() * 0.85f); it != guess->Get_Genes()->end(); ++it)
		result += to_string(*it);

	printf("%s Seconds: %f Fitness: %i  Generation: %i \n", result.c_str(), deltaTime, guess->Get_Fitness(), generation);
}


template class IntVectorGuesser<vector<int>>;
template class Chromosome<vector<int>>;