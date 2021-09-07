#include "ball.h"


Ball::Ball(QObject *parent) : Touchable(parent)
{
    this -> setType(STElement::Ball);
}

Ball::Ball(double radius) : Touchable()
{
    this -> radius = radius;
    this -> setType(STElement::Ball);
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

bool Ball::touched(Touchable *touchable)
{
    if (nullptr == touchable) return false;
    if (this == touchable) return false;

    if (touchable -> getType() == STElement::Ball) {
        QPointer<Ball> ball = dynamic_cast<Ball*>(touchable);
        return pow(ball -> getPos_x() - this -> getPos_x(), 2.0) + pow(ball -> getPos_y() - this -> getPos_y(), 2.0) <= pow(this -> getRadius() + ball -> getRadius(), 2.0);
    }
    return pow(touchable -> getPos_x() - this -> getPos_x(), 2.0) + pow(touchable -> getPos_y() - this -> getPos_y(), 2.0) <= pow(this -> getRadius(), 2.0);
}
