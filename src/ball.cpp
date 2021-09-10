#include "ball.h"

Ball::Ball(double radius, QObject *parent) : Touchable(parent)
{
    this -> radius = radius;
    this -> setType(STElement::Ball);
    this -> setPos_x(FieldSizes::BallXStartPosition);
    this -> setPos_y(FieldSizes::BallYStartPosition);
    this -> setMasse(radius * 0.1225);
    this -> setVelocities(5, 0);
    initKonstante();
}

void Ball::equation()
{
    konstante[Konstante::Delta] = pow(konstante[Konstante::Daempfer], 2.0) + 4 * getMasse() * konstante[Konstante::Feder];

    konstante[Konstante::Lambda1] = (- konstante[Konstante::Daempfer] - sqrt(konstante[Konstante::Delta])) / (2 * getMasse());
    konstante[Konstante::Lambda2] = (- konstante[Konstante::Daempfer] + sqrt(konstante[Konstante::Delta])) / (2 * getMasse());

    konstante[Konstante::C1] = (konstante[Konstante::Lambda2] * FieldSizes::BallYStartPosition) / (konstante[Konstante::Lambda2] - konstante[Konstante::Lambda1]);
    konstante[Konstante::C2] = FieldSizes::BallYStartPosition - konstante[Konstante::C1];

}

double Ball::yHomogen(double time)
{
    return konstante[Konstante::C1] * exp(-konstante[Konstante::Lambda1] * time) + konstante[Konstante::C2] * exp(-konstante[Konstante::Lambda2] * time);
}

double Ball::yPartikular(double dudx, double u)
{
    return (getMasse() * M_G + konstante[Konstante::Daempfer] * dudx + konstante[Konstante::Feder] * (konstante[Konstante::L0] - u)) / (- konstante[Konstante::Feder]);
}

double Ball::gradientY(double time)
{
    return -konstante[Konstante::Lambda1] * konstante[Konstante::C1] * exp(-konstante[Konstante::Lambda1] * time) - konstante[Konstante::Lambda2] * konstante[Konstante::C2] * exp(-konstante[Konstante::Lambda2] * time);
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
    this -> konstante[Konstante::C1] = 0;
    this -> konstante[Konstante::C2] = 0;
    this -> konstante[Konstante::C3] = 0;
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
