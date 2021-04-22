#include "widget.h"

#include <QApplication>
#include "pgconnection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PgConnection conn;
    if(conn.open()){
        Widget w;
        w.setConnection(&conn);
        w.show();
        return a.exec();
    }
    return -1;
}
