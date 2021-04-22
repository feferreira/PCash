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
    query = QSqlQuery("select * from carteira_atual",conn->getDb());
    record = query.record();
    for(int c = 0; c < record.count()+COLUNAS_ADICIONAIS; c++){
        if(!(c >= record.count())){
            colunas.append(record.fieldName(c));
        }
        else{
            colunas.append("");
        }
    }
    while(query.next()){
        std::vector<QVariant> row;
        for (int i=0; i< query.record().count(); i++){
            row.push_back(query.value(i));
        }
        data_table.push_back(row);
    }
    //qDebug() << record.count() << query.size();
}

int CarteiraModel::rowCount(const QModelIndex &parent) const
{
    return query.size();
}

int CarteiraModel::columnCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : record.count();
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
        for (int c = 0; c < count; ++c) {
            QSqlField field;
            field.setReadOnly(true);
            field.setGenerated(false);
            record.insert(column, field);
            colunas.push_front(record.fieldName(c));
        }
    endInsertColumns();
        return true;
}

bool CarteiraModel::removeColumns(int column, int count, const QModelIndex &parent)
{

}
