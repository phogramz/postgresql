#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "dialogadddata.h"
#include "dialogupdatedata.h"
#include "dialogabout.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    modelBTechnique = new TableModel(this); //создаём и выделяем память объекту модели
    proxyModel = new QSortFilterProxyModel; //создаём и выделяем память объекту прокси модели

    ui->tableView->setSortingEnabled(true); //включаем возможность сортировки

    setSettings();

    isEnabled = true;
    ui->action_add->setDisabled(isEnabled); //отключаем работу кнопок до подключение к БД
    ui->action_connectDB->setDisabled(!isEnabled);
    ui->action_delete->setDisabled(isEnabled);
    ui->action_edit->setDisabled(isEnabled);
    ui->pushButton_search->setDisabled(isEnabled);

#ifdef QT_DEBUG
    if (QSqlDatabase::isDriverAvailable("QPSQL"))
        qDebug() << "SUCCESS: PostgreSQL Database driver found.";
    else
        qDebug() << "FAILURE: No PostgreSQL Database driver available/";
#endif
}

MainWindow::~MainWindow()
{
    delete ui;
    delete modelBTechnique; //удаляем объект основной таблицы
}

void MainWindow::Read_db(QString searchLine) //читает данные из БД и пишет в QList
{
    //Connect_db();
    BuildMachines tempClassObject;

    QString myQuery = "SELECT tcars.id, tcars.\"technicType\", tcars.brand, tcars.power, tcars.weight, tcars.\"productYear\", "
                      "tcars_price.\"rentPrice\" "
                      "FROM tcars, tcars_price WHERE tcars.id = tcars_price.id "
                      "AND tcars.\"technicType\" LIKE '";
    QString myQueryEnd = "%' ORDER BY id ASC;";

    myQuery += searchLine;
    myQuery += myQueryEnd;

    QSqlQuery query;
    bool ok = query.exec(myQuery);
    if (!ok) {
        QMessageBox::critical(this, tr("Сообщение"),
                              query.lastError().text());
        return;
    }

    while (query.next()) {
        tempClassObject.setId(query.value(0).toInt());
        tempClassObject.setTechnicType(query.value(1).toString());
        tempClassObject.setBrand(query.value(2).toString());
        tempClassObject.setPower(query.value(3).toString());
        tempClassObject.setWeight(query.value(4).toString());
        tempClassObject.setProductYear(query.value(5).toString());
        tempClassObject.setRentPrice(query.value(6).toString());

        //tempList->push_back(tempClassObject);
        modelBTechnique->addData(tempClassObject); //добавляем элемент(класс) в контейнер
    }
}

void MainWindow::SetData(QString searchLine)
{
    //ui->tableView->setModel(modelBTechnique); //передаем модель с данными на отображение
    proxyModel->setSourceModel(modelBTechnique); //заполняем прокси-модель данными основной модели
    ui->tableView->setModel(proxyModel); //передаем прокси-модель на отображение
    //ui->tableView->setSortingEnabled(true);


    modelBTechnique->clearTable(); //пользовательский метод очистки контейнера
    Connect_db();
    Read_db(searchLine);

    ui->action_add->setEnabled(isEnabled); //включаем видимость кнопок
    ui->action_delete->setEnabled(isEnabled);
    ui->action_edit->setEnabled(isEnabled);
    ui->pushButton_search->setEnabled(isEnabled);
}

void MainWindow::Connect_db()
{
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("127.0.0.1");
    db.setPort(5432);
    db.setConnectOptions("requiressl=1"); //включение ssl подключения
    if (!db.open()) {
        db.setConnectOptions("requiressl=0"); // подключение без ssl
        // ...
    }
    db.setDatabaseName("pr-btechnique");
    db.setUserName("usermaxim");
    db.setPassword("110622");
    db.open();
    if (!db.isOpen()) {
        QMessageBox::warning(this,
                             tr("Сообщение"),
                             db.lastError().text());
        qDebug() << db.connectOptions();
        return;
    }
}


void MainWindow::on_action_connectDB_triggered()
{
    SetData("");
}


void MainWindow::on_action_add_triggered()
{
    DialogAddData dialogAdd;
    dialogAdd.setMaximumHeight(200);
    dialogAdd.setMaximumWidth(800);
    dialogAdd.setWindowTitle(tr("Добавление записи"));
    dialogAdd.setWindowIcon(QIcon(":/ic0/plus_add.ico"));
    dialogAdd.exec();
}


