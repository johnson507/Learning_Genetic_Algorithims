#pragma once

#include <string>
#include "Utilities.h"

using namespace std;
using namespace Utilities;

class StringGuesser
{
public:
	StringGuesser();
	~StringGuesser();

	int Get_Fitness();
	string Generate_Parent(int wordLength);
	
	string geneSet  = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!.";
	string target = "a";
};

