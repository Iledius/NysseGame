#ifndef STATISTICS_H
#define STATISTICS_H
#include "interfaces/istatistics.hh"
#include <QString>
#include <map>
#include <unordered_map>

class Statistics
{
public:
    Statistics();
    ~Statistics();

    void setCurrentScore(int s);
    void incrementScore(int i);
    void nysseRemoved();
    int currentScore = 0;
    int nyssesDestroyed = 0;
    int elonsSaved = 0;
    QString playerName = "Tero Default";
    std::multimap<int, QString> highScores = {};
    void saveScores(QString playerName);
    std::multimap<int, QString> readScores();
    bool isNewHighScore(int score);

    QString getPlayerName() const;
    void setPlayerName(const QString &value);

private:

};

#endif // STATISTICS_H
