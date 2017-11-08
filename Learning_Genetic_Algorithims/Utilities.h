#pragma once

namespace Utilities
{

	namespace Random
	{
		
		//Sample
		/* 
		Returns a sample of elements from a larger population set, without replacement. Leaves the original population unchanged.

		@param population_Input, type T: the larger set to take the sample from.
		@param k_Length, type int: the size of the returned sample.
		@return: type T set of k_length samples from the given population_Input;
		*/
		template<T>
		T Sample(T* population_Input, int k_Length);
	}

}