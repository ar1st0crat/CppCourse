#pragma once

#include <string>
#include "employee.h"
#include "vehicle.h"
#include "booking.h"

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
    bool hasTruck() const;

    void handleBooking(Booking& booking);

    // переопределение методов Employee
public:
    double salaryBonus(double salary) const override;
    std::string benefits() const override;

    // реализация интерфейса IPrintable
public:
    void print() const override;

public:
    static double top_rate;

private:
    double rate_;

    const Vehicle* vehicle_;
};
