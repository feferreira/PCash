#include "operacao.h"
#include <QSqlQuery>
#include "pgconnection.h"
#include <QDate>
#include <QSqlError>
#include <QDebug>
#include "carteiramodel.h"
#include <QSqlQueryModel>

Operacao::Operacao() : query(new QSqlQuery)
{

}

bool Operacao::insertOrdem(QString data, QString papel, unsigned int quantidade, unsigned int preco, unsigned int corretora, unsigned int operacao)
{
    unsigned int papel_id{0};
    QSqlQuery query(conn->getDb());
    query.prepare("select papel_id from papel where cod_neg = :nome");
    query.bindValue(":nome",papel.toUpper());
    if(!query.exec()){
        qDebug() << "query para codneg nao executou";
        return false;
    }
    if(query.next()){ 
        papel_id = query.value(0).toInt();
    }
    else{
        qDebug() << "não encontrou papel_id";
        return false;
    }
    query.prepare("INSERT INTO public.operacao (data_pregao, papel, corretora, tipo, quantidade, preco_unitario) "
                  "VALUES(:data, :papel, :corretora, :tipo, :quantidade, :preco)");
    query.bindValue(":data", data);
    query.bindValue(":papel",papel_id);
    query.bindValue(":quantidade", quantidade);
    query.bindValue(":preco",preco);
    query.bindValue(":tipo",operacao);
    query.bindValue(":corretora", corretora);
    if(!query.exec()){
        qDebug() << query.lastError();
        qDebug() << "não executou query";
        return false;
    }
    return true;
}

bool Operacao::removeOperacao(int operacaoId)
{
    QSqlQuery query(conn->getDb());
    query.prepare("DELETE FROM public.operacao WHERE operacao_id = :operaId");
    query.bindValue(":operaId", operacaoId);
    if(!query.exec()){
        qDebug() << query.lastError().text();
        return false;
    }
    return true;
}
