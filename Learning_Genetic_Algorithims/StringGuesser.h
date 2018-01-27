#pragma once
#include "GenericGuesser.h"

using namespace std;

template <typename T>
class StringGuesser : public GenericGuesser<T>
{
public:
	StringGuesser();
	~StringGuesser();

private:
	virtual void Display(Chromosome<T>* const guess) override;
};

