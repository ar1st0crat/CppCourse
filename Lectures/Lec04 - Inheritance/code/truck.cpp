#include <iostream>
#include "truck.h"

Truck::Truck() : Vehicle()
{
}

Truck::Truck(const std::string& make,
             const std::string& model,
             const std::string& no,
             Color color,
             short year)
    : Vehicle(make, model, no, color, year)

{
}

void Truck::setMaxWeight(double max_weight)
{
    max_weight_ = max_weight;
}

void Truck::setColor(Color color)
{
    color_ = color;
}

Color Truck::getColor() const
{
    return color_;
}

void Truck::print() const
{
    std::cout << make_ << " "
              << model_ << " (" << no_ << ") "
              << "max weight: " << max_weight_
              << std::endl;
}
