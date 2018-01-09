// Learning_Genetic_Algorithims.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Utilities.h"
#include <iostream>
#include <string>
#include <vector>
#include "StringGuesser.h"
#include <ctime>

using namespace std;

int main()
{
	clock_t currentTime;// init the time variable
	StringGuesser guesser;
	
	int average_Generations = 0;


	//input variables
	string guess;
	string genes = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!,?':;. 123456789/*-+()@#$%^&*{}[]|\'/<>`~=";
	int num_Guesses;

	cout << "Enter string to guess: ";
	getline(cin, guess);
	cout << "Enter the number of times to run the algorithim: ";
	cin >> num_Guesses;

	currentTime = clock();//now start the time variable so the countdown only considers the algorithm

	for (int i = 0; i < num_Guesses; ++i)
	{
		cout << endl;
		guesser.Get_Best(guess, genes, guess.length());
		average_Generations += guesser.Get_Generation();

		printf("\nGuess Number: %i/%i", i + 1, num_Guesses);
	}

	currentTime = clock() - currentTime;

	average_Generations /= num_Guesses;

	printf("\nAverage Generations: %i \nRuntime: %.3f seconds", average_Generations, (float)currentTime / CLOCKS_PER_SEC);

	cin.get();
	cin.get();
	return 0;
}



