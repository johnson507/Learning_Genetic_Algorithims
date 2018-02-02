#pragma once
#include "GenericGuesser.h"

using namespace std;

template<typename T>
class Chromosome_SortedNumbers;
class Fitness;

template<typename T>
class SortedNumbers_Guesser : public GenericGuesser<T>
{
public:
	SortedNumbers_Guesser();
	~SortedNumbers_Guesser();

	//Functions
	virtual Chromosome_SortedNumbers<T> Get_Best(T* const goal, T* const genes, Fitness const optimalFitness);

private:
	//Functions
	virtual void Display(Chromosome_SortedNumbers<T>* const guess);
	virtual int Get_Fitness(T* const genes) override;
	virtual Chromosome_SortedNumbers<T> Mutate(T* const parent);
	//virtual Chromosome<T> Generate_Parent(int const wordLength);
	//void Init(T* const goal, T* const genes);

	//Varibles
	Chromosome_SortedNumbers<T> bestParent;
};

class Fitness
{
public:
	Fitness();
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

template<typename T>
class Chromosome_SortedNumbers 
{
public:
	Chromosome_SortedNumbers();
	Chromosome_SortedNumbers(Fitness fitness, T* genes);
	~Chromosome_SortedNumbers();

	//Accessors
	Fitness Get_Fitness() { return _fitness; };
	T* Get_Genes() { return &_genes; };

private:

	//variable
	Fitness _fitness;
	T _genes;
};