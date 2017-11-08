#include "Utilities.h"
#include <random>

namespace Utilities
{
	namespace Random
	{
		template<T>
		T Sample(T* population_Input, int k_Length)
		{
			/*
			1. Loop K times
			2. Randomly choose an element from population
			3. If new element is not in sample, add it and ++K
			4. Else choose another random element.
			5. Return the sample set.
			*/

			int K = 0;
			T sampleSet;


			//while sample.size() < K
			//if new element is not in sample, then append and ++K
			//else do again
		}
	}
}