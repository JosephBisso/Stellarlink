#ifndef STELLARENGINE_H
#define STELLARENGINE_H

#include <QObject>
#include <QElapsedTimer>

#include "ball.h"

class StellarEngine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool engineOn READ getEngineOn WRITE setEngineOn NOTIFY engineOnChanged)
    Q_PROPERTY(double maxVelocity READ getMaxVelocity WRITE setMaxVelocity NOTIFY maxVelocityChanged)
    Q_PROPERTY(double maxHeigth READ getMaxHeigth  WRITE setMaxHeigth  NOTIFY maxHeigthChanged)

private:
    QPointer<Ball> ball;
    QPointer<Floor> floor;

    QElapsedTimer globalTime;
    QElapsedTimer airTime;
    QElapsedTimer stateTime;

    bool engineOn;

    double launchingTangent;

    double maxVelocity;
    double maxHeigth;

    void resetLauchingTangent();

    void resetStates();

    void resetAll();

public:
    explicit StellarEngine(Ball* ball, Floor* floor, QObject *parent = nullptr);

    QPointer<Ball> getBall() const;

    QPointer<Floor> getFloor() const;

    void restartTime();
    void restartAirTime();

    bool getEngineOn() const;
    void setEngineOn(bool newEngineOn);


    double getMaxVelocity() const;
    void setMaxVelocity(double newMaxVelocity);

    double getMaxHeigth() const;
    void setMaxHeigth(double newMaxHeigth);

signals:
    void engineOnChanged();

    void maxVelocityChanged();
    void maxHeigthChanged();

public slots:
    void start();
    void pause();
    void stop();

    bool touched(Touchable* toubchable);
    void step();

    void accelerate();
    void brake();
    void stick();
    void freeBall();
};

#endif // STELLARENGINE_H
