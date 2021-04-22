#ifndef PGCONNECTION_H
#define PGCONNECTION_H

class QSqlDatabase;
class QSqlQuery;

class PgConnection
{

private:
    bool setConfig();
public:
    PgConnection();
    bool open();
    QSqlDatabase getDb();
};

#endif // PGCONNECTION_H
