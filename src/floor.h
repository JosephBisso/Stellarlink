#ifndef FLOOR_H
#define FLOOR_H

#include "touchable.h"
#include "ball.h"

class Floor : public Touchable
{
    Q_OBJECT
    Q_PROPERTY(double rauheit READ getRauheit WRITE setRauheit NOTIFY rauheitChanged)

private:
    double rauheit;

    FloorType floorType;

public:
    explicit Floor(QObject *parent = nullptr);
    Floor(double rauheit);

    void equation();

    bool touched(Touchable* touchable);

    double getRauheit() const;
    void setRauheit(double newRauheit);
    FloorType getFloorType() const;
    void setFloorType(FloorType newFloorType);

signals:
    void rauheitChanged();
};

#endif // FLOOR_H
