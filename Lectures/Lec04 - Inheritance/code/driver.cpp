#include <iostream>
#include "driver.h"

Driver::Driver() :
    Employee("unknown"), rate_(0.0), vehicle_(nullptr)
{
}

Driver::Driver(const std::string& name)
    : Employee(name), rate_(0.0), vehicle_(nullptr)
{
}

Driver::Driver(const std::string& name, const Vehicle &vehicle)
    : Employee(name), rate_(0.0), vehicle_(&vehicle)
{
}


void Driver::setVehicle(const Vehicle& vehicle)
{
    vehicle_ = &vehicle;
}

void Driver::setRate(double rate)
{
    this->rate_ = rate;

    if (rate > top_rate)
    {
        top_rate = rate;
    }
}

const Vehicle* Driver::getVehicle() const
{
    return vehicle_;
}

double Driver::getRate() const
{
    return rate_;
}

void Driver::print() const
{
    if (vehicle_)
    {
        std::cout << name_ << " drives "
                  << vehicle_->getModel() << " "
                  << vehicle_->getNo()
                  << std::endl << std::endl;
    }
    else
    {
        std::cout << name_ << " is currently without a car"
                  << std::endl << std::endl;
    }
}

// статический член класса
double Driver::top_rate = 0.0;
