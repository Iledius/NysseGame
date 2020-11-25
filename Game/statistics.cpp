#include "statistics.h"
#include <iostream>
#include <iostream>
#include <fstream>
#include <map>
#include <unordered_map>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <string>

Statistics::Statistics()
{
highScores = readScores();
std::multimap<int, QString>::iterator i;
//for (i = highScores.begin(); i != highScores.end(); i++)
//{
//    std::cout << i->second.toStdString() << i->first << std::endl;
//}
//std::cout << isNewHighScore(100) << std::endl;
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

void Statistics::saveScores(QString name)
{
    std::pair<int, QString> newHS = std::make_pair(currentScore, name);
    std::multimap<int, QString> newList;

    bool scoreInserted = false;
    std::multimap<int, QString>::iterator i;
    for (i = highScores.begin(); i != highScores.end(); i++)
    {
        if (currentScore > i->first && !scoreInserted)
        {
            newList.insert(newHS);
            scoreInserted = true;
            std::cout << "lisätty uusi score" << std::endl;
        }
        if (newList.size() <= 10)
        {
            newList.insert(std::make_pair(i->first, i->second));
            std::cout << "insert " << i->first << " " << i->second.toStdString() << std::endl;
        }
    }

    for (i = newList.begin(); i != newList.end(); i++)
    {
        std::cout << i->second.toStdString() << i->first << std::endl;
    }

    QFile file("scores.txt");
    if(file.open(QIODevice::WriteOnly))
    {
        QTextStream outStream(&file);
        for (i = newList.begin(); i != newList.end(); i++)
        {
            std::cout << i->second.toStdString() << i->first << std::endl;
            std::string str = std::to_string(i->first) + ":" +  i->second.toStdString();
            QString qstr = QString::fromStdString(str);
            outStream << qstr << endl;
        }
        file.close();
        std::cout << "scores saved!"<<  std::endl;
    }
    file.close();

}

std::multimap<int, QString> Statistics::readScores()
{
    std::multimap<int, QString> highScores;

    QFile file("scores.txt");
    QTextStream in(&file);
    if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        std::cout << "Error in opening high score file." << std::endl;
        return highScores;
    }
    while(!in.atEnd())
    {
        QString line = in.readLine();
        std::string linestr = line.toStdString();
        std::string delimitter = ":";
        std::string score = linestr.substr(0, linestr.find(delimitter));
        std::string name = linestr.substr(linestr.find(delimitter)+1, linestr.length());
        std::cout << score << name << std::endl;
        std::pair<int, QString> instance;
        instance = std::make_pair(std::stoi(score),QString::fromStdString(name));
        highScores.insert(instance);
    }
    //High scores are now in low to high order

    return highScores;
}

bool Statistics::isNewHighScore(int score)
{
    std::multimap<int, QString>::iterator it = highScores.end();
    if(it->second < score)
    {
        return true;
    }
    else
    {
        return false;
    }
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
