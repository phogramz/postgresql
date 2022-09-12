#ifndef DIALOGUPDATEDATA_H
#define DIALOGUPDATEDATA_H

#include <QDialog>
#include <QRegExpValidator>

#include "mainwindow.h"


/*!
    \brief Класс диалогового окна для обновления записей
    \date Июнь 2022 года
*/

namespace Ui {
class DialogUpdateData;
}

class DialogUpdateData : public QDialog
{
    Q_OBJECT

public:
    ///Конструктор
    explicit DialogUpdateData(QWidget *parent = nullptr);
    ///Деструктор
    ~DialogUpdateData();
    QString getLine;
    //MainWindow w;

    void setId(QString Id);
    void setTechnicType(QString techicType);
    void setBrand(QString brand);
    void setPower(QString power);
    void setWeight(QString weight);
    void setProductYear(QString productYear);
    void setRentPrice(QString rentPrice);

protected:
    void changeEvent(QEvent *e);

private slots:
    ///Метод(слот) для обновления данных в БД по нажатию на кнопку
    void on_pushButton_clicked();

    ///Метод(слот) для настройки валидатора ввода параметра "год выпуска строительной техники"
    void on_lineEdit_productYear_update_textChanged(const QString &arg1);

private:
    ///Указатель на форму диалогового окна обновления данных
    Ui::DialogUpdateData *ui;

    ///Валидатор ввода для параметра "тип строительной техники"
    QRegExpValidator technicType_validator;
};

#endif // DIALOGUPDATEDATA_H
