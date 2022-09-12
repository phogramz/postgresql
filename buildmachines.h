#ifndef BUILDMACHINES_H
#define BUILDMACHINES_H

#include <QList>
/*!
    \brief Класс для хранения характеристик строительной техники
    \date Июнь 2022 года

    Все характеристики записей о строительной технике,
        получаемые из базы данных записываются в переменные этого класса.
*/
class BuildMachines
{
private:

    ///Номер записи
    int id;
    ///Тип строительной техники
    QString technicType;
    ///Производитель строительной техники
    QString brand;
    ///Мощность строительной техники
    QString power;
    ///Масса строительной техники
    QString weight;
    ///Год выпуска строительной техники
    QString productYear;
    ///Цена аренды строительной техники
    QString rentPrice;

public:
    ///Конструктур по умолчанию
    BuildMachines();
    ///Конструктор копирования
    BuildMachines(const int lid,
                  const QString ltechnicType,
                  const QString lbrand,
                  const QString lpower,
                  const QString lweight,
                  const QString lproductYear,
                  const QString lrentPrice);
    ///Деструктор
    ~BuildMachines();

    ///Метод для установки значения переменной id
    void setId(const int lid);
    ///Метод для установки значения переменной technicType
    void setTechnicType(const QString ltechicType);
    ///Метод для установки значения переменной brand
    void setBrand(const QString lbrand);
    ///Метод для установки значения переменной power
    void setPower(const QString lpower);
    ///Метод для установки значения переменной weight
    void setWeight(const QString lweight);
    ///Метод для установки значения переменной productYear
    void setProductYear(const QString lproductYear);
    ///Метод для установки значения переменной rentPrice
    void setRentPrice(const QString lrentPrice);

    ///Метод для получения значения переменной id
    int getId() const;
    ///Метод для получения значения переменной technicType
    QString getTechicType() const;
    ///Метод для получения значения переменной brand
    QString getBrand() const;
    ///Метод для получения значения переменной power
    QString getPower() const;
    ///Метод для получения значения переменной weight
    QString getWeight() const;
    ///Метод для получения значения переменной productYear
    QString getProductYear() const;
    ///Метод для получения значения переменной rentPrice
    QString getRentPrice() const;
};

#endif // BUILDMACHINES_H
