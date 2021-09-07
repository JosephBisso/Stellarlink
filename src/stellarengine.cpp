#include "stellarengine.h"

StellarEngine::StellarEngine(QObject *parent) : QObject(parent)
{

}

void StellarEngine::computeFall(Ball* ball)
{
    for (int i = 0; i < 100; i++) {ball -> move(5, 5);}
}
