#ifndef STATISTICS_H
#define STATISTICS_H
#include "interfaces/istatistics.hh"
#include <QString>
#include <map>
#include <unordered_map>

class Statistics : public Interface::IStatistics
{
public:
    Statistics();
    ~Statistics() override;

    void setCurrentScore(int s);
    void incrementScore(int i);
    int currentScore = 0;
    int nyssesDestroyed = 0;
    int elonsSaved = 0;
    std::multimap<int, QString> highScores;
    void saveScores(QString playerName);
    std::multimap<int, QString> readScores();
    bool isNewHighScore(int score);

    void newNysse() override;
    void nysseLeft() override;
    void nysseRemoved() override;
    void morePassengers(int num) override;

private:

};

#endif // STATISTICS_H
