#include <QtTest>
#include "../Game/statistics.h"

// add necessary includes here

class statistics_test : public QObject
{
    Q_OBJECT

public:
    statistics_test();
    ~statistics_test();
    void tst_readScores();
    void tst_highScores();
    Statistics *stats;
    std::multimap<int, QString> startScores;
    std::multimap<int, QString> scoresAfterAdding;
    int passedCases = 0;

private slots:
    void initTestCase();
    void cleanupTestCase();

};

statistics_test::statistics_test()
{
}

statistics_test::~statistics_test()
{

}

void statistics_test::initTestCase()
{
    startScores = stats->readScores();
    tst_readScores();
    tst_highScores();
}

void statistics_test::cleanupTestCase()
{

}

void statistics_test::tst_readScores(){
    int testScore=0;
    QString test_person = "test_man";
    if(startScores.size()>0){
        qDebug() << "Highest score is:";
        qDebug() << startScores.end()--->first;
        qDebug() << "Adding test_man with 10 points higher score";
        testScore = (startScores.end()--)->first+10;
    }
    else{
        qDebug() << "No highscores yet! adding test_man with score 100";
        testScore = 100;
    }
    stats->incrementScore(testScore);
    scoresAfterAdding = stats->readScores();
    if(scoresAfterAdding.end()--->first==testScore&&scoresAfterAdding.end()--->second==test_person)
        qDebug() << "readScores TEST CASE PASSED";passedCases++;
}

void statistics_test::tst_highScores(){
    if(stats->isNewHighScore(scoresAfterAdding.end()--->first+10))
       qDebug() << "isNewHighScore TEST CASE PASSED";passedCases++;
}

QTEST_APPLESS_MAIN(statistics_test)

#include "tst_statistics_test.moc"
