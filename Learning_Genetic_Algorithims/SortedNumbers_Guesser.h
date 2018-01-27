#pragma once
#include "GenericGuesser.h"

using namespace std;

template<typename T>
class SortedNumbers_Guesser : public GenericGuesser<T>
{
public:
	SortedNumbers_Guesser();
	~SortedNumbers_Guesser();

private:
	//Functions
	virtual void Display(Chromosome<T>* const guess);
	virtual int Get_Fitness(T* const genes) override;
	//virtual Chromosome<T> Mutate(T* const parent);
	//virtual Chromosome<T> Generate_Parent(int const wordLength);
	//void Init(T* const goal, T* const genes);
};

class Fitness
{
public:
	Fitness(int numbersInSequenceCount, int totalGap);
	~Fitness();

	bool operator>(const Fitness* fitnessB);

	int Get_CountOfNumbers() const
	{
		return _numbersInSequenceCount;
	};
	int Get_TotalGap() const
	{
		return _totalGap;
	};

	string To_String();

private:
	int _totalGap;
	int _numbersInSequenceCount;
};