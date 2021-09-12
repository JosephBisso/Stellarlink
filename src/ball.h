#ifndef BALL_H
#define BALL_H

#include "touchable.h"
#include "floor.h"

class Ball : public Touchable
{

    Q_OBJECT
    Q_PROPERTY(double radius READ getRadius WRITE setRadius NOTIFY radiusChanged)
    Q_PROPERTY(double fuelle READ getFuelle WRITE setFuelle NOTIFY fuelleChanged)
    Q_PROPERTY(double health READ getHealth WRITE setHealth NOTIFY healthChanged)
    Q_PROPERTY(QPolygonF ballPath READ getBallPath NOTIFY ballPathChanged)
    Q_PROPERTY(BallStates ballState READ getBallState NOTIFY statesChanged)

private:
    double radius;
    double fuelle;
    double health;

    QMap<Konstante, double> konstante;
    QPolygonF ballPath;

    BallStates ballState;
    BallLocation ballLocation;

    bool highTanResistant;

public:
    explicit Ball(double radius, QObject *parent = nullptr);

    bool hit(double health);

    void equation();
    double yHomogen(double time);
    double yPartikular(double dudx, double u);

    double getRadius() const;
    void setRadius(double newRadius);

    double getFuelle() const;
    void setFuelle(double newFuelle);

    double getHealth() const;
    void setHealth(double newHealth);

    const QPolygonF &getBallPath() const;
    void setBallPath(const QPolygonF &newBallPath);
    void trail();

    void initKonstante();
    double getL0() const;

    bool isAccelerating();
    bool isDecelerating();
    bool isSticking();
    bool moveByItself();
    void setBallState(BallStates newBallState);
    BallStates getBallState() const;
    void resetState();

    void setBallLocation(BallLocation newBallLocation);
    bool isLaunching();
    bool isFalling();
    bool isOnGround();

    bool isHighTanResistant();
    void setHighTanResistance(bool resistant);

signals:
    void radiusChanged();

    void fuelleChanged();

    void healthChanged();

    void ballPathChanged();

    int statesChanged();

public slots:
    bool touched(Touchable* touchable);

    void defineKonstante(double feder, double l0, double daempfer);

    void resetBallPath();
};

#endif // BALL_H
