#ifndef LIGHTSENSECONS_H
#define LIGHTSENSECONS_H

#include <QtCore>


class LightsenseCons : public QThread
{
    Q_OBJECT
public:
   LightsenseCons();

public:
    void run() override;


};

#endif // LIGHTSENSECONS_H
