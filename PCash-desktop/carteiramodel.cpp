#include "carteiramodel.h"
#include <QDebug>
#include <QAbstractTableModel>
#include <QSqlQuery>
#include "pgconnection.h"
#include <QSqlField>
#include <vector>

void CarteiraModel::setConn(PgConnection *conn)
{
    this->conn = conn;
}

CarteiraModel::CarteiraModel()
{


}

bool CarteiraModel::refresh()
{
    emit layoutAboutToBeChanged();
    data_table.clear();
    query = QSqlQuery("SELECT cod_neg, bdi, total, investido FROM public.carteira_atual",conn->getDb());
    record = query.record();
    for(int c = 0; c < record.count(); c++){
            colunas.append(record.fieldName(c));
    }
    while(query.next()){
        std::vector<QVariant> row;
        for (int i=0; i< query.record().count(); i++){
            row.push_back(query.value(i));
            if(i == COLUNA::INVESTIDO){
               QString
                totalInvestido += query.value(i).toInt();

            }
        }
        data_table.push_back(row);
    }
    inserirColunaPercentual();
    emit layoutChanged();
    return true;
}

int CarteiraModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return data_table.size();
}

int CarteiraModel::columnCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : colunas.size();
}

QVariant CarteiraModel::data(const QModelIndex &item, int role) const
{
    if(role == Qt::DisplayRole)
    return data_table.at(item.row()).at(item.column());
    else return QVariant();
}


QVariant CarteiraModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal){
        if (role == Qt::DisplayRole){
            return colunas.at(section);
        }
    }
    return QAbstractItemModel::headerData(section, orientation, role);;
}

bool CarteiraModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{

}

bool CarteiraModel::insertColumns(int column, int count, const QModelIndex &parent)
{
    beginInsertColumns(parent, column, column + count - 1);

    endInsertColumns();
        return true;
}

bool CarteiraModel::removeColumns(int column, int count, const QModelIndex &parent)
{

}

void CarteiraModel::inserirColunaPercentual()
{
    colunas.append("%");
    for(auto &dt : data_table){
        double percentual = 100*(dt.at(COLUNA::INVESTIDO).toDouble()/double(totalInvestido));
        dt.push_back(percentual);
    }
}
