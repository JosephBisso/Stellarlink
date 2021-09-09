#include "floor.h"

Floor::Floor(double rauheit, QObject *parent) : Touchable(parent)
{
    this -> rauheit = rauheit;
    this -> setType(STElement::Floor);
    this -> randomFactor = rand() % 100;
    this -> randomFactor2 = rand() % 100;
    this -> randomFactor3 = rand() % 100;
    createFloorLine();
}

const QPolygonF &Floor::getFloorLine() const
{
    return floorLine;
}

void Floor::createFloorLine()
{
    for (int i = 0; i <= FieldSizes::Width; i++) {
        this -> floorLine << QPointF(i, equation(i));
    }

    emit floorLineChanged();

//    qDebug() << this -> floorLine;
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

    return this -> floorLine.at(touchable -> getPos_x()).y() <= touchable -> getPos_y();
}

double Floor::equation(double x)
{
    return 40 * sin (0.00015 * this -> randomFactor3 * M_PI * x) + 40 * sin (0.0001 * this -> randomFactor2 * M_PI * x) + 40 * sin (this -> randomFactor * M_PI * 0.0002 * x) + FieldSizes::FloorMittelPosition;
}
