#ifndef STELLARENGINE_H
#define STELLARENGINE_H

#include <QObject>

#include "ball.h"

class StellarEngine : public QObject
{
    Q_OBJECT


public:
    explicit StellarEngine(QObject *parent = nullptr);

    void computeFall(Ball* ball);

signals:

public slots:


};

#endif // STELLARENGINE_H
