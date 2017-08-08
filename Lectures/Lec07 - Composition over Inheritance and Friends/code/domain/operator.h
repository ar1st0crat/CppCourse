#pragma once

#include <ctime>
#include "iprintable.h"
#include "employee.h"
#include "booking.h"

class TaxiService;

class Operator : public Employee, public IPrintable
{
public:
    Operator();
    Operator(const std::string& name);
    Operator(const std::string& name, const std::string& phone, tm reg_date);

    void setId(unsigned int id);
    unsigned int getId() const;

    Booking* processBooking(std::tm call_time);


    // переопределение методов Employee
public:
    double salary_bonus(double salary) const override;
    std::string benefit() const;

    // реализация интерфейса IPrintable
public:
    void print() const override;

private:
    unsigned int id_;
};
