#pragma once

#include <string>
#include "employee.h"
#include "vehicle.h"

class Driver : public Employee
{
public:
    Driver();
    explicit Driver(const std::string& name);
    Driver(const std::string& name, const Vehicle& vehicle);

    void setVehicle(const Vehicle& vehicle);
    void setRate(double rate);
    const Vehicle* getVehicle() const;
    double getRate() const;

    void print() const;

public:
    static double top_rate;

private:
    double rate_;

    // У водителя есть машина
    // (это *агрегация*, но пока умничать не будем)
    const Vehicle* vehicle_;
    // данная машина константна в том смысле, что ее данные не меняются,
    // но саму машину водитель поменять может
};
