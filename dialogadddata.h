#ifndef DIALOGADDDATA_H
#define DIALOGADDDATA_H

#include <QDialog>
#include <QRegExpValidator>

#include "mainwindow.h"

/*!
    \brief Класс диалогового окна для добавления записей
    \date Июнь 2022 года
*/
namespace Ui {
class DialogAddData;
}

class DialogAddData : public QDialog
{
    Q_OBJECT

public:
    ///Конструктор
    explicit DialogAddData(QWidget *parent = nullptr);
    ///Деструктор
    ~DialogAddData();

protected:
    void changeEvent(QEvent *e);

private slots:
    ///Метод(слот) для отправки данных в БД по нажатию на кнопку
    void on_pushButton_send_clicked();

    ///Метод(слот) для настройки валидатора ввода параметра "год выпуска строительной техники"
    void on_lineEdit_productYear_textChanged(const QString &arg1);

private:
    ///Указатель на форму диалогового окна добавления данных
    Ui::DialogAddData *ui;

    ///Валидатор ввода для параметра "тип строительной техники"
    QRegExpValidator technicType_validator;
};

#endif // DIALOGADDDATA_H
