#include "statistics.h"
#include <iostream>
#include <iostream>
#include <fstream>
#include <map>

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
    std::cout << "increment score" << std::endl;
    currentScore = currentScore + i;
}

void Statistics::saveScores(QString name)
{
    std::cout << "Kutsuttu savea" << std::endl;
    std::ofstream file("scores.txt");
    if(file){
        std::cout  << "avattu oikein" << std::endl;
        file << "Vittu älä crashaa pls :D" << std::endl;
    }
    //std::string str = "";
    //std::map<std::string, int> scores;
    file.close();
    std::cout  << "suljettu oikein" << std::endl;
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
