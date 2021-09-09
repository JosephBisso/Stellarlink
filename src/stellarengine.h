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

    bool engineOn;

public:
    explicit StellarEngine(Ball* ball, Floor* floor, QObject *parent = nullptr);

    QPointer<Ball> getBall() const;

    QPointer<Floor> getFloor() const;

    QElapsedTimer getTime() const;

    bool getEngineOn() const;
    void setEngineOn(bool newEngineOn);

signals:
    void engineOnChanged();

public slots:
    void start();
    void pause();
    void stop();

    void step();
};

#endif // STELLARENGINE_H
