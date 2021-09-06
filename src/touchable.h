#ifndef TOUCHABLE_H
#define TOUCHABLE_H

#include <QObject>

class Touchable : public QObject
{
    Q_OBJECT
public:
    explicit Touchable(QObject *parent = nullptr);

signals:

};

#endif // TOUCHABLE_H
