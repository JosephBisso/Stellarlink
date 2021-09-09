#ifndef STELLARENGINE_H
#define STELLARENGINE_H

#include <QObject>
#include <QElapsedTimer>

#include "ball.h"

class StellarEngine : public QObject
{
    Q_OBJECT
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

signals:


public slots:
    void start();
    void pause();

    void ballFallStep();
};

#endif // STELLARENGINE_H
