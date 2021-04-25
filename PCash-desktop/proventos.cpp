#include "proventos.h"
#include <QSqlQuery>
#include <QSqlError>
#include "pgconnection.h"
#include <QVariant>
#include <QDebug>

bool Proventos::getListaTipoProvento()
{
    QSqlQuery query(conn->getDb());
    if(!query.exec("SELECT tipo_provento_id, tipo FROM public.tipo_provento")){
        return false;
    }
    while(query.next()){
        listaTipoProvento.insert(std::pair<QString,int>(query.value(1).toString(),query.value(0).toInt()));
    }
    return true;

}

bool Proventos::insertProvento(QString data, QString papel, unsigned int valor, unsigned int corretora, unsigned int tipo)
{
    unsigned int papel_id{0};
    QSqlQuery query(conn->getDb());
    query.prepare("select papel_id from papel where cod_neg = :nome");
    query.bindValue(":nome",papel.toUpper());
    if(!query.exec()){
        return false;
    }
    if(query.next()){
        papel_id = query.value(0).toInt();
    }
    else{
        return false;
    }
    query.prepare("INSERT INTO public.provento "
                  "(data_provento, papel, corretora, total_provento, tipo_provento) "
                  "VALUES(:data, :papel, :corretora, :valor, :tipo)");
    query.bindValue(":data", data);
    query.bindValue(":papel",papel_id);
    query.bindValue(":valor",valor);
    query.bindValue(":corretora", corretora);
    query.bindValue(":tipo",tipo);
    if(!query.exec()){
        qDebug() << query.lastError().text();
        return false;
    }
    qDebug() << "deubom";
    return true;

}
