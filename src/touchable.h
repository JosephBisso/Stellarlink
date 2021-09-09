#ifndef TOUCHABLE_H
#define TOUCHABLE_H

#include <QObject>
#include <QPointer>
#include <qqml.h>
#include <QPolygonF>
#include <QDebug>

#include "STElement.cpp"

class Touchable : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double pos_x READ getPos_x WRITE setPos_x NOTIFY pos_xChanged)
    Q_PROPERTY(double pos_y READ getPos_y WRITE setPos_y NOTIFY pos_yChanged)
    Q_PROPERTY(double velocity READ getVelocity WRITE setVelocity NOTIFY velocityChanged)

private:
    double pos_x;
    double pos_y;
    double velocity;
    double masse;
    STElement type;

public:
    explicit Touchable(QObject *parent = nullptr);

//    virtual void equation() = 0;

    void setPos_x(double newPos_x);
    double getPos_x() const;

    double getPos_y() const;
    void setPos_y(double newPos_y);

    double getVelocity() const;
    void setVelocity(double newVelocity);

    STElement getType() const;
    void setType(STElement newType);

    double getMasse() const;
    void setMasse(double newMasse);

signals:
    void pos_xChanged();

    void pos_yChanged();

    void velocityChanged();

public slots:
    void move(double dx, double dy);

    virtual bool touched(Touchable* touchable) = 0;
};

#endif // TOUCHABLE_H
