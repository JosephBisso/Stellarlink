#ifndef FLOOR_H
#define FLOOR_H

#include "touchable.h"

class Floor : public Touchable
{
    Q_OBJECT
    Q_PROPERTY(double rauheit READ getRauheit WRITE setRauheit NOTIFY rauheitChanged)
    Q_PROPERTY(QPolygonF floorLine READ getFloorLine NOTIFY floorLineChanged)

private:
    double rauheit;

    QPolygonF floorLine;

    FloorType floorType;

public:
    explicit Floor(double rauheit, QObject *parent = nullptr);

    double equation(double x);

    double getRauheit() const;
    void setRauheit(double newRauheit);

    FloorType getFloorType() const;
    void setFloorType(FloorType newFloorType);

    const QPolygonF &getFloorLine() const;
    void createFloorLine();
    int randomFactor;
    int randomFactor2;
    int randomFactor3;

signals:
    void rauheitChanged();

    void floorLineChanged();

public slots:
    bool touched(Touchable* touchable);
};

#endif // FLOOR_H
