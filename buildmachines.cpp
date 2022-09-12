#include "buildmachines.h"

BuildMachines::BuildMachines():
    id(0)
  , technicType("")
  , brand("")
  , power("")
  , weight("")
  , productYear("")
  , rentPrice("")
{

}

BuildMachines::BuildMachines(const int lid,
                             const QString ltechicType,
                             const QString lbrand,
                             const QString lpower,
                             const QString lweight,
                             const QString lproductYear,
                             const QString lrentPrice):
    id(lid)
  , technicType(ltechicType)
  , brand(lbrand)
  , power(lpower)
  , weight(lweight)
  , productYear(lproductYear)
  , rentPrice(lrentPrice)
{

}

BuildMachines::~BuildMachines()
{

}

//Добавление данных в объект класса

void BuildMachines::setId(const int lid)
{
    id = lid;
}

void BuildMachines::setTechnicType(const QString ltechicType)
{
    technicType = ltechicType;
}

void BuildMachines::setBrand(const QString lbrand)
{
    brand = lbrand;
}

void BuildMachines::setPower(const QString lpower)
{
    power = lpower;
}

void BuildMachines::setWeight(const QString lweight)
{
    weight = lweight;
}

void BuildMachines::setProductYear(const QString lproductYear)
{
    productYear = lproductYear;
}

void BuildMachines::setRentPrice(const QString lrentPrice)
{
    rentPrice = lrentPrice;
}


//Методы полученния дынных из объекта класса

int BuildMachines::getId() const
{
    return id;
}

QString BuildMachines::getTechicType() const
{
    return technicType;
}

QString BuildMachines::getBrand() const
{
    return brand;
}

QString BuildMachines::getPower() const
{
    return power;
}

QString BuildMachines::getWeight() const
{
    return weight;
}

QString BuildMachines::getProductYear() const
{
    return productYear;
}

QString BuildMachines::getRentPrice() const
{
    return rentPrice;
}

