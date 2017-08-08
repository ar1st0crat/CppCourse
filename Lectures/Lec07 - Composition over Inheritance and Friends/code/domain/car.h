#pragma once

#include <string>
#include "vehicle.h"

class Car : public Vehicle
{
public:
    // ================================== конструкторы/деструктор
    Car();
    Car(const std::string& make,
        const std::string& model,
        const std::string& no,
        Color color,
        short year);
    ~Car();

    void setSeatCount(short seat_count);
    short getSeatCount() const;

private:
    short seat_count_;
};
