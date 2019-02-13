#ifndef LIGHTSENSECONSTANTS_H
#define LIGHTSENSECONSTANTS_H

#include <QtCore>

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

//#define I2CSETUP
#define GPIOSETUP

#define BOUNCING 50
#define TIMEOVERFLOW 3000
#define FILEPATH "/home/pi/SimpleNodeJs/Db/MyDb.db"


extern const int DataSize;
extern const int BufferSize;
extern long buffer[];
extern long bufferSQL[];

extern QSemaphore freeBytesLightsensor;
extern QSemaphore usedBytesLightsensor;
extern QSemaphore freeBytesSQL;
extern QSemaphore usedBytesSQL;


#endif // LIGHTSENSECONSTANTS_H
