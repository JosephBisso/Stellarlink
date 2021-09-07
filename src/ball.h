#ifndef BALL_H
#define BALL_H

#include "touchable.h"

class Ball : public Touchable
{

    Q_OBJECT
    Q_PROPERTY(double radius READ getRadius WRITE setRadius NOTIFY radiusChanged)
    Q_PROPERTY(double fuelle READ getFuelle WRITE setFuelle NOTIFY fuelleChanged)
    Q_PROPERTY(double health READ getHealth WRITE setHealth NOTIFY healthChanged)

private:
    double radius;
    double fuelle;
    double health;

public:
    explicit Ball(QObject *parent = nullptr);
    Ball(double radius);

    bool touched(Touchable* touchable);

    bool hit(double health);

    void equation();

    double getRadius() const;
    void setRadius(double newRadius);

    double getFuelle() const;
    void setFuelle(double newFuelle);

    double getHealth() const;
    void setHealth(double newHealth);

signals:
    void radiusChanged();

    void fuelleChanged();

    void healthChanged();

};

#endif // BALL_H
