#include "StringGuesser.h"
#include <cmath>
#include <random>


StringGuesser::StringGuesser()
{
}


StringGuesser::~StringGuesser()
{
}

string StringGuesser::Generate_Parent(int wordLength)
{
	string genes = "";

	while (genes.size() < wordLength)
	{
		int sampleSize = fmin(wordLength - genes.size(), geneSet.size());
		//genes.append(rand())
	}

	return string();
}
