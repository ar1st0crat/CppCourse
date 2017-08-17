#pragma once

#include <ctime>
#include "employee.h"
#include "booking.h"

class Operator : public Employee
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
    double salaryBonus(double salary) const override;
    std::string benefits() const override;

    // реализация интерфейса IPrintable
public:
    void print() const override;

private:
    unsigned int id_;
};
