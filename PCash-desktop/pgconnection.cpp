#include "pgconnection.h"
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "INIReader.h"

bool PgConnection::setConfig()
{
    INIReader reader("config/db.ini");
    if (reader.ParseError() < 0) {
        return false;
    }
    QString password = QString::fromStdString(reader.Get("database","password",""));
    QString user = QString::fromStdString(reader.Get("database","user",""));
    QString database = QString::fromStdString(reader.Get("database","database",""));
    QString hostname = QString::fromStdString(reader.Get("database","hostname",""));
    int port = reader.GetInteger("database","port",5432);
    if(QSqlDatabase::contains("financeiro")){
        QSqlDatabase db = QSqlDatabase::database("financeiro",false);
        if(db.isOpen()){
            db.close();
        }
        QSqlDatabase::removeDatabase("financeiro");
    }
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL","financeiro");
    db.setDatabaseName(database);
    db.setHostName(hostname);
    db.setUserName(user);
    db.setPassword(password);
    db.setPort(port);
    return true;
}

PgConnection::PgConnection()
{

}

bool PgConnection::open()
{
    if(!setConfig()){
        return false;
    }
    QSqlDatabase db = QSqlDatabase::database("financeiro");
    if(db.isOpen()){
        return true;
    }
    else{
        return false;
    }

}

QSqlDatabase PgConnection::getDb()
{
    return QSqlDatabase::database("financeiro");
}

