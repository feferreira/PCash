#ifndef DATA_H
#define DATA_H

class PgConnection;

class Data
{
protected:
    PgConnection *conn{nullptr};
public:
    void setConn(PgConnection *conn);
};

#endif // DATA_H
