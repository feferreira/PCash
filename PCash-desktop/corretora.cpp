#include "corretora.h"
#include "pgconnection.h"
#include <QSqlQuery>
#include <map>
#include <QString>
#include <QVariant>

bool Corretora::getListaCorretora()
{
    QSqlQuery query(conn->getDb());
    if(!query.exec("select corretora_id, nome from corretora")){
        return false;
    }
    while(query.next()){
        listaCorretora.insert(std::pair<QString,int>(query.value(1).toString(),query.value(0).toInt()));
    }
    return true;
}
