#include "touchable.h"

STElement Touchable::getType() const
{
    return type;
}

void Touchable::setType(STElement newType)
{
    type = newType;
}

double Touchable::getMasse() const
{
    return masse;
}

void Touchable::setMasse(double newMasse)
{
    masse = newMasse;
}

Touchable::Touchable(QObject *parent) : QObject(parent)
{
    this -> pos_x = 0;
    this -> pos_y = 0;
    this -> velocity = 0;
}

void Touchable::setPos_x(double newPos_x)
{
    pos_x = newPos_x;

    emit pos_xChanged();
}

double Touchable::getPos_x() const
{
    return pos_x;
}

double Touchable::getPos_y() const
{
    return pos_y;
}

void Touchable::setPos_y(double newPos_y)
{
    pos_y = newPos_y;

    emit pos_yChanged();
}

double Touchable::getVelocity() const
{
    return velocity;
}

void Touchable::setVelocity(double newVelocity)
{
    velocity = newVelocity;

    emit velocityChanged();
}

void Touchable::move(double dx, double dy)
{
    this -> setPos_x(this -> getPos_x() + dx);
    this -> setPos_y(this -> getPos_y() + dy);
}


