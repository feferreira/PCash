#ifndef OPERACAO_H
#define OPERACAO_H
#include<iostream>
#include<QString>
#include"data.h"

class PgConnection;
class QSqlQuery;

class Operacao : public Data
{
    QSqlQuery* query{nullptr};
    unsigned int papel{0};
    unsigned int corretora{0};
    unsigned int quantidade{0};
    unsigned int preco{0};

    QString lastError;
public:
    Operacao();
    bool insertOrdem(QString data, QString papel, unsigned int quantidade, unsigned int preco, unsigned int corretora, unsigned int operacao);
    bool removeOperacao(int operacaoId);
};

#endif // OPERACAO_H
