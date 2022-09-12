#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QAbstractTableModel>

#include "mainwindow.h"
#include "buildmachines.h"

/*!
    \brief Класс модели хранения данных (MVC)
    \date Июнь 2022 года

    Дочерний класс абстрактного класса QAbstractTableModel.
    Организует хранение и обработку данных получаемых из БД данных.
*/
class TableModel: public QAbstractTableModel
{
    Q_OBJECT

    int rows;

public:

    ///Конструктор
    explicit TableModel(QObject *parent = nullptr);

public:
    ///Метод для установки количества строк при отображении в таблице
    int rowCount(const QModelIndex &parent) const override;
    ///Метод для установки количества колонок при отображении в таблице
    int columnCount(const QModelIndex &parent) const override;
    ///Метод для установки значения каждой ячейки модели
    QVariant data(const QModelIndex &index, int role) const override;

    ///Метод для добавления записи(строки) типа BuildMachines в QList
    void addData(const BuildMachines &tempBuildClass);
    ///Метод для очистки контейнера (QList)
    void clearTable();

private:
    ///Контейнер для хранения записей о строительной технике (основные данные)
    QList<BuildMachines> mainList;

    // QAbstractItemModel interface
public:
    ///Метод для установки заголовков таблицы
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    // QAbstractItemModel interface
public:

    ///Метод для подгрузки записей на экран
    void fetchMore(const QModelIndex &parent) override;

    ///Метод для проверки возможности подгрузки записей из БД
    bool canFetchMore(const QModelIndex &parent) const override;
};

#endif // TABLEMODEL_H
