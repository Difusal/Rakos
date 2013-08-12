#pragma once

#include "stdIncludes.h"

class Gold {
public:
	Gold();
	Gold(unsigned int NumberOfCoins);

	unsigned int getAmountOfGoldCoins() { return goldCoins; }
	void addGoldCoins(unsigned int NumberOfCoins) { goldCoins += NumberOfCoins; }

	~Gold();

private:
	unsigned int goldCoins;
};