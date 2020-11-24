#ifndef STATISTICS_H
#define STATISTICS_H
#include "interfaces/istatistics.hh"
#include <QString>

class Statistics : public Interface::IStatistics
{
public:
    Statistics();
    ~Statistics() override;

    void setCurrentScore(int s);
    void incrementScore(int i);
    int currentScore = 0;
    int nyssesDestroyed = 0;
    void saveScores(QString playerName);

    void newNysse() override;
    void nysseLeft() override;
    void nysseRemoved() override;
    void morePassengers(int num) override;


private:

};

#endif // STATISTICS_H
