#include "floor.h"

Floor::Floor(QObject *parent) : Touchable(parent)
{
    this -> setType(STElement::Floor);
}

Floor::Floor(double rauheit) : Touchable()
{
    this -> rauheit = rauheit;
    this -> setType(STElement::Floor);
}

FloorType Floor::getFloorType() const
{
    return floorType;
}

void Floor::setFloorType(FloorType newFloorType)
{
    floorType = newFloorType;
}

double Floor::getRauheit() const
{
    return rauheit;
}

void Floor::setRauheit(double newRauheit)
{
    rauheit = newRauheit;

    emit rauheitChanged();
}

bool Floor::touched(Touchable *touchable)
{
    if (nullptr == touchable) return false;
    if (this == touchable) return false;

    if (touchable -> getType() == STElement::Ball) {
        QPointer<Ball> ball = dynamic_cast<Ball*>(touchable);
        return pow(ball -> getPos_x() - this -> getPos_x(), 2.0) + pow(ball -> getPos_y() - this -> getPos_y(), 2.0) <= pow(ball -> getRadius(), 2.0);
    }

    return touchable -> getPos_x() == this -> getPos_x() && touchable -> getPos_y() == this -> getPos_y();
}
