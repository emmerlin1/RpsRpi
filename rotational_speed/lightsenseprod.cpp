#include "lightsenseprod.h"
#include "lightsenseconstants.h"
#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

LightsenseProd::LightsenseProd()
{
    QThread::currentThread()->setPriority(QThread::HighestPriority);

#ifdef I2CSETUP

    this->handle = wiringPiI2CSetup(0x23) ;
    wiringPiI2CWrite(handle,0x13);
#elif defined GPIOSETUP
    wiringPiSetup();                    // Init
    wiringPiISR(PIN_IN, INT_EDGE_FALLING, &(gpioInterrupt));  // Bind to interrupt
#endif
sleep(1)    ;
}

//void gpiointerrupt(void) {
//    printf("\t" YELLOW "INTERRUPT\n" RESET);
//}
#ifdef GPIOSETUP

void LightsenseProd::gpioInterrupt(void) {
    static long diffms=0;
    static long start=0;
    static long lux=0;
    static struct timeval timeval;
    static long i=0;

    if (start!=0)
    {
        gettimeofday(&timeval, NULL);
        diffms = ((long)timeval.tv_sec * 1000 + (long)timeval.tv_usec / 1000) - start;
        if (diffms > BOUNCING)
        {
            gettimeofday(&timeval, NULL);
            start = (long)timeval.tv_sec * 1000 + (long)timeval.tv_usec / 1000;
            freeBytesLightsensor.acquire();
            buffer[i % BufferSize] = diffms;
            buffer[(i+1) % BufferSize] = lux;
            usedBytesLightsensor.release();
            i = (i+2) % 1000000;
        } else
            qDebug() << "\t\t BOUNCING - DIFFMS not counted " << diffms;
    } else
    {
        gettimeofday(&timeval, NULL);
        start = (long)timeval.tv_sec * 1000 + (long)timeval.tv_usec / 1000;
        qDebug() << YELLOW << "\tSTARTED\n" << RESET;
    }

}
#endif

void LightsenseProd :: run()  {

    int word;
    long lux;
    long diffms=0;
    long start=0;
    struct timeval timeval;
    char toggle=0;
    long i=0;

    while(1) {
#ifdef I2CSETUP
        word=wiringPiI2CReadReg16(this->handle,0x00);
        lux=(long)(((word & 0xff00)>>8) | ((word & 0x00ff)<<8));

        if (toggle == 0 && lux>10000)
        {
            if (start!=0)
            {
                gettimeofday(&timeval, NULL);
                diffms = ((long)timeval.tv_sec * 1000 + (long)timeval.tv_usec / 1000) - start;
            }
            freeBytesLightsensor.acquire();
            buffer[i % BufferSize] = diffms;
            buffer[(i+1) % BufferSize] = lux;
            usedBytesLightsensor.release();
            i = (i+2) % 1000000;

            toggle = 1;
            //printf("\tAktuelle Beleuchtungsstärke in Lux:%ld \n",lux);
            gettimeofday(&timeval, NULL);
            start = (long)timeval.tv_sec * 1000 + (long)timeval.tv_usec / 1000;
            //printf("\twrite start: %ld\n", start);
            //printf("\twrite diffms: %ld\n", diffms);
            //if (start>0)


        } else if (toggle == 1 && lux<10000)
        {
            toggle = 0;
        }

        //usleep(1000);
        wiringPiI2CWrite(this->handle,0x13);
        usleep(15000);
        //i += 1;
#endif
    }

}
