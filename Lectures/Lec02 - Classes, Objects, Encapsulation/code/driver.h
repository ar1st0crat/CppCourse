// Второй способ написать header guards - это #ifndef .. #define .. #endif

#ifndef DRIVER_H
#define DRIVER_H

#include <string>
#include "car.h"

class Driver
{
public:
    Driver();
    explicit Driver(const std::string& name);
    Driver(const std::string& name, const Car& car);
    Driver(const Driver& driver);
    ~Driver();

    void setCar(const Car& car);
    void setName(const std::string& name);
    void setRate(double rate);
    const Car* getCar() const;
    std::string getName() const;
    double getRate() const;

    void print() const;

private:
    std::string name_;
    double rate_;

    // У водителя есть машина
    // (это *агрегация*, но пока умничать не будем)
    const Car* car_;
    // данная машина константна в том смысле, что ее данные не меняются,
    // но саму машину водитель поменять может

public:
    static double top_rate;
};

#endif
