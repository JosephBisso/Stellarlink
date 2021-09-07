#ifndef TOUCHABLE_H
#define TOUCHABLE_H

#include <QObject>
#include <QPointer>
#include <qqml.h>

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
    STElement type;

public:
    explicit Touchable(QObject *parent = nullptr);

    virtual bool touched(Touchable* touchable) = 0;

    void moveOnScreen();

    void setPos_x(double newPos_x);
    double getPos_x() const;

    double getPos_y() const;
    void setPos_y(double newPos_y);

    double getVelocity() const;
    void setVelocity(double newVelocity);

    STElement getType() const;
    void setType(STElement newType);

signals:
    void pos_xChanged();

    void pos_yChanged();

    void velocityChanged();

public slots:
    void move(double dx, double dy);

};

#endif // TOUCHABLE_H
