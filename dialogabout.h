#ifndef DIALOGABOUT_H
#define DIALOGABOUT_H

#include <QDialog>

/*!
    \brief Класс диалогового окна, отображающего информацию об авторе программы
    \date Июнь 2022 года
    \warning Данный класс не имеет пользовательских методов
*/
namespace Ui {
class DialogAbout;
}

class DialogAbout : public QDialog
{
    Q_OBJECT

public:
    ///Конструктор
    explicit DialogAbout(QWidget *parent = nullptr);
    ///Деструктор
    ~DialogAbout();

protected:
    void changeEvent(QEvent *e);

private:
    ///Указатель на форму диалогового окна "О программе"
    Ui::DialogAbout *ui;
};

#endif // DIALOGABOUT_H
