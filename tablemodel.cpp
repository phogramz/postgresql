#include "tablemodel.h"

#include <QList>
#include <QDebug>

TableModel::TableModel(QObject *parent) //определение конструктора
    : QAbstractTableModel(parent)
    , rows(20) //////////
{
      mainList = *new QList<BuildMachines>();
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return parent.isValid() ? 0 : rows;
    //return mainList.count(); // фиксировано 5 строк в таблице
    //если вы станете использовать скажем QList, то пишите return list.size();

}

int TableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return parent.isValid() ? 0 : 7;
    //return 7; // фиксировано 7 столбцов в таблице
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    int row = index.row();

    if (row >= mainList.size() || row < 0)
        return QVariant();

     QVariant value;
            switch ( role )
            {
                case Qt::DisplayRole: //string
                {
                    switch (index.column())
                    {
                        case 0: {
                            value = this->mainList.at(index.row()).getId();
                            break;
                        }
                        case 1: {
                            value = this->mainList.at(index.row()).getTechicType();
                            break;
                        }
                        case 2: {
                            value = this->mainList.at(index.row()).getBrand();
                            break;
                        }
                        case 3: {
                            value = this->mainList.at(index.row()).getPower();
                            break;
                        }
                        case 4: {
                            value = this->mainList.at(index.row()).getWeight();
                            break;
                        }
                        case 5: {
                            value = this->mainList.at(index.row()).getProductYear();
                            break;
                        }
                        case 6: {
                            value = this->mainList.at(index.row()).getRentPrice();
                            break;
                        }
                    }
                }
                break;

                case Qt::UserRole: //data
                {
                    value = this->mainList.at(index.row()).getId();
                }
                break;

                default:
                    break;
            }

        return value;
}

void TableModel::addData(const BuildMachines &tempBuildClass)
{
    beginResetModel();
    mainList.append(tempBuildClass);

    endResetModel();
}

void TableModel::clearTable()
{
    beginResetModel();
    mainList.clear(); //очистка контейнера

    endResetModel();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
             switch (section) {
             case 0:
                 return QString("Номер");
             case 1:
                 return QString("Тип техники");
             case 2:
                 return QString("Производитель");
             case 3:
                 return QString("Мощность");
             case 4:
                 return QString("Масса");
             case 5:
                 return QString("Год выпуска");
             case 6:
                 return QString("Цена аренды");
             }
         }
    return QVariant();
}

void TableModel::fetchMore(const QModelIndex &parent)
{
    if (parent.isValid())
        return;

    qDebug() << "Fetch more";

    const int start = rows;

    const int remainder = mainList.size() - start;
    const int itemsToFetch = qMin(20, remainder);

    if (itemsToFetch <= 0)
        return;

    beginInsertRows(QModelIndex(), start, start + itemsToFetch - 1);

    rows += itemsToFetch;

    endInsertRows();
}

bool TableModel::canFetchMore(const QModelIndex &parent) const
{
    if (parent.isValid())
        return false;
    qDebug() << "Can fetch more";
    return (rows < mainList.count());
}

