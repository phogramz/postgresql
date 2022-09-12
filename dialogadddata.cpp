#include "dialogadddata.h"
#include "ui_dialogadddata.h"

DialogAddData::DialogAddData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddData)

  , technicType_validator(QRegExp("^[А-я]\{1,20}\\s[А-я]\{1,20}\\s[А-я]\{1,20}$"))
{
    ui->setupUi(this);

    //ui->lineEdit_productYear->setInputMask("0000"); //маска ввода года (4 цифры)
    ui->lineEdit_technicType->setValidator(&technicType_validator);  //установка валидатора (только русские буквы и 3 слова)
}

DialogAddData::~DialogAddData()
{
    delete ui;
}

void DialogAddData::changeEvent(QEvent *e)
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

void DialogAddData::on_pushButton_send_clicked()
{
    //Получение max id
    int maxId = 0;

    QSqlQuery queryId;
    bool ok = queryId.exec("SELECT MAX(id) FROM tcars;");
    if (!ok) {
        QMessageBox::critical(this, tr("Сообщение"),
                              queryId.lastError().text());
        return;
    }

    while (queryId.next()) {
        maxId = queryId.value(0).toInt();
    }
    maxId += 1;

    //Вставка данных в БД
    QSqlQuery query;
    query.prepare("INSERT INTO tcars(id, \"technicType\", brand, power, weight, \"productYear\") VALUES (?, ?, ?, ?, ?, ?);");

    query.bindValue(0, maxId);
    query.bindValue(1, ui->lineEdit_technicType->text());
    query.bindValue(2, ui->lineEdit_brand->text());
    query.bindValue(3, ui->lineEdit_power->text());
    query.bindValue(4, ui->lineEdit_weight->text());
    query.bindValue(5, ui->lineEdit_productYear->text());
    bool ok1 = query.exec();

    QSqlQuery query2;
    query2.prepare("INSERT INTO tcars_price(id, \"rentPrice\") VALUES (?, ?);");
    query2.bindValue(0, maxId);
    query2.bindValue(1, ui->lineEdit_rentPrice->text());
    bool ok2 = query2.exec();

    if (!ok1 || !ok2) {
        QMessageBox::critical(this, tr("Сообщение"),
                              query.lastError().text());
        return;
    }
    else
    {
    QMessageBox msgBox;
            //устанавливаем название окна
            msgBox.setWindowTitle("Готово");
            //устанавливаем исходный текст окна
            msgBox.setText("Данные успешно добавлены!");
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


void DialogAddData::on_lineEdit_productYear_textChanged(const QString &arg1)
{
    QRegularExpression rx("^[1,2]{1}[0,9]{1}[0-9][0-9]$",
                                  QRegularExpression::CaseInsensitiveOption);
        ui->lineEdit_productYear->setValidator(new QRegularExpressionValidator(rx, this));
        if(!ui->lineEdit_productYear->hasAcceptableInput())
        {
            ui->lineEdit_productYear->setStyleSheet("QLineEdit { color: red;}");
            ui->pushButton_send->setEnabled(false);
        }
        else
        {
            ui->lineEdit_productYear->setStyleSheet("QLineEdit { color: green;}");
            ui->pushButton_send->setEnabled(true);
        }
}

