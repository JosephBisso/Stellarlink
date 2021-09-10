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

    double zeit = ((double) (time.elapsed())) * 0.001;


    if (this -> floor -> equation(startPositionX) - startPositionY > LevelParameter::FloatingFrom) {
//        qDebug() << "floating";
//        qDebug() << "x = " << startPositionX << "; y = " << startPositionY << "; boden = " << this -> floor -> equation(startPositionX);
        if (M_G * pow(zeit, 20) < LevelParameter::MaxFallingVelocity_1) {
            this -> ball -> setPos_y(0.5 * M_G * pow(zeit, 2.0) + startPositionY);

        } else {
            this -> ball -> setPos_y(0.5 * LevelParameter::MaxFallingVelocity_1 + startPositionY);
        }

    } else {
//        qDebug() << "ground";
//        qDebug() << "x = " << startPositionX << "; y = " << startPositionY;
        double dudx = (this -> floor -> equation(startPositionX) - this -> floor -> equation(startPositionX - 0.25) ) / 0.25;
        this -> ball -> setPos_y(this -> ball -> yHomogen(zeit) + this -> ball -> yPartikular(dudx, this -> floor -> equation(startPositionX)));
    }

    qDebug() << "velocity gradient";
    qDebug() << this -> ball -> gradientY(zeit) << "for x = " << startPositionX;

    this -> floor -> createFloorLine(this -> ball -> getPos_x());

    if (this -> ball -> getVelocityX() * zeit < LevelParameter::MaxVelocity_1) {
        this -> ball -> setPos_x(this -> ball -> getVelocityX() * zeit + startPositionX);

    } else {
        this -> ball -> setPos_x(LevelParameter::MaxVelocity_1 + startPositionX);
    }

    if (ball -> getPos_y() < 0) {
         this -> ball -> setPos_y(- 2 * this -> ball -> getRadius());
    } else if (ball -> getPos_y() + this -> ball -> getRadius() >= this -> floor -> equation(this -> ball -> getPos_x())) {
        this -> ball -> setPos_y(this -> floor -> equation(this -> ball -> getPos_x()) - this -> ball -> getRadius());
    }


//    qDebug() << "time elapsed"<< zeit;
//    qDebug() << "ballY = " << startPositionY << "; boden = " << this -> floor -> equation(startPositionX);
}
