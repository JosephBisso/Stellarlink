#include "stellarengine.h"

StellarEngine::StellarEngine(Ball* ball, Floor* floor, QObject *parent) : QObject(parent)
{
    this -> ball = ball;
    this -> floor = floor;
    this -> engineOn = false;
    this -> launchingTangent = 0;
    this -> launching = false;
    this -> ballFloating = false;
}

bool StellarEngine::getEngineOn() const
{
    return engineOn;
}

void StellarEngine::setEngineOn(bool newEngineOn)
{
    engineOn = newEngineOn;
}

void StellarEngine::resetLauchingTangent()
{
    this -> launchingTangent = 0;
    this -> launching = false;
    airTime.restart();
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

bool StellarEngine::touched(Touchable *touchable)
{
    if (this -> ball -> touched(touchable)) {
        qDebug() << "Touched";
        return true;
    }
    return false;
}


QPointer<Ball> StellarEngine::getBall() const
{
    return ball;
}

QPointer<Floor> StellarEngine::getFloor() const
{
    return floor;
}

void StellarEngine::restartTime()
{
    time.restart();
}

void StellarEngine::restartAirTime()
{
    airTime.restart();
}

void StellarEngine::start()
{
    this -> time.start();
    this -> airTime.start();
    this -> engineOn = true;
    this -> step();
    this -> launchingTangent = 0;
    this -> launching = false;
    this -> ballFloating = false;
    this -> ball -> setVelocities(LevelParameter::BallMovingVelocity, LevelParameter::MaxVelocity_1);
    qDebug() << "Starting StellarEngine";
}

void StellarEngine::step()
{
    double startPositionY = ball -> getPos_y();
    double startPositionX = ball -> getPos_x();

    double zeit = ((double) (time.elapsed())) * 0.001;
    double luftZeit = ((double) (airTime.elapsed())) * 0.001;
    double dudx = (this -> floor -> equation(startPositionX) - this -> floor -> equation(startPositionX + 0.25)) / 0.25;

    if (this -> launching) {
        if (ball -> getVelocityY() < 0) {
            resetLauchingTangent();
            ball -> setVelocityY(LevelParameter::MaxVelocity_1);
        } else {
            qDebug()<< "lauching!!" ;
            if (0.5 * M_G * pow(luftZeit , 2.0) < LevelParameter::MaxFallingVelocity_1) {
                this -> ball -> setVelocityY(this -> ball -> getVelocityY() - 0.5 * M_G * pow(luftZeit , 2.0));

            } else {
                this -> ball -> setVelocityY(this -> ball -> getVelocityY() - LevelParameter::MaxFallingVelocity_1);
            }

            this -> ball -> setPos_y(startPositionY - this -> ball -> getVelocityY());
        }

    } else {
        if (this -> floor -> equation(startPositionX) - startPositionY >= LevelParameter::FloatingFrom && !this -> launching) {
             qDebug()<< "floating";
            this -> ballFloating = true;
            if (0.5 * M_G * pow(luftZeit + 0.283, 2.0) < LevelParameter::MaxFallingVelocity_1) {
                this -> ball -> setPos_y(0.5 * M_G * pow(luftZeit + 0.283, 2.0) + startPositionY);

            } else {
                this -> ball -> setPos_y(LevelParameter::MaxFallingVelocity_1 + startPositionY);
            }

        } else if (dudx > 0 && dudx > this -> launchingTangent && !this -> launching) {
            launchingTangent = dudx;

        } else if (dudx > 0 && dudx < this -> launchingTangent && !this -> launching) {
            this -> launching = true;
            qDebug() << "dudx = "<<dudx;
            if (this -> ball -> getVelocityX() * zeit < LevelParameter::MaxVelocity_1) {
                this -> ball -> setVelocityY(this -> ball -> getVelocityX() * zeit * this -> launchingTangent);
            } else {
                this -> ball -> setPos_x(LevelParameter::MaxVelocity_1 + startPositionX);
                this -> ball -> setVelocityY(LevelParameter::MaxVelocity_1 * this -> launchingTangent);
            }
            airTime.start();

        }

        if (this -> floor -> equation(startPositionX) - startPositionY < LevelParameter::FloatingFrom) {
            qDebug()<< "ground";
            this -> ball -> setPos_y(this -> ball -> yHomogen(zeit) + this -> ball -> yPartikular(dudx, this -> floor -> equation(startPositionX)));
        }

    }

    if (this -> ball -> getPos_y() > this -> floor -> equation(startPositionX)) {
        qDebug()<< "Underground";
        this -> ball -> setPos_y(this -> floor -> equation(startPositionX));
        resetLauchingTangent();
    }

    this -> floor -> createFloorLine(this -> ball -> getPos_x());

    qDebug() << "x =" << ball -> getPos_x() << "; y =" << ball -> getPos_y();

    if (this -> ball -> getVelocityX() * zeit < LevelParameter::MaxVelocity_1) {
        this -> ball -> setPos_x(this -> ball -> getVelocityX() * zeit + startPositionX);
    } else {
        this -> ball -> setPos_x(LevelParameter::MaxVelocity_1 + startPositionX);
        this -> ball -> setVelocityX(LevelParameter::MaxVelocity_1);
    }

}

void StellarEngine::accelerate()
{

}

void StellarEngine::brake()
{

}

void StellarEngine::haften()
{

}
