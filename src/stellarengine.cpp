#include "stellarengine.h"

StellarEngine::StellarEngine(Ball* ball, Floor* floor, QObject *parent) : QObject(parent)
{
    this -> ball = ball;
    this -> floor = floor;
    this -> engineOn = false;
    this -> launchingTangent = 0;
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
    airTime.restart();
}

void StellarEngine::pause()
{
    this -> engineOn = false;
}

void StellarEngine::stop()
{
    this -> engineOn = false;
    this -> globalTime.restart();

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
    globalTime.restart();
}

void StellarEngine::restartAirTime()
{
    airTime.restart();
}

void StellarEngine::resetStates()
{
    this -> ball -> resetState();
}

void StellarEngine::start()
{
    this -> globalTime.start();
    this -> airTime.start();
    this -> engineOn = true;
    this -> step();
    this -> launchingTangent = 0;
    this -> ball -> setVelocities(LevelParameter::BallMovingVelocity, LevelParameter::MaxVelocity);
    this -> ball -> setBallLocation(BallLocation::Falling);
    qDebug() << "Starting StellarEngine";
    resetStates();
}

void StellarEngine::step()
{
    double startPositionY = ball -> getPos_y();
    double startPositionX = ball -> getPos_x();

    double zeit = ((double) (globalTime.elapsed())) * 0.001;
    double luftZeit = ((double) (airTime.elapsed())) * 0.001;
    double zustandZeit = ((double) (stateTime.elapsed())) * 0.001;
    double dx = 0.125;
    double dudx = (this -> floor -> equation(startPositionX) - this -> floor -> equation(startPositionX + dx)) / dx;

    if (this -> ball -> isLaunching()) {
        if (ball -> getVelocityY() < 1) {
            this -> ball -> setBallLocation(BallLocation::Falling);
            resetLauchingTangent();
        } else {
//            qDebug()<< "lauching!!" ;
            this -> ball -> setVelocityY(this -> ball -> getVelocityY() - 0.5 * M_G * pow(luftZeit, 2.0));
            this -> ball -> setPos_y(startPositionY - this -> ball -> getVelocityY());
        }

    } else {
        if (this -> floor -> equation(startPositionX) - startPositionY >= LevelParameter::FloatingFrom && !this -> ball -> isLaunching()) {
//             qDebug()<< "floating";
             this -> ball -> setBallLocation(BallLocation::Falling);
             if (ball -> getVelocityY() < LevelParameter::MaxFallingVelocity) {
                 this -> ball -> setVelocityY(0.5 * M_G * pow(luftZeit, 2.0) + this -> ball -> getVelocityY());

             } else {
                 this -> ball -> setVelocityY(LevelParameter::MaxFallingVelocity);
             }
             this -> ball -> setPos_y(this -> ball -> getVelocityY() + startPositionY);

        } else if (dudx > 0 && dudx > this -> launchingTangent && !this -> ball -> isLaunching()) {
            launchingTangent = dudx;

        } else if (dudx > 0 && dudx < this -> launchingTangent && !this -> ball -> isLaunching()) {
            this -> ball -> setBallLocation(BallLocation::Launching);
//            qDebug() << "dudx = "<<dudx;
            this -> ball -> setVelocityY(this -> ball -> getVelocityX() * this -> launchingTangent);
            airTime.start();
        }

        if (this -> floor -> equation(startPositionX) - startPositionY < LevelParameter::FloatingFrom) {
//            qDebug()<< "ground";
            if (!this -> ball -> isLaunching()){this -> ball -> setBallLocation(BallLocation::Ground);}
            this -> ball -> setPos_y(this -> ball -> yHomogen(zeit) + this -> ball -> yPartikular(dudx, this -> floor -> equation(startPositionX)));

            if (dudx < 0){
                this -> ball -> setVelocityX (sqrt(pow(this -> ball -> getVelocityX(), 2.0) + 2 * M_G * dx * abs(dudx)) + 0.5);
                this -> ball -> setBallState(BallStates::Accelerating);
            }
        }

    }


    if (this -> ball -> isAccelerating()) {
        if (this -> ball -> getVelocityX() >= LevelParameter::MaxVelocity) {
            this -> ball -> setPos_x(this -> ball -> getVelocityX() + startPositionX);
        } else if (this -> ball -> getVelocityX() < LevelParameter::MaxVelocity) {
            this -> ball -> setPos_x(this -> ball -> getVelocityX() + startPositionX);
            this -> ball -> setVelocityX( 0.5 * LevelParameter::BallAcceleration * pow(zeit, 2.0) + this -> ball -> getVelocityX());
        }

    } else if (this -> ball -> isDecelerating() && !this -> ball -> isFalling() && !this -> ball -> isLaunching()) {
        double  brakingSpeed = this -> ball -> getVelocityX() - LevelParameter::BallDecelerationX * zustandZeit;
        if ( brakingSpeed < 0) {
            brakingSpeed = 0;
            globalTime.restart();
        }
        this -> ball -> setPos_x(brakingSpeed + startPositionX);
        this -> ball -> setVelocityX(brakingSpeed);

    } else if (this -> ball -> isDecelerating() && (this -> ball -> isFalling() || this -> ball -> isLaunching())) {
         this -> ball -> setPos_x(this -> ball -> getVelocityX() + startPositionX);

    } else if (this -> ball -> moveByItself() && !this -> ball -> isFalling() && !this -> ball -> isLaunching()) {
        double slowingSpeed = 0;
        if (dudx > 0) {
            bool goingUp = pow(this -> ball -> getVelocityX(), 2.0) - 2 * M_G * dx * abs(dudx) >= 0;
            if (goingUp) {slowingSpeed = sqrt(pow(this -> ball -> getVelocityX(), 2.0) - 2 * M_G * dx * abs(dudx));}
            else {slowingSpeed = -sqrt(pow(this -> ball -> getVelocityX(), 2.0) + 2 * M_G * dx * abs(dudx));}

        } else if (dudx < 0){
            slowingSpeed = sqrt(pow(this -> ball -> getVelocityX(), 2.0) + 2 * M_G * dx * abs(dudx));
            if (slowingSpeed > LevelParameter::MaxVelocity) {
                slowingSpeed = LevelParameter::MaxVelocity;
            }

        } else {
            // GAME OVER
        }
        this -> ball -> setPos_x(slowingSpeed + startPositionX);
        this -> ball -> setVelocityX(slowingSpeed);

    } else if (this -> ball -> moveByItself() && (this -> ball -> isFalling() || this -> ball -> isLaunching())) {
        this -> ball -> setPos_x(this -> ball -> getVelocityX() + startPositionX);

    } else if (this -> ball -> isSticking()) {
        if (this -> ball -> isLaunching()) {this -> ball -> setBallLocation(BallLocation::Falling);}
        double descend = this -> ball -> getVelocityY() - LevelParameter::BallDecelerationY * zustandZeit < 0 ? 0 : this -> ball -> getVelocityY() - LevelParameter::BallDecelerationY * zustandZeit;
        this -> ball -> setVelocityY(descend);
        this -> ball -> setPos_x(this -> ball -> getVelocityX() + startPositionX);
    }


    if (this -> ball -> getPos_y() > this -> floor -> equation(startPositionX)) {
//        qDebug()<< "Underground";
        this -> ball -> setPos_y(this -> floor -> equation(startPositionX));
        resetLauchingTangent();
    }

    this -> floor -> createFloorLine(this -> ball -> getPos_x());
    this -> ball -> trail();

//    qDebug() << "x =" << ball -> getPos_x() << "; y =" << ball -> getPos_y();
    qDebug()<< "V_x = " <<this -> ball -> getVelocityX() << "; V_y = s" << this -> ball -> getVelocityY();
}

void StellarEngine::accelerate()
{
    this -> ball -> setBallState(BallStates::Accelerating);
    this -> globalTime.restart();
}

void StellarEngine::brake()
{
    this -> ball -> setBallState(BallStates::Decelerating);
    this -> stateTime.restart();
}

void StellarEngine::stick()
{
    this -> ball -> setBallState(BallStates::Sticking);
    this -> stateTime.restart();
}

void StellarEngine::freeBall()
{
    this -> ball -> setBallState(BallStates::None);
    this -> stateTime.restart();
}
