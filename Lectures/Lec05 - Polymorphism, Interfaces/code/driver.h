#pragma once

#include <string>
#include "employee.h"
#include "vehicle.h"


// По сути здесь не множественное наследование,
// а наследование одной реализации (Employee) и реализация одного интерфейса (IPrintable)

class Driver : public Employee, public IPrintable
{
public:
    Driver();
    explicit Driver(const std::string& name);
    Driver(const std::string& name, const Vehicle& vehicle);

    void setVehicle(const Vehicle& vehicle);
    void setRate(double rate);
    const Vehicle* getVehicle() const;
    double getRate() const;

    // переопределение методов Employee
public:
    double salaryBonus(double salary) const override;
    std::string benefits() const;

    // реализация интерфейса IPrintable
public:
    void print() const override;

public:
    static double top_rate;

private:
    double rate_;

    const Vehicle* vehicle_;
};
