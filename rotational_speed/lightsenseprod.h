#ifndef LIGHTSENSEPROD_H
#define LIGHTSENSEPROD_H

#include <QtCore>
#include "lightsenseconstants.h"

#define PIN_IN         3    // GPIO 22 - header PIN 15


class LightsenseProd : public QThread
{
public:
    LightsenseProd();
    void run() override;
#ifdef  GPIOSETUP
    static void gpioInterrupt(void);
#endif
private:
    int handle;
};

#endif // LIGHTSENSEPROD_H
