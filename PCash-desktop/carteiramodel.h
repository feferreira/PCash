#ifndef CARTEIRAMODEL_H
#define CARTEIRAMODEL_H

#include <QAbstractTableModel>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QModelIndex>

class PgConnection;

enum COLUNA{
    COD_NEG = 0,
    BDI,
    TOTAL,
    INVESTIDO,
    PERCENTUAL
};

class CarteiraModel : public QAbstractTableModel
{
    QSqlRecord record;
    QSqlQuery query;
    QStringList colunas; // nome das colunas
    std::vector<std::vector<QVariant>> data_table;
    QModelIndex last = QModelIndex();
    PgConnection *conn{nullptr};

public:
    int totalInvestido;
    void setConn(PgConnection *conn);;
    CarteiraModel();
    bool refresh();
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &item, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value,
                       int role = Qt::EditRole) override;

    bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;
    void inserirColunaPercentual();
};

#endif // CARTEIRAMODEL_H
