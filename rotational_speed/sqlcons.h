#ifndef SQLCONS_H
#define SQLCONS_H

#include <QtCore>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

class SqlCons : public QThread
{
public:
    SqlCons(QString);
    ~SqlCons();
public:
    void run() override;
    void setSqlitePath (QString );
    QString getSqlitePath ();
private:
    bool createConnection();

    QString m_sqlitepath;
    QSqlDatabase m_db;
    bool m_dbok;
};

#endif // SQLCONS_H
