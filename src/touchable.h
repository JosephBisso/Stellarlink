#ifndef TOUCHABLE_H
#define TOUCHABLE_H

#include <QObject>
#include <QPointer>
#include <qqml.h>
#include <QPolygonF>
#include <QDebug>
#include <QMap>

#include "STElement.cpp"

class Touchable : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double pos_x READ getPos_x NOTIFY pos_xChanged)
    Q_PROPERTY(double pos_y READ getPos_y NOTIFY pos_yChanged)
    Q_PROPERTY(double velocityX READ getVelocityX NOTIFY velocityXChanged)
    Q_PROPERTY(double velocityY READ getVelocityY NOTIFY velocityYChanged)
    Q_PROPERTY(double heigth READ getHeigth NOTIFY heigthChanged)

private:
    double pos_x;
    double pos_y;
    double velocityX;
    double velocityY;
    double heigth;
    double masse;
    STElement type;

public:
    explicit Touchable(QObject *parent = nullptr);

//    virtual void equation(double d = 0) = 0;

    void setPos_x(double newPos_x);
    double getPos_x() const;

    double getPos_y() const;
    void setPos_y(double newPos_y);

    double getVelocityX() const;
    void setVelocityX(double newVelocity);

    double getVelocityY() const;
    void setVelocityY(double newVelocityY);
    void setVelocities(double velocityX, double velocityY);

    STElement getType() const;
    void setType(STElement newType);

    double getMasse() const;
    void setMasse(double newMasse);

    double getHeigth() const;
    void setHeigth(double newHeigth);

signals:
    void pos_xChanged();

    void pos_yChanged();

    void velocityXChanged();
    void velocityYChanged();

    void heigthChanged();

public slots:
    void move(double dx, double dy);

    virtual bool touched(Touchable* touchable) = 0;
};

#endif // TOUCHABLE_H
