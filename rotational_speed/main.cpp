#include <QCoreApplication>
#include <wiringPiI2C.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include "lightsenseprod.h"
#include "lightsensecons.h"
#include "sqlcons.h"

//#define FILEPATH "/tmp/sqlite.db"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //lightsensor* mlight = new lightsensor();
    LightsenseProd lightsenseproducer;
    LightsenseCons lightsenseconsumer;
    SqlCons sqlconsumer(FILEPATH);
    lightsenseproducer.start();
    lightsenseconsumer.start();
    sqlconsumer.start();
    lightsenseproducer.wait();
    lightsenseconsumer.wait();
    sqlconsumer.wait();

    //return a.exec();
    return 0;
}
