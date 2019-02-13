#include "lightsenseconstants.h"

const int DataSize = 100000;

const int BufferSize = 8192;

long buffer[BufferSize];
long bufferSQL[BufferSize];

QSemaphore freeBytesLightsensor(BufferSize);
QSemaphore usedBytesLightsensor;
QSemaphore freeBytesSQL(BufferSize);
QSemaphore usedBytesSQL;
