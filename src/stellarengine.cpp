#include "stellarengine.h"

StellarEngine::StellarEngine(Ball* ball, Floor* floor, QObject *parent) : QObject(parent)
{
    this -> ball = ball;
    this -> floor = floor;
    this -> engineOn = false;
}

bool StellarEngine::getEngineOn() const
{
    return engineOn;
}

void StellarEngine::setEngineOn(bool newEngineOn)
{
    engineOn = newEngineOn;
}

void StellarEngine::pause()
{
    this -> engineOn = false;
}

void StellarEngine::stop()
{
    this -> engineOn = false;
    this -> time.restart();

    this -> ball -> setPos_x(FieldSizes::BallXStartPosition);
    this -> ball -> setPos_y(FieldSizes::BallYStartPosition);
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
    this -> step();
    qDebug() << "Starting StellarEngine";
}

void StellarEngine::step()
{
    double startPositionY = ball -> getPos_y();
    double startPositionX = ball -> getPos_x();

    ball -> setVelocities(5, 0);

    double zeit = ((double) (time.elapsed())) * 0.001;

    this -> ball -> setPos_y(startPositionY + 0.5 * M_G* pow(zeit, 2.0));
    this -> ball -> setPos_x(this -> ball -> getVelocityX() * zeit + startPositionX);

    this -> floor -> createFloorLine(this -> ball -> getPos_x());


//    qDebug() << "time elapsed"<< zeit;
//    qDebug() << "x = " << this -> ball -> getPos_x() /*<< "; y = " << this -> ball -> getPos_y()*/;
}
