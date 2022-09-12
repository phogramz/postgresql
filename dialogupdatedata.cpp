#include "dialogupdatedata.h"
#include "ui_dialogupdatedata.h"

DialogUpdateData::DialogUpdateData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogUpdateData)
  , technicType_validator(QRegExp("^[А-я]\{1,20}\\s[А-я]\{1,20}\\s[А-я]\{1,20}$"))
{
    ui->setupUi(this);
    //w = dynamic_cast<MainWindow*> (parent);
    //ui->lineEdit_productYear_update->setInputMask("0000"); //маска ввода года (4 цифры)

    ui->lineEdit_technicType_update->setValidator(&technicType_validator); //установка валидатора (только русские буквы и 3 слова)
}

DialogUpdateData::~DialogUpdateData()
{
    delete ui;
}

void DialogUpdateData::setId(QString Id)
{
    ui->lineEdit_id_update->insert(Id);
}

void DialogUpdateData::setTechnicType(QString techicType)
{
    ui->lineEdit_technicType_update->insert(techicType);
}

void DialogUpdateData::setBrand(QString brand)
{
    ui->lineEdit_brand_update->insert(brand);
}

void DialogUpdateData::setPower(QString power)
{
    ui->lineEdit_power_update->insert(power);
}

void DialogUpdateData::setWeight(QString weight)
{
    ui->lineEdit_weight_update->insert(weight);
}

void DialogUpdateData::setProductYear(QString productYear)
{
    ui->lineEdit_productYear_update->insert(productYear);
}

void DialogUpdateData::setRentPrice(QString rentPrice)
{
    ui->lineEdit_rentPrice_update->insert(rentPrice);
}


void DialogUpdateData::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void DialogUpdateData::on_pushButton_clicked()
{

    //QSqlDatabase *db = w.return_db_point();
    //Обновление данных в БД
    //QSqlDatabase::database().transaction();
    //qDebug()<<db->isOpen();

    //db->transaction(); //объявление (начало) транзакции

    QSqlQuery query;
    query.prepare("UPDATE tcars SET \"technicType\"=?, brand=?, power=?, weight=?, \"productYear\"=? WHERE id=?;");

    query.bindValue(0, ui->lineEdit_technicType_update->text());
    query.bindValue(1, ui->lineEdit_brand_update->text());
    query.bindValue(2, ui->lineEdit_power_update->text());
    query.bindValue(3, ui->lineEdit_weight_update->text());
    query.bindValue(4, ui->lineEdit_productYear_update->text());

    query.bindValue(5, ui->lineEdit_id_update->text().toInt());
    bool ok1 = query.exec();

    QSqlQuery query2;
    query2.prepare("UPDATE tcars_price SET \"rentPrice\" = ? WHERE id = ?;");
    query2.bindValue(0, ui->lineEdit_rentPrice_update->text());
    query2.bindValue(1, ui->lineEdit_id_update->text().toInt());
    bool ok2 = query2.exec();

    if (!ok1 || !ok2) {
        //db->rollback(); //отмена операции
        QMessageBox::critical(this, tr("Сообщение"),
                              query.lastError().text());
        return;
    }

    //db->commit(); //завершение и отправка транзакции

    if (ok1 && ok2)
    {
    QMessageBox msgBox;
            //устанавливаем название окна
            msgBox.setWindowTitle(tr("Готово"));
            //устанавливаем исходный текст окна
            msgBox.setText(tr("Данные успешно обновлены!"));
            //задаем кнопки
            msgBox.setStandardButtons(QMessageBox::Ok);
            //устанавливаем иконку для окна
            msgBox.setIcon(QMessageBox::Information);
            //задаем кнопку по умолчанию
            msgBox.setDefaultButton(QMessageBox::Ok);
            //запускаем окно обработки исключения
            msgBox.exec();
    }

}

void DialogUpdateData::on_lineEdit_productYear_update_textChanged(const QString &arg1)
{
    QRegularExpression rx("^[1,2]{1}[0,9]{1}[0-9][0-9]$",
                                  QRegularExpression::CaseInsensitiveOption);
        ui->lineEdit_productYear_update->setValidator(new QRegularExpressionValidator(rx, this));
        if(!ui->lineEdit_productYear_update->hasAcceptableInput())
        {
            ui->lineEdit_productYear_update->setStyleSheet("QLineEdit { color: red;}");
            ui->pushButton->setEnabled(false);
        }
        else
        {
            ui->lineEdit_productYear_update->setStyleSheet("QLineEdit { color: green;}");
            ui->pushButton->setEnabled(true);
        }
}

