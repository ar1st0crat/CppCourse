#pragma once

#include "iprintable.h"
#include "employee.h"

// По сути здесь не множественное наследование,
// а наследование одной реализации (Employee) и реализация одного интерфейса (IPrintable)

class Operator : public Employee, public IPrintable
{
public:
    Operator();
    Operator(const std::string& name);
    Operator(const std::string& name, const std::string& phone, tm reg_date);

    void setId(unsigned int id);
    unsigned int getId() const;

    // переопределение методов Employee
public:
    double salaryBonus(double salary) const override;
    std::string benefits() const;

    // переопределение методов Employee
public:
    void print() const override;

private:
    unsigned int id_;
};
