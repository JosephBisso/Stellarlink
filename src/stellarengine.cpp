#include "stellarengine.h"

StellarEngine::StellarEngine(Ball* ball, Floor* floor, QObject *parent) : QObject(parent)
{
    this -> ball = ball;
    this -> floor = floor;
}

void StellarEngine::pause()
{
    this -> engineOn = false;
}


QPointer<Ball> StellarEngine::getBall() const
{
    return ball;
}

QPointer<Floor> StellarEngine::getFloor() const
{
    return floor;
}

QElapsedTimer StellarEngine::getTime() const
{
    return time;
}

void StellarEngine::start()
{
    this -> time.start();
    this -> engineOn = true;
    this -> ballFallStep();
    qDebug() << "Starting StellarEngine";
}

void StellarEngine::ballFallStep()
{
    double startPosition = ball -> getPos_y();
    double zeit = ((double) (time.elapsed())) * 0.001;
    this -> ball -> setPos_y(startPosition + 0.5 * M_G * pow(zeit, 2.0));
    qDebug() << "time elapsed"<< zeit;
}
