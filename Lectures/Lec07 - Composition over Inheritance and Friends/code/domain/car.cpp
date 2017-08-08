#include <iostream>
#include "car.h"

// ==================== КОНСТРУКТОРЫ / ДЕСТРУКТОР =======================

Car::Car() : Vehicle()
{
}

Car::Car(const std::string& make,
         const std::string& model,
         const std::string& no,
         Color color,
         short year)
    : Vehicle(make, model, no, color, year)

{
}

Car::~Car()
{
}

void Car::setSeatCount(short seat_count)
{
    seat_count_ = seat_count;
}

short Car::getSeatCount() const
{
    return seat_count_;
}
