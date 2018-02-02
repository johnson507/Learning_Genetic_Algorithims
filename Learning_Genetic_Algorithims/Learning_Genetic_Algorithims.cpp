// Learning_Genetic_Algorithims.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Utilities.h"
#include <iostream>
#include <string>
#include <vector>
#include "IntVectorGuesser.h"
#include "StringGuesser.h"
#include <ctime>
#include "SortedNumbers_Guesser.h"


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
		cout << endl;
		//guesser->Get_Best(guess, genes, guess->size());
		average_Generations += guesser->Get_Generation();

		printf("\nGuess Number: %i/%i", i + 1, num_Guesses);
	}

	currentTime = clock() - currentTime;

	average_Generations /= num_Guesses;

	printf("\nAverage Generations: %i \nRuntime: %.3f seconds", average_Generations, (float)currentTime / CLOCKS_PER_SEC);

	cin.get();
	cin.get();
}

void InitStringGuesser(int num_Guesses)
{
	StringGuesser<string> guesser;
	string genes = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!,?':;. 123456789/*-+()@#$%^&*{}[]|\'/<>`~=";

	string guess;

	cin.get();
	cout << "Enter string to guess: ";
	getline(cin, guess);

	DoGuess_Benchmark(num_Guesses, &genes, &guess, &guesser);
}

void InitOneMaxProblem(int num_Guesses)
{
	IntVectorGuesser<vector<int>> guesser;
	vector<int> genes{ 0,1 };

	vector<int> guess;

	for (size_t i = 0; i < 100; i++)
		guess.push_back(1);

	DoGuess_Benchmark(num_Guesses, &genes, &guess, &guesser);
}

void SortedNumbers(int num_Guesses, int size)
{
	SortedNumbers_Guesser<vector<int>> guesser;
	vector<int> genes;
	vector<int> guess(10);

	for (size_t i = 0; i < size; i++)
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

		cout << "[0] String Gueser\n[1] One Max Problem\n[2] Sorted Numbers\n" << endl;
		getline(cin, choice);

		int num_Guesses;
		cout << "Enter the number of times to run the algorithim: ";
		cin >> num_Guesses;

		if (choice == "0")
			InitStringGuesser(num_Guesses);
		else if (choice == "1")
			InitOneMaxProblem(num_Guesses);
		else if (choice == "2")
			SortedNumbers(num_Guesses, 100);
	}


	return 0;
}
