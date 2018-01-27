#pragma once
#include "GenericGuesser.h"

template<typename T>
class IntVectorGuesser :
	public GenericGuesser<T>
{
public:
	IntVectorGuesser();
	~IntVectorGuesser();

private:
	virtual void Display(Chromosome<T>* const guess) override;
};

