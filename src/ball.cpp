#include "ball.h"


Ball::Ball(double radius, QObject *parent) : Touchable(parent)
{
    this -> radius = radius;
    this -> setType(STElement::Ball);
    this -> setPos_x(FieldSizes::BallXPosition);
    this -> setPos_y(FieldSizes::BallYStartPosition);
}

void Ball::equation()
{

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
