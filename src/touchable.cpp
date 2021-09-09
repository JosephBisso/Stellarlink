#include "touchable.h"

double Touchable::getVelocityY() const
{
    return velocityY;
}

void Touchable::setVelocityY(double newVelocityY)
{
    velocityY = newVelocityY;
}

void Touchable::setVelocities(double velocityX, double velocityY)
{
    this -> velocityX = velocityX;
    this -> velocityY = velocityY;
}

Touchable::Touchable(QObject *parent) : QObject(parent)
{
    this -> pos_x = 0;
    this -> pos_y = 0;
    this -> velocityX = 0;
    this -> velocityY = 0;
}

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

double Touchable::getVelocityX() const
{
    return velocityX;
}

void Touchable::setVelocityX(double newVelocity)
{
    velocityX = newVelocity;

    emit velocityXChanged();
}

void Touchable::move(double dx, double dy)
{
    this -> setPos_x(this -> getPos_x() + dx);
    this -> setPos_y(this -> getPos_y() + dy);
}


