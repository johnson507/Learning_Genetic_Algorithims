#pragma once

#include "Utilities.h"
#include <time.h>

using namespace std;

class StringGuesser
{
public:
	StringGuesser();
	~StringGuesser();

	//Functions
	string Guess(string goal);

	//Variables
	string geneSet  = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!. ";

	//Acessors
	int Get_Generation() const { return generation; };//only let the user acess this but not change it

private:
	//Functions
	void Display(const string guess);
	int Get_Fitness(const string guess);
	string Mutate(const string parent);
	string Generate_Parent(int wordLength);
	void Init(string goal);

	//Variables
	clock_t startTime;
	string bestParent;
	string target;
	int bestFitness;
	int generation = 0;//how many generations have gone through
};

