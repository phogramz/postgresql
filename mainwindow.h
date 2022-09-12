#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>
#include <QSortFilterProxyModel>
#include <QTranslator>
#include <QSettings>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include "tablemodel.h"
#include "buildmachines.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class TableModel;

/*!
    \brief Класс формы основного окна программы
    \date Июнь 2022 года

    Отображает все получаемые данные. Обрабатывает поступающие сигналы интерфейса.
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    /*!
        \brief Указатель для модели отображения.

        Является оболочкой основной модели представления.
        Необходим для обеспечения сортировки выводимых данных.
    */
    QSortFilterProxyModel* proxyModel;
    /// Объект для обеспечения перевода
    QTranslator languageTranslator;

public:
    ///Конструктор
    MainWindow(QWidget *parent = nullptr);
    ///Деструктор
    ~MainWindow();

    ///Метод для чтения данных из БД и записи в контейнер (QList)
    void Read_db(QString searchLine);
    ///Метод для передачи модели данных на отображение
    void SetData(QString searchLine);

    ///Метод для сохранения настроек интерфейса
    void setSettings();

    ///Метод для подключения базе данных (БД)
    void Connect_db();

    ///Метод возвращает ссылку на базу данных
    QSqlDatabase * return_db_point();

private slots:

    ///Метод(слот) для обработки нажатия кнопки Подключения к БД
    void on_action_connectDB_triggered();

    ///Метод(слот) для обработки нажатия кнопки добавления записи
    void on_action_add_triggered();

    ///Метод(слот) для обработки нажатия кнопки редактирования записи
    void on_action_edit_triggered();

    ///Метод(слот) для обработки нажатия кнопки удаления записи
    void on_action_delete_triggered();

    ///Метод(слот) для тестирования различного функционала
    void on_actionTest_triggered();

    ///Метод(слот) для поиска данных (кнопка)
    void on_pushButton_search_clicked();

    ///Метод(слот) для запуска процесса поиска при вводе данных в строку поиска
    void on_lineEdit_search_textChanged(const QString &arg1);

    ///Метод(слот) для вызова диалогового окна о пользователе
    void on_action_About_triggered();

    ///Метод(слот) для сохранения настроек (кнопка)
    void on_action_settings_save_triggered();

    ///Метод(слот) для сброса настроек (кнопка)
    void on_action_settings_reset_triggered();

    ///Метод(слот) для переключения языка интерфейса на Английский (кнопка)
    void on_action_language_English_triggered();

    ///Метод(слот) для переключения языка интерфейса на Русский (кнопка)
    void on_action_language_Russian_triggered();

    void changeEvent(QEvent *event);

private:
    ///Указатель на форму главного окна
    Ui::MainWindow *ui;
    ///Установка режима доступности("кликабельности") кнопок
    bool isEnabled;

    ///Указатель на модель хранения информации о строительной техники (основная таблица)
    TableModel *modelBTechnique;

    ///Объект базы данных
    QSqlDatabase db;
};
#endif // MAINWINDOW_H
