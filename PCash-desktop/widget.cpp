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
#include "pgconnection.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , op(new Operacao)
    , carteiraModel (new CarteiraModel)
    , operacaoModel (new QSqlQueryModel)
    , proventoModel (new QSqlQueryModel)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->ui->dataOrdem->setDate(QDate::currentDate());
    this->ui->dataProvento->setDate(QDate::currentDate());
    getValoresDefault();
    op->setConn(conn);
    carteiraModel->setConn(conn);
    refreshModels();
    ui->proventoTableView->setCornerButtonEnabled(false);
    ui->proventoTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->proventoTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->operacaoTableView->setCornerButtonEnabled(false);
    ui->proventoTableView->setModel(proventoModel);
    ui->operacaoTableView->setModel(operacaoModel);
    ui->carteiraTableView->setModel(carteiraModel);
    ui->operacaoTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->operacaoTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    this->ui->removeOperacao->setEnabled(false);
    this->ui->removeProvento->setEnabled(false);
}

void Widget::setConnection(PgConnection *conn)
{
    this->conn = conn;
}

void Widget::refreshModels()
{
    carteiraModel->refresh();
    operacaoModel->setQuery("select * from historico_operacao",conn->getDb());
    proventoModel->setQuery("select * from historico_provento",conn->getDb());
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
    if(ordem.insertOrdem(data,papel,quantidade,preco,corretora,operacao)){
        refreshModels();
        this->ui->statusLabel->setText("operação inserida!");
    }
    else{
        this->ui->statusLabel->setText("falha inserindo operação");
    }
}

void Widget::on_insereProvento_clicked()
{
    QString papel = this->ui->linePapelProvento->text();
    unsigned int corretora = this->ui->comboCorretoraProventos->currentData().toInt();
    unsigned int preco = this->ui->valorProvento->value()*100;
    unsigned int tipo = this->ui->comboTipoProvento->currentData().toInt();
    QString data = this->ui->dataProvento->date().toString(Qt::DateFormat::ISODate);
    Proventos p;
    if(p.insertProvento(data,papel,preco,corretora,tipo)){
        refreshModels();
        this->ui->statusLabel->setText("provento inserido!");
    }
    else{
        this->ui->statusLabel->setText("falha inserindo provento");
    }

}

void Widget::on_removeProvento_clicked()
{
    int row =  this->ui->proventoTableView->currentIndex().row();
    int proventoId = this->ui->proventoTableView->model()->index(row,0).data().toInt();
    Proventos p;
    if(p.removeProvento(proventoId)){
        this->ui->statusLabel->setText("provento removido!");
    }
    else{
        this->ui->statusLabel->setText("Falha removendo provento");
    }
    this->ui->removeProvento->setEnabled(false);
    refreshModels();
}

void Widget::on_proventoTableView_clicked(const QModelIndex &index)
{
    if(index.isValid()){
        this->ui->removeProvento->setEnabled(true);
    }
}

void Widget::on_removeOperacao_clicked()
{
    int row =  this->ui->operacaoTableView->currentIndex().row();
    int operacaoId = this->ui->operacaoTableView->model()->index(row,0).data().toInt();
    Operacao o;
    if(o.removeOperacao(operacaoId)){
        this->ui->statusLabel->setText("operação removida!");
    }
    else{
        this->ui->statusLabel->setText("Falha removendo operação");
    }
    this->ui->removeOperacao->setEnabled(false);
    refreshModels();
}



void Widget::on_operacaoTableView_clicked(const QModelIndex &index)
{
    if(index.isValid()){
        this->ui->removeOperacao->setEnabled(true);
    }
}
