#include "statistics.h"
#include <iostream>

Statistics::Statistics()
{

}

Statistics::~Statistics()
{

}

void Statistics::setCurrentScore(int s)
{
    currentScore = s;
}

void Statistics::incrementScore(int i)
{
    currentScore = currentScore + i;
}

void Statistics::saveScores()
{

}

void Statistics::newNysse()
{

}

void Statistics::nysseLeft()
{

}

void Statistics::nysseRemoved()
{
    int scoreForBus = 10;
    nyssesDestroyed = nyssesDestroyed + 1;
    incrementScore(scoreForBus);
}

void Statistics::morePassengers(int num)
{

}
