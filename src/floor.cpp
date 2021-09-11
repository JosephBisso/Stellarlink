#include "floor.h"

Floor::Floor(double rauheit, QObject *parent) : Touchable(parent)
{
    this -> rauheit = rauheit;
    this -> setType(STElement::Floor);
    this -> randomFactor = rand() % 100;
    this -> randomFactor2 = rand() % 100;
    this -> randomFactor3 = rand() % 100;
    createFloorLine(0);
}

const QPolygonF &Floor::getFloorLine() const
{
    return floorLine;
}

void Floor::createFloorLine(double ballAbsoluteXPosition)
{
    if (ballAbsoluteXPosition < FieldSizes::BallXPosition) {
        if (!this -> floorLine.isEmpty()) {this -> floorLine.remove(0, this -> floorLine.length());}
        for (int i = 0; i <= FieldSizes::Width; i++) {
            this -> floorLine << QPointF(i, equation(i));
        }

    } else {
        this -> floorLine.remove(0, this -> floorLine.length());

        int index = 0;
        double i = ballAbsoluteXPosition - FieldSizes::BallXPosition;

        while (i <= ballAbsoluteXPosition + FieldSizes::XSpaceRightOfBall) {
            this -> floorLine << QPointF(index++, equation(i));
            i++;
        }

//        qDebug() << "SHIFTED: P1:" <<this -> floorLine.at(200) << "SHIFTED: P2:" <<this -> floorLine.at(205);
//        qDebug() << this -> floorLine.length();
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

void Floor::resetFloorLine()
{
    this -> randomFactor = rand() % 100;
    this -> randomFactor2 = rand() % 100;
    this -> randomFactor3 = rand() % 100;
    createFloorLine(0);
}

double Floor::equation(double x)
{
    return 20 * sin (0.00015 * this -> randomFactor3 * M_PI * x) + 20 * sin (0.0001 * this -> randomFactor2 * M_PI * x) + 20 * sin (this -> randomFactor * M_PI * 0.0002 * x) + FieldSizes::FloorMittelPosition;
}
