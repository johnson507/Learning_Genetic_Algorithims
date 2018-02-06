// Learning_Genetic_Algorithims.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Utilities.h"
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "GenericGuesser.h"

using namespace std;

/**/
template <class T, class U>
void DoGuess_Benchmark(int num_Guesses, T* genes, T* guess, U* guesser)
{
	clock_t currentTime;// init the time variable
	currentTime = clock();//now start the time variable so the countdown only considers the algorithm
	int average_Generations = 0;

	for (int i = 0; i < num_Guesses; ++i)
	{
		Fitness optimalFitness(guess->size(), 0);//we want to sort 10 numbers	

		cout << endl;
		guesser->Get_Best(guess, genes, &optimalFitness);
		average_Generations += guesser->Get_Generation();

		printf("\nGuess Number: %i/%i", i + 1, num_Guesses);
	}

	currentTime = clock() - currentTime;

	average_Generations /= num_Guesses;

	printf("\nAverage Generations: %i \nRuntime: %.3f seconds", average_Generations, (float)currentTime / CLOCKS_PER_SEC);

	cin.get();
	cin.get();
}


void SortedNumbers(int num_Guesses, int size)
{
	GenericGuesser<vector<int>> guesser;
	vector<int> genes;
	vector<int> guess(10);

	for (size_t i = 0; i < size; i++)//genes are numbers 0-99
		genes.push_back(i);

	DoGuess_Benchmark(num_Guesses, &genes, &guess, &guesser);
}

int main()
{
	bool isRunning = true;
	//input variables

	while (isRunning)
	{
		system("cls");

		string choice;

		cout << "[0] Sorted Numbers\n" << endl;
		getline(cin, choice);

		int num_Guesses;
		cout << "Enter the number of times to run the algorithim: ";
		cin >> num_Guesses;

		if (choice == "0")
			SortedNumbers(num_Guesses, 100);
	}


	return 0;
}
