#include "ball.h"

Ball::Ball(double radius, QObject *parent) : Touchable(parent)
{
    this -> radius = radius;
    this -> setType(STElement::Ball);
    this -> setPos_x(FieldSizes::BallXStartPosition);
    this -> setPos_y(FieldSizes::BallYStartPosition);
    this -> setMasse(2);
    this -> setVelocities(LevelParameter::BallMovingVelocity, 0);
    this -> highTanResistant = false;
    setHealth(100);
    initKonstante();
    resetState();
    trail();
}

bool Ball::hit(double health)
{
    this -> health -= health;
    emit healthChanged();
    return health > 0;
}

const QPolygonF &Ball::getBallPath() const
{
    return ballPath;
}

void Ball::setBallPath(const QPolygonF &newBallPath)
{
    ballPath = newBallPath;

    emit ballPathChanged();
}

void Ball::resetBallPath()
{
    if (!this -> ballPath.isEmpty()) {this -> ballPath.remove(0, this -> ballPath.length());}
}

void Ball::trail()
{
    double x = getPos_x() < 250 ? getPos_x() : 250;
    if (this -> ballPath.length() > 0) {this -> ballPath.translate(-getVelocityX(), 0);}
    this -> ballPath << QPointF(x, getPos_y() - 0.5 * getRadius());
    while(this -> ballPath.first().x() < 0) {this->ballPath.removeFirst();}
}

void Ball::setBallLocation(BallLocation newBallLocation)
{
    ballLocation = newBallLocation;
}

BallLocation Ball::getBallLocation() const
{
    return this -> ballLocation;
}

bool Ball::isLaunching()
{
    return this -> ballLocation == BallLocation::Launching;
}

bool Ball::isFalling()
{
    return this -> ballLocation == BallLocation::Falling;
}
bool Ball::isOnGround()
{
    return this -> ballLocation == BallLocation::Ground;
}

bool Ball::isHighTanResistant()
{
    return highTanResistant;
}

void Ball::setHighTanResistance(bool resistant)
{
    highTanResistant = resistant;
}

void Ball::equation()
{
    konstante[Konstante::Delta] = pow(konstante[Konstante::Daempfer], 2.0) - 4 * getMasse() * konstante[Konstante::Feder];

    konstante[Konstante::Lambda1] = (konstante[Konstante::Daempfer] - sqrt(konstante[Konstante::Delta])) / (2 * getMasse());
    konstante[Konstante::Lambda2] = (konstante[Konstante::Daempfer] + sqrt(konstante[Konstante::Delta])) / (2 * getMasse());

    if (konstante[Konstante::Delta] != 0) {
        konstante[Konstante::C1] = (konstante[Konstante::Lambda2] * FieldSizes::BallYStartPosition / 4) / (konstante[Konstante::Lambda2] - konstante[Konstante::Lambda1]);
        konstante[Konstante::C2] = FieldSizes::BallYStartPosition - konstante[Konstante::C1];
    } else {
        konstante[Konstante::C0] = FieldSizes::BallYStartPosition;
    }
}

double Ball::yHomogen(double time)
{
//    qDebug() << "yH0" <<konstante[Konstante::C0] * exp(-konstante[Konstante::Lambda1] * time);
//    qDebug() << "yH" <<konstante[Konstante::C1] * exp(-konstante[Konstante::Lambda1] * time) + konstante[Konstante::C2] * exp(-konstante[Konstante::Lambda2] * time);
    return konstante[Konstante::Delta] != 0.0 ?
            konstante[Konstante::C1] * exp(-konstante[Konstante::Lambda1] * time) + konstante[Konstante::C2] * exp(-konstante[Konstante::Lambda2] * time)
            : konstante[Konstante::C0] * exp(-konstante[Konstante::Lambda1] * time);
}

double Ball::yPartikular(double dudx, double u)
{
//     qDebug() << "yP" <<(-getMasse() * M_G + konstante[Konstante::Daempfer] * dudx + konstante[Konstante::Feder] * (konstante[Konstante::L0] - u)) / (-konstante[Konstante::Feder]);
    return (-getMasse() * M_G + konstante[Konstante::Daempfer] * dudx + konstante[Konstante::Feder] * (konstante[Konstante::L0] - u)) / (-konstante[Konstante::Feder]);
 }

double Ball::getRadius() const
{
    return radius;
}

void Ball::setRadius(double newRadius)
{
    radius = newRadius;

    emit radiusChanged();
}

double Ball::getFuelle() const
{
    return fuelle;
}

void Ball::setFuelle(double newFuelle)
{
    fuelle = newFuelle;

    emit fuelleChanged();
}

double Ball::getHealth() const
{
    return health;
}

void Ball::setHealth(double newHealth)
{
    health = newHealth;

    emit healthChanged();
}

void Ball::initKonstante()
{
    this -> konstante[Konstante::Feder] = 0;
    this -> konstante[Konstante::L0] = 0;
    this -> konstante[Konstante::Daempfer] = 0;
    this -> konstante[Konstante::Delta] = 0;
    this -> konstante[Konstante::Lambda1] = 0;
    this -> konstante[Konstante::Lambda2] = 0;
    this -> konstante[Konstante::C0] = 0;
    this -> konstante[Konstante::C1] = 0;
    this -> konstante[Konstante::C2] = 0;
}

void Ball::defineKonstante(double feder, double l0, double daempfer)
{
    this -> konstante[Konstante::Feder] = feder;
    this -> konstante[Konstante::L0] = l0;
    this -> konstante[Konstante::Daempfer] = daempfer;
    equation();
}

double Ball::getL0() const
{
    return  this -> konstante[Konstante::L0];
}

void Ball::setBallState(BallStates newBallState)
{
    ballState = newBallState;

    emit statesChanged();
}

BallStates Ball::getBallState() const
{
    return this -> ballState;
}

void Ball::resetState()
{
    ballState = BallStates::None;
}

bool Ball::isAccelerating()
{
    return this -> ballState == BallStates::Accelerating;
}

bool Ball::isDecelerating()
{
    return this -> ballState == BallStates::Decelerating;
}

bool Ball::isSticking()
{
    return this -> ballState == BallStates::Sticking;
}

bool Ball::moveByItself()
{
    return this -> ballState == BallStates::None;
}

bool Ball::touched(Touchable *touchable)
{
    if (nullptr == touchable) return false;
    if (this == touchable) return false;

    switch (touchable -> getType()) {
        case STElement::Ball : {
            QPointer<Ball> ball = dynamic_cast<Ball*>(touchable);
            return pow(ball -> getPos_x() - this -> getPos_x(), 2.0) + pow(ball -> getPos_y() - this -> getPos_y(), 2.0) <= pow(this -> getRadius() + ball -> getRadius(), 2.0);
        }

        case STElement::Floor : {
            QPointer<Floor> floor = dynamic_cast<Floor*>(touchable);
            double winkel = 0;
            for (int i= 0; i <= 90; i++) {
                winkel = i * M_PI / 180;
                if (floor -> getFloorLine().containsPoint(QPointF(this -> getPos_x() + this -> getRadius() * sin(winkel), this -> getPos_y() + this -> getRadius() * cos(winkel)), Qt::WindingFill)) {return true;}
            }
            return false;
        }

        case STElement::BonusBox : {

        }
    }

    return pow(touchable -> getPos_x() - this -> getPos_x(), 2.0) + pow(touchable -> getPos_y() - this -> getPos_y(), 2.0) <= pow(this -> getRadius(), 2.0);
}
