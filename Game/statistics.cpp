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
if(highScores.size() == 0)
{
    std::vector<QString> fillerNames =
    {
        "Yoshimitsu",
        "King",
        "Paul",
        "Eddy",
        "Mokujin",
        "Anna",
        "Kuma",
        "Heihachi",
        "Lei",
        "Jin"

    };
    std::vector<int> fillerScores =
    {
        4000,
        3670,
        3200,
        2700,
        2600,
        2350,
        2000,
        1800,
        1500,
        1200
    };
    std::transform(fillerScores.begin(),
                   fillerScores.end(),
                   fillerNames.begin(),
                   std::inserter(highScores,
                                 highScores.end()),
                   [](int a, QString b)
    {
        return std::make_pair(a, b);
    });
}
std::multimap<int, QString>::iterator i;

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

    std::multimap<int, QString>::reverse_iterator ir;
    std::multimap<int, QString>::iterator i;

    //Insert the new score and fill the newList with old scores
    for (ir = highScores.rbegin(); ir != highScores.rend(); ir++)
    {
        if (currentScore >= ir->first && !scoreInserted)
        {
            newList.insert(newHS);
            scoreInserted = true;
        }
        if (newList.size() < 10)
        {
            newList.insert(std::make_pair(ir->first, ir->second));
        }
    }

    //Save new scores to scores.txt if no scores.txt made yet, fill it with placeholders
    QFile file("scores.txt");
    if(file.open(QIODevice::WriteOnly))
    {
        QTextStream outStream(&file);
        for (i = newList.begin(); i != newList.end(); i++)
        {
            std::string str = std::to_string(i->first) + ":" +  i->second.toStdString();
            QString qstr = QString::fromStdString(str);
            outStream << qstr << endl;
        }
        file.close();
    }
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
    //High scores are in low to high order!
    file.close();
    return highScores;
}

bool Statistics::isNewHighScore(int score)
{
    std::multimap<int, QString>::iterator it = highScores.end();
    it--;
    if(it->second < score || highScores.size() == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Statistics::nysseRemoved()
{
    int scoreForBus = 10;
    nyssesDestroyed = nyssesDestroyed + 1;
    incrementScore(scoreForBus);
}

QString Statistics::getPlayerName() const
{
    return playerName;
}

void Statistics::setPlayerName(const QString &value)
{
    playerName = value;
}

