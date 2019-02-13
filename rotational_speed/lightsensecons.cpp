#include "lightsensecons.h"
#include "lightsenseconstants.h"
#include <stdio.h>



LightsenseCons::LightsenseCons() {
    QThread::currentThread()->setPriority(QThread::LowestPriority);

}

void LightsenseCons :: run() {

    int countms=0;
    long countms_startdiff_relation=0;
    long countms_enddiff_relation=0;
    long hundredth=0;
    long countrps=0;
    int countmsprevious=0;
    long i=0, j=0;
    long lux;
    long diffms;
    long anzahl=0;

    while(1) {
        usedBytesLightsensor.acquire();
        diffms=buffer[i % BufferSize];
        lux=buffer[(i+1) % BufferSize];
        freeBytesLightsensor.release();

        printf("Timediff: %ld \n", diffms);
        //printf("Aktuelle Beleuchtungsstärke in Lux:%ld \n",lux);

        countrps += 1;
        countmsprevious = countms;
        if (diffms < TIMEOVERFLOW) //timeoverflow rps
           countms += diffms;
        if ((countms >= 1000) && (countms != countmsprevious)) //count diffms for 1000ms, then calculate rounds per second
        {
            //write to sqlite-database queue
            anzahl += 1;

//            printf("\t\t\trps:\t\t\t%d\n", countrps-1);
//            printf("\t\t\hundredth:\t\t%d\n", (1000-countmsprevious)*100/(countms-countmsprevious));
//            printf("\t\t\tnew start countms: \t%d\n", countms-1000);
              //printf("\t\t\tAnzahl Messungen seit Beginn: %ld\n ", anzahl);
              qDebug() << "\t\t\tAnzahl Messungen seit Beginn:" << anzahl;
//            printf("\tUmdrehungen pro Sekunde: " CYAN "%d,%02d\n\n" RESET,  countrps-1, (1000-countmsprevious)*100/(countms-countmsprevious));

            countms_enddiff_relation = 1000 - (long)(((countms-1000)%1000)*1000/(countms-countmsprevious)); //Verhaeltnis(!) letzte Messung von letztem Wert bis TIMEOVERFLOW zu Differenz des letzten Werts

            if ((countms-countmsprevious) >= 1000)
            {
                qDebug() << "??????????????????????????????????????????????????";
                hundredth = (countms_enddiff_relation + countms_startdiff_relation)/(10*(countms/1000));
                if (hundredth<100)
                    countrps -= 1;
                hundredth = hundredth % 100;

            } else if ((countms_enddiff_relation + countms_startdiff_relation)>=1000) //Verhaeltnis(!) zwischen 0-1 ist größer 1 (durch Faktor 1000 also größer 1000!)
            {
                qDebug() << "==================================================";
                hundredth = (countms_startdiff_relation + countms_enddiff_relation - 1000)/10;
            } else
            {
                countrps -= 1;
                hundredth = (countms_enddiff_relation + countms_startdiff_relation)/10;

            }
            freeBytesSQL.acquire();
            bufferSQL[j % BufferSize] = countrps;
            bufferSQL[(j+1) % BufferSize] =  hundredth;
            bufferSQL[(j+2) % BufferSize] =  anzahl;
            usedBytesSQL.release();
            j = (j+3) % 1000000;


            countrps = 0;
            countms_startdiff_relation = (long)(((countms-1000)%1000)*1000/(countms-countmsprevious));
            countms = countms-countms/1000*1000;

        } else if (countms == countmsprevious)
        {
            printf("\tTIMEOVERFLOW\n");
            countrps = 0;
            countms = 0;
        }
        //i += 1;
        i = (i+2) % 1000000;
    }



}
