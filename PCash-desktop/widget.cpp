#include "widget.h"
#include "ui_widget.h"
#include "corretora.h"
#include "operacao.h"
#include "data.h"
#include "proventos.h"
#include <QMap>
#include <QString>
#include <QSqlQueryModel>
#include <QAbstractTableModel>
#include "carteiramodel.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , op(new Operacao)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->ui->dataOrdem->setDate(QDate::currentDate());
    this->ui->dataProvento->setDate(QDate::currentDate());
    getValoresDefault();
    op->setConn(conn);
    ui->operacaoTableView->setModel(op->getModel());
    ui->operacaoTableView->show();
}

void Widget::setConnection(PgConnection *conn)
{
    this->conn = conn;
}

Widget::~Widget()
{
    delete ui;
}

bool Widget::getValoresDefault()
{
    Corretora c;
    Proventos p;
    p.setConn(conn);
    c.setConn(conn);
    c.getListaCorretora();
    for (auto &i : c.listaCorretora) {
        this->ui->comboCorretoraOrdem->addItem(static_cast<QString>(i.first), static_cast<int>(i.second));
        this->ui->comboCorretoraProventos->addItem(static_cast<QString>(i.first), static_cast<int>(i.second));
    }
    p.getListaTipoProvento();
    for(auto &i : p.listaTipoProvento){
        this->ui->comboTipoProvento->addItem(static_cast<QString>(i.first),static_cast<int>(i.second));
    }
    return true;
}


void Widget::on_InsereOrdem_clicked()
{

    QString papel = this->ui->linePapel->text();
    unsigned int corretora = this->ui->comboCorretoraOrdem->currentData().toInt();
    unsigned int quantidade = this->ui->spinQuantidade->value();
    unsigned int preco = this->ui->precoOrdem->value()*100;
    unsigned int operacao{0};
    QString data = this->ui->dataOrdem->date().toString(Qt::DateFormat::ISODate);
    if(this->ui->radioCompra->isChecked()){
        operacao = 1;
    }
    else if(this->ui->radioVenda->isChecked()){
        operacao = 2;
    }
    Operacao ordem;
    ordem.setConn(conn);
    ordem.insertOrdem(data,papel,quantidade,preco,corretora,operacao);
    this->ui->dataOrdem->setDate(QDate::currentDate());

}

void Widget::on_insereProvento_clicked()
{
    QString papel = this->ui->linePapelProvento->text();
    unsigned int corretora = this->ui->comboCorretoraProventos->currentData().toInt();
    unsigned int preco = this->ui->valorProvento->value()*100;
    unsigned int tipo = this->ui->comboTipoProvento->currentData().toInt();
    QString data = this->ui->dataProvento->date().toString(Qt::DateFormat::ISODate);
    Proventos p;
    p.insertProvento(data,papel,preco,corretora,tipo);

}
