#include "sqlcons.h"
#include "lightsenseconstants.h"

#include <sqlite3.h>

SqlCons::SqlCons(QString sqlitepath)
{
    this->setSqlitePath(sqlitepath);
    qDebug() << "KONSTRUKTOR";
    this->m_dbok = false;
    QThread::currentThread()->setPriority(QThread::LowestPriority);


}

SqlCons::~SqlCons()
{
    this->m_db.close();
}

void SqlCons::run()
{
    long j=0;
    long rps=0;
    long hundertstel=0;
    long anzahl=0;
    bool success=0;
    QString m_string;
    int table_counter=0;
    bool querySuccessful = false;

    success = this->createConnection();
    QSqlQuery query(this->m_db); //first Database needs to be opened!

    if (success == true)
    {



        if (this->m_db.isOpen())
            qDebug() << "IS OPEN!";


        while (querySuccessful==false)
        {
            table_counter += 1;
            m_string = "create table rpmentry_";
            m_string.append(QString::number(table_counter).rightJustified(5,'0'));
            m_string.append(" (id long primary key, ");
            m_string.append("count INTEGER, ");
            m_string.append("rpslowerend INTEGER, ");
            m_string.append("hundredth INTEGER)");
            querySuccessful = query.exec(m_string.toUtf8().constData());
        }
        qDebug() << m_string.toUtf8().constData();
        if (!querySuccessful)
            qDebug() << "Table rpmentry_" << QString::number(table_counter).rightJustified(5,'0') << "could not be created!";
        this->m_dbok = true;

    }

    while(1){
        usedBytesSQL.acquire();
        rps = bufferSQL[j % BufferSize];
        hundertstel =  bufferSQL[(j+1) % BufferSize];
        anzahl =  bufferSQL[(j+2) % BufferSize];
        freeBytesSQL.release();

        if (this->m_dbok)
        {
            //insert into Database
            m_string = "INSERT INTO rpmentry_";
            m_string.append(QString::number(table_counter).rightJustified(5,'0'));
            m_string.append("(count, rpslowerend, hundredth) VALUES (:count, :rpslowerend, :hundredth)");
            printf("%s\n",m_string.toUtf8().constData());
            query.prepare(m_string.toUtf8().constData());
            qDebug().noquote() << "\tUmdrehungen pro Sekunde:" << CYAN << QString("%1.%2").arg(rps,2,10,QChar(' ')).arg(hundertstel,2,10,QChar('0')) << RESET;
            //query.prepare("INSERT INTO rpmentry (count, rpslowerend, hundredth)"
                          //"VALUES (:count, :rpslowerend, :hundredth)");
            query.bindValue(":count", (qlonglong)anzahl);
            query.bindValue(":rpslowerend",  (qlonglong)rps);
            query.bindValue(":hundredth", (qlonglong)hundertstel);
            if(!query.exec())
               {
                    qDebug() << "add rpm error:  "
                             << query.lastError();
               }
        } else
        {
            //print to console
            qDebug() << "\t\t\trps:\t\t\t" << rps;
            //printf("\t\t\tzehntel:\t\t%d\n", (1000-countmsprevious)*10/(countms-countmsprevious));
            qDebug() << "\t\t\thundertstel:\t\t\t" << hundertstel;
            qDebug() << "\t\t\tAnzahl Messungen seit Beginn:" << anzahl;
            qDebug() << "\tNr:" << RED << anzahl << RESET;
            qDebug() << "\tUmdrehungen pro Sekunde:" << CYAN << rps << "." << QString("%1").arg(hundertstel,2,2,QChar('0')) << RESET;
            //printf("\tNr:" RED "%02ld\n" RESET "\tUmdrehungen pro Sekunde: " CYAN "%ld,%02ld\n\n" RESET,  anzahl, rps, hundertstel);
        }

        j = (j+3) % 1000000;

    }
}

void SqlCons::setSqlitePath(QString sqlitepath)
{
    this->m_sqlitepath = sqlitepath;
}


QString SqlCons::getSqlitePath()
{
    return this->m_sqlitepath;
}

bool SqlCons::createConnection()
{
    this->m_db = QSqlDatabase::addDatabase("QSQLITE");
    this->m_db.setDatabaseName(this->getSqlitePath());

    if (!this->m_db.open()) {
        qWarning() << "Unable to establish a database connection.\n";

        return false;
    } else
        return true;
}