void MainWindow::on_action_edit_triggered()
{
    DialogUpdateData dialogUpdate;
    dialogUpdate.setMaximumHeight(200);
    dialogUpdate.setMaximumWidth(800);
    dialogUpdate.setWindowTitle(tr("Обновление записи"));
    dialogUpdate.setWindowIcon(QIcon(":/ic0/edit_file.ico"));

//    QModelIndexList lineList = ui->tableView->selectionModel()->selectedRows();
//    if(lineList.isEmpty()) return;

    QModelIndex current  = ui->tableView->currentIndex();
    //qDebug() << ui->tableView->model()->data(ui->tableView->model()->index(current.row(),0),0);

    dialogUpdate.setId(ui->tableView->model()->data(ui->tableView->model()->index(current.row(), 0), 0).toString());
    dialogUpdate.setTechnicType(ui->tableView->model()->data(ui->tableView->model()->index(current.row(), 1), 0).toString());
    dialogUpdate.setBrand(ui->tableView->model()->data(ui->tableView->model()->index(current.row(), 2), 0).toString());
    dialogUpdate.setPower(ui->tableView->model()->data(ui->tableView->model()->index(current.row(), 3), 0).toString());
    dialogUpdate.setWeight(ui->tableView->model()->data(ui->tableView->model()->index(current.row(), 4), 0).toString());
    dialogUpdate.setProductYear(ui->tableView->model()->data(ui->tableView->model()->index(current.row(), 5), 0).toString());
    dialogUpdate.setRentPrice(ui->tableView->model()->data(ui->tableView->model()->index(current.row(), 6), 0).toString());

    //ui->tableView->currentIndex().
        db.transaction(); //объявление (начало) транзакции
    dialogUpdate.exec();
        db.commit();  //завершение и отправка транзакции
}

void MainWindow::on_action_delete_triggered()
{
    int row = ui->tableView->currentIndex().row() + 1;

    QSqlQuery queryDelete;
    queryDelete.prepare("DELETE FROM tcars WHERE id = ?;");
    queryDelete.addBindValue(row);

    bool ok = queryDelete.exec();

    if (!ok) {
        QMessageBox::critical(this, tr("Сообщение"),
                              queryDelete.lastError().text());
        return;
    }
    else
    {
    QMessageBox msgBox;
            //устанавливаем название окна
            msgBox.setWindowTitle(tr("Готово"));
            //устанавливаем исходный текст окна
            msgBox.setText(tr("Данные успешно удалены!"));
            //задаем кнопки
            msgBox.setStandardButtons(QMessageBox::Ok);
            //устанавливаем иконку для окна
            msgBox.setIcon(QMessageBox::Information);
            //задаем кнопку по умолчанию
            msgBox.setDefaultButton(QMessageBox::Ok);
            //запускаем окно обработки исключения
            msgBox.exec();
    }

    //Обновление id у элементов ниже
    int counter = row;
    const int rowCount = ui->tableView->model()->rowCount(); //

    QSqlQuery queryUpdate;
    while(counter <= rowCount) {
        queryUpdate.prepare("UPDATE tcars SET id=? WHERE id =?;");

        queryUpdate.bindValue(0, counter);
        queryUpdate.bindValue(1, counter + 1);
        queryUpdate.exec();
        counter++;
    }
    SetData("");
}

void MainWindow::on_pushButton_search_clicked() //поиск по записям
{
    SetData(ui->lineEdit_search->text());
}


void MainWindow::on_actionTest_triggered()
{
//    Connect_db();
//    QSqlQuery queryUpdate;
//    int counter = 1;
//    while(counter <= 21) {
//        queryUpdate.prepare("UPDATE tcars SET id=? WHERE id =?;");

//        queryUpdate.bindValue(0, counter);
//        queryUpdate.bindValue(1, counter);
//        queryUpdate.exec();
//        counter++;
//    }
}

void MainWindow::on_lineEdit_search_textChanged(const QString &arg1) //динамический поиск
{
    on_pushButton_search_clicked();
}


void MainWindow::on_action_About_triggered() //окно "об авторе"
{
    DialogAbout dialogAbout;
    dialogAbout.setMaximumHeight(250);
    dialogAbout.setMaximumWidth(600);
    dialogAbout.setWindowTitle(tr("Информация об авторе программы"));
    dialogAbout.setWindowIcon(QIcon(":/ic0/about.ico"));
    dialogAbout.exec();
}

void MainWindow::setSettings()
{
    QSettings settings("Мои настройки");
    settings.beginGroup("Настройки окна");

    resize(settings.value("size", QSize(1000, 600)).toSize()); //установка размера окна
    move(settings.value("position", QPoint(600, 150)).toPoint()); //установка положения ЛВ точки окна
    settings.setValue("position", pos()); //установка текущей позиции
    settings.endGroup();
}

void MainWindow::on_action_settings_save_triggered()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Сохранение настроек");
    msgBox.setText("Подтвердить сохранение?");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();

    QSettings settings("Мои настройки");
    settings.beginGroup("Настройки окна");

    settings.setValue("size", size()); //сохранение размера окна
    settings.setValue("position", pos()); //сохранение положения окна
    settings.endGroup();
}


void MainWindow::on_action_settings_reset_triggered()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Сброс настроек");
    msgBox.setText("Подтвердить сброс настроек?");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();

    setSettings();
}


void MainWindow::on_action_language_English_triggered()
{
    qApp->removeTranslator(&languageTranslator);
                languageTranslator.load(":/Kursova_1_en_US");
                qApp->installTranslator(&languageTranslator);
}


void MainWindow::on_action_language_Russian_triggered()
{
    qApp->removeTranslator(&languageTranslator);
                languageTranslator.load(":/Kursova_1_ru_RU");
                qApp->installTranslator(&languageTranslator);
}

void MainWindow::changeEvent(QEvent *event) // проверка смены языка
{
    if (event->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);    // переведём окно заново
    }
}

QSqlDatabase *MainWindow::return_db_point()
{
    return &db;
}

