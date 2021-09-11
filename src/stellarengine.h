#ifndef STELLARENGINE_H
#define STELLARENGINE_H

#include <QObject>
#include <QElapsedTimer>

#include "ball.h"

class StellarEngine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool engineOn READ getEngineOn WRITE setEngineOn NOTIFY engineOnChanged)

private:
    QPointer<Ball> ball;
    QPointer<Floor> floor;

    QElapsedTimer time;
    QElapsedTimer airTime;

    bool engineOn;

    bool launching;
    double launchingTangent;
    bool ballFloating;

    bool accelerating;
    bool haftend;

public:
    explicit StellarEngine(Ball* ball, Floor* floor, QObject *parent = nullptr);

    QPointer<Ball> getBall() const;

    QPointer<Floor> getFloor() const;

    void restartTime();
    void restartAirTime();

    bool getEngineOn() const;
    void setEngineOn(bool newEngineOn);

    void resetLauchingTangent();


signals:
    void engineOnChanged();

public slots:
    void start();
    void pause();
    void stop();

    bool touched(Touchable* toubchable);
    void step();

    void accelerate();
    void brake();
    void haften();
};

#endif // STELLARENGINE_H
